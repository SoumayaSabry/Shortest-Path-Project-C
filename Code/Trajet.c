#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Trajet.h"

ville Transform_char_en_ville(char * chaine)
{
	ville m ;
	if(chaine[0] == 'A'&& chaine[1] == 'm')	m = Amiens;
	if(chaine[0] == 'B'&& chaine[1] == 'a')	m = Bayonne;
	if(chaine[0] == 'B'&& chaine[2] == 'r')	m = Bordeaux;
	if(chaine[0] == 'B'&& chaine[2] == 'u')	m = Bourges;
	if(chaine[0] == 'C'&& chaine[1] == 'a')	m = Caen;
	if(chaine[0] == 'C'&& chaine[1] == 'l')	m = Clermont_Ferrand;
	if(chaine[0] == 'D'&& chaine[1] == 'i')	m = Dijon;
	if(chaine[0] == 'G'&& chaine[1] == 'r')	m = Grenoble;
	if(chaine[0] == 'L'&& chaine[1] == 'e')	m = Le_Mans;
	if(chaine[0] == 'L'&& chaine[1] == 'i')	m = Lille;
	if(chaine[0] == 'L'&& chaine[1] == 'y')	m = Lyon;
	if(chaine[0] == 'M'&& chaine[1] == 'a')	m = Marseille;
	if(chaine[0] == 'M'&& chaine[1] == 'e')	m = Metz;
	if(chaine[0] == 'M'&& chaine[1] == 'o')	m = Montpellier;
	if(chaine[0] == 'N'&& chaine[1] == 'a')	m = Nantes;
	if(chaine[0] == 'N'&& chaine[2] == 'c')	m = Nice;
	if(chaine[0] == 'N'&& chaine[2] == 'o')	m = Niort;
	if(chaine[0] == 'P'&& chaine[1] == 'a')	m = Paris;
	if(chaine[0] == 'R'&& chaine[2] == 'i')	m = Reims;
	if(chaine[0] == 'R'&& chaine[2] == 'n')	m = Rennes;
	if(chaine[0] == 'S'&& chaine[1] == 't')	m = Strasbourg ;
	if(chaine[0] == 'T'&& chaine[3] == 'l')	m = Toulouse;
	if(chaine[0] == 'T'&& chaine[3] == 'r')	m = Tours;
	return m ;
}
int Transform_char_en_int(char * chaine)
{
	int k=0;
	int compt=1;
	for(int i = longeur_chaine(chaine)-1;i>=0;i--)
	{
		k += (chaine[i]-'0')*compt;
		compt=compt * 10;
	}
	return k;
}
duree Transform_char_en_duree(char * chaine)
{
	duree sortie ;
	do {
	sortie.heure = (chaine[0]-'0')*10+(chaine[1]-'0');
	} while (sortie.heure < 0 || sortie.heure > 24 );
	do{
	sortie. minute = (chaine[3]-'0')*10+(chaine[4]-'0');
	}while (sortie.minute < 0 || sortie.minute > 60 );
	
	return sortie ;

}
void villeToString(ville nom_ville)
{
	switch(nom_ville)
	{
		case 0:
			printf("Amiens");
			break;
		case 1:
			printf("Bayonne");
			break;
		case 2:
			printf("Bordeaux");
			break;
		case 3:
			printf("Bourges");
			break;
		case 4:
			printf("Caen");
			break;
		case 5:
			printf("Clermont_Ferrand");
			break;
		case 6:
			printf("Dijon");
			break;
		case 7:
			printf("Grenoble");
			break;
		case 8:
			printf("Le_Mans");
			break;
		case 9:
			printf("Lille");
			break;
		case 10:
			printf("Lyon");
			break;
		case 11:
			printf("Marseille");
			break;
		case 12:
			printf("Metz");
			break;
		case 13:
			printf("Montpellier");
			break;
		case 14:
			printf("Nantes");
			break;
		case 15:
			printf("Nice");
			break;
		case 16:
			printf("Niort");
			break;
		case 17:
			printf("Paris");
			break;
		case 18:
			printf("Reims");
			break;
		case 19:
			printf("Rennes");
			break;
		case 20:
			printf("Strasbourg");
			break;
		case 21:
			printf("Toulouse");
			break;
		case 22:
			printf("Tours");
			break;
	}
	
}
void afficher_duree(duree*  h)
{
	if(h->minute > 59)
	{
		h->heure += h->minute / 60;
		h->minute %= 60;
	}
	if(h->heure < 10)printf("0%d",h->heure);
	else printf("%d",h->heure);
	printf("H");
	if(h->minute < 10)printf("0%d",h->minute);
	else printf("%d",h->minute);

}
void connectionToString(connection * my_connection)
{
	connection* parcours=my_connection;
	while(parcours!=NULL)
	{
		villeToString(parcours->nom_connex);
		printf("\t%d\t ",parcours->kilomettre);
		afficher_duree(&parcours->temps_trajet);
		parcours=parcours->next;
		printf("\n");
	}
}
connection* inserer_new_connection ( duree temps , int km,  ville nom_ville , connection * c  )
{
	connection* new_connection = (connection* ) malloc(sizeof(connection));
	 new_connection->temps_trajet= temps ;
	 new_connection->kilomettre = km;
	 new_connection->nom_connex = nom_ville;
	 new_connection->next = NULL;
	 if(c==NULL)
	{
		return new_connection;
	}
	else
	{
		connection* parcours= c;
		while(parcours->next!=NULL)parcours=parcours->next;
		parcours->next=new_connection;
		return c;
	}
}

unsigned int longeur_chaine(const char * chaine)
{
	unsigned int taille = 0;
	if( chaine != NULL )
	{
		while( chaine[taille] != '\0' )taille++;
	}
	return taille; 
}

char** lire_ficher(char  nom_du_fichier[],int nb_ligne)
{
	FILE* fichier = fopen(nom_du_fichier,"r");
	char** mots = malloc(sizeof(char*)*nb_ligne);
	if(fichier != NULL)
	{
		for(int ligne = 0 ; ligne < nb_ligne; ligne++)
		{
			mots[ligne]=malloc(sizeof(char)*20);//pour lire tt la ligne ds le case la ligne est assez grande
			fscanf(fichier, "%s",mots[ligne]);
		}
	}
	else
	{
		printf("Problème lors de l'ouverture du fichier %s\n", nom_du_fichier);
	}
	fclose(fichier);
	return mots ;
}
void libere_tab (char** tab,int taille)
{
	for(int i = 0 ; i< taille; i++)
	{
		free(tab[i]);
	}
	free(tab);
}
void remplisage_donnees(Case* regroupage_villes )
{
	char** tableau_villes = lire_ficher("villes.csv", 24);
	for(int ligne = 0 ; ligne < 24; ligne++) // ligne = 1 ?
	{
		if(ligne > 0 )//POUR EVITER LA PREMIERE LIGNE 
		{
			 regroupage_villes[ligne-1].nom_de_la_ville = Transform_char_en_ville(tableau_villes[ligne]);
			 regroupage_villes[ligne-1].nb_de_connection = 0;
			 regroupage_villes[ligne-1].list_connections = NULL;
		}
	}
	
	libere_tab(tableau_villes,24);
	
	char** tableau_connex = lire_ficher("connexions.csv", 73);
	char* souspartie;
	ville ville1; ville ville2; int km; duree time ;
	for(int ligne = 0 ; ligne < 73; ligne++)
	{
		if(ligne > 0 )//POUR EVITER LA PREMIERE LIGNE 
		{
				 
				 souspartie = strtok(tableau_connex[ligne], ",");
				 ville1=Transform_char_en_ville(souspartie);
				 
				 souspartie = strtok(NULL, ",");
				 ville2=Transform_char_en_ville(souspartie);
				 
				 souspartie = strtok(NULL, ",");
				 km = Transform_char_en_int(souspartie);
				 
				 souspartie = strtok(NULL, "\n");
				 time= Transform_char_en_duree(souspartie);
				 
				 regroupage_villes[ville1].list_connections = inserer_new_connection(time,km,ville2,regroupage_villes[ville1].list_connections);
				 
				 regroupage_villes[ville1].nb_de_connection = regroupage_villes[ville1].nb_de_connection +1;
		}
	}
	free(tableau_connex);
	//car en strtok c'est deja videe
}
void affiche_gdtab(Case* grand_tab)
{
	for(int i = 0 ; i<23; i++)
	{
		
		printf("||");
		villeToString(grand_tab[i].nom_de_la_ville);
		printf("||\n");
		printf("Elle a %d connection::\n",grand_tab[i].nb_de_connection);
		//printf("Nom Ville  Km \t duree \n");
		connectionToString(grand_tab[i].list_connections);
		printf ("\n\n\n");
	}
}

//----------*----------*----------*----------*----------*----------*----------*//
noeud* ajouter_noeud(Case* gdTab, noeud* parent,connection ville_a_ajouter, ville destination_Final , int trajetMAX)
{
	noeud* add_noeud = (noeud*)malloc(sizeof(noeud));
	add_noeud->position_actuelle = gdTab[ville_a_ajouter.nom_connex];
	add_noeud->distance_parcourue_cumule= ville_a_ajouter.kilomettre + parent->distance_parcourue_cumule;
	add_noeud->duree_trajet_cumule.heure =ville_a_ajouter.temps_trajet.heure+parent->duree_trajet_cumule.heure;
	add_noeud->duree_trajet_cumule.minute =ville_a_ajouter.temps_trajet.minute+parent->duree_trajet_cumule.minute;
	add_noeud->nb_villes_visitees = 1+ parent->nb_villes_visitees;// meme que racine 
	add_noeud->villes_visitees = (ville*) malloc(add_noeud->nb_villes_visitees * sizeof(ville));
	for(int i = 0 ; i<add_noeud->nb_villes_visitees-1; i++)
	{
		add_noeud->villes_visitees[i]=parent->villes_visitees[i];
	}
	add_noeud->villes_visitees[add_noeud->nb_villes_visitees-1] = ville_a_ajouter.nom_connex; 
	if(add_noeud->nb_villes_visitees >= trajetMAX|| ville_a_ajouter.nom_connex== destination_Final)
	{
		add_noeud->suite_trajet =NULL;
		return add_noeud;
		//return NULL;
	}
	else 
	{
		int nb_de_connection_restant = add_noeud->position_actuelle.nb_de_connection;
		connection * temp_01 = add_noeud->position_actuelle.list_connections;
		while(temp_01 != NULL)
		{
			for(int i = 0 ; i<add_noeud->nb_villes_visitees; i++)
			{
				if(temp_01->nom_connex==add_noeud->villes_visitees[i])nb_de_connection_restant-=1;
			}
			temp_01 = temp_01->next;
		}
		
		add_noeud->suite_trajet =(noeud**) malloc(sizeof(noeud*)*nb_de_connection_restant);
		
		connection * temp_02 = add_noeud->position_actuelle.list_connections;
		for(int i = 0; i<nb_de_connection_restant ; i ++)
		{
			connection t = *temp_02;
			bool ilExiste = false ;
			for(int j = 0 ; j<add_noeud->nb_villes_visitees; j++)
			{
				if(t.nom_connex==add_noeud->villes_visitees[j])
				{
					ilExiste= true;
				}
			}
			if(!ilExiste)
			{
				add_noeud->suite_trajet[i]=(noeud*)malloc(sizeof(noeud)); 
				add_noeud->suite_trajet[i]=ajouter_noeud(gdTab,add_noeud,t,destination_Final, trajetMAX);
			}
			else 
			{
				i--;
			}
			temp_02 = temp_02->next;
		}
		return add_noeud;
	}
}

noeud* creation_racine(Case* tab, ville destination_Final, ville villeDeDepart, int trajetMAX)
{
	noeud * racine = (noeud *) malloc(sizeof(noeud)); // Allocation mémoire
	racine->position_actuelle = tab[villeDeDepart];
	racine->distance_parcourue_cumule= 0;
	racine->duree_trajet_cumule.heure = 0;
	racine->duree_trajet_cumule.minute = 0;
	racine->nb_villes_visitees = 1;
	racine->villes_visitees = (ville*) malloc(racine->nb_villes_visitees * sizeof(ville));
	racine->villes_visitees[0] = villeDeDepart;
	racine->suite_trajet =(noeud**) malloc(sizeof(noeud*)*racine->position_actuelle.nb_de_connection);
	connection * temp = racine->position_actuelle.list_connections;
	for(int i = 0; i<racine->position_actuelle.nb_de_connection ; i ++)
	{
		connection t = *temp;
		racine->suite_trajet[i]=(noeud*)malloc(sizeof(noeud));
		racine->suite_trajet[i]=ajouter_noeud(tab,racine,t,destination_Final, trajetMAX);// mais ca pourras continuer avec i ++ tu vois ? je rejoute un fils avec tt ce qui contient de fils 
		temp = temp->next;
	}
	return racine;
}

noeud* creation_arbre(ville depart, ville destination, int trajetMAX)
{
	Case * grandTab = malloc(sizeof(Case) * 23); // On créé un tableau de Case de taille 23 (une case par ville)
	remplisage_donnees(grandTab); // Fonction de remplissage du tableau à partir des fichiers .csv
	noeud * arbre = creation_racine(grandTab, destination,depart,  trajetMAX); // Création de la racine (correspond à la ville de départ)
	//liberation_GdTab(grandTab);
	return arbre;
}
void affichage_arb(noeud const * arbre, int offset)
{
	if(arbre != NULL) // On regarde d'abord si l'arbre existe pour ensuite faire des tests dessus
	{
		for(int i = 0 ; i < offset ; i++)	printf("|\t");
		printf("|-"); 
		villeToString(arbre->position_actuelle.nom_de_la_ville); // Affiche le nom de la ville
		printf("\n"); 
		if(arbre->suite_trajet!=NULL) // Si l'arbre a un tableau de pointeurs vers des connexions
		{
			int nb_de_connection_restant = arbre->position_actuelle.nb_de_connection; // Variable qui compte le nb de connexions restantes possibles
			connection * temp_01 = arbre->position_actuelle.list_connections; // Pointeur temporaire vers la liste de connexions de la case actuelle de l'arbre
			while(temp_01 != NULL) // Tant qu'il y a des connexions
			{
				for(int i = 0 ; i<arbre->nb_villes_visitees; i++)
				{
					if(temp_01->nom_connex==arbre->villes_visitees[i])nb_de_connection_restant-=1; // On compte le nombre de villes visitées
				}
				temp_01 = temp_01->next;
			}
			for(int i = 0;i<nb_de_connection_restant;i++)
			{
				affichage_arb(arbre->suite_trajet[i],offset+1); // On utilise une récursion pour afficher le reste des villes
			}
		}
	}
}

//----------*----------*----------*----------*----------*----------*----------*//
void affichage_tout_trajet(noeud * arbre, int offset, ville destination)
{
	if(arbre != NULL) // On regarde d'abord si l'arbre existe pour ensuite faire des tests dessus
	{
		if(arbre->suite_trajet!=NULL) // Si l'arbre a un tableau de pointeurs vers des connexions
		{
			int nb_de_connection_restant = arbre->position_actuelle.nb_de_connection; // Variable qui compte le nb de connexions restantes possibles
			connection * temp_01 = arbre->position_actuelle.list_connections; // Pointeur temporaire vers la liste de connexions de la case actuelle de l'arbre
			while(temp_01 != NULL) // Tant qu'il y a des connexions
			{
				for(int i = 0 ; i<arbre->nb_villes_visitees; i++)
				{
					if(temp_01->nom_connex==arbre->villes_visitees[i])nb_de_connection_restant-=1; // On compte le nombre de villes visitées
				}
				temp_01 = temp_01->next;
			}
			for(int i = 0;i<nb_de_connection_restant;i++) 
			{
				affichage_tout_trajet(arbre->suite_trajet[i],offset+1,destination); // On utilise une récursion pour afficher le reste du trajet
			}
		}
		else // Si l'arbre n'a plus de connexions possibles
		{
			if(arbre->position_actuelle.nom_de_la_ville==destination) // On vérifie que la ville atteinte est bien la destination souhaitée
			{
				printf("%d\t | ",arbre->distance_parcourue_cumule); // Puis la distance et la durée totale
				afficher_duree(&arbre->duree_trajet_cumule);
				printf("\t | ");
				for(int i = 0 ; i < arbre->nb_villes_visitees ;i ++)
				{
					villeToString(arbre->villes_visitees[i]); // On affiche toutes les villes visitées pendant le trajet
					if(i < arbre->nb_villes_visitees - 1) printf(", ");
				}
				printf("\n\n________________________________________________________________________________________________________________________\n\n\n");
			}
		}
	}
}

void interprete_arbre(noeud const * arbre, ville destination, trajet * tabDeTrajet, int* tailledutab)
{
	if(arbre != NULL) // On regarde d'abord si l'arbre existe pour ensuite faire des tests dessus
	{
		if(arbre->suite_trajet!=NULL) // Si l'arbre a un tableau de pointeurs vers des connexions
		{
			int nb_de_connection_restant = arbre->position_actuelle.nb_de_connection; // Variable qui compte le nb de connexions restantes possibles
			connection * temp_01 = arbre->position_actuelle.list_connections; // Pointeur temporaire vers la liste de connexions de la case actuelle de l'arbre
			while(temp_01 != NULL) // Tant qu'il y a des connexions
			{
				for(int i = 0 ; i<arbre->nb_villes_visitees; i++)
				{
					if(temp_01->nom_connex==arbre->villes_visitees[i])nb_de_connection_restant-=1; // On compte le nombre de villes visitées
				}
				temp_01 = temp_01->next;
			}
			for(int i = 0;i < nb_de_connection_restant; i++) 
			{
				interprete_arbre(arbre->suite_trajet[i],destination, tabDeTrajet, tailledutab); // On utilise une récursion pour afficher le reste du trajet
			}
		}
		else // Si l'arbre n'a plus de connexions possibles// 
		{
			if(arbre->position_actuelle.nom_de_la_ville == destination) // On vérifie que la ville atteinte est bien la destination souhaitée
			{
				*tailledutab += 1;
				trajet * tempt= malloc(sizeof(trajet)*(*tailledutab));
				for(int i = 0 ; i<*tailledutab-1;i++)
				{
					tempt[i]=tabDeTrajet[i];
				}
				
				tempt[*tailledutab-1].distance_parcourue_cumule=arbre->distance_parcourue_cumule;
				tempt[*tailledutab-1].duree_trajet_cumule=arbre->duree_trajet_cumule;
				tempt[*tailledutab-1].villes_visitees=arbre->villes_visitees;
				tempt[*tailledutab-1].nb_villes_visitees = arbre->nb_villes_visitees;
				for(int i = 0 ; i < *tailledutab; i++)
				{
					tabDeTrajet[i]=tempt[i]; 
				}
			}
		}
	}
}

bool comparer_duree(duree d1, duree d2)
{
	int h1 = d1.heure * 60 + d1.minute;
	int h2 = d2.heure * 60 + d2.minute;
	if(h1 < h2) return true; // Vrai si d1 < d2
	else return false;
}

void distance_duree_min(noeud * arbre, int choix, ville arrivee)
{
	
	trajet* tab_trajets = (trajet*) malloc(sizeof(trajet));
	int taille = 0;
	interprete_arbre(arbre, arrivee, tab_trajets, &taille);
	trajet* trajets_min = (trajet*) malloc(8 * sizeof(trajet));
	
	if(choix == 3)
	{
		int distance_min = tab_trajets[0].distance_parcourue_cumule;
		trajets_min[0] = tab_trajets[0];
		
		int compt_trajets = 1;
		for(int i = 1; i < taille; i++)
		{
			if(tab_trajets[i].distance_parcourue_cumule == distance_min)
			{
				trajets_min[compt_trajets] = tab_trajets[i];
				compt_trajets++;
			}
			if(tab_trajets[i].distance_parcourue_cumule < distance_min)
			{
				distance_min = tab_trajets[i].distance_parcourue_cumule;
				trajets_min[0] = tab_trajets[i];
			}
		}
		for(int i = 0; i < compt_trajets; i++)
		{
			printf("\nDistance du trajet : %d km\t", trajets_min[i].distance_parcourue_cumule);
			printf("Duree totale : ");
			afficher_duree(&trajets_min[i].duree_trajet_cumule);
			printf("\tTrajet : ");
			for(int j = 0; j < trajets_min[i].nb_villes_visitees; j++) 
			{
				villeToString(trajets_min[i].villes_visitees[j]);
				if(j != trajets_min[i].nb_villes_visitees - 1) printf(", ");
			}
			printf("\n");
		}
	}
	
	if(choix == 4)
	{
		duree duree_min = tab_trajets[0].duree_trajet_cumule;
		trajets_min[0] = tab_trajets[0];
		
		int compt_trajets = 1;
		for(int i = 1; i < taille; i++)
		{
			if((tab_trajets[i].duree_trajet_cumule.heure ==duree_min.heure) && (tab_trajets[i].duree_trajet_cumule.minute ==duree_min.minute))
			{
				trajets_min[compt_trajets] = tab_trajets[i];
				compt_trajets++;
			}
			if(comparer_duree(tab_trajets[i].duree_trajet_cumule, duree_min))
			{
				duree_min = tab_trajets[i].duree_trajet_cumule;
				trajets_min[0] = tab_trajets[i];
			}
		}
		for(int i = 0; i < compt_trajets; i++)
		{
			printf("\nDistance du trajet : %d km\t", trajets_min[i].distance_parcourue_cumule);
			printf("Duree totale : ");
			afficher_duree(&trajets_min[i].duree_trajet_cumule);
			printf("\tTrajet : ");
			for(int j = 0; j < trajets_min[i].nb_villes_visitees; j++) 
			{
				villeToString(trajets_min[i].villes_visitees[j]);
				if(j != trajets_min[i].nb_villes_visitees - 1) printf(", ");
			}
			printf("\n");
		}
	}
}

void trajet_alea(noeud * arbre, ville arrivee)
{
	trajet* tab_trajets = (trajet*) malloc(sizeof(trajet));
	int taille = 0;
	interprete_arbre(arbre, arrivee, tab_trajets, &taille);
	int rand = generation_alea_int(taille);
	printf("\nDistance du trajet : %d km\t", tab_trajets[rand].distance_parcourue_cumule);
	printf("Duree totale : ");
	afficher_duree(&tab_trajets[rand].duree_trajet_cumule);
	printf("\tTrajet : ");
	for(int i = 0; i < tab_trajets[rand].nb_villes_visitees; i++) 
	{
		villeToString(tab_trajets[rand].villes_visitees[i]);
		if(i < tab_trajets[rand].nb_villes_visitees - 1) printf(", ");
	}
	printf("\n");
}

int generation_alea_int(int valeur_max)
{
	int alea = 0;
	do
	{
		alea = rand() / (RAND_MAX / valeur_max); // valeur aléatoire entre 0 inclus et valeur_max exclus
	} while (alea > valeur_max);
	return alea ;
}

void liberation_GdTab(Case* gdTab)
{
	for(int i =0; i<23; i++)
	{
		free(gdTab[i].list_connections);
	}
	free(gdTab);
}
void liberation_arbre(noeud * arbre)
{
	if(arbre != NULL) // On regarde d'abord si l'arbre existe pour ensuite faire des tests dessus
	{
		if(arbre->suite_trajet!=NULL) // Si l'arbre a un tableau de pointeurs vers des connexions
		{
			int nb_de_connection_restant = arbre->position_actuelle.nb_de_connection; // Variable qui compte le nb de connexions restantes possibles
			connection * temp_01 = arbre->position_actuelle.list_connections; // Pointeur temporaire vers la liste de connexions de la case actuelle de l'arbre
			while(temp_01 != NULL) // Tant qu'il y a des connexions
			{
				for(int i = 0 ; i<arbre->nb_villes_visitees; i++)
				{
					if(temp_01->nom_connex==arbre->villes_visitees[i])nb_de_connection_restant-=1; // On compte le nombre de villes visitées
				}
				temp_01 = temp_01->next;
			}
			for(int i = 0;i<nb_de_connection_restant;i++) 
			{
				 liberation_arbre(arbre->suite_trajet[i]); // On utilise une récursion pour afficher le reste du trajet
			}
		}
		else // Si l'arbre n'a plus de connexions possibles
		{
			free(arbre);
		}
	}
}
void liberation_trajet(trajet * tabDeTrajet, int taille)
{
	for(int i = 0 ; i < taille ; i++)
	{
		
			free(tabDeTrajet[i].villes_visitees);
		
	}
	free(tabDeTrajet);
}
