#include "Personnel.h"
#include "Developpeur.h"

/*
 * Constructeur vide par défaut (test uniquement)
 */
Developpeur::Developpeur() :
	Personnel()
{
	// rien
}

/*
 * Constructeur de base
 */
Developpeur::Developpeur(std::string nom, std::string prenom) :
	Personnel(nom, prenom)
{
	// rien
}

/*
 * informations de debug
 */
void Developpeur::debug()
{
	std::cout << "Developpeur :\n" <<
		"ID : " << this->id <<
		"Nom : " << this->nom <<
		"Prenom : " << this->prenom << std::endl;
}
