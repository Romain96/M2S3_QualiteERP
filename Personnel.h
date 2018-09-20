#ifndef __PERSONNEL_H__
#define __PERSONNEL_H__

#include <iostream>

/*
 * Classe Personnel : classe abstraite représentant les personnel de développement
 * ainsi que le personnel de gestion de projet
 */

class Personnel
{
public:
	static int id_gen;
	int id;
	std::string nom;
	std::string prenom;

public:
	// ctor
	Personnel();
	Personnel(std::string nom, std::string prenom);

	// méthodes
	bool isDev();
	bool isChefProjet();

	virtual void debug();
};

#endif
