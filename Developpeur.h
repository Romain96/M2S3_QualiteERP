#ifndef __DEVELOPPEUR_H__
#define __DEVELOPPEUR_H__

#include <iostream>

/*
 * Classe Developpeur : implémentation concrète de la classe abstraite Personnel
 * Représente le personnel de développement
 */

class Developpeur : public Personnel
{
public:
	Developpeur();
	Developpeur(std::string nom, std::string prenom);

public:
	void debug();
};

#endif
