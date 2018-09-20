#ifndef __PROJET_H__
#define __PROJET_H__

#include <iostream>

/*
 * Classe projet: contient les informations concernant les projets en cours de développement
 */

class Projet
{
	protected:
		static int id;
		std::string nom;
		//TODO nombre jours de dev
		//TODO nombre jours de gestion de projet
		//TODO date de fin de projet
	
	public:
		//Constructeurs
		Projet();
		Projet(std::string nom);
		
		void debug();
	
};

#endif //PROJET_H
