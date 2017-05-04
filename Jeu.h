#ifndef JEU_H
#define JEU_H
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "Joueur.h"
#include <string>
using namespace std;
class Jeu{
      private:
              void afficher_menu_principal(SDL_Surface * ecran); // menu principal
              long ancien_score();
              void enregistrer_score(long &score);
      public:
             Jeu();
             ~Jeu();
             
             void charger_images(SDL_Surface * cases[]); // fonction de chargement des cellules du labyrinthe
             void afficher_entree(SDL_Surface *); // affichage du menu d'entrée
             void jeu_termine(SDL_Surface *ecran , long &score); // tester la fin du partie
             void appuyer_pour_continuer(SDL_Surface *ecran); // invité à appuyer pour continuer
             void choix_menu(short c, SDL_Surface *); // affichage des choix dans le menu
             void afficher_a_propos(SDL_Surface * ecran); // à propos
             void afficher_option(SDL_Surface * ecran); // les options du jeu
             void menu_choix_joueur(SDL_Surface * ecran); // affichage du choix de joueurs
             string choix_joueur(short j, SDL_Surface * ecran); // fonction qui charge le joueur choisit
             void son_arrete(SDL_Surface *ecran); // afficher le logo "no sound"
             void nouvelle_partie(SDL_Surface * ecran, Joueur &j1); // démarrer une nouvelle partie
             void changer_musique(short &m,Mix_Music *tab[5], SDL_Surface *ecran); // passer à la musique suivante
             void pause(SDL_Surface *ecran);
             
      };
#endif
