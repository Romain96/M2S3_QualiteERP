# Projet de l'UE "Qualité et ERP"

## Equipe de développement

- Romain Perrin
- Maxime Seyer
- Tan Dat Truong
- Isabelle Wingert

## Hypothèses simplificatrices

- Nous choisissons de prendre les projets se terminant les plus tôt en premiers.
- Non prise en compte des jours fériés
- Prise en compte des week-end
- Non simulation des maladies (chaque employé travaille exactement 5 jours par semaine)
- Non simulation de l'humeur (l'efficience reste constante)
- Non prise en compte des congés payés
- Il y a toujours au moins un projet actif
- L'outil a été conçu en ayant à l'esprit la feuille de style des ERP des années 80, d'ou son design retro.


## Conventions de nommage

- Langue: **Anglais**
- Nom des fichers: **snake\_case**
- Fichiers source: dossier **src**
- Fichiers header: dossier **include**
- Documentation: dossier **doc**
- Fichiers librairies: dossier **lib**
- Noms de variable: **snake\_case**

## Compilation et lancement de l'ERP

Il faut ouvrir le .pro avec qtcreator, le compiler et le lancer.

## Déroulement d'une simulation

Voici l'interface qui s'affiche lors du lancement de l'ERP:

![Screenshot](img/launch.png)

On peut:

- Charger un fichier qui contient au préalable l'ensemble des informations nécessaires à la simulation dans la barre déroulante

Puis, au besoin:

- Ajouter des membres d'équipe

![Screenshot](img/add_employee.png)

- Ajouter des projets

![Screenshot](img/add_project.png)

Une fois l'ensemble des données entrées, on lance la simulation et les résultats s'affichent dans une nouvelle fenêtre.

Ces résultats contiennent seulement à la question principale: est-ce que les projets sont faisables dans les délais impartis avec les ressources à disposition, et dans le cas contraire, les resssources supplémentaires nécessaires. Pour le détail des évènements, on pourra se reporter au log généré dans le répertoire d'éxecution.

Dans le dossier **test**, plusieurs simulations ont été effectuées, et un comparatif des résultats obtenus à l'aide de l'ERP par rapport aux résultats attendus (calculés à la main). On y trouve également un fichier log obtenu en sortie du programme pour chaque simulation.

* [simulation 1](./test/grille_01.md)
  * [log simulation 1](./test/results_01)
* [simulation 2](./test/grille_02.md)
  * [log simulation 2](./test/results_02)
* [simulation 3](./test/grille_03.md)
  * [log simulation 3](./test/results_03)
* [simulation 4](./test/grille_04.md)
  * [log simulation 4](./test/results_04)

## Résumé de l'algorithme:

L'algorithme principal se trouve dans le fichier mainwindow.cpp.

La gestion s'effectue à l'aide d'une pile d'événements (les événements sont soit des projets soit des employés).

Pour le calcul du nombre de jours de travail:

nombre de jours par dev = nombre de jour de dev du projet / nombre de dev

nombre de jours par manager = nombre de jours de management / nombre de jours de management

ALGO :

variables utilisées :
* p : liste d'événements triés dans l'ordre croissant de leurs dates
* l : liste temporaire d'événements (recrutement uniquement)
* proj : projet courant
* e : événement de type recrutement courant
* date : date de fin de projet calculée
* date_courante : la date courante de la simulation

Créer une pile d'événements **p** à partir de la liste de projets et de celle des recrutements

TANT QUE la pile p n'est pas vide FAIRE

    TANT QUE la tête de pile **p** n'est pas un projet FAIRE
        
        dépiler **p** et placer l'événement dans la liste **l**
        
    FIN TANT QUE
    
    **proj** = tête de pile **p**
    calculer la charge de travail par développeur         
    calculer la charge de travail par manager         
    calculer le nombre total de jours de travail nécessaires pour fininr le projet courant         
    calculer la date de fin du projet courant dans **date**
    
    SI la liste temporaire **l** est vide
         
         SI la date de fin de projet **date** est inférieure ou égale à la **deadline* du projet courant ALORS
         
             écrire dans le log que le projet courant est validé
             dépiler la tête de pile **p** (retirer le projet validé)
             la **date_courante** est désormais égale à la date de fin du projet validé calculée **date** 
             avancer d'un jour
         
         SINON (**date** est supérieure à **deadline**)
         
             calculer le nombre minimal de managers requis pour compléter le projet
             calculer le nombre minimal de développeurs requis pour compléter le projet
             écrire dans le log la non validation du projet
             considérer le projet comme terminé à la deadline (comme si les ressources nécessaires étaient présentes) 
             écrire dans le log ces infos/valeurs
             la **date_courante** est désormais la **deadline** du projet courant
             dépiler le projet de la pile **p**
             avancer d'un jour
         
         FIN SI
    
    SINON (la liste temporaire **l** n'est pas vide)
    
        TANT QUE la liste **l** n'est pas vide FAIRE
        
            retirer le premier élément de la liste **l** et le placer dans **e**
        
            SI la date de fin calculée **date** est inférieure ou égale à la date de l'événement **e**
            
                dépiler la tête de pile **p** (le projet courant)
                réempiler tous les événements de la liste temporaire **l** dans la pile **p**
                
                SI la date de fin calculée **date** est inférieure ou égale à la **deadline** du projet courant
                
                    écrire dans le log que le projet courant est validé
                    dépiler la tête de pile **p** (retirer le projet validé)
                    la **date_courante** est désormais égale à la date de fin du projet validé calculée **date** 
                    avancer d'un jour
                
                SINON (**date** est supérieure à **deadline**)
         
                    calculer le nombre minimal de managers requis pour compléter le projet
                    calculer le nombre minimal de développeurs requis pour compléter le projet
                    écrire dans le log la non validation du projet
                    considérer le projet comme terminé à la deadline (comme si les ressources nécessaires étaient présentes) 
                    écrire dans le log ces infos/valeurs
                    la **date_courante** est désormais la **deadline** du projet courant
                    dépiler le projet de la pile **p**
                    avancer d'un jour
         
                FIN SI
            
            SINON (**date** supérieure à la date de **e**)
            
                ajouter l'employé relatif à **e** dans l'équipe
                avancer la **date_courante** à la date de **e**
                retirer le nombre de jours de travail écoulés
                calculer la nouvelle date de fin avec le nouvel employé **date**
            
            FIN SI
        
        FIN TANT QUE
    
    FIN SI

FIN FAIRE

Pour de plus amples informations, se reporter au code commenté dans le fichier correspondant.

**Toute faille est totalement volontaire et entièrement maîtrisée et testée**
