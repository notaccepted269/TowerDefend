//NOM pr�nom �tudiant 1 : MOHAMED Rayane
//NOM pr�nom �tudiant 2 : LOUIBA Angel

#include "SDL.h"
#include "maSDL.h"    //biblioth�que avec des fonctions d'affichage utilisant la SDL
#include "towerdefend.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



/*--------- Main ---------------------*/
int main(int argc, char* argv[])
{
    srand(time(NULL));
    SDL_Window *pWindow;
    SDL_Init(SDL_INIT_VIDEO);

    pWindow = SDL_CreateWindow(
        "Appuyez sur ECHAP pour quitter, S/C ET D/V les gerer les sauvegardes",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        LARGEURJEU*40,
        HAUTEURJEU*40,
        SDL_WINDOW_SHOWN
    );

    //SDL_Renderer * renderer = SDL_CreateRenderer(pWindow, -1, 0);  //non utilis�, pour m�moire

    SDL_Surface* pWinSurf = SDL_GetWindowSurface(pWindow);  //le sprite qui couvre tout l'�cran
    SDL_Surface* pSpriteTourSol = SDL_LoadBMP("./data/TourSol.bmp");  //indice 0 dans tabSprite (via l'enum TuniteDuJeu)
    SDL_Surface* pSpriteTourAir = SDL_LoadBMP("./data/TourAir.bmp");  //indice 1 dans tabSprite (via l'enum TuniteDuJeu)
    SDL_Surface* pSpriteTourRoi = SDL_LoadBMP("./data/TourRoi.bmp"); //indice 2
    SDL_Surface* pSpriteArcher = SDL_LoadBMP("./data/Archer.bmp"); //indice 3
    SDL_Surface* pSpriteChevalier = SDL_LoadBMP("./data/Chevalier.bmp"); //indice 4
    SDL_Surface* pSpriteDragon = SDL_LoadBMP("./data/Dragon.bmp"); //indice 5
    SDL_Surface* pSpriteGargouille = SDL_LoadBMP("./data/Gargouille.bmp"); //indice 6
    SDL_Surface* pSpriteEau = SDL_LoadBMP("./data/Eau.bmp"); //indice 7  Ne figure pas dans l'enum TuniteDuJeu
    SDL_Surface* pSpriteHerbe = SDL_LoadBMP("./data/Herbe.bmp"); //indice 8 idem
    SDL_Surface* pSpritePont = SDL_LoadBMP("./data/Pont.bmp"); //indice 9 idem
    SDL_Surface* pSpriteTerre = SDL_LoadBMP("./data/Terre.bmp"); //indice 10 idem

    // ASTUCE : on stocke le sprite d'une unit� � l'indice de son nom dans le type enum TuniteDuJeu, dans le tableau TabSprite
    // SAUF pour l'Eau, l''herbe et le pont qui apparaitront en l absence d'unit� (NULL dans le plateau) et en foction de certains indices x,y d�finissant le chemin central
    SDL_Surface* TabSprite[11]={pSpriteTourSol,pSpriteTourAir,pSpriteTourRoi,pSpriteArcher,pSpriteChevalier,pSpriteDragon,pSpriteGargouille,pSpriteEau,pSpriteHerbe,pSpritePont,pSpriteTerre};

    int** tabParcours=initChemin();  //tabParcours est un tableau de NBCOORDPARCOURS cases, chacune contenant un tableau � 2 cases (indice 0 pour X, indice 1 pour Y)

    if ( pSpriteTourSol )  //si le permier sprite a bien �t� charg�, on suppose que les autres aussi
    {
        TplateauJeu jeu = AlloueTab2D(LARGEURJEU,HAUTEURJEU);
        initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
        affichePlateauConsole(jeu,LARGEURJEU,HAUTEURJEU);



        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
        maj_fenetre(pWindow);


        //A COMMENTER quand vous en aurez assez de cliquer sur ces popups ^^

        //message("Welcome in TowerDfend","Ceci est un point de depart pour votre future interface de votre jeu TowerDefend");
        //message("et fin","ECHAP->quitter, S/C ET D/V les gerer les sauvegardes");

        /**********************************************************************/
        /*                                                                    */
        /*              DEFINISSEZ/INITIALISER ICI VOS VARIABLES              */

        TListePlayer listeRoi = NULL;
        TListePlayer listeHorde = NULL;
        Tunite *tourRoi = creeTourRoi(tabParcours[NBCOORDPARCOURS-1][0], tabParcours[NBCOORDPARCOURS-1][1]);
        AjouterUnite(&listeRoi, tourRoi); 
        int compteur_tour = 0;
  

        /*
        // FIN de vos variables                                               */
        /**********************************************************************/

        // boucle principale du jeu
        int cont = 1;
        while ( cont != 0 ){   //VOUS DEVEZ GERER (DETECTER) LA FIN DU JEU -> tourRoiDetruite
                SDL_PumpEvents(); //do events
                efface_fenetre(pWinSurf);
                /***********************************************************************/
                /*                                                                     */
                /*                                                                     */
                //APPELEZ ICI VOS FONCTIONS QUI FONT EVOLUER LE JEU

                initPlateauAvecNULL(jeu, LARGEURJEU, HAUTEURJEU);
                PositionnePlayerOnPlateau(listeRoi, jeu);
                PositionnePlayerOnPlateau(listeHorde, jeu);
                prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                

                //Probabilité d'apparition de la horde
                int probabilite_horde = 5 + rand() % (60 - 5 + 1);
                if ((rand() % 100) < probabilite_horde){
                        if(jeu[tabParcours[0][0]][tabParcours[0][1]] == NULL){
                                int type = rand() % 4;
                                switch (type)
                                {
                                case 0: AjouterUnite(&listeHorde, creeDragon(tabParcours[0][0], tabParcours[0][1]));
                                        break;
                                case 1: AjouterUnite(&listeHorde, creeArcher(tabParcours[0][0], tabParcours[0][1]));
                                        break;
                                case 2: AjouterUnite(&listeHorde, creeGargouille(tabParcours[0][0], tabParcours[0][1]));
                                        break;                                                                              
                                case 3: AjouterUnite(&listeHorde, creeChevalier(tabParcours[0][0], tabParcours[0][1]));
                                        break;                               
                                }
                        }
                }



                //Probabilité d'apparition des tours
                // Génère une probabilité aléatoire entre 15 et 50 pour l'apparition d'une tour
                int probabilite_tour = 15 + rand() % (50 - 15 + 1);
                
                // Si le nombre aléatoire est inférieur à la probabilité ET que le tour est un multiple de 5
                // (permets d'espacer les apparitions de tours)
                if ((rand () % 100) < probabilite_tour && compteur_tour % 5 == 0){
                                // Directions possibles : droite, gauche, bas, haut
                                int dx[] = {1, -1, 0, 0};
                                int dy[] = {0, 0, 1, -1};
                                
                                // Tableaux pour stocker les positions valides autour du chemin
                                int validX[NBCOORDPARCOURS * 4];
                                int validY[NBCOORDPARCOURS * 4];
                                int nbValides = 0;

                                // Parcourt tous les points du chemin pour trouver les cases adjacentes valides
                                for (int i = 0; i < NBCOORDPARCOURS; i++) {
                                                for (int d = 0; d < 4; d++) {
                                                                // Calcule la position adjacente
                                                                int nx = tabParcours[i][X] + dx[d];
                                                                int ny = tabParcours[i][Y] + dy[d];

                                                                // Vérifie que la case est dans les limites du plateau
                                                                if (nx < 0 || nx >= LARGEURJEU || ny < 0 || ny >= HAUTEURJEU) continue;
                                                                // Vérifie que la case n'est pas sur le chemin
                                                                if (estSurChemin(nx, ny, tabParcours)) continue;
                                                                // Vérifie que la case est vide (pas déjà occupée par une unité)
                                                                if (jeu[nx][ny] != NULL) continue;

                                                                // Évite les doublons dans la liste des positions valides
                                                                bool dejaVu = false;
                                                                for (int k = 0; k < nbValides; k++)
                                                                                if (validX[k] == nx && validY[k] == ny) { dejaVu = true; break; }
                                                                if (!dejaVu) { validX[nbValides] = nx; validY[nbValides++] = ny; }
                                                }
                                }

                                // Si au moins une position valide existe, on place une tour
                                if (nbValides > 0) {
                                                // Choisit aléatoirement une des positions valides
                                                int choixCase = rand() % nbValides;
                                                Tunite * tour  = NULL;
                                                
                                                // Choix aléatoire du type de tour : Air ou Sol
                                                switch (rand() % 2){
                                                                case 0: tour = creeTourAir(validX[choixCase], validY[choixCase]);
                                                                                break;
                                                                case 1: tour = creeTourSol(validX[choixCase], validY[choixCase]);
                                                                                break;
                                                }

                                                // Ajoute la tour créée à la liste des unités du roi
                                                if(tour != NULL) {
                                                                AjouterUnite(&listeRoi, tour);
                                                }
                                }
                }
                // Incrémente le compteur de tours
                compteur_tour++;


                deplacerHorde(listeHorde, tabParcours, jeu);
                phaseCombat(&listeRoi, &listeHorde, jeu, pWinSurf);
                reinitialiserAttaques(listeRoi);
                reinitialiserAttaques(listeHorde);
                        /* dans votre fonction "combat" que vous appelerez ici, dans son code utiliser dessineAttaque

                //exemple d'appel de dessineAttaque (factice car les unit�s n'appartiennent pas ici � aucune liste d'unit� (ni � la horde ni au Roi)
                // c'est juste pour la d�mo, a supprimer donc
                */

                // utiliser dessineAttaque dans votre fonction de combat va vous obliger � ajouter un argument li� � la SDL
                // -> SDL_Surface *surface
                // regarder le prototype de dessineAttaque dans maSDL.c pour (mieux) comprendre
                if (tourRoiDetruite(tourRoi)){
                        cont = 0;
                }


                /*                                                                     */
                /*                                                                     */
                // FIN DE VOS APPELS
                /***********************************************************************/
                //affichage du jeu � chaque tour

                maj_fenetre(pWindow);
                SDL_Delay(150);  //valeur du d�lai � modifier �ventuellement


                //LECTURE DE CERTAINES TOUCHES POUR LANCER LES RESTAURATIONS ET SAUVEGARDES
                const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
                if ( pKeyStates[SDL_SCANCODE_V] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur D */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        //message("Sauvegarde","Placer ici votre fonction de restauration/sauvegarde");
                        chargerSequentielle(&listeRoi, &listeHorde, jeu);
                        PositionnePlayerOnPlateau(listeRoi, jeu);
                        PositionnePlayerOnPlateau(listeHorde, jeu);
                        message("Sauvegarde","Chargement de la sauvegarde sequentielle");
                        

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_C] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur C */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        //message("Sauvegarde","Placer ici votre fonction de restauration/sauvegarde");
                        chargerBinaire(&listeRoi, &listeHorde, jeu);
                        message("Sauvegarde","Chargement de la sauvegarde binaire");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_D] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appuye sur D */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        //message("Sauvegarde","Placer ici votre fonction de restauration/sauvegarde");
                        sauvegarderSequentielle(listeRoi, listeHorde);
                        message("Sauvegarde","Sauvergarde sequentielle en cours...");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_S] ){
                        /* Ajouter vos appels de fonctions ci-dessous qd le joueur appyue sur S */

                        // APPELEZ ICI VOTRE FONCTION DE SAUVEGARDE/RESTAURATION DEMANDEE
                        //message("Sauvegarde","Placer ici votre fonction de restauration/sauvegarde");
                        sauvegarderBinaire(listeRoi, listeHorde);
                        message("Sauvegarde","Sauvergarde binaire en cours...");


                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_ESCAPE] ){
                        cont = 0;  //sortie de la boucle
                }

        }
        //fin boucle du jeu

        SDL_FreeSurface(pSpriteTourSol); // Lib�ration de la ressource occup�e par le sprite
        SDL_FreeSurface(pSpriteTourAir);
        SDL_FreeSurface(pSpriteTourRoi);
        SDL_FreeSurface(pSpriteArcher);
        SDL_FreeSurface(pSpriteChevalier);
        SDL_FreeSurface(pSpriteDragon);
        SDL_FreeSurface(pSpriteGargouille);
        SDL_FreeSurface(pSpriteEau);
        SDL_FreeSurface(pSpriteHerbe);
        SDL_FreeSurface(pSpritePont);
        SDL_FreeSurface(pWinSurf);
    }
    else
    {
        fprintf(stdout,"�chec de chargement du sprite (%s)\n",SDL_GetError());
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    freeChemin(tabParcours);
    return 0;
}
