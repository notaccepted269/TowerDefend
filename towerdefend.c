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
        
                if (distance <= UniteAttaquante -> portee && (cible != UniteAttaquante) && (UniteAttaquante -> cibleAttaquable == cible -> maposition || UniteAttaquante -> cibleAttaquable == solEtAir )){
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

                /* Supprime la tour du roi si détruite */
                if (cible->pointsDeVie == 0) {

                    SupprimerUnite(roi, cible, jeu);
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

/* Objectif  : Vérifier si une case (x,y) appartient au chemin de la horde
 * Algorithme: Recherche linéaire dans tabParcours
 * Complexité: Temps O(NBCOORDPARCOURS) | Espace O(1)
 */
bool estSurChemin(int x, int y, int **tabParcours) {
    for (int i = 0; i < NBCOORDPARCOURS; i++) {
        if (tabParcours[i][X] == x && tabParcours[i][Y] == y)
            return true;
    }
    return false;
}


int **initChemin() {
    int **chemin = (int**)malloc(sizeof(int*) * NBCOORDPARCOURS);
    for(int j = 0; j < NBCOORDPARCOURS; j++){
        chemin[j] = (int*)malloc(sizeof(int) * 2);
    }

    int ydepart = HAUTEURJEU - 1;   // 18
    int xdepart = LARGEURJEU / 2;   // 5 = milieu de la fenetre de 11 de largeur (0-10)
    int i = 0;                      //parcourt les i cases du chemin
    int distanceMaxRestante = NBCOORDPARCOURS; 

    int premierMouvement = 1;
    int dernierDirHorizontale = 0;
    int casesHautDepuisHorizontale = 0;

    while( i < NBCOORDPARCOURS){
        int choixDirection;
        int distance = (rand() % 4) + 2; //choix de case entre 2 et 4 cases

        if(distance > distanceMaxRestante){
            distance = distanceMaxRestante;
        }

        // Pour que le chemin commence TOUJOURS par le haut
        if(premierMouvement){
            choixDirection = 0;
            premierMouvement = 0;
        } else {
            choixDirection = rand() % 3;
        }

        int mouvementValide = 0;
        if (choixDirection == 0){
            mouvementValide = 1;
        }   else if (choixDirection == 1){
                //Verifie qu'on ne depasse pas la limite ET qu'on ne fait pas demi-tour
                if ((xdepart + distance < LARGEURJEU) && (dernierDirHorizontale != 2 || casesHautDepuisHorizontale >= 2)){
                    mouvementValide = 1;
            }  
        }   else if (choixDirection == 2){
                //Verifie qu'on ne depasse pas la limite ET qu'on ne fait pas demi-tour
                if((xdepart - distance >= 0) && (dernierDirHorizontale != 1 || casesHautDepuisHorizontale >= 2)){
                    mouvementValide = 1;
            }
        }
        
        if (!mouvementValide) {
            choixDirection = 0; 
            distance = 1; 
            if (distance > distanceMaxRestante) distance = distanceMaxRestante;
        }

        if (choixDirection == 0) {
            ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, distance, &distanceMaxRestante);
            casesHautDepuisHorizontale += distance; 
        } 
        else if (choixDirection == 1) {
            ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, distance, &distanceMaxRestante);
            dernierDirHorizontale = 1;       
            casesHautDepuisHorizontale = 0;    
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

