#ifndef __CHEFPROJET__
#define __CHEFPROJET__

#include "Personnel.h"

/*
 * Classe ChefProjet : implémentation concrète de la classe abstraite Personnel
 */

class ChefProjet : public Personnel
{
	public:
	
		// Constructeurs
		ChefProjet();
		ChefProjet(std:string nom, std:string prenom);
	
	
};

#endif 
