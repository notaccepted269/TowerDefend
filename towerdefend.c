#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL.h"
#include "towerdefend.h"


//typedef Tunite* ** TplateauJeu;

TplateauJeu AlloueTab2D(int largeur, int hauteur){
    TplateauJeu jeu;
    jeu = (Tunite***)malloc(sizeof(Tunite**)*largeur);
    for (int i=0;i<largeur;i++){            
        jeu[i] = (Tunite**)malloc(sizeof(Tunite*)*hauteur);
    }
    return jeu;  //tab2D contenant des pointeurs
}
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur){
    for (int i=0;i<largeur;i++){
        for (int j=0;j<hauteur;j++){
            jeu[i][j] = NULL;
        }
    }
}


/*
void ecritCheminVersleHaut  : permet d'initilaiser le tab chemin de distance cases (avec des coord x y) dans une direction, � partir d'un point x y donn�

int **chemin  : tab de coordonn�es x y du chemin
int *ichemin  : indice de la case du chemin d'o� on part
int *xdepart, int *ydepart : valeur en x y de d�part pouri la premiere case
int distance  : distance sur laquelle on va �crire des coordonn�es dans le tab chemin
int *distanceMaxRestante : securit� pour ne pas sortir de la plage d'indice de chemin
*/
void ecritCheminVersleHaut(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante){
    if ((*distanceMaxRestante - distance)>=0){
        int y;
        for (y=*ydepart;y>*ydepart-distance;y--){
            chemin[*ichemin][X]= *xdepart;
            chemin[*ichemin][Y]= y;
            (*ichemin)++;
        }
        *ydepart=y;
    }
    else printf("erreur longueur chemin\n");
}
void ecritCheminVerslaDroite(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante){
    if ((*distanceMaxRestante - distance)>=0){
        int x;
        for (x=*xdepart;x<*xdepart+distance;x++){
            chemin[*ichemin][X]= x;
            chemin[*ichemin][Y]= *ydepart;
            (*ichemin)++;
        }
        *xdepart=x;
    }
    else printf("erreur longueur chemin\n");
}
void ecritCheminVerslaGauche(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante){
    if ((*distanceMaxRestante - distance)>=0){
        int x;
        for (x=*xdepart;x>*xdepart-distance;x--){
            chemin[*ichemin][X]= x;
            chemin[*ichemin][Y]= *ydepart;
            (*ichemin)++;
        }
        *xdepart=x;
    }
    else printf("erreur longueur chemin\n");
}

int **initChemin(){
    int **chemin = (int**)malloc(sizeof(int*)*NBCOORDPARCOURS);

    for (int j=0;j<NBCOORDPARCOURS;j++){
        chemin[j] = (int*)malloc(sizeof(int)*2);  //2 cases :indice 0 pour la coord en X, indice 1 pour la coord en Y
    }

    int ydepart = 18;  //et non 19
    int xdepart = 5;  //5 = milieu de la fenetre de 11 de largeur (0-10)
    int i = 0;  //parcourt les i cases du chemin
    int distanceMaxRestante = NBCOORDPARCOURS;

    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);
    ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVerslaGauche(chemin, &i, &xdepart, &ydepart, 5, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);
    ecritCheminVerslaGauche(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);

    return chemin;  //tab2D contenant des pointeurs
}

void afficheCoordonneesParcours(int **chemin, int nbcoord){
    printf("Liste coordonnees: ");
    for (int i=0; i<nbcoord; i++){
        printf("(%d, %d)",chemin[i][X], chemin[i][Y]);
    }
    printf("\nfin liste coordonn�es\n");
}

void freeChemin(int **tab){
    for (int j=0;j<NBCOORDPARCOURS;j++){
        free(tab[j]);  //libere chaque case, qui est un tableau de 2 cases
    }
    free(tab);
}

void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur){
    //pour un affichage sur la console, en relation avec enum TuniteDuJeu
    const char* InitialeUnite[7]={"s", "a", "r", "A", "C", "D", "G"};

    printf("\n");
    for (int j=0;j<hauteur;j++){
        for (int i=0;i<largeur;i++){
                // A ne pas donner aux etudiants
            if (jeu[i][j] != NULL){
                    printf("%s",InitialeUnite[jeu[i][j]->nom]);
            }
            else printf(" ");  //cad pas d'unit� sur cette case
        }
        printf("\n");
    }
}

Tunite *creeTourSol(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourSol;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 120;
    nouv->portee = 5;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeTourAir(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourAir;
    nouv->cibleAttaquable = air;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.0;
    nouv->degats = 100;
    nouv->portee = 3;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeTourRoi(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourRoi;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 800;
    nouv->vitesseAttaque = 1.2;
    nouv->degats = 180;
    nouv->portee = 4;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}


Tunite *creeDragon(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = dragon;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 200;
    nouv->vitesseAttaque = 1.1;
    nouv->degats = 180;
    nouv->portee = 2;
    nouv->vitessedeplacement = 2;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeGargouille(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv -> nom = gargouille;
    nouv -> cibleAttaquable = solEtAir;
    nouv -> maposition = air;
    nouv -> pointsDeVie =80;
    nouv -> vitesseAttaque = 0.6;
    nouv -> degats = 90;
    nouv -> portee = 1;
    nouv -> vitessedeplacement = 3.0;
    nouv -> posX = posx;
    nouv -> posY = posy;
    nouv -> peutAttaquer = 1;
    //nouv -> cible = NULL;
    return nouv;
}

Tunite *creeArcher(int posx, int posy){
    Tunite *nouv = (Tunite*) malloc(sizeof(Tunite));
    nouv -> nom = archer;
    nouv -> cibleAttaquable = solEtAir;
    nouv -> maposition = sol;
    nouv -> pointsDeVie = 80;
    nouv -> vitesseAttaque = 0.7;
    nouv -> degats = 120;
    nouv -> portee = 3;
    nouv -> vitessedeplacement = 1.0;
    nouv -> posX = posx;
    nouv -> posY = posy;
    nouv -> peutAttaquer = 1;
    //nouv -> cible = NULL;
    return nouv;
}

Tunite *creeChevalier(int posx, int posy){
    Tunite *nouv = (Tunite*) malloc(sizeof(Tunite));
    nouv -> nom = chevalier;
    nouv -> cibleAttaquable = sol;
    nouv -> maposition = sol;
    nouv -> pointsDeVie = 400;
    nouv -> vitesseAttaque = 1.5;
    nouv -> degats = 250;
    nouv -> portee = 1;
    nouv -> vitessedeplacement = 2.0;
    nouv -> posX = posx;
    nouv -> posY = posy;
    //nouv -> cible = NULL;
    return nouv;
}

/**
 * Objectif   : Vérifier si la tour du roi  est détruit
 * Algorithme : Vérification directe sur la tête de liste
 * Complexité : Temps O(1) | Espace O(1)
 *
 * @param playerRoi  Pointeur vers la cellule représentant le roi du joueur
 * @return           true si le roi est détruit ou absent, false sinon
 *
 * Fonctionnement :
 *   On considère le roi comme détruit dans trois cas : si la cellule est NULL,
 *   si son pointeur de données est NULL, ou si ses points de vie sont à 0.
 *   Dans tous les autres cas, le roi est encore en vie et la fonction retourne false.
 */
bool tourRoiDetruite(TListePlayer playerRoi){
    if (playerRoi == NULL) return true;
    if(playerRoi -> pdata == NULL || playerRoi -> pdata -> pointsDeVie == 0) return true;
    else return false;
}


/**
 * Objectif   : Insère une unité en tête de la liste chaînée d'un joueur
 * Algorithme : Insertion en tête
 * Complexité : Temps O(1) | Espace O(1)
 *
 * @param player        Pointeur vers la tête de la liste du joueur
 * @param nouvelleUnite Pointeur vers l'unité à insérer
 *
 * Fonctionnement :
 *   On alloue une nouvelle cellule en mémoire, puis on vérifie le succès
 *   de l'allocation. On lui affecte ensuite la donnée (unité), on la relie
 *   à l'ancienne tête de liste, et on met à jour la tête pour qu'elle
 *   pointe vers la nouvelle cellule.
 */
void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite){
    T_cell *newPlayer =(T_cell *)malloc(sizeof(T_cell));
    if(newPlayer == NULL) {
        fprintf(stderr, "Echec d'allocation");
        return;
    }

    (newPlayer -> pdata) = nouvelleUnite;
    newPlayer -> suiv = *player;
    *player = newPlayer; 
}

/**
 * Objectif   : Supprimer une unité morte de la liste d'un joueur et du plateau
 * Algorithme : Parcours linéaire avec pointeur précédent (prev/current)
 * Complexité : Temps O(n) | Espace O(1)
 *
 * @param player        Pointeur vers la tête de la liste du joueur
 * @param uniteDetruite Pointeur vers l'unité à supprimer
 * @param jeu           Plateau de jeu (tableau 2D de pointeurs)
 *
 * Fonctionnement :
 *   On vérifie d'abord que la liste et la cible sont valides, puis que
 *   l'unité est bien morte (PV == 0). On parcourt ensuite la liste jusqu'à
 *   trouver la cellule correspondante. On efface l'unité du plateau, on
 *   recoud la liste (cas tête ou milieu/fin), puis on libère la cellule.
 */
void SupprimerUnite(TListePlayer *player, Tunite *uniteDetruite, TplateauJeu jeu){
    T_cell *prev = NULL;
    T_cell *current = *player;

    if(*player == NULL) return;
    if(uniteDetruite == NULL) return;
    if(uniteDetruite -> pointsDeVie == 0)//voir si pointsDeVie <= 0 ne serait pas mieux
    {
        while(current != NULL){
            if (current -> pdata == uniteDetruite){
            
                jeu[current->pdata->posX][current->pdata->posY] = NULL;
            
                if(prev == NULL) {
                    *player = current -> suiv;
                } else {
                    prev -> suiv = current -> suiv;
                }
        
                free(current);
                break;
            }

            prev = current;
            current = current->suiv;
        }
    }
}

/**
 * Objectif   : Construire la liste de toutes les unités ennemies à portée d'attaque
 *              d'une unité attaquante, en tenant compte de sa portée et de ses cibles valides.
 * Algorithme : Balayage exhaustif du plateau (double boucle) + distance de Manhattan
 * Complexité : Temps O(n²) | Espace O(k) avec k = nombre d'unités à portée
 *
 * @param jeu              Plateau de jeu (tableau 2D de pointeurs vers Tunite)
 * @param UniteAttaquante  Pointeur vers l'unité qui effectue l'attaque
 * @return                 Liste chaînée des unités situées à portée et attaquables
 *
 * Fonctionnement :
 *   On balaye chaque case du plateau. Pour chaque case non vide, on calcule
 *   la distance de Manhattan entre la cible et l'attaquant :
 *       d = |xCible - xAttaquant| + |yCible - yAttaquant|
 *   Une unité est ajoutée au résultat si et seulement si :
 *     1. d <= portée de l'attaquant
 *     2. Le type de position de la cible (sol, air) est attaquable par l'unité
 *        (cibleAttaquable == maposition  OU  cibleAttaquable == solEtAir)
 *   La liste résultat est construite via AjouterUnite et retournée en fin de parcours.
 *
 */
TListePlayer quiEstAPortee(TplateauJeu jeu, Tunite *UniteAttaquante){
    TListePlayer resultat = NULL;
    int distance = 0;
    Tunite *cible;

    for(int i = 0; i < LARGEURJEU; i++){
        for(int j = 0; j < HAUTEURJEU; j++){
            if(jeu[i][j] != NULL){
               cible = jeu[i][j];
               distance = abs(cible->posX - UniteAttaquante->posX) + abs(cible->posY - UniteAttaquante->posY);
        
                if (distance <= UniteAttaquante -> portee && (UniteAttaquante -> cibleAttaquable == cible -> maposition || UniteAttaquante -> cibleAttaquable == solEtAir )){
                    AjouterUnite(&resultat, cible);
                }
            }
        }
    }
    return resultat;
}

/**
 * Objectif   : Positionner toutes les unités d'un joueur sur le plateau de jeu
 * Algorithme : Parcours linéaire de la liste chaînée du joueur
 * Complexité : Temps O(n) | Espace O(1)
 *
 * @param player  Pointeur vers la tête de la liste du joueur
 * @param jeu     Plateau de jeu (tableau 2D de pointeurs)
 *
 * Fonctionnement :
 *   On parcourt la liste chaînée du joueur cellule par cellule. Pour chaque
 *   unité, on utilise ses coordonnées (posX, posY) pour placer un pointeur
 *   vers ses données directement dans la case correspondante du plateau.
 *   Le parcourt s'arrête quand on atteint la fin de la liste (NULL).
 */
void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu){
     T_cell *current = player;
     while(current != NULL)
     {
        jeu[current->pdata->posX][current->pdata->posY] = current->pdata;        
        current = current -> suiv;
     }
}

/**
 * Objectif   : Échanger les données entre deux cellules de la liste chaînée
 * Algorithme : Swap par variable temporaire
 * Complexité : Temps O(1) | Espace O(1)
 *
 * @param source       Pointeur vers la cellule source
 * @param destination  Pointeur vers la cellule destination
 *
 * Fonctionnement :
 *   On vérifie d'abord que les deux pointeurs sont valides. Si l'un d'eux
 *   est NULL, un message d'erreur est affiché et aucun échange n'est effectué.
 *   Sinon, on utilise un pointeur temporaire pour échanger les champs `pdata`
 *   des deux cellules, sans modifier la structure chaînée elle-même.
 */
void swapData(T_cell *source, T_cell *destination)
{
	if (source == NULL || destination == NULL) {
		printf("Erreur swapData ptr = NULL, la valeur cherchee n'existe pas");
	} else {
	Tunite *tmp = source -> pdata;
	source -> pdata = destination -> pdata;
	destination -> pdata = tmp;
	}
}

/**
 * Objectif   : Trier la liste chaînée d'un joueur par ordre croissant de points de vie
 * Algorithme : Tri par sélection sur liste chaînée
 * Complexité : Temps O(n²) | Espace O(1)
 *
 * @param player  Pointeur vers le pointeur de tête de la liste du joueur
 * @return        La liste triée 
 *
 * Fonctionnement :
 *   Pour chaque cellule courante, on recherche dans le reste de la liste
 *   la cellule ayant le minimum de points de vie. Si ce minimum est différent
 *   de la cellule courante, on échange leurs données via swapData(). On avance
 *   ensuite jusqu'à la fin de la liste. On ne change pas la structure des chaînages ;
 *   seules les données pointées par `pdata` sont permutées.
 */
TListePlayer sortListPlayer(TListePlayer *player){
	T_cell *current = *player;
	
	while(current != NULL){
		T_cell* min = current;
		T_cell* next_Cell = current -> suiv;
		while (next_Cell != NULL){
			if (next_Cell -> pdata ->pointsDeVie < min -> pdata -> pointsDeVie)
			{
			min = next_Cell;
			}
			next_Cell = next_Cell -> suiv;
		}
		if (min != current){
			swapData(current, min);
		}
		current = current -> suiv;
	}
	
	return *player;
}


void combat(SDL_Surface *surface, Tunite *UniteAttaquante, Tunite *UniteCible);