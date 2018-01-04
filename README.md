# Todo
* Corriger les constantes de position 
* [OK] Passer le capteur de couleur du mode RGB au mode couleur simple
* [OK] Modifier node pour tenir compte de la nouvelle architecture du robot (pont levis) et
ajouter une fonction pour libérer un objet.
* Finir et tester map
* [OK] Gérer touch dans un thread
* Rendre la rotation précise (en faisant tourner les moteurs d'une valeur précise)
* Terminer behaviour et y inclure deux modes : un pour la petite et un pour la grande arène. On fera deux exécutables distinct pour simplifier.

# Requirements :
* lev3dev-c
* pthread
* lncurses

# Connexion au robot
En ssh à ev3.tibol.fr

* Utilisateur : ton prénom
* Mot de passe : [motDePasseWifi]

Exemple :
```
ssh hugo@ev3.tibol.fr
```
* On est tous sudo.
* Le soft appartient à l'utilisateur 'robot' mais on a les droits dessus.
* Le soft est dans /home/robot/os-robot/
* On a tous un lien symbolique ~/robot/ qui pointe dessus
* Les Todos sont à l'adresse https://trello.com/b/Wm6gXrfV/robot.

# Compilation
* Pour compiler, faire simplement 'make' à la racine du projet.
* L'executable est bin/main

