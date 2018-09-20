#include "projet.h"

/*Constructeur*/

Projet::Projet() : nom(???)
{
	id = 0;
	id++;
}

Projet::Projet(std::string nom) : nom(nom)
{
	
}

void Projet::debug()
{
	std::cout << "Projet : " << this->id << this->nom << std::endl;
}

