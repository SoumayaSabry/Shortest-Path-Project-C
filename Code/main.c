#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "Trajet.h"
void change_couleur(int couleurDuTexte,int couleurDeFond) 
{
	HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void afficher_menu(const char* options[], int longueur, int index_curseur, char * quelleChoix)
{
	printf("Veuillez choisir votre ville %s \n", quelleChoix);
	for (int i=0; i< longueur; i++)
	{
		if (i==index_curseur) change_couleur(3,14);
		else change_couleur(7 ,0);
		printf("%s\n", options[i]);
	}
	change_couleur( 15, 0 );
}

ville menuChoixVille(const char* options[], const int l_options,char * quelleChoix)
{
	ville v ; 
	int indice_choisie=0; //Par défaut la premiere option du menu est selectionnée <=> au debut, le curseur se trouve sur la premiere option du menu
	int termine=0;
	int c=0;
	while(termine==0)
	{	
		system("cls");
		afficher_menu(options, l_options, indice_choisie,quelleChoix);
		c = _getch();
		switch(c)
		{
			case KEY_UP:
				indice_choisie--;
				if (indice_choisie<0) indice_choisie+=l_options;
				break;
			case KEY_DOWN:
				indice_choisie++;
				indice_choisie%=l_options;
				break;
			case KEY_ENTER:
				termine=1;
				//printf("Option %d choisie.\n", indice_choisie);
				v = indice_choisie;
			case KEY_ESC:
				termine=1;
				break;
		}
	}
	return v ;
}
int saisir_entier_borne(int borne_inf, int borne_sup)
{
	int resultat = borne_inf - 1;
	scanf("%d", &resultat);
	while(resultat < borne_inf || resultat > borne_sup )
	{
		printf("\nValeur non valide, entrez un entier valide :");
		scanf("%d", &(resultat));
		getchar();
	}
	return resultat;
}

char* demander_chaine()
{
	char* mot = (char*) malloc(100 * sizeof(char));
	mot[99] = '\0';
	scanf("%s", mot);
	return mot;
}

void interface_utilisateur()
{
	printf("*----------*----------*----------*----------*----------*----------*----------*\n");
	printf("\tBIENVENUE SUR CE PROGRAMME DE GENERATION D'UN ARBRE DES TRAJETS\n");
	printf("*----------*----------*----------*----------*----------*----------*----------*\n\n");
	
	int continuer = 1; // Pour savoir quand l'utilisateur a fini
	int change_villes = 1; // Pour savoir si l'utilisateur veut changer les villes
	ville depart;
	ville arrivee;
	
	while(continuer == 1)
	{
		if(change_villes == 1)
		{
			const char* optionss[] = 
			{
				"Amiens","Bayonne","Bordeaux","Bourges","Caen","Clermont_Ferrand","Dijon",
				"Grenoble","Le_Mans","Lille","Lyon","Marseille","Metz","Montpellier",
				"Nantes","Nice","Niort","Paris","Reims","Rennes","Strasbourg","Toulouse","Tours"
			};
			int long_options=23;
			char* quellechoix = "de depart";
			depart = menuChoixVille(optionss, long_options,quellechoix );
			quellechoix = "d'arriver" ;
			arrivee = menuChoixVille(optionss, long_options, quellechoix);
			while(depart==arrivee)
			{
				printf("\n Vous avez choisi la ville d'arrive meme que la ville de depart, reessayez \n");
				system("pause");
				quellechoix = "d'arriver" ;
				arrivee = menuChoixVille(optionss, long_options, quellechoix);
			}
		}
		
		printf("\n \n Veuillez choirir une taille maximal de ville visitee ==>");
		int tailleMax = saisir_entier_borne(2, 23);
		noeud* arbre = creation_arbre(depart, arrivee,tailleMax);
		
		system("cls");
		printf("VOICI LES FONCTIONNALITES PROPOSEES PAR CE PROGRAMME :\n");
		printf("-> 1 : Affichage d'un trajet aleatoire\n");
		printf("-> 2 : Affichage de tous les trajets possibles\n");
		printf("-> 3 : Affichage du ou des trajets les plus courts (en distance)\n");
		printf("-> 4 : Affichage du ou des trajets les plus rapides (en temps)\n");
		printf("-> 5 : Affichage de l'arbre des trajets\n");
		printf("Faites votre choix !\n");
		
		int choix_utilisateur = saisir_entier_borne(1, 5);
		switch(choix_utilisateur)
		{
			case 1:
			system("cls");
			printf("Vous avez choisi : Affichage d'un trajet aleatoire\n");
			trajet_alea(arbre, arrivee);
			break;
			
			case 2:
			system("cls");
			printf("Vous avez choisi : Affichage de tous les trajets possibles\n");
			printf("Distance | Duree\t | \t\tTrajet \n");
			printf("----------------------------------------------------------------------------------------------------------------------- \n");
			affichage_tout_trajet(arbre, 0, arrivee);
			printf("Tous les trajets possibles ont ete affiches !\n");
			break;
			
			case 3:
			system("cls");
			printf("Vous avez choisi : Affichage du ou des trajets les plus courts (en distance)\n");
			distance_duree_min(arbre, choix_utilisateur, arrivee);
			break;
			
			case 4:
			system("cls");
			printf("Vous avez choisi : Affichage du ou des trajets les plus rapides (en temps)\n");
			distance_duree_min(arbre, choix_utilisateur, arrivee);
			break;
			
			case 5:
			system("cls");
			printf("Vous avez choisi : Affichage de l'arbre des trajets\n");
			affichage_arb(arbre, 0);
			printf("Votre arbre est affiche !\n");
			break;
		}
		printf("\n\nVoulez vous effectuer un autre parcours ? Tapez 1 si oui et 0 sinon\n");
		continuer = saisir_entier_borne(0, 1);
		if(continuer == 1)
		{
			printf("Voulez vous garder les villes de depart et d'arrivee ? Tapez 1 si oui et 0 sinon\n");
			change_villes = saisir_entier_borne(0, 1);
		}
		system("cls");
		liberation_arbre(arbre);
	}
}

int main(int argc, char **argv)
{
	interface_utilisateur();
	return 0;
}
