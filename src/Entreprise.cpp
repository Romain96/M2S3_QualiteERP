#include <iostream>

#include "Entreprise.h"

/*
 * Constructeur par défaut
 */
Entreprise::Entreprise() :
	nom("Inside Out")
	// TODO liste du personnel [classe Personnel]
	// TODO liste des projets [classe Projet]
{
	// rien
}

/*
 * Constructeur paramétré
 */

Entreprise::Entreprise(std::string nom) :
	nom(nom)
{
	// rien
}

/*
 * Informations de debug
 */
void Entreprise::debug()
{
	std::cout << "Entreprise : " << this->nom << std::endl;
}
