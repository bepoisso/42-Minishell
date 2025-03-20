#!/bin/bash

#! expect packet added in order to got this script working
#! (=> sudo apt-get install expect)

# Définition le chemin vers minishell
MINISHELL=./minishell

# Définition des fichiers
OUTPUT_FILE=output.txt
CORRECT_OUTPUT_FILE=correct_output.txt
DIFF_FILE=diff_output.txt

# Vider le fichier de sortie
echo -n > $OUTPUT_FILE

# execution de minishell + entrée commande -> copie de l'output dans output.txt 
run_minishell() {
    echo "Commande: $1" >> $OUTPUT_FILE
    {
        echo "$1"
        if [ -n "$2" ]; then
            echo "$2"
        fi
		if [ -n "$3" ]; then
            echo "$3"
        fi
    } | $MINISHELL >> $OUTPUT_FILE 2>&1
    echo "-----------------------" >> $OUTPUT_FILE
    echo "" >> $OUTPUT_FILE  # Ajoute une ligne vide entre chaque série de tests
}

# Commandes à tester
# BUILTINS: cd & pwd
# run_minishell "cd" "pwd"
# run_minishell "cd /"  "pwd"
# run_minishell "cd chemin/inexistant"  "pwd"
# run_minishell "cd src/builtins"  "pwd"
# run_minishell "cd .."  "pwd"
# run_minishell "pwd"
# run_minishell "pwd blabla"
# run_minishell "'pwd' blabla"

# # BUILTINS: echo
# run_minishell 'echo "Hello, World!"'
# run_minishell 'echo '\''Single quotes'\'''
# run_minishell "echo 'Single quotes'"
# run_minishell 'echo -n "No newline"'
# run_minishell "echo -n 'No newline'"
# run_minishell 'echo -n "With space at the end"   '
# run_minishell 'echo -n "With space at the end"   "Another argument"'
# run_minishell 'echo -n "With space at the end"   '\''Single quotes'\'''

# # BUILTINS: unset
# run_minishell "env" "unset SHELL" "env"
# run_minishell "env" "unset _" "env"
# run_minishell "env" "unset OLDPWD" "env"

# # BUILTINS: export
# run_minishell "export"

run_minishell "true || echo aaa && echo bbb"
# run_minishell true || (echo aaa && echo bbb)
# run_minishell true || (echo aaa && echo bbb
# run_minishell true || echo aaa && echo bbb)
# run_minishell true || (echo a && echo b) && echo c
# run_minishell true || (echo a) && echo b
# run_minishell true || ((echo a && echo b) && echo c)
# run_minishell true || "("echo b && echo c)
# run_minishell echo a && ls >
# run_minishell echo a && awoiejlk
# run_minishell ls > file && echo "salut"
# run_minishell false && (echo aaa)
# run_minishell (ls && ls)
# ls & & ls
# ls && && ls
# ls | | ls
# ls (&&) ls
# echo "&&" ls
# exit && ls
# ls && exit
# ls &&
# && ls
# &&
# ||
# (&&)
# echo a || wc << fin

# Comparaison avec fichier de référence

if diff -u $OUTPUT_FILE $CORRECT_OUTPUT_FILE; then
    echo "Les tests ont réussi! Fichier de sortie identique au fichier de référence."	
fi
