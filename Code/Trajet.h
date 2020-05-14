#ifndef TRAJET_H
#define TRAJET_H
#include <stdbool.h>

//----------*----------*----------*----------*----------*----------*----------*

typedef enum {
	Amiens,
	Bayonne,Bordeaux,Bourges,
	Caen,Clermont_Ferrand,
	Dijon,
	Grenoble,
	Le_Mans,Lille,Lyon,
	Marseille,Metz,Montpellier,
	Nantes,Nice,Niort,
	Paris,
	Reims,Rennes,
	Strasbourg,
	Toulouse,Tours } ville;
	
typedef struct 
	{
		int heure;
		int minute;
	} duree;

typedef struct _connection
	{
		duree temps_trajet;
		int kilomettre;
		ville nom_connex;
		struct _connection* next ;
		
	}connection;

typedef struct
{
	ville nom_de_la_ville;
	connection* list_connections;
	int nb_de_connection;
}Case;

typedef struct _noeud
{
	Case position_actuelle;
	int distance_parcourue_cumule;
	duree duree_trajet_cumule;
	ville* villes_visitees; // tableaux de ville visitee// 
	int nb_villes_visitees;
	struct _noeud** suite_trajet;
} noeud;
 
typedef struct 
{
	int distance_parcourue_cumule;
	duree duree_trajet_cumule;
	ville* villes_visitees;
	int nb_villes_visitees;
} trajet ;

//*----------*----------*----------*----------*----------*----------*----------*

ville Transform_char_en_ville(char * chaine);
duree Transform_char_en_duree(char * chaine);
int Transform_char_en_int(char * chaine);

void afficher_duree(duree * h);
void villeToString(ville nom_ville);
void connectionToString(connection * my_connection);
void affiche_gdtab(Case* grand_tab);

connection* inserer_new_connection ( duree temps , int km,  ville nom_ville , connection * c  );
//besion de faire un free apres ses mallo mais a la fin de ma fonction 

unsigned int longeur_chaine(const char * chaine);
char** lire_ficher(char nom_du_fichier [],int nb_ligne);
void remplisage_donnees(Case* grand_tab);
void libere_tab (char** tab, int taille);


noeud* creation_arbre(ville depart, ville destination, int trajetMAX);
noeud* creation_racine(Case* tab, ville destination_Final, ville villeDeDepart, int trajetMAX);
noeud* ajouter_noeud(Case* gdTab, noeud* parent,connection ville_a_ajouter, ville destination_Final, int trajetMAX );
void affichage_arb(noeud const * arbre, int offset);

void affichage_tout_trajet(noeud * arbre, int offset, ville destination);
void interprete_arbre(noeud const * arbre, ville destination, trajet * tabDeTrajet, int* tailledutab);
void distance_duree_min(noeud * arbre, int choix, ville arrivee);
bool comparer_duree(duree d1, duree d2);
void trajet_alea(noeud * arbre, ville destination);
int generation_alea_int(int valeur_max);

void liberation_GdTab(Case* gdTab);
void liberation_arbre(noeud * arbre);
void liberation_trajet(trajet * tabDeTrajet, int taille);

//*----------*----------*----------*----------*----------*----------*----------*
enum
{
	KEY_ENTER = 13,
	KEY_ESC   = 27,
	KEY_UP    = 72,
	KEY_DOWN  = 80,
	KEY_LEFT  = 75,
	KEY_RIGHT =  77,
	KEY_A = 97
};

#endif