#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../includes/minishell.h"

/* --- Supposons que vos structures sont définies dans minishell.h --- */
/*
typedef struct s_token
{
    int             id;
    char            *data;
    int             index_pipe;
    struct s_token  *next;
    struct s_token  *prev;
} t_token;

typedef struct s_cmd
{
    char            **cmd;
    char            *path_cmd;
    bool            builtin;
    struct s_cmd    *next;
    struct s_cmd    *prev;
} t_cmd;

typedef struct s_base
{
    int             exit_code;
    int             count_forks;
    int             count_pipe;
    int             **pipes;
    char            **path_list;
    t_cmd           *cmds;
    t_token         *token;
} t_base;
*/

// Fonction de création d'un token alloué dynamiquement
t_token *new_token(char *data, int id, int index_pipe) {
    t_token *token = malloc(sizeof(t_token));
    if (!token) {
        perror("malloc token");
        exit(EXIT_FAILURE);
    }
    token->data = strdup(data);
    token->id = id;
    token->index_pipe = index_pipe;
    token->next = NULL;
    token->prev = NULL;
    return token;
}

// Ajoute un token en fin de liste
void append_token(t_token **head, t_token *new_tok) {
    if (!*head) {
        *head = new_tok;
    } else {
        t_token *curr = *head;
        while (curr->next)
            curr = curr->next;
        curr->next = new_tok;
        new_tok->prev = curr;
    }
}

// Parse argv en construisant une liste de tokens
t_token *parse_tokens(int argc, char **argv) {
    t_token *token_list = NULL;
    int curr_pipe_index = 0;
    // On considère que argv[1]..argv[argc-1] forment la commande.
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "|") == 0) {
            // Crée un token pipe (id 7)
            t_token *token = new_token(argv[i], 7, curr_pipe_index);
            append_token(&token_list, token);
            // Le prochain token sera le début d'une nouvelle commande
            curr_pipe_index++;
        } else {
            int id;
            // Si c'est le premier argument ou l'argument précédent était un pipe, c'est une commande
            if (i == 1 || strcmp(argv[i-1], "|") == 0)
                id = 9;
            else
                id = 10;
            t_token *token = new_token(argv[i], id, curr_pipe_index);
            append_token(&token_list, token);
        }
    }
    return token_list;
}

// À partir de la liste de tokens, on construit la liste de commandes.
// Chaque commande débute par un token de type commande (id 9) et se termine
// avant le prochain token de type pipe (id 7) ou à la fin de la liste.
t_cmd *parse_commands(t_token *token_list) {
    t_cmd *cmd_list = NULL;
    t_cmd *last_cmd = NULL;
    t_token *curr = token_list;
    while (curr) {
        if (curr->id == 9) {
            // Création d'un nouveau noeud commande
            t_cmd *cmd = malloc(sizeof(t_cmd));
            if (!cmd) {
                perror("malloc cmd");
                exit(EXIT_FAILURE);
            }
            cmd->builtin = false;
            cmd->path_cmd = NULL;
            cmd->prev = NULL;
            cmd->next = NULL;
            // Compter le nombre d'arguments de la commande
            int count = 0;
            t_token *tmp = curr;
            while (tmp && tmp->id != 7) {
                if (tmp->id == 9 || tmp->id == 10)
                    count++;
                tmp = tmp->next;
            }
            // Allouer le tableau d'arguments
            cmd->cmd = malloc(sizeof(char *) * (count + 1));
            if (!cmd->cmd) {
                perror("malloc cmd->cmd");
                exit(EXIT_FAILURE);
            }
            int j = 0;
            // Copier les données depuis les tokens jusqu'au prochain pipe ou fin
            while (curr && curr->id != 7) {
                if (curr->id == 9 || curr->id == 10) {
                    cmd->cmd[j++] = strdup(curr->data);
                }
                curr = curr->next;
            }
            cmd->cmd[j] = NULL;
            // Ajouter la commande à la liste
            if (!cmd_list) {
                cmd_list = cmd;
                last_cmd = cmd;
            } else {
                last_cmd->next = cmd;
                cmd->prev = last_cmd;
                last_cmd = cmd;
            }
        } else {
            curr = curr->next;
        }
    }
    return cmd_list;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s command [args] | command [args] | ...\n", argv[0]);
        return 1;
    }

    // Parse des arguments en tokens
    t_token *token_list = parse_tokens(argc, argv);

    // Parse des tokens en une liste chaînée de commandes
    t_cmd *cmd_list = parse_commands(token_list);

    // Affichage pour vérification (debug)
/*     printf("Tokens:\n");
    t_token *tok = token_list;
    while (tok) {
        printf("Token: %s, id: %d, index_pipe: %d\n", tok->data, tok->id, tok->index_pipe);
        tok = tok->next;
    }
    printf("\nCommands:\n");
    t_cmd *cmd = cmd_list;
    while (cmd) {
        printf("Commande: ");
        for (int i = 0; cmd->cmd[i] != NULL; i++) {
            printf("%s ", cmd->cmd[i]);
        }
        printf("\n");
        cmd = cmd->next;
    } */

    /* Initialisation de la structure base sur la pile.
       Notez que la structure base elle-même n'est pas allouée dynamiquement.
       Les champs pipes et path_list seront initialisés par les fonctions 
       create_pipe() et extract_paths() dans votre fonction sauron.
       cmds pointe vers la liste des commandes, et token pointe vers la tête de la liste des tokens.
    */
    t_base base;
    base.exit_code = 0;
    // Calcul du nombre de pipes en comptant les tokens de type pipe (id 7)
    int pipe_count = 0;
    t_token *tmp = token_list;
    while (tmp) {
        if (tmp->id == 7)
        pipe_count++;
        tmp = tmp->next;
    }
    base.count_pipe = pipe_count;
    base.pipes = NULL;     // Sera alloué dans sauron() par create_pipe()
    base.path_list = NULL; // Sera extrait dans sauron() par extract_paths()
    base.cmds = cmd_list;
    base.token = token_list;
    base.count_forks = 0; // À déterminer selon le nombre de forks lancés par sauron

    /* Appel de la fonction sauron pour exécuter la pipeline.
       Cette fonction devra gérer la création des forks, la configuration des pipes,
       et l'exécution des commandes en fonction de la liste de commandes et de tokens.
    */
    sauron(&base);
/*     print base.cmds->cmd;
    base.cmds->next */


    /* Libération des ressources allouées pour les tokens */
    t_token *next_tok;
    while (token_list) {
        next_tok = token_list->next;
        free(token_list->data);
        free(token_list);
        token_list = next_tok;
    }
    /* Libération de la liste des commandes */
    t_cmd *next_cmd;
    while (cmd_list) {
        int i = 0;
        while (cmd_list->cmd[i]) {
            free(cmd_list->cmd[i]);
            i++;
        }
        free(cmd_list->cmd);
        next_cmd = cmd_list->next;
        free(cmd_list);
        cmd_list = next_cmd;
    }
    return 0;
}
