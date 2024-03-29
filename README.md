# Projet de l'UE "Qualité et ERP"

## Equipe de développement

- Romain Perrin
- Maxime Seyer
- Tan Dat Truong
- Isabelle Wingert

## Hypothèses simplificatrices

- Nous choisissons de prendre les projets se terminant les plus tôt en premiers.
- Les jours fériés ne sont pas pris en compte
- Les week-end sont pris en compte
- Il n'y a pas d'arrêt maladie (chaque employé travaille exactement 5 jours par semaine)
- Les employés n'ont pas d'humeur (l'efficience reste constante)
- Les employés ne peuvent pas prendre de congés payés
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

Le projet a été développé avec l'outil Qt Creator.
La compilation est gérée par le fichier .pro qu'il faut compiler avec Qt Creator.

## Déroulement d'une simulation

Voici l'interface qui s'affiche lors du lancement de l'ERP:

![Screenshot](img/interface.png)

Il est possible de charger un fichier de données contenant toutes les informations nécessaires à la simulation. Quatre fichiers de données sont fournis avec le projet correspondant aux quatre scénarios définis dans le sujet.

Il est possible de modifier la date de départ de la simulation en cliquant sur le bouton "change date" de l'interface.

![Screenshot](img/date_changer.png)

Il est possible de modifier l'efficience de l'équipe en cliquant sur le bouton "change efficiency" de l'interface.

![Screenshot](img/efficiency_changer.png)

Il est également possible d'ajouter des employés en recrutement. Ces employés seront ajoutés à la date indiquée par l'utilisateur.

![Screenshot](img/add_employee.png)

Il est également possible d'ajouter manuellement des projets. Le prix du projet est pris en compte lorsqu'au moins deux projet ont la même deadline (le plus cher est alors privilégié).

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
* date_fin : date de fin de projet calculée
* date_courante : la date courante de la simulation

<pre>
Créer une pile d'événements <b>p</b> à partir de la liste de projets et de celle des recrutements

<i><b>TANT QUE</b></i> la pile <b>p</b> n'est pas vide <i><b>FAIRE</b></i>

    <i><b>TANT QUE</b></i> la tête de pile <b>p</b> n'est pas un projet <i><b>FAIRE</b></i>
        
        dépiler <b>p</b> et placer l'événement dans la liste <b>l</b>
        
    <i><b>FIN TANT QUE</b></i>
    
    <b>proj</b> = tête de pile <b>p</b>
    calculer la charge de travail par développeur         
    calculer la charge de travail par manager         
    calculer le nombre total de jours de travail nécessaires pour finir le projet courant         
    calculer la date de fin du projet courant dans <b>date_fin</b>
    
    <i><b>SI</b></i> la liste temporaire <b>l</b> est vide <i><b>ALORS</b></i>
         
         <i><b>SI</b></i> la <b>date_fin</b> est inférieure ou égale à la <b>deadline</b> du projet courant <i><b>ALORS</b></i>
         
             écrire dans le log que le projet courant est validé
             dépiler la tête de pile <b>p</b> (retirer le projet validé)
             la <b>date_courante</b> est désormais égale à la <b>date_fin</b> du projet validé (calculée)
             avancer d'un jour
         
         <i><b>SINON</b></i> (<b>date_fin</b> est supérieure à <b>deadline</b>)
         
             calculer le nombre minimal de managers requis pour compléter le projet
             calculer le nombre minimal de développeurs requis pour compléter le projet
             écrire dans le log la non validation du projet
             considérer le projet comme terminé à la deadline (1)
             écrire dans le log ces infos/valeurs
             la <b>date_courante</b> est désormais la <b>deadline</b> du projet courant
             dépiler le projet de la pile <b>p</b>
             avancer d'un jour
         
         <i><b>FIN SI</b></i>
    
    <i><b>SINON</b></i> (la liste temporaire <b>l</b> n'est pas vide)
    
        <i><b>TANT QUE</b></i> la liste <b>l</b> n'est pas vide <i><b>FAIRE</b></i>
        
            retirer le premier élément de la liste <b>l</b> et le placer dans <b>e</b>
        
            <i><b>SI</b></i> la <b>date_fin</b> calculée est inférieure ou égale à la date de l'événement <b>e</b> <i><b>ALORS</b></i>
            
                dépiler la tête de pile <b>p</b> (le projet courant)
                réempiler tous les événements de la liste temporaire <b>l</b> dans la pile <b>p</b>
                
                <i><b>SI</b></i> la <b>date_fin</b> calculée est inférieure ou égale à la <b>deadline</b> du projet courant <i><b>ALORS</b></i>
                
                    écrire dans le log que le projet courant est validé
                    dépiler la tête de pile <b>p</b> (retirer le projet validé)
                    la <b>date_courante</b> est désormais égale à <b>date_fin</b> du projet validé (calculée)
                    avancer d'un jour
                
                <i><b>SINON</b></i> (<b>date</b> est supérieure à <b>deadline</b>)
         
                    calculer le nombre minimal de managers requis pour compléter le projet
                    calculer le nombre minimal de développeurs requis pour compléter le projet
                    écrire dans le log la non validation du projet
                    considérer le projet comme terminé à la deadline (1)
                    écrire dans le log ces infos/valeurs
                    la <b>date_courante</b> est désormais la <b>deadline</b> du projet courant
                    dépiler le projet de la pile <b>p</b>
                    avancer d'un jour
         
                <i><b>FIN SI</b></i>
            
            <i><b>SINON</b></i> (<b>date</b> supérieure à la date de <b>e</b>)
            
                ajouter l'employé relatif à <b>e</b> dans l'équipe
                avancer la <b>date_courante</b> à la date de <b>e</b>
                retirer le nombre de jours de travail écoulés
                calculer la nouvelle <b>date_fin</b> avec le nouvel employé
            
            <i><b>FIN SI</b></i>
        
        <i><b>FIN TANT QUE</b></i>
    
    <i><b>FIN SI</b></i>

<i><b>FIN FAIRE</b></i>
</pre>

(1) On considère le projet comme terminé à la deadline comme si les ressources nécessaires étaient présentes pour faciliter les calculs.
En réalité on calcule on optimum local plutôt que de rechercher l'optimum global. Il s'agit d'une stratégie gloutonne.

Pour de plus amples informations, se reporter au code commenté dans le fichier correspondant.
