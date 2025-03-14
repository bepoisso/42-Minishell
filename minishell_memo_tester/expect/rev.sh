#!/usr/bin/expect

set timeout 0
# Lance le programme `cat`
spawn rev
after 100
# Attend que `cat` soit prêt
expect "seblin@Laptop ~ $"
after 100
# Envoie la chaîne "0x004" à `cat`
send "crapeau"
after 100
# Simule l'envoi de Control-D pour indiquer la fin de l'entrée
send "\r\x04"
after 100
# Fin du script
expect eof

