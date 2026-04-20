#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL.h"
#include "towerdefend.h"
#include "maSDL.h"


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

/*int **initChemin(){
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
}*/

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
    nouv -> nom = tourSol;
    nouv -> cibleAttaquable = sol;
    nouv -> maposition = sol;
    nouv -> pointsDeVie = 500;
    nouv -> vitesseAttaque = 1.5;
    nouv -> degats = 120;
    nouv -> portee = 5;
    nouv -> vitessedeplacement = 0;
    nouv -> posX = posx;
    nouv -> posY = posy;
    nouv -> peutAttaquer = 1;
    nouv -> indiceParcours = -1;
    //nouv -> cible = NULL;
    return nouv;
}

Tunite *creeTourAir(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv -> nom = tourAir;
    nouv -> cibleAttaquable = air;
    nouv -> maposition = sol;
    nouv -> pointsDeVie = 500;
    nouv -> vitesseAttaque = 1.0;
    nouv -> degats = 100;
    nouv -> portee = 3;
    nouv -> vitessedeplacement = 0;
    nouv -> posX = posx;
    nouv -> posY = posy;
    nouv -> peutAttaquer = 1;
    nouv -> indiceParcours = -1;
    //nouv -> cible = NULL;
    return nouv;
}

Tunite *creeTourRoi(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv -> nom = tourRoi;
    nouv -> cibleAttaquable = solEtAir;
    nouv -> maposition = sol;
    nouv -> pointsDeVie = 800;
    nouv -> vitesseAttaque = 1.2;
    nouv -> degats = 180;
    nouv -> portee = 4;
    nouv -> vitessedeplacement = 0;
    nouv -> posX = posx;
    nouv -> posY = posy;
    nouv -> peutAttaquer = 1;
    nouv -> indiceParcours = -1;
    //nouv -> cible = NULL;
    return nouv;
}


Tunite *creeDragon(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv -> nom = dragon;
    nouv -> cibleAttaquable = solEtAir;
    nouv -> maposition = air;
    nouv -> pointsDeVie = 200;
    nouv -> vitesseAttaque = 1.1;
    nouv -> degats = 180;
    nouv -> portee = 2;
    nouv -> vitessedeplacement = 2;
    nouv -> posX = posx;
    nouv -> posY = posy;
    nouv -> peutAttaquer = 1;
    nouv -> indiceParcours = 0;
    //nouv -> cible = NULL;
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
    nouv -> indiceParcours = 0;   
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
    nouv -> indiceParcours = 0;    
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
    nouv -> peutAttaquer = 1;
    nouv -> indiceParcours = 0;
    //nouv -> cible = NULL;
    return nouv;
}


//====================================================================
//                      FONCTION NOYAU
//====================================================================


/**
 * Objectif   : Vérifier si la tour du roi a été détruite.
 * Algorithme : Vérification directe sur le pointeur et les points de vie.
 * Complexité : Temps O(1) | Espace O(1)
 *
 * @param tourRoi Pointeur vers l'unité représentant le roi.
 * @return        True si le roi est détruit ou absent, false sinon.
 *
 * Fonctionnement :
 * On considère le roi comme détruit si son pointeur est NULL 
 * ou si ses points de vie sont tombés à 0 (ou moins).
 */
bool tourRoiDetruite(Tunite *tourRoi){
    if (tourRoi == NULL){
        return true;
    }

    if (tourRoi -> pointsDeVie <= 0){
        return true;
    }

    return false;
}


/**
 * Objectif   : Insère une unité en tête de la liste chaînée d'un joueur
 * Algorithme : Insertion standart en tête de liste
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
 * Objectif   : Retourner la liste de toutes les unités ennemies à portée d'attaque
 * Algorithme : Double boucle sur le plateau avec filtre distance + camp + type de cible
 * Complexité : Temps O(n*m) | Espace O(k) avec k = nombre de cibles valides
 *
 * @param jeu              Plateau de jeu (tableau 2D de pointeurs)
 * @param UniteAttaquante  Pointeur vers l'unité qui attaque
 * @return                 Liste chaînée des unités ennemies attaquables
 *
 * Fonctionnement :
 *   On commence par déterminer si l'attaquant est une tour (roi/sol/air).
 *   On parcourt ensuite chaque case du plateau ; pour chaque unité présente,
 *   on calcule la distance de Manhattan entre elle et l'attaquant.
 *   Une cible est ajoutée au résultat si et seulement si :
 *     - elle est dans la portée de l'attaquant,
 *     - elle n'est pas l'attaquant lui-même,
 *     - elle appartient au camp adverse (anti-tir allié),
 *     - son type de position correspond à ce que l'attaquant peut cibler.
 */
TListePlayer quiEstAPortee(TplateauJeu jeu, Tunite *UniteAttaquante){
    TListePlayer resultat = NULL;
    int distance = 0;
    Tunite *cible;

    int attaquantEstRoi = (UniteAttaquante->nom == tourSol || UniteAttaquante->nom == tourAir || UniteAttaquante->nom == tourRoi);

    for(int i = 0; i < LARGEURJEU; i++){
        for(int j = 0; j < HAUTEURJEU; j++){
            if(jeu[i][j] != NULL){
               cible = jeu[i][j];
               distance = abs(cible->posX - UniteAttaquante->posX) + abs(cible->posY - UniteAttaquante->posY);
        
                int cibleEstRoi = (cible->nom == tourSol || 
                                   cible->nom == tourAir || 
                                   cible->nom == tourRoi);

                if (distance <= UniteAttaquante -> portee && 
                    (cible != UniteAttaquante) && 
                    (attaquantEstRoi != cibleEstRoi) && // ANTI-TIR ALLIÉ 
                    (UniteAttaquante -> cibleAttaquable == cible -> maposition || UniteAttaquante -> cibleAttaquable == solEtAir )){
                    
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


/**
 * Objectif   : Résoudre un combat entre une unité attaquante et une unité cible
 * Algorithme : Soustraction directe des dégâts avec clamp à 0
 * Complexité : Temps O(1) | Espace O(1)
 *
 * @param surface          Surface SDL sur laquelle afficher l'animation d'attaque
 * @param UniteAttaquante  Pointeur vers l'unité qui attaque
 * @param UniteCible       Pointeur vers l'unité qui reçoit les dégâts
 *
 * Fonctionnement :
 *   On vérifie d'abord que l'unité attaquante peut agir (peutAttaquer == 1)
 *   et que la cible est encore en vie (pointsDeVie > 0). Si les conditions
 *   sont remplies, on soustrait les dégâts de l'attaquant aux points de vie
 *   de la cible, en les limitant à 0 pour éviter toute valeur négative.
 *   L'attaquant est ensuite marqué comme ayant déjà agi (peutAttaquer = 0)
 *   et l'animation d'attaque est déclenchée via dessineAttaque().
 */
void combat(SDL_Surface *surface, Tunite *UniteAttaquante, Tunite *UniteCible)
{
	if (UniteAttaquante -> peutAttaquer == 1 && UniteCible -> pointsDeVie > 0)
    {
		UniteCible -> pointsDeVie -= UniteAttaquante -> degats;
		
        if (UniteCible -> pointsDeVie < 0){
             UniteCible -> pointsDeVie = 0;
        }
		
        UniteAttaquante -> peutAttaquer = 0;
		
        dessineAttaque(surface, UniteAttaquante, UniteCible);
	}

}


/**
 * Objectif   : Réinitialiser le droit d'attaque de toutes les unités d'un joueur
 *              en début de tour, afin que chacune puisse agir une fois par round.
 * Algorithme : Parcours linéaire de la liste chaînée
 * Complexité : Temps O(n) | Espace O(1)
 *
 * @param player  Tête de la liste chaînée du joueur à réinitialiser
 *
 * Fonctionnement :
 *   On parcourt chaque cellule de la liste. Pour chaque unité rencontrée,
 *   on remet le champ `peutAttaquer` à 1 (vrai). Cette fonction doit être
 *   appelée en début de chaque nouveau tour, avant la phase de combat,
 *   pour que les unités dont la valeur a été mise à 0 lors du tour précédent
 *   puissent de nouveau agir.
 */
void reinitialiserAttaques(TListePlayer player){
    T_cell* current = player;
    while (current != NULL){
        current->pdata->peutAttaquer = 1;
            current = current -> suiv;
    }
}


/**
 * Objectif   : Avancer chaque unité de la horde d'une case sur le parcours prédéfini
 * Algorithme : Parcours linéaire de la liste + accès direct au tableau de chemin
 * Complexité : Temps O(n) | Espace O(1)
 *
 * @param player      Tête de la liste chaînée de la horde à déplacer
 * @param tabParcours Tableau 2D des coordonnées du chemin (index → {x, y})
 * @param jeu         Plateau de jeu (tableau 2D de pointeurs vers Tunite)
 *
 * Fonctionnement :
 *   On parcourt toute la liste de la horde. Pour chaque unité, on lit son
 *   `indiceParcours`. Si l'unité n'a pas;encore atteint la fin du chemin (i < NBCOORDPARCOURS - 1), 
 *   on lit les coordonnées de la prochaine case dans tabParcours[i+1]. Le déplacement
 *   n'est effectué que si la case de destination est libre (jeu[x][y] == NULL),
 *   afin d'éviter les collisions entre unités. Lorsque le déplacement est validé,
 *   on met à jour posX, posY et indiceParcours de l'unité.
 *
 *
 */
void deplacerHorde(TListePlayer player, int **tabParcours, TplateauJeu jeu){
    T_cell *current = player;
    while(current != NULL){
        int i = current->pdata->indiceParcours;
        if(i < NBCOORDPARCOURS - 1){
        int prochainX = tabParcours[i+1][0];
        int prochainY = tabParcours[i+1][1];
        if(jeu[prochainX][prochainY] == NULL){
            current->pdata->posX = prochainX;
            current->pdata->posY = prochainY;
            current->pdata->indiceParcours = i+1;
            }  
        }  
    current = current->suiv;
    }
}


/**
 * Objectif   : Résoudre l'intégralité d'un round de combat entre les tours du roi
 *              et la horde ennemie, en deux phases successives.
 * Algorithme : Double parcours de liste chaînée + appels à quiEstAPortee / combat
 * Complexité : Temps O(n * L²) | Espace O(k)  avec n = nb d'unités, L = dimension
 *              du plateau, k = nb de cibles à portée
 *
 * @param roi      Pointeur vers la tête de liste des unités du roi (tours)
 * @param horde    Pointeur vers la tête de liste des unités ennemies
 * @param jeu      Plateau de jeu (tableau 2D de pointeurs vers Tunite)
 * @param surface  Surface SDL pour l'affichage des animations d'attaque
 *
 * Fonctionnement :
 *   Phase 1 — Tours du roi attaquent la horde :
 *     On parcourt chaque tour du roi. Si elle peut attaquer (peutAttaquer == 1),
 *     on récupère la liste des cibles à portée via quiEstAPortee(). La liste est
 *     triée par PV croissants (priorité aux unités les plus faibles). La tour
 *     attaque la première cible. Si celle-ci tombe à 0 PV, elle est supprimée
 *     de la liste horde et du plateau via SupprimerUnite(). La liste temporaire
 *     de cibles (T_cell uniquement, pas les pdata) est libérée après usage.
 *
 *   Phase 2 — Horde attaque les tours du roi :
 *     Même logique en sens inverse : chaque unité de la horde cherche une cible
 *     parmi les tours du roi. On sauvegarde `suivant` avant la boucle interne
 *     car la cellule courante peut être supprimée si elle est elle-même la cible
 *     d'une contre-attaque dans un autre appel (précaution défensive).
 */
void phaseCombat(TListePlayer* roi, TListePlayer* horde, TplateauJeu jeu, SDL_Surface* surface) {
    // Phase 1 : tours du roi → attaquent la horde
    T_cell *tourCourante = *roi;

    while (tourCourante != NULL) {
        Tunite *attaquant = tourCourante->pdata;

        if (attaquant->peutAttaquer == 1) {
            TListePlayer ciblesAPortee = quiEstAPortee(jeu, attaquant);

            if (ciblesAPortee != NULL) {
                sortListPlayer(&ciblesAPortee);
                Tunite *cible = ciblesAPortee->pdata;
                combat(surface, attaquant, cible);

                if (cible->pointsDeVie == 0) {
                    SupprimerUnite(horde, cible, jeu);
                }

                /* Libère uniquement les T_cell temporaires, pas les pdata */
                T_cell *tmp;
                while (ciblesAPortee != NULL) {
                    tmp = ciblesAPortee->suiv;
                    free(ciblesAPortee);
                    ciblesAPortee = tmp;
                }
            }
        }
        tourCourante = tourCourante->suiv;
    }

    // Phase 2 : horde → attaque la tour du roi
    T_cell *hordeCourante = *horde;

    while (hordeCourante != NULL) {
        T_cell *suivant = hordeCourante->suiv;
        Tunite *attaquant = hordeCourante->pdata;
        
        if (attaquant->peutAttaquer == 1) {
            TListePlayer ciblesAPortee = quiEstAPortee(jeu, attaquant);

            if (ciblesAPortee != NULL) {
                sortListPlayer(&ciblesAPortee);
                Tunite *cible = ciblesAPortee->pdata;
                combat(surface, attaquant, cible);

                TListePlayer cibleCourante = ciblesAPortee;
                while(cibleCourante != NULL){
                    if(cibleCourante -> pdata -> nom == tourRoi){
                        combat(surface, attaquant, cibleCourante -> pdata);
                        if(cibleCourante -> pdata -> pointsDeVie == 0){
                            SupprimerUnite(roi, cibleCourante -> pdata, jeu);
                        }
                        break;
                    }
                    cibleCourante = cibleCourante -> suiv;
                }
                

                T_cell *tmp;
                while (ciblesAPortee != NULL) {
                    tmp = ciblesAPortee->suiv;
                    free(ciblesAPortee);
                    ciblesAPortee = tmp;
                }
            }
        }

        hordeCourante = suivant;
    }
}


/**
 * Objectif   : Vérifier si une case (x, y) appartient au chemin emprunté par la horde.
 * Algorithme : Recherche linéaire dans le tableau de coordonnées du parcours.
 * Complexité : Temps O(NBCOORDPARCOURS) | Espace O(1)
 *
 * @param x           Coordonnée en abscisse de la case à tester.
 * @param y           Coordonnée en ordonnée de la case à tester.
 * @param tabParcours Tableau 2D des coordonnées du chemin (index → {x, y}).
 * @return            True si (x, y) figure parmi les cases du chemin, false sinon.
 *
 * Fonctionnement :
 *   On itère sur chaque entrée du tableau tabParcours. Dès qu'une paire de
 *   coordonnées correspond exactement à (x, y), on retourne immédiatement true.
 *   Si aucune correspondance n'est trouvée après le parcours complet, on retourne false.
 *   Cette fonction sert notamment à interdire le placement de tours sur le chemin
 *   de la horde lors de la phase de construction.
 */
bool estSurChemin(int x, int y, int **tabParcours) {
    for (int i = 0; i < NBCOORDPARCOURS; i++) {
        if (tabParcours[i][X] == x && tabParcours[i][Y] == y)
            return true;
    }
    return false;
}


/**
 * Objectif   : Générer aléatoirement un chemin valide que la horde empruntera
 *              du bas du plateau jusqu'à la zone du roi, en respectant des contraintes
 *              de cohérence directionnelle.
 * Algorithme : Marche aléatoire dirigée (haut prioritaire) avec règles anti-zigzag.
 * Complexité : Temps O(NBCOORDPARCOURS) | Espace O(NBCOORDPARCOURS)
 *
 * @return  Tableau 2D alloué dynamiquement de taille [NBCOORDPARCOURS][2],
 *          où chaque ligne contient les coordonnées {x, y} d'une case du chemin,
 *          dans l'ordre de progression. À libérer par l'appelant.
 *
 * Fonctionnement :
 *   On alloue le tableau de chemin puis on initialise le point de départ au
 *   centre bas du plateau (x = LARGEURJEU/2, y = HAUTEURJEU-1). À chaque étape,
 *   on choisit aléatoirement une direction (haut=0, droite=1, gauche=2) et une
 *   distance (1 à 4 cases). Plusieurs règles contraignent les choix :
 *     - Le tout premier mouvement est toujours vers le haut.
 *     - On ne peut pas enchaîner deux directions horizontales opposées sans
 *       au moins 2 cases de montée intermédiaires (anti-zigzag).
 *     - Si le mouvement choisi sort du plateau ou viole une contrainte, on
 *       replie sur un mouvement de secours (haut ou latéral vers le centre).
 *   Les cases de chaque segment sont écrites dans le tableau via les helpers
 *   ecritCheminVersleHaut(), ecritCheminVerslaDroite() et ecritCheminVerslaGauche().
 */
int **initChemin() {
    int **chemin = (int**)malloc(sizeof(int*) * NBCOORDPARCOURS);
    for(int j = 0; j < NBCOORDPARCOURS; j++){
        chemin[j] = (int*)malloc(sizeof(int) * 2);
    }

    int ydepart = HAUTEURJEU - 1;   // On commence tout en bas (18)
    int xdepart = LARGEURJEU / 2;   // On commence au milieu (5)
    int i = 0;                      // Compteur pour les cases du chemin
    int distanceMaxRestante = NBCOORDPARCOURS; 

    int premierMouvement = 1;
    int dernierDirHorizontale = 0; // 0 = rien, 1 = droite, 2 = gauche
    int casesHautDepuisHorizontale = 0;

    while (i < NBCOORDPARCOURS) {
        int choixDirection;
        
        int distance = (rand() % 4) + 2;

        if (distance > distanceMaxRestante) {
            distance = distanceMaxRestante;
        }

        // Le tout premier mouvement doit obligatoirement être vers le haut
        if (premierMouvement == 1) {
            choixDirection = 0; 
            premierMouvement = 0;
        } else {
            choixDirection = rand() % 3; 
        }

        int mouvementValide = 0; 

        
        if (choixDirection == 0) { 
            // C'est la direction HAUT
            if (ydepart - distance >= 0) {
                mouvementValide = 1;
            } else if (ydepart > 0) {
                distance = ydepart; 
                mouvementValide = 1;
            }
        } 
        else if (choixDirection == 1) { 
            // C'est la direction DROITE
            if (xdepart + distance < LARGEURJEU) { 
                
                // Règle : on ne peut pas aller à droite si on vient d'aller à gauche
                if (dernierDirHorizontale != 2) {
                    mouvementValide = 1;
                } else if (casesHautDepuisHorizontale >= 2) {
                    mouvementValide = 1;
                }
            }
        } 
        else if (choixDirection == 2) { 
            if (xdepart - distance >= 0) { 
                
                // Règle : on ne peut pas aller à gauche si on vient d'aller à droite
                if (dernierDirHorizontale != 1) {
                    mouvementValide = 1;
                } else if (casesHautDepuisHorizontale >= 2) {
                    mouvementValide = 1;
                }
            }
        }

        if (mouvementValide == 0) {
            if (ydepart == 0) {
                if (xdepart < LARGEURJEU / 2) {
                    choixDirection = 1; // On va à droite
                } else {
                    choixDirection = 2; // On va à gauche
                }
                distance = 1;
            } else {
                choixDirection = 0; 
                distance = 1; 
            }
            
            if (distance > distanceMaxRestante) {
                distance = distanceMaxRestante;
            }
        }

        if (choixDirection == 0) {
            ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, distance, &distanceMaxRestante);
            casesHautDepuisHorizontale = casesHautDepuisHorizontale + distance; 
        } 
        else if (choixDirection == 1) {
            ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, distance, &distanceMaxRestante);
            dernierDirHorizontale = 1;       
            casesHautDepuisHorizontale = 0; // On remet le compteur de montée à zéro
        } 
        else if (choixDirection == 2) {
            ecritCheminVerslaGauche(chemin, &i, &xdepart, &ydepart, distance, &distanceMaxRestante);
            dernierDirHorizontale = 2;       
            casesHautDepuisHorizontale = 0; 
        }

        distanceMaxRestante = NBCOORDPARCOURS - i;
    }

    return chemin;
}


/**
 * Objectif   : Sauvegarder l'état courant de la partie dans un fichier binaire
 *              ("partiebin.tdb") en sérialisant les unités du roi et de la horde.
 * Algorithme : Parcours séquentiel de deux listes chaînées avec écriture brute
 *              en mémoire (fwrite sur les structures Tunite).
 * Complexité : Temps O(N + M) | Espace O(1)
 *              où N = nb unités du roi, M = nb unités de la horde.
 *
 * @param listeRoi   Liste chaînée des unités appartenant au joueur roi.
 * @param listeHorde Liste chaînée des unités appartenant à la horde.
 *
 * Fonctionnement :
 *   On ouvre le fichier en écriture binaire, puis on parcourt d'abord la liste
 *   du roi pour compter ses unités. On écrit ce compteur en tête, puis on
 *   reparcourt la liste en sérialisant chaque Tunite via fwrite. On reproduit
 *   exactement le même processus pour la liste de la horde. Le fichier résultant
 *   a la structure : [nbRoi | unités roi... | nbHorde | unités horde...].
 */
void sauvegarderBinaire(TListePlayer listeRoi, TListePlayer listeHorde) {
    FILE *f = fopen("partiebin.tdb", "wb");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier binaire.\n");
        return;
    }

    // 1. Compter les unités du roi
    int nbRoi = 0;
    T_cell *courant = listeRoi;
    while (courant != NULL) {
        nbRoi++;
        courant = courant->suiv;
    }
    
    // 2. Ecrire le nombre puis les unités
    fwrite(&nbRoi, sizeof(int), 1, f);
    courant = listeRoi;
    while (courant != NULL) {
        fwrite(courant->pdata, sizeof(Tunite), 1, f);
        courant = courant->suiv;
    }

    // 3. Compter les unités de la horde
    int nbHorde = 0;
    courant = listeHorde;
    while (courant != NULL) {
        nbHorde++;
        courant = courant->suiv;
    }
    
    // 4. Ecrire le nombre puis les unités
    fwrite(&nbHorde, sizeof(int), 1, f);
    courant = listeHorde;
    while (courant != NULL) {
        fwrite(courant->pdata, sizeof(Tunite), 1, f);
        courant = courant->suiv;
    }

    fclose(f);
    printf("Sauvegarde binaire reussie !\n");
}


/**
 * Objectif   : Restaurer l'état d'une partie depuis un fichier binaire
 *              ("partiebin.tdb") en reconstruisant les listes du roi et de la horde,
 *              et en mettant à jour le plateau de jeu.
 * Algorithme : Vidage des listes existantes suivi d'une désérialisation séquentielle
 *              avec allocation dynamique pour chaque unité relue.
 * Complexité : Temps O(N + M) | Espace O(N + M)
 *              où N = nb unités du roi, M = nb unités de la horde.
 *
 * @param listeRoi   Pointeur vers la liste du roi (sera vidée puis reconstruite).
 * @param listeHorde Pointeur vers la liste de la horde (sera vidée puis reconstruite).
 * @param jeu        Plateau de jeu 2D dont les cases sont remises à NULL lors du
 *                   vidage, puis implicitement repeuplées par AjouterUnite.
 *
 * Fonctionnement :
 *   On commence par libérer intégralement les deux listes courantes : pour chaque
 *   cellule, on remet à NULL la case du plateau pointée par l'unité, on libère la
 *   Tunite puis la cellule elle-même. On lit ensuite le fichier binaire : d'abord
 *   le nombre d'unités du roi, puis chaque Tunite allouée dynamiquement est
 *   désérialisée via fread et insérée dans listeRoi par AjouterUnite. On répète
 *   l'opération pour la horde.
 */
void chargerBinaire(TListePlayer *listeRoi, TListePlayer *listeHorde, TplateauJeu jeu) {
    FILE *f = fopen("partiebin.tdb", "rb");
    if (f == NULL) {
        printf("Erreur : fichier binaire introuvable.\n");
        return;
    }

    while (*listeRoi != NULL) {
        T_cell *tmp = *listeRoi;
        if (jeu != NULL && tmp->pdata != NULL) jeu[tmp->pdata->posX][tmp->pdata->posY] = NULL;
        *listeRoi = (*listeRoi)->suiv;
        free(tmp->pdata);
        free(tmp);
    }
    while (*listeHorde != NULL) {
        T_cell *tmp = *listeHorde;
        if (jeu != NULL && tmp->pdata != NULL) jeu[tmp->pdata->posX][tmp->pdata->posY] = NULL;
        *listeHorde = (*listeHorde)->suiv;
        free(tmp->pdata);
        free(tmp);
    }

    int nbRoi = 0, nbHorde = 0;

    fread(&nbRoi, sizeof(int), 1, f);
    for (int i = 0; i < nbRoi; i++) {
        Tunite *u = (Tunite *)malloc(sizeof(Tunite));
        fread(u, sizeof(Tunite), 1, f);
        AjouterUnite(listeRoi, u);
    }

    fread(&nbHorde, sizeof(int), 1, f);
    for (int i = 0; i < nbHorde; i++) {
        Tunite *u = (Tunite *)malloc(sizeof(Tunite));
        fread(u, sizeof(Tunite), 1, f);
        AjouterUnite(listeHorde, u); 
    }

    fclose(f);
    printf("Chargement binaire reussi !\n");
}


/**
 * Objectif   : Sauvegarder l'état courant de la partie dans un fichier texte
 *              lisible ("partieseq.tds") en écrivant les champs de chaque unité
 *              sous forme de valeurs séparées par des espaces.
 * Algorithme : Parcours séquentiel de deux listes chaînées avec écriture formatée
 *              champ par champ via fprintf.
 * Complexité : Temps O(N + M) | Espace O(1)
 *              où N = nb unités du roi, M = nb unités de la horde.
 *
 * @param listeRoi   Liste chaînée des unités appartenant au joueur roi.
 * @param listeHorde Liste chaînée des unités appartenant à la horde.
 *
 * Fonctionnement :
 *   On ouvre le fichier en mode texte puis on parcourt la liste du roi pour en
 *   compter les éléments. Ce compteur est écrit en première ligne, suivi d'une
 *   ligne par unité listant ses 12 champs (nom, cible, position, PV, vitesses,
 *   dégâts, portée, coordonnées, etc.). Le même traitement est appliqué à la
 *   liste de la horde. Le format résultant est : [nbRoi\n lignes roi... nbHorde\n
 *   lignes horde...], intégralement ré-interprétable par chargerSequentielle.
 */
void sauvegarderSequentielle(TListePlayer listeRoi, TListePlayer listeHorde) {
    FILE *f = fopen("partieseq.tds", "w");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier texte.\n");
        return;
    }

    // sauvegarde du roi
    int nbRoi = 0;
    T_cell *courant = listeRoi;
    while (courant != NULL) {
        nbRoi++;
        courant = courant->suiv;
    }
    fprintf(f, "%d\n", nbRoi); 

    courant = listeRoi;
    while (courant != NULL) {
        Tunite *u = courant->pdata;
        fprintf(f, "%d %d %d %d %f %d %d %f %d %d %d %d\n",
                u->nom, u->cibleAttaquable, u->maposition, u->pointsDeVie,
                u->vitesseAttaque, u->degats, u->portee, u->vitessedeplacement,
                u->posX, u->posY, u->peutAttaquer, u->indiceParcours);
        courant = courant->suiv;
    }

    // sauvegarde de la horde
    int nbHorde = 0;
    courant = listeHorde;
    while (courant != NULL) {
        nbHorde++;
        courant = courant->suiv;
    }
    fprintf(f, "%d\n", nbHorde);

    courant = listeHorde;
    while (courant != NULL) {
        Tunite *u = courant->pdata;
        fprintf(f, "%d %d %d %d %f %d %d %f %d %d %d %d\n",
                u->nom, u->cibleAttaquable, u->maposition, u->pointsDeVie,
                u->vitesseAttaque, u->degats, u->portee, u->vitessedeplacement,
                u->posX, u->posY, u->peutAttaquer, u->indiceParcours);
        courant = courant->suiv;
    }

    fclose(f);
    printf("Sauvegarde sequentielle (.tds) reussie !\n");
}


/**
 * Objectif   : Restaurer l'état d'une partie depuis un fichier texte séquentiel
 *              ("partieseq.tds") en reconstruisant les listes du roi et de la horde,
 *              et en mettant à jour le plateau de jeu.
 * Algorithme : Vidage des listes existantes suivi d'une lecture formatée champ par
 *              champ via fscanf, avec allocation dynamique pour chaque unité relue.
 * Complexité : Temps O(N + M) | Espace O(N + M)
 *              où N = nb unités du roi, M = nb unités de la horde.
 *
 * @param listeRoi   Pointeur vers la liste du roi (sera vidée puis reconstruite).
 * @param listeHorde Pointeur vers la liste de la horde (sera vidée puis reconstruite).
 * @param jeu        Plateau de jeu 2D dont les cases sont remises à NULL lors du
 *                   vidage, puis implicitement repeuplées par AjouterUnite.
 *
 * Fonctionnement :
 *   On commence par libérer les deux listes courantes en remettant à NULL chaque
 *   case du plateau associée. On lit ensuite le nombre d'unités du roi via fscanf,
 *   puis pour chacune on alloue une Tunite, on lit ses 12 champs (les champs de
 *   type enum sont lus dans des temporaires entiers puis réaffectés), et on
 *   l'insère dans listeRoi. Le même processus est répété pour la horde. La
 *   vérification du retour de fscanf sur les compteurs protège contre un fichier
 *   vide ou corrompu.
 */
void chargerSequentielle(TListePlayer *listeRoi, TListePlayer *listeHorde, TplateauJeu jeu) {
    FILE *f = fopen("partieseq.tds", "r");
    if (f == NULL) {
        printf("Erreur : fichier sequentiel introuvable.\n");
        return;
    }

    while (*listeRoi != NULL) {
        T_cell *tmp = *listeRoi;
        if (jeu != NULL && tmp->pdata != NULL) jeu[tmp->pdata->posX][tmp->pdata->posY] = NULL;
        *listeRoi = (*listeRoi)->suiv;
        free(tmp->pdata);
        free(tmp);
    }
    while (*listeHorde != NULL) {
        T_cell *tmp = *listeHorde;
        if (jeu != NULL && tmp->pdata != NULL) jeu[tmp->pdata->posX][tmp->pdata->posY] = NULL;
        *listeHorde = (*listeHorde)->suiv;
        free(tmp->pdata);
        free(tmp);
    }

    int nbRoi, nbHorde;
    int tNom, tCible, tPos; 

    if (fscanf(f, "%d", &nbRoi) == 1) {
        for (int i = 0; i < nbRoi; i++) {
            Tunite *u = (Tunite *)malloc(sizeof(Tunite));
            fscanf(f, "%d %d %d %d %f %d %d %f %d %d %d %d",
                   &tNom, &tCible, &tPos, &u->pointsDeVie,
                   &u->vitesseAttaque, &u->degats, &u->portee, &u->vitessedeplacement,
                   &u->posX, &u->posY, &u->peutAttaquer, &u->indiceParcours);
            u->nom = tNom;
            u->cibleAttaquable = tCible;
            u->maposition = tPos;
            AjouterUnite(listeRoi, u);
        }
    }

    if (fscanf(f, "%d", &nbHorde) == 1) {
        for (int i = 0; i < nbHorde; i++) {
            Tunite *u = (Tunite *)malloc(sizeof(Tunite));
            fscanf(f, "%d %d %d %d %f %d %d %f %d %d %d %d",
                   &tNom, &tCible, &tPos, &u->pointsDeVie,
                   &u->vitesseAttaque, &u->degats, &u->portee, &u->vitessedeplacement,
                   &u->posX, &u->posY, &u->peutAttaquer, &u->indiceParcours);
            u->nom = tNom;
            u->cibleAttaquable = tCible;
            u->maposition = tPos;
            AjouterUnite(listeHorde, u);
        }
    }

    fclose(f);
    printf("Chargement sequentiel (.tds) reussi !\n");
}


/**
 * Objectif   : Rechercher et retourner le pointeur vers l'unité de type "tour du roi"
 *              dans la liste des unités du joueur roi.
 * Algorithme : Parcours linéaire de la liste chaînée avec comparaison du champ nom.
 * Complexité : Temps O(N) | Espace O(1)
 *              où N = nombre d'unités dans listeRoi.
 *
 * @param listeRoi Liste chaînée des unités appartenant au joueur roi.
 * @return         Pointeur vers la Tunite dont le champ nom vaut tourRoi,
 *                 ou NULL si aucune unité correspondante n'est trouvée.
 *
 * Fonctionnement :
 *   On parcourt la liste cellule par cellule en comparant le champ nom de chaque
 *   Tunite à la constante tourRoi. Dès qu'une correspondance est trouvée, on
 *   retourne directement le pointeur pdata associé. Si la liste est épuisée sans
 *   correspondance (tour détruite ou liste vide), on retourne NULL, ce qui permet
 *   à l'appelant de détecter une condition de fin de partie.
 */
Tunite* trouverTourRoi(TListePlayer listeRoi){
    T_cell *current = listeRoi;
    while(current != NULL){
        if(current->pdata->nom == tourRoi)
            return current->pdata;
        current = current->suiv;
    }
    return NULL;
}