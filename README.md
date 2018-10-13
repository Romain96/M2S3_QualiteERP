# Projet de l'UE "Qualité et ERP"

## Equipe de développement

- Romain Perrin
- Maxime Seyer
- Tan Dat Truong
- Isabelle Wingert

## Hypothèses simplificatrices

- non prise en compte des jours fériés
- prise en compte des week-end
- non simulation des maladies (chaque employé travaille exactement 5 jours par semaine)
- non simulation de l'humeur (l'efficience reste constante)
- non prise en compte des congés payés
- il y a toujours au moins un projet actif
- un recrutement de personnel dure exactement 3 mois
- un nouvel employé a une efficience nulle le mois de son embauche (il est considéré en formation)
- un nouvel employé atteint l'efficience globale au bout d'exactement un mois
- non prise en compte des années bissextiles

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

On peut:
- Ajouter des membres d'équipe
- Ajouter des projets
- Charger un fichier qui contient l'ensemble des informations nécessaires à la simulation dans la barre déroulante

Une fois l'ensemble des données entrée, on lance la simulation et les résultats s'affichent dans une nouvelle fenêtre.

Dans le dossier tests, plusieurs simulations ont été effectuées, et un comparatif des résultats obtenus à l'aide de l'ERP part rapport aux résultats attendus (calculés à la main).

* [simulation 1](./test/grille_01.md)
* [simulation 2](./test/grille_02.md)
* [simulation 3](./test/grille_03.md)
* TODO simulation 4
