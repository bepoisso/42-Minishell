#!/usr/bin/expect

set timeout 1

system "<<end <<end"
#spawn <<end <<end
after 1000
# Attendre une sortie quelconque
expect {
    timeout { send_user "Le délai d'attente est dépassé\n" }
    -re .+ { set reponse $expect_out(buffer) }
}

# Afficher la sortie capturée
send_user "Réponse capturée :\n$reponse\n"

send "my here doque\r"
after 100

send "\x04"
after 100

send "my here cat\r"
after 100
send "\x04"
after 100

#expect eof

system "<<end <<end"
after 100
send "voila\r"
after 100
send "end\r"
after 100
send "veulu\r"
after 100
send "end\r"
# Fin du script
expect eof

