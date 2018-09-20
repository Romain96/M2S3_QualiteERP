#include "Personnel.h"

// initialisation de l'id à 0
int Personnel::id_gen = 0;

/*
 * Constructeur vide par défaut (test uniquement)
 */
Personnel::Personnel() :
	id(id_gen),
	nom("John"),
	prenom("Doe")
{
	id_gen += 1;
}

/*
 * Constructeur de base (nom et prénom)
 */
Personnel::Personnel(std::string nom, std::string prenom) :
	id(id_gen),
	nom(nom),
	prenom(prenom)
{
	id_gen += 1;
}

/*
 * informations de debug
 */
void Personnel::debug()
{
	std::cout << "objet personnel" << std::endl;
}
