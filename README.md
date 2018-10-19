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

Une fois l'ensemble des données entrées, on lance la simulation et les résultats s'affichent dans une nouvelle fenêtre.

Dans le dossier **test**, plusieurs simulations ont été effectuées, et un comparatif des résultats obtenus à l'aide de l'ERP par rapport aux résultats attendus (calculés à la main). On y trouve également un fichier log obtenu en sortie du programme pour chaque simulation.

* [simulation 1](./test/grille_01.md)
  * [log simulation 1](./test/results_01)
* [simulation 2](./test/grille_02.md)
  * [log simulation 2](./test/results_02)
* [simulation 3](./test/grille_03.md)
  * [log simulation 3](./test/results_03)
* [simulation 4](./test/grille_04.md)
  * [log simulation 4](./test/results_04)
