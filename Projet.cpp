#include "Projet.h"

// initialisation de l'id de projet à 0
int Projet::id = 0;

/*Constructeur*/

Projet::Projet() : nom("Projet machine à café")
{
	// incrémentation de l'id de projet
	id += 1;
	//TODO ajouter à la liste des projet
}

Projet::Projet(std::string nom) : nom(nom)
{
	// incrémentation de l'id de projet
	id += 1;
	// TODO ajouter à la liste des projets
}

void Projet::debug()
{
	std::cout << "Projet ID : " << this->id 
		<< "\nNom : " << this->nom << std::endl;
}

