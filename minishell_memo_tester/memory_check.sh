#!/bin/bash

# Obtenir le chemin absolu du répertoire courant
CURRENT_DIR=$(pwd)

# Obtenir le chemin absolu de l'exécutable Minishell
MINISHELL_EXECUTABLE=$(dirname "$CURRENT_DIR")/minishell

# Vérifier si l'exécutable Minishell est présent et exécutable
if [ ! -f "$MINISHELL_EXECUTABLE" ] || [ ! -x "$MINISHELL_EXECUTABLE" ]; then
    echo "File not found or not executable : $MINISHELL_EXECUTABLE"
    echo "No minishell executable. Compile the project?"
    exit 1
fi

# Initialiser les compteurs
total_tests=0
successful_tests=0

# Fonction pour exécuter une commande avec Valgrind
run_with_valgrind() {
    command="$1"
    # Exécute la commande avec Valgrind dans un sous-shell pour isoler la redirection de la sortie
    valgrind_output=$( (valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all --suppressions=valgrind.supp --log-file=test_valgrind.log"$MINISHELL_EXECUTABLE" <<< "$command") 2>&1 >/dev/null )

    # Vérifier s'il y a des fuites de mémoire dans la sortie de Valgrind
    if echo "$valgrind_output" | grep -q "0x"; then
		echo "---------------------------------------"
		echo "*******************************************************"
        echo "Memory leaks detected for the command: $command"
        echo "*******************************************************"
		echo "Valgrind output:"

        # Vérifier si la valeur après "definitely lost:" est autre que 0
        if echo "$valgrind_output" | grep -q "definitely lost: [1-9]"; then
            # Afficher la sortie en rouge
            echo -e "\033[91m$valgrind_output\033[0m"
        else
            # Afficher la sortie normalement
            echo "$valgrind_output"
        fi

        echo "---------------------------------------"
        echo "Command: $command" >> "$LEAKS_OUTPUT_FILE"
        echo "Valgrind output:" >> "$LEAKS_OUTPUT_FILE"
        echo "$valgrind_output" >> "$LEAKS_OUTPUT_FILE"
        echo "" >> "$LEAKS_OUTPUT_FILE"
	else
		# Incrémenter le compteur de tests réussis si aucune fuite de mémoire n'a été détectée
		successful_tests=$((successful_tests + 1))
    fi
	    total_tests=$((total_tests + 1))

}

# Lire les commandes à partir du fichier spécifié, une ligne à la fois
while IFS= read -r cmd; do
    run_with_valgrind "$cmd"
done < "$1"

echo "Memory leak analysis finished."
echo "TESTS : $successful_tests / $total_tests"

# merci chatGPT
