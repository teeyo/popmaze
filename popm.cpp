#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "Labyrinthe.h"
#include "Cellule.h"
#include "Jeu.h"
#include "Joueur.h"
#include <ctime>
#include <string>
#include <cstdlib>
#include <sstream>
using namespace std;

// PROJET C++ / LPI Méknés 2011/2012

int main(int argc ,char* argv[] ) {
    //_DECLARATIONS ET INITIALISATIONS__________________________________________
    
    // Les initialisations des variables
    long score(0) , _pause(0) ;
    string joueur;
    const int pixel(50) ; // une constante contenant la largeur/longueur d'une cllule (50x50)
    SDL_Event event; // une variable SDL_Event qui va contenir les evenements
    srand(time(0)); // initialisation de srand pour générer des nombres aléatoire
    SDL_Surface  * cases[15] ={NULL}; // initialisation du tableau de cellules
    SDL_Surface *ecran(NULL) ; // initialisation de la surface principale (ecran)
    Labyrinthe laby; // instanciation d'un objet Labyrinthe
    int memo[laby.get_l()*laby.get_l()] , temp[4] , solution[14*14] = {-1} ; // initialisation d'un tableau
                                                    // pour les id des cellules 
                                                    //et un autre pour le tirage d'un nombre aléatoire
                                                    //le troisième pour stockage des id de la solution
    //_GENERATION DU LABYRINTHE_________________________________________________
    bool chemin(false);
    do {
        
        Labyrinthe l;
        l.initialiser_cellules();
        l.generation(memo,temp);
        l.affecter_types();
        if (l.verificateur_de_chemin()){
                                        chemin = true;
                                        laby = l ;
                                        }
        }while(!chemin);
    //laby.initialiser_cellules(); // initialisaer les cellules
//    laby.generation(memo,temp); // appel de la  fonction qui génère le labyrinthe
//    laby.affecter_types(); // affecter à chaque cellule son type
    
    //_DECLARATION ET INITIALISATION D'UN OBJET JEU_____________________________
    
    Jeu njeu; // initialisation d'un objet jeu
    njeu.charger_images(cases); // charger les images necessaire pour le dessin du labyrinthe
    if (SDL_Init(SDL_INIT_VIDEO) == -1 or TTF_Init() == -1) // initialiser la SDL et TTF
    {
        exit(EXIT_FAILURE); // cas d'erreur on quitte le programme
    }
    SDL_WM_SetIcon(IMG_Load("pix/ico.png"),NULL); // donner une icône à la fenêtre
    // fixer les dimensions et les propriétés de la fenêtre
    ecran = SDL_SetVideoMode((laby.get_l()*pixel), (laby.get_l()*pixel), 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
    if (ecran == NULL)
    {
        // en cas d'erreur on passe au mode plus bas de qualités vidéo "mode sans_echec"
        ecran = SDL_SetVideoMode((laby.get_l()*pixel), (laby.get_l()*pixel), 16, SDL_HWSURFACE | SDL_DOUBLEBUF );
        if ( ecran == NULL ) {
        exit(EXIT_FAILURE); // cas d'erreur en mode "sans_echec" on arrête le programme
        }
    }
    SDL_WM_SetCaption("PRINCE OF PERSIA MAZE - LPI JAVA/C++ - 2011/2012", NULL); // On donne un nome à la fenêtre
    
    //_SON ET MUSIQUE___________________________________________________________
    
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) // Initialiser l'API mixer
    {
    return EXIT_FAILURE;
    }
    // instancié un objet mix_music qui contiendra la musique à jouer plutard
    Mix_Music *in_game[5]={NULL}, *pop_menu(NULL);
    for ( int i = 0 ; i < 5 ;  i++ ){  // Charger la musique
        std::string nom_son = "";
        nom_son = "son/pop_ingame";
        std::stringstream num;
        num << i;
        nom_son += num.str() + ".mp3";
        in_game[i] = Mix_LoadMUS(nom_son.c_str());
        }
    
    pop_menu = Mix_LoadMUS("son/pop_menu.mp3");
    
    //_CACHER LE CURSEUR DURANT LE JEU__________________________________________
    
    SDL_ShowCursor(SDL_DISABLE);
    
    //_AFFICHAGE DES MENU_______________________________________________________
    
    njeu.afficher_entree(ecran); // affichage du menu d'entré
    bool rester = true;
    while (rester) // boucle principale
    {
    SDL_PollEvent(&event); // la boucle va continuer à s'exécuter même s'il n'y-a aucun évenement
                switch (event.key.keysym.sym){
                       case SDLK_SPACE:
                            rester = false; // si on clique sur Espace en sortira du menu
                            break;
                            }
                            njeu.appuyer_pour_continuer(ecran); // on continue d'invité le joueur à cliquer sur espace
                            }
    rester = true; // on réutilise la variable rester pour le menu suivant
    short i(2), m(0) ; // des variables utiles pour le menu principal
    bool stay(true) , f(true); // un autre boolean pour les sous-menu
    Mix_PlayMusic(pop_menu,-1); // on va lire la musique du menu principal
    while (rester) // boucle principale
    {
        SDL_WaitEvent(&event);
                switch (event.key.keysym.sym){
                       case SDLK_RETURN: // au clique sur entré on testera le contenu de "i"
                            switch (i) {
                                   case 2:
                                        njeu.menu_choix_joueur(ecran); // affichage du menu "choix du joueur"
                                        joueur = njeu.choix_joueur(2,ecran);
                                        while (stay){
                                              SDL_WaitEvent(&event);
                                              switch (event.key.keysym.sym){ //  choix du joueur
                                              case SDLK_RIGHT:
                                                   njeu.menu_choix_joueur(ecran); // affichage du menu "choix du joueur"
                                                   joueur = njeu.choix_joueur(4,ecran); // on sortira du menu
                                                   break; 
                                              case SDLK_LEFT:
                                                    njeu.menu_choix_joueur(ecran); // affichage du menu "choix du joueur"
                                                    joueur = njeu.choix_joueur(2,ecran); // on sortira du menu
                                                   break; 
                                              case SDLK_SPACE:
                                                   stay = false;
                                                   rester = false;
                                                   break;
                                              case SDLK_p :
                                                   Mix_PauseMusic();
                                                   break;
                                              case SDLK_r :
                                                   Mix_ResumeMusic(); 
                                                   break;
                                              default :
                                                      break;  
                                                      
                                              }
                                              if (Mix_PausedMusic() == 1)
                                              njeu.son_arrete(ecran); // si la musique est en pause on reprend sa lecture
                                              }
                                        stay = true ; // pour permettre le retour en arrière dans les menu
                                        f = true ;
                                        break;
                                   case 4: // le même fonctionement pour le sous-menu "option"
                                        njeu.afficher_option(ecran);
                                        while (stay){
                                              SDL_WaitEvent(&event);
                                              switch (event.key.keysym.sym){
                                              case SDLK_BACKSPACE:
                                                   stay = false;
                                                   njeu.choix_menu(i,ecran);
                                                   break;
                                              case SDLK_p :
                                                   Mix_PauseMusic();
                                                   break;
                                              case SDLK_r :
                                                   Mix_ResumeMusic(); 
                                                   break;
                                              default :
                                                      break;  
                                              }
                                              if (Mix_PausedMusic() == 1)
                                              njeu.son_arrete(ecran);
                                              }
                                        stay = true ;
                                        break;
                                   case 6: // aussi pour le sous-menu "à propos"
                                        njeu.afficher_a_propos(ecran);
                                        while (stay){
                                              SDL_WaitEvent(&event);
                                              switch (event.key.keysym.sym){
                                              case SDLK_BACKSPACE:
                                                   stay = false;
                                                   njeu.choix_menu(i,ecran);
                                                   break;
                                              case SDLK_p :
                                                   Mix_PauseMusic();
                                                   break;
                                              case SDLK_r :
                                                   Mix_ResumeMusic(); 
                                                   break;
                                              default :
                                                      break; 
                                              }
                                              if (Mix_PausedMusic() == 1)
                                              njeu.son_arrete(ecran);
                                              }
                                        stay = true ;
                                        break;
                                   case 8:
                                        // cas de clique sur quitter dans le menu, on quitte
                                        rester = false;
                                        return EXIT_FAILURE;
                                        break;
                                   }
                            break;
                            // Les flèches haut et bas pour la selection à partir du menu
                       case SDLK_UP:
                            i<2?i=2:i--;
                            njeu.choix_menu(i,ecran); // affichage des choix
                            break;
                       case SDLK_DOWN:
                            i>8?i=8:i++;
                            njeu.choix_menu(i,ecran); // affichage des choix
                            break;
                       case SDLK_p :
                            Mix_PauseMusic(); // pour mettre la musique en pause
                            break;
                       case SDLK_r :
                            Mix_ResumeMusic();  // pour reprendre la lecture de la musique
                            break;
                       default :
                            break;
                            }
                            if (f) {
                            njeu.choix_menu(i,ecran);
                            f = false ;
                            }
                            if (Mix_PausedMusic() == 1)
                            njeu.son_arrete(ecran); // si la musique est en pause on affiche le logo "no sound"
                            SDL_Flip(ecran);
                            SDL_Delay(100); 
                            }
    Mix_FreeMusic(pop_menu); // libérer la mémoire 
    //_ENTREE DANS LE JEU_______________________________________________________
    Mix_PlayMusic(in_game[0],-1); // Lecture de la musique du jeu ( y'en a 5 musique du jeu, on commence avec la 1ère)
    laby.dessiner(cases,ecran,pixel); // dessiner le labyrinthe
    bool go(true); // Un booléan pour sortir de la boucle while
    bool afficher(true) , resolu(false) , noMorePause(false); // un bouléan qui va nous aidez a manipuler l'affichage quand le jeu se termine
    Joueur j1 ( 5 , 5, 6, 4, joueur ); // Instanciation d'un joueur
    SDL_EnableKeyRepeat(10,10); // Autoriser l'appui continu sur une touche du clavier
    while (go) // la boucle principale
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                go = false; // ça ne sert à rien si on joue en mode plein ecran
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                       case SDLK_ESCAPE:
                            go = false; // on quitte en cliquant sur Echap
                            break;
                       case SDLK_LEFT:
                                  if(afficher){   // si le jeu n'est pas encore terminer on cntinue 
                                  j1.setDirection (OUEST); // changement de la direction du joueur
                                  if ( j1.get_yr()  % pixel >= 5 and j1.get_yr()  % pixel <= (j1.get_L()-5) and j1.get_x() % pixel == 0 ){
                                       j1.marcher(-5); // cas de collision
                                       }
                                  if ( (j1.get_x() % pixel == 0 )){ // quand on parcours la largeur/longeur d'un cellule on test la collision
                                  if ( j1.collision(laby((j1.get_x()/pixel),(j1.get_y()/pixel)),OUEST) or j1.collision(laby((j1.get_x()/pixel),((j1.get_yr()-2)/pixel)),OUEST) ){
                                       j1.marcher(-5);
                                     break ;
                                     }
                                     }
                                  j1.marcher(5);
                                  }
                                  break;
                                  
                             case SDLK_RIGHT: // même fonctionement pour les autre flèches
                                  if(afficher){
                                  j1.setDirection (EST);
                                  if ( j1.get_yr()  % pixel >= 5 and j1.get_yr()  % pixel <= (j1.get_L()-5) and j1.get_xr() % pixel == 0 ){
                                       j1.marcher(-5);
                                       }
                                  if ( (j1.get_xr() % pixel) == 0){
                                  if ( j1.collision(laby((j1.get_x()/pixel),(j1.get_y()/pixel)),EST) or j1.collision(laby((j1.get_x()/pixel),((j1.get_yr()-2)/pixel)),EST)){
                                       j1.marcher(-5);
                                     break ;
                                     }
                                     }
                                  j1.marcher(5);
                                  }
                                  break;
                                  
                             case SDLK_UP:
                                  if(afficher){
                                  j1.setDirection (NORD);
                                  if ( j1.get_xr() % pixel >= 5 and j1.get_xr() % pixel <= (j1.get_l()-5) and j1.get_y() % pixel == 0 ) {
                                      j1.marcher(-5);
                                     }
                                  if ( j1.get_y() % pixel == 0 ){
                                  if ( j1.collision(laby((j1.get_x()/pixel),((j1.get_y())/pixel)),NORD) or j1.collision(laby(((j1.get_xr()-2)/pixel),((j1.get_y())/pixel)),NORD)){
                                       j1.marcher(-5);
                                     }
                                     }
                                  j1.marcher(5);
                                  }
                                  break;
                                  
                             case SDLK_DOWN:
                                  if(afficher){
                                  j1.setDirection (SUD);
                                  if ( j1.get_xr()  % pixel >= 5 and j1.get_xr() % pixel <= (j1.get_l()-5) and j1.get_yr() % pixel == 0) {
                                       j1.marcher(-5);
                                     }
                                  if ( j1.get_yr() % pixel == 0 or j1.get_y() == 0){
                                  if (j1.collision(laby((j1.get_x()/pixel),(j1.get_y()/pixel)),SUD) or j1.collision(laby(((j1.get_xr() - 2)/pixel),(j1.get_y()/pixel)),SUD)){
                                     j1.marcher(-5);
                                     break ;
                                     }
                                     }
                                  j1.marcher(5);
                                  }
                                  break;
                             case SDLK_p :
                                  //if(afficher)
                                  Mix_PauseMusic(); // mettre la musique du jeu en pause
                                  break;
                             case SDLK_r :
                                  //if(afficher)
                                  Mix_ResumeMusic();  // reprendre la lecture de la musique
                                  break;
                             case SDLK_TAB : // Jouer une nouvelle partie
                                  afficher = true;
                                  resolu = false;
                                  noMorePause = false ;
                                  score = 0 ;
                                  {
                                  chemin = false;
                                  do {
                                     Labyrinthe l;
                                     l.initialiser_cellules();
                                     l.generation(memo,temp);
                                     l.affecter_types();
                                     if (l.verificateur_de_chemin()){
                                        chemin = true;
                                        laby = l ; // affectation du nouveau labyrinthe à l'ancien labyrinthe
                                        }
                                        }while(!chemin); 
                                  njeu.nouvelle_partie(ecran,j1);
                                  }
                                  Mix_PlayMusic(in_game[0],-1);
                                  break;
                             case SDLK_SPACE : 
                                  if(afficher)
                                  njeu.changer_musique(m,in_game,ecran); // lire la musique suivante
                                  break;
                             case SDLK_s :
                                  if(afficher){
                                  laby.dessiner(cases,ecran,pixel);             
                                  laby.generer_solution(solution,temp);
                                  laby.dessiner(ecran,pixel,solution);
                                  resolu = true;
                                  noMorePause = true ;
                                  }
                                  break;
                             case SDLK_RETURN :
                                  if(!noMorePause){
                                  if (_pause % 2 == 0)
                                  {
                                  afficher = false ;
                                  resolu = true ;
                                  njeu.pause(ecran);
                                  }else {
                                  afficher = true ; 
                                  resolu = false ;     
                                  }
                                  _pause++;  
                                  }           
                                  break;
                             default :
                                     break ;
                                  }
                default: 
                break;
          }
          // tester si le joueur est dans la dernière case
          if ( j1.get_y() >= (ecran->h - pixel) and j1.get_x() >= (ecran->w - pixel)){
               if(afficher){
               njeu.jeu_termine(ecran, score); // afficher le menu de fin de partie
               afficher = false ; // limiter l'utilisation du clavier à Echap pour quitter
                                  // et Tab pour une nouvelle partie
               }
          } 
          else 
          {
               if(!resolu)
               {
          laby.dessiner(cases,ecran,pixel); // Redéssiner le labyrinthe
          j1.dessiner(ecran); // Puis redéssiner le personnage
          score+=100; 
          if (Mix_PausedMusic() == 1) 
          njeu.son_arrete(ecran); // si la musique est arrêter on affiche le logo "no sound"
          }
          }
          SDL_Flip (ecran); // on actualise l'ecran
          SDL_Delay (40); // ralentir le mouvement du joueur
    }
    //_LIBERATION DE LA MEMOIRE_________________________________________________
    Mix_CloseAudio(); // fermer le mixer
    SDL_FreeSurface(ecran); // Libérer la surface ecran 
    TTF_Quit(); // quitter la TTF
    SDL_Quit(); // quitter la SDL
    
}




