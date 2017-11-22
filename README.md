# Requirements :
* lev3dev-c
* pthread
* lncurses
# Connexion au robot
En ssh à ev3.tibol.fr\
Utilisateur : ton prénom\
Mot de passe : [motDePasseWifi]

Exemple :
```
ssh hugo@ev3.tibol.fr
```
On est tous sudo.\
Le soft appartient à l'utilisateur 'robot' mais on a les droits dessus.\
Le soft est dans /home/robot/os-robot/\
On a tous un lien symbolique ~/robot/ qui pointe dessus\
Les Todos sont à l'adresse https://trello.com/b/Wm6gXrfV/robot.

# Compilation
Pour compiler, faire simplement 'make' à la racine du projet.\
L'executable est bin/main

