#include "ChefProjet.h"

/*
 * Constructeur vide par défaut
 */ 

ChefProjet::ChefProjet() :
	Personnel()
{
	
}

/*
 * Constructeur de base
 */
  
ChefProjet::ChefProjet(std::string nom, std::string prenom) : 
	Personnel(nom, prenom)
{
	
}

/*
 * Informations de debug
 */
 
void ChefProjet::debug()
{
	std::cout << "Chef de Projet ID : " << this->id << "\nNom : " << this->nom << "\nPrenom : " << this->prenom << std::endl;
} 
