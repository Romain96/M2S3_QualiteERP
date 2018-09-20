#ifndef __ENTREPRISE_H__
#define __ENTREPRISE_H__

#include <iostream>

/*
 * Classe Entreprise : contient les données relatives à l'entreprise
 * contient la liste du personnel ainsi que celle des projets
 */

class Entreprise
{
public:
	std::string nom;
	// TODO liste du personnel [classe Personnel]
	// TODO liste des projets [classe Projet]
public:
	Entreprise();
	Entreprise(std::string nom);

	// infos de debug
	void debug();
};

#endif
