#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <sstream>
#include <fstream>
#include "Jeu.h"
#include <string>
#include <cstdlib>

// Constructeur
Jeu::Jeu(){}
// Destructeur
Jeu::~Jeu(){
            }
//_MENU D'ENTREE AVEC LE LOGO DE LA FACULTE_____________________________________

void Jeu::afficher_entree(SDL_Surface *ecran){
     Mix_Music * entree(NULL);
     entree = Mix_LoadMUS("son/pop_entree.mp3");
     SDL_Rect pos;   
     SDL_Surface *logo(NULL);
     logo = IMG_Load("pix/logo.png"); 
     for (int i = 0 ; i < 256 ; i++ ) {
         SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,i,i,i));
         SDL_Flip(ecran);
         SDL_Delay(5);
         }
         Mix_PlayMusic(entree,1);
         pos.x = (ecran->w /2) - (logo->w/2);
         pos.y = (ecran->h /2) - (logo->h /2);
         SDL_BlitSurface(logo,NULL,ecran,&pos);
         SDL_Flip(ecran);
         SDL_Delay(4800);
         Mix_FreeMusic(entree);
         for (int i = 256 ; i > 0 ; i-- ) {
         SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,i,i,i));
         SDL_Flip(ecran);
         SDL_Delay(5);
         }
         SDL_FreeSurface(logo);
     }


// fonction de chargement des cellules après qu'on les attribuées ses types
// prend en paramètre un pointeur char qui contiendra le nom de l'image
// et aussi un tableau de surfaces cellules
void Jeu::charger_images(SDL_Surface * cellules[])
{
     std::string nomImg = "";
    // on a 16 type donc on aura 16 image qui représente chaque type
    for (int i=1; i<=15; i++)
    {
        nomImg = "pix/cellule";
        std::stringstream num;
        num << i;
        nomImg += num.str() + ".png";
        cellules[i] = IMG_Load(nomImg.c_str());
    }
}

// Tester si le joueur est sur la dernière case
void Jeu::jeu_termine(SDL_Surface *ecran , long & score){
     TTF_Font * police(NULL);
     string sc = "";
     SDL_Surface *coupe(NULL), *menu(NULL) , *message(NULL);
     SDL_Rect pos;
     menu = IMG_Load("pix/menu_principal.png");
     pos.x = 0 ;
     pos.y = 0 ;
     SDL_BlitSurface(menu,NULL,ecran,&pos);
     Mix_Music *congrat(NULL);
     congrat = Mix_LoadMUS("son/winner.mp3");
     Mix_PlayMusic(congrat,1);
     coupe = IMG_Load("pix/winner.png");
     pos.x = (ecran->w - coupe->w) /2 ;
     pos.y = (ecran->h - coupe->h) /2 ;
     SDL_BlitSurface(coupe,NULL,ecran,&pos);
     SDL_Flip(ecran);
     SDL_FreeSurface(coupe);
     SDL_FreeSurface(menu);
     SDL_Delay(1650);
     SDL_Color couleur = {255,46,50};
     police = TTF_OpenFont("font/font10.ttf",24);
     //_________________________
     score = 1000000 - score ;
     score<=0?score=50:1;
     if(score>ancien_score()){
     sc = "Bravo ! Nouveau meilleur score : ";
     enregistrer_score(score);                         
                           }
     else {
     sc = "Votre score est : ";
          }
     std::stringstream num;
     num << score;
     sc += num.str();
     //_________________________
     message = TTF_RenderText_Blended(police, sc.c_str() ,couleur);
     pos.x = (ecran->w - message->w) /2 ;
     pos.y = 50;
     SDL_BlitSurface(message,NULL,ecran,&pos);
     SDL_Flip(ecran);
     SDL_FreeSurface(message);
     Mix_FreeMusic(congrat);
     TTF_CloseFont(police);
     }

void Jeu::appuyer_pour_continuer(SDL_Surface *ecran){
     TTF_Font * police(NULL);
     SDL_Surface *menu(NULL), *message(NULL);
     menu = IMG_Load("pix/menu.png");
     SDL_Rect pos;
     pos.x = 0;
     pos.y = 0;
     SDL_BlitSurface(menu,NULL,ecran,&pos);
     SDL_Color couleur = {255,46,50};
     police = TTF_OpenFont("font/font10.ttf",24);
     message = TTF_RenderText_Blended(police,"Appuyer sur ESPACE pour continuer",couleur);
     pos.x = 20 ;
     pos.y = (ecran->h - 20 - message->h );
     SDL_BlitSurface(message,NULL,ecran,&pos);
     SDL_Flip(ecran);
     SDL_Delay(50);
     SDL_FreeSurface(message);
     message = TTF_RenderText_Blended(police,"Appuyer sur ESPACE pour continuer.",couleur);
     SDL_BlitSurface(message,NULL,ecran,&pos);
     SDL_Flip(ecran);
     SDL_Delay(50);
     SDL_FreeSurface(message);
     message = TTF_RenderText_Blended(police,"Appuyer sur ESPACE pour continuer..",couleur);
     SDL_BlitSurface(message,NULL,ecran,&pos);
     SDL_Flip(ecran);
     SDL_Delay(50);
     SDL_FreeSurface(message);
     message = TTF_RenderText_Blended(police,"Appuyer sur ESPACE pour continuer...",couleur);
     SDL_BlitSurface(message,NULL,ecran,&pos);
     SDL_Flip(ecran);
     SDL_Delay(50);
     SDL_FreeSurface(menu);
     SDL_FreeSurface(message);
     TTF_CloseFont(police); 
}

void Jeu::afficher_menu_principal(SDL_Surface * ecran){
     TTF_Font * police(NULL);
     SDL_Surface *menu_principal(NULL), *message(NULL);
     menu_principal = IMG_Load("pix/menu_principal.png");
     SDL_Rect pos;
     pos.x = 0;
     pos.y = 0;
     SDL_BlitSurface(menu_principal,NULL,ecran,&pos);
     SDL_FreeSurface(menu_principal);
     SDL_Color couleur = {255,46,50};
     police = TTF_OpenFont("font/font10.ttf",28);
     message = TTF_RenderText_Blended(police,"-   MENU   -",couleur);
     pos.x = (ecran->w - message->w ) /2;
     pos.y = ((ecran->h - message->h ) /2) ;
     SDL_BlitSurface(message,NULL,ecran,&pos);
     SDL_FreeSurface(message);
     TTF_CloseFont(police);
     police = TTF_OpenFont("font/font10.ttf",18);
     message = TTF_RenderText_Blended(police,"Jouer",couleur);
     pos.x = (ecran->w - message->w ) /2;
     pos.y = ((ecran->h - message->h ) /2) + 40 ;
     SDL_BlitSurface(message,NULL,ecran,&pos);
     SDL_FreeSurface(message);
     message = TTF_RenderText_Blended(police,"Options",couleur);
     pos.x = (ecran->w - message->w ) /2;
     pos.y = ((ecran->h - message->h ) /2) + 80 ;
     SDL_BlitSurface(message,NULL,ecran,&pos);
     SDL_FreeSurface(message);
     message = TTF_RenderText_Blended(police,"A propos",couleur);
     pos.x = (ecran->w - message->w ) /2;
     pos.y = ((ecran->h - message->h ) /2) + 120 ;
     SDL_BlitSurface(message,NULL,ecran,&pos);
     SDL_FreeSurface(message);
     message = TTF_RenderText_Blended(police,"Quitter",couleur);
     pos.x = (ecran->w - message->w ) /2;
     pos.y = ((ecran->h - message->h ) /2) + 160 ;
     SDL_BlitSurface(message,NULL,ecran,&pos);
     SDL_FreeSurface(message);
     SDL_Flip(ecran);
     TTF_CloseFont(police); 
     }

 void Jeu::choix_menu(short c, SDL_Surface * ecran){
      TTF_Font * police(NULL);
      afficher_menu_principal(ecran);
      Mix_Chunk *son;
      son = Mix_LoadWAV("son/sword.wav");
      Mix_VolumeChunk(son, MIX_MAX_VOLUME/2); 
      SDL_Surface *curseur(NULL);
      curseur = IMG_Load("pix/pop_cursor.png");
      SDL_Rect pos;
      switch (c) {
             case 2:
                  pos.x = (ecran->w /2) + 30;
                  pos.y = (ecran->h /2) + 30 + ( curseur->h /2 ) ; 
                  SDL_BlitSurface(curseur,NULL,ecran,&pos);
                  Mix_PlayChannel(0, son, 0);
                  break;
             case 4:
                  pos.x = (ecran->w /2) + 40;
                  pos.y = (ecran->h /2) + 70  + ( curseur->h /2 ); 
                  SDL_BlitSurface(curseur,NULL,ecran,&pos);
                  Mix_PlayChannel(0, son, 0);
                  break;
             case 6:
                  pos.x = (ecran->w /2) + 50;
                  pos.y = (ecran->h /2) + 110 + ( curseur->h /2 ) ; 
                  SDL_BlitSurface(curseur,NULL,ecran,&pos);
                  Mix_PlayChannel(0, son, 0);
                  break;
             case 8:
                  pos.x = (ecran->w /2) + 40;
                  pos.y = (ecran->h /2) + 150 + ( curseur->h /2 ); 
                  SDL_BlitSurface(curseur,NULL,ecran,&pos);
                  Mix_PlayChannel(0, son, 0);
                  break;
             }
             SDL_Flip(ecran);
             SDL_FreeSurface(curseur);
             SDL_Delay(45);
             Mix_FreeChunk(son);
      }

void Jeu::afficher_a_propos(SDL_Surface * ecran){
     SDL_Surface * a_propos(NULL) ;
     a_propos = IMG_Load("pix/a_propos.png");
     SDL_Rect pos;
     pos.x = 0;
     pos.y = 0;
     SDL_BlitSurface(a_propos,NULL,ecran,&pos);
     SDL_Flip(ecran);
     SDL_Delay(150);
     SDL_FreeSurface(a_propos);
     }

void Jeu::afficher_option(SDL_Surface * ecran){
     SDL_Surface * option(NULL) ;
     option = IMG_Load("pix/comment_jouer.png");
     SDL_Rect pos;
     pos.x = 0;
     pos.y = 0;
     SDL_BlitSurface(option,NULL,ecran,&pos);
     SDL_Flip(ecran);
     SDL_Delay(150);
     SDL_FreeSurface(option);
     }

void Jeu::menu_choix_joueur(SDL_Surface * ecran){ 
     TTF_Font * police(NULL);
     SDL_Surface *profile(NULL) , *menu(NULL), *message(NULL);
     SDL_Rect pos;
     SDL_Color couleur = {255,46,50};
     police = TTF_OpenFont("font/font10.ttf",28);
     profile = IMG_Load("pix/prince.png");
     menu = IMG_Load("pix/menu_principal.png");
     pos.x = 0 ;
     pos.y = 0;
     SDL_BlitSurface(menu,NULL,ecran,&pos);
     pos.x = (ecran->w /4) ;
     pos.y = (ecran->h - profile->h ) /2;
     SDL_BlitSurface(profile,NULL,ecran,&pos);
     SDL_FreeSurface(profile);
     profile = IMG_Load("pix/princess.png");
     pos.x = ((ecran->w /4) * 2) + 40 ;
     pos.y = (ecran->h - profile->h ) /2;
     SDL_BlitSurface(profile,NULL,ecran,&pos);
     SDL_FreeSurface(profile);
     message = TTF_RenderText_Blended(police,"Choisissez votre joueur (ESPACE pour confirmer)",couleur);
     pos.x = (ecran->w - message->w )/ 2 ;
     pos.y = ((ecran->h - message->h )/2) - 80;
     SDL_BlitSurface(message,NULL,ecran,&pos);
     SDL_FreeSurface(message);
     SDL_Flip(ecran);
     SDL_FreeSurface(menu);
     TTF_CloseFont(police);
     }

 string Jeu::choix_joueur(short j, SDL_Surface * ecran){
      Mix_Chunk *son;
      son = Mix_LoadWAV("son/sword.wav");
      Mix_VolumeChunk(son, MIX_MAX_VOLUME);  
      SDL_Surface *curseur(NULL);
      curseur = IMG_Load("pix/pop_cursor.png");
      SDL_Rect pos;
      switch (j) {
             case 2:
                  pos.x = (ecran->w /4) + 40;
                  pos.y = ((ecran->h - 25 )/2 ) + 10 + ( curseur->h /2 ) ; 
                  SDL_BlitSurface(curseur,NULL,ecran,&pos);
                  SDL_FreeSurface(curseur);
                  SDL_Flip(ecran);
                  Mix_PlayChannel(0, son, 0);
                  SDL_Delay(45);
                  Mix_FreeChunk(son);
                  return "pix/p1.png";
                  break;
             case 4:
                  pos.x = ((ecran->w /4) * 2) + 80;
                  pos.y = ((ecran->h - 25 ) /2) + 10  + ( curseur->h /2 ); 
                  SDL_BlitSurface(curseur,NULL,ecran,&pos);
                  SDL_FreeSurface(curseur);
                  SDL_Flip(ecran);
                  Mix_PlayChannel(0, son, 0);
                  SDL_Delay(45);
                  Mix_FreeChunk(son);
                  return "pix/p2.png";
                  break;
             }
      }
 
 void Jeu::son_arrete(SDL_Surface *ecran){
      SDL_Surface *son(NULL);
      son = IMG_Load("pix/noSound.png");
      SDL_Rect pos;
      pos.x = (ecran->w - son->w );
      pos.y = 0 ;
      SDL_BlitSurface(son,NULL,ecran,&pos);
      SDL_Flip(ecran);
      SDL_FreeSurface(son);
      }

void Jeu::nouvelle_partie(SDL_Surface * ecran, Joueur &j1){
     TTF_Font * police(NULL);
     SDL_Surface *menu(NULL) , *message(NULL) ;
     SDL_Rect pos;
     menu = IMG_Load("pix/menu_principal.png");
     pos.x = 0 ;
     pos.y = 0 ;
     SDL_BlitSurface(menu,NULL,ecran,&pos);
     j1.set_x(5);
     j1.set_y(5);
     j1.setDirection(SUD);
     //____________________________________
     SDL_Color couleur = {255,46,50};
     police = TTF_OpenFont("font/font10.ttf",28);
     message = TTF_RenderText_Blended(police,"Chargement de la nouvelle partie",couleur);
     pos.x = 125 ;
     pos.y = (ecran->h - message->h )/2;
     SDL_BlitSurface(message,NULL,ecran,&pos);
     SDL_FreeSurface(message);
     SDL_Flip(ecran);
     SDL_Delay(500);
     message = TTF_RenderText_Blended(police,"Chargement de la nouvelle partie.",couleur);
     pos.x = 125 ;
     pos.y = (ecran->h - message->h )/2;
     SDL_BlitSurface(message,NULL,ecran,&pos);
     SDL_FreeSurface(message);
     SDL_Flip(ecran);
     SDL_Delay(500);
     message = TTF_RenderText_Blended(police,"Chargement de la nouvelle partie..",couleur);
     pos.x = 125 ;
     pos.y = (ecran->h - message->h )/2;
     SDL_BlitSurface(message,NULL,ecran,&pos);
     SDL_FreeSurface(message);
     SDL_Flip(ecran);
     SDL_Delay(500);
     message = TTF_RenderText_Blended(police,"Chargement de la nouvelle partie...",couleur);
     pos.x = 125 ;
     pos.y = (ecran->h - message->h )/2;
     SDL_BlitSurface(message,NULL,ecran,&pos);
     SDL_FreeSurface(message);
     TTF_CloseFont(police);
     SDL_Flip(ecran);
     SDL_Delay(500);
     SDL_FreeSurface(menu);
     }

void Jeu::changer_musique(short &m,Mix_Music *tab[5], SDL_Surface *ecran)
{
     m++;
     Mix_PlayMusic(tab[m%5],-1);     
     SDL_Surface *next(NULL);
     next = IMG_Load("pix/next.png");
     SDL_Rect pos;
     pos.x = (ecran->w - next->w ) / 2;
     pos.y = (ecran->h - next->h ) / 2;
     SDL_BlitSurface(next,NULL,ecran,&pos);
     SDL_Flip(ecran);
     SDL_Delay(1000);
     SDL_FreeSurface(next);
         
}

long Jeu::ancien_score(){
     long a_score;
     ifstream monFichier("score.pop");
     if(monFichier)
     monFichier >> a_score;          
     else
     a_score = 0 ;
     return a_score;
     }

void Jeu::enregistrer_score(long &score){
     ofstream monFichier("score.pop");
     if(monFichier)
     monFichier << score;        
     }

void Jeu::pause(SDL_Surface *ecran){
     SDL_Surface *pause_img(NULL);
     pause_img = IMG_Load("pix/pause.png");
     SDL_Rect pos;
     pos.x = (ecran->w - pause_img->w) /2 ;
     pos.y = (ecran->h - pause_img->h) /2 ;
     SDL_BlitSurface(pause_img,NULL,ecran,&pos);
     SDL_Flip(ecran);
     SDL_FreeSurface(pause_img);
     }
