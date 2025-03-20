#!/usr/bin/expect

# Configuration initiale
set timeout 10
system "<<end"

# Envoi de la commande
#send "votre_commande\r"

# Attendre une sortie quelconque
expect {
    timeout { send_user "Le délai d'attente est dépassé\n" }
    -re .+ { set reponse $expect_out(buffer) }
}

# Afficher la sortie capturée
send_user "Réponse capturée :\n$reponse\n"
