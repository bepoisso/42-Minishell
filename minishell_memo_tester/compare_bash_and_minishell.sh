#!/bin/bash

# Définir le chemin de votre exécutable Minishell
MINISHELL_EXECUTABLE="./minishell"

# Définir les chemins des fichiers de sortie
BASH_OUTPUT_FILE="mytest/outfile/bash_output.txt"
MINISHELL_OUTPUT_FILE="mytest/outfile/minishell_output.txt"

# Vider les fichiers de sortie avant chaque exécution
> "$BASH_OUTPUT_FILE"
> "$MINISHELL_OUTPUT_FILE"

# Initialiser les compteurs
total_tests=0
successful_tests=0

# Fonction pour comparer les sorties et compter les tests
compare_outputs() {
    command="$1"
    
	command_output=$(eval "$command" 2>&1 | sed 's|./mytest/compare_bash_and_minishell.sh: line 22: ||g')
    minishell_output=$($MINISHELL_EXECUTABLE <<< "$command" 2>&1 | tail -n +2 | sed '$d')

    # Filtrer les sorties pour ignorer les différences non significatives
    # filtered_command_output=$(echo "$command_output" | sed 's/ //g')
    # filtered_minishell_output=$(echo "$minishell_output" | sed 's/ //g')

    if [ "$command_output" != "$minishell_output" ]; then
        echo "Différence détectée pour la commande: $command"
        echo "Sortie Minishell: $minishell_output"
        echo "Sortie Bash: $command_output"
        echo "---------------------------------------"
    else
        successful_tests=$((successful_tests + 1))
    fi

    total_tests=$((total_tests + 1))

    # Ajouter les sorties dans les fichiers correspondants
    echo "Commande: $command" >> "$BASH_OUTPUT_FILE"
    echo "$command_output" >> "$BASH_OUTPUT_FILE"
    echo "" >> "$BASH_OUTPUT_FILE"

    echo "Commande: $command" >> "$MINISHELL_OUTPUT_FILE"
    echo "$minishell_output" >> "$MINISHELL_OUTPUT_FILE"
    echo "" >> "$MINISHELL_OUTPUT_FILE"
}

# Lire les commandes à partir du fichier spécifié, une ligne à la fois
while IFS= read -r cmd; do
    compare_outputs "$cmd"
done < "$1"

# Afficher les résultats
echo "TESTS $successful_tests / $total_tests"
echo "Comparaison terminée."
