# Tic Tac Toe
#### Tic Tac Toe Game implementation in C language

## INTRODUCTION

Bienvenue dans notre projet de jeu du Morpion développé en C, 
réalisé dans le cadre d'un cours de langage C ! 
Ce projet a pour but de mettre en pratique les compétences que nous  
avons acquis durant ce cours et de démontrer notre compréhension des 
concepts de base de la programmation en C.
Ce jeu permet à deux joueurs de jouer au Morpion sur une interface 
en ligne de commande et une interface graphique avec la librairie SDL. 
Les joueurs placent tour à tour leur marque (X ou O) sur un plateau de 3x3 
cases jusqu'à ce qu'un joueur obtienne trois marques alignées horizontalement, 
verticalement ou en diagonale, ou que le plateau soit rempli et que 
le jeu se termine par une égalité.
Dans ce projet, nous avons utilisé différentes techniques et structures de programmation 
en C pour implémenter la logique du jeu, gérer l'entrée et la sortie et créer une interface 
conviviale pour l'utilisateur.
De plus, nous avons intégré des vérifications d'erreurs pour nous assurer que les joueurs 
saisissent des entrées valides.

Le projet a été réalisé en 3 étapes, chacune d'elles implémentant une brique supplémentaire.
Ainsi, l'étape 1 a permis de valider le fonctionnement du jeu, l'étape 2 a rendu possible 
l'interaction des joueurs avec le plateau en ligne de commande et la dernière étape met en place une
interface graphique dans laquelle les deux joueurs peuvent jouer avec la souris, avec des sons et 
des affichages de textes.
## INSTALLATION
Afin de faire fonctionner le jeu de la manière la plus facile nous avons 
créer un Makefile qui va se charger de placer les fichiers exécutables dans un dossier
appelé "bin" à la racine du projet. Un simple "make" à la racine du projet devrait suffire à condition 
d'avoir installer les différents packages présents dans le fichier "requirements.txt".
Les étapes 1 et 2 ne devraient pas poser de problèmes à l'éxecution, cependant il est nécessaire d'effectuer un
changement dans le fichier "etape3/board_view_sdl.c" à la ligne 129 où il faut remplacer le chemin absolu
existant "/home/user/Projects/2023_Morpion_GERMOND_PEREZ_code/etape3/Purple_Smile.ttf" par celui ou se
trouve votre dossier sur votre machine. La fonction ne prend que des chemins absolus et non relatifs.
La commande make binclean va venir effacer le dossier contenant les fichiers exécutables.
La commande make clean va venir effacer les fichiers objets. 
Les binaires déjà présents dans le dossier bin sont au format ELF 64-bit LSB executable, x86-64 et ont été
compilés sous Fedora.
## UTILISATION
Si vous avez bien respecté les consignes d'installations, il vous suffit de vous rendre
dans le dossier bin et d'executer les fichiers binaires. Le fichier "etape_1" va venir faire
une démo du fonctionnement du jeu sans interaction avec les joueurs. L'exécutable "etape_2" va
demander aux joueurs de placer leur pièce sous le format "x,y" uniquement avec x et y compris entre
0 et 2. Enfin le binaire "etape_3" va ouvrir un plateau de jeu dans lequel les joueurs pourront cliquer
dans la case où ils souhaitent placer leur pièce. Une vidéo de démo est présente à la racine du projet
pour montrer les différentes fonctionnalités des étapes.
## AUTEUR

PEREZ Etienne <etienne.perez@reseau.eseo.fr>
