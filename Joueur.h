#ifndef JOUEUR_H
#define JOUEUR_H
#include "SDL/SDL.h"
#include "Cellule.h"
#include <string>
using namespace std;
enum DIRECTION { SUD, OUEST , NORD, EST }; // enum�ration des directions (sorte de type personnalis�)
const int ecran_l(14*50); // la largeur/longeur de l'�cran (nombre de cellule * largeur/longeur de la cellule)
class Joueur{
      int l; // largeur
      int L; // longeur
      int x; // coordonn�e x
      int y; // coordpnn�e y
      int frame_l; // frames de largeur (ou bien dite "clip")
      int frame_L; // frames de longueur
      int frame_actuel; // le frame qu'on affiche actuellement
      
      DIRECTION direction;
      
      SDL_Surface* img_joueur; // le sprite du joueur
      
      public:
             Joueur ( int, int, int, int, string ); // initialiser le personnage sur l'�cran
             ~Joueur ();
             void charger_img_joueur( string ); // charger le sprite (png)
             void setDirection ( DIRECTION ); // modifier la direction
             void marcher(int) ; // avancer
             void dessiner( SDL_Surface* ); // ddessiner le joueur sur l'�cran
             bool collision( Cellule & , DIRECTION d) ; // tester la collision
             // Les accesseurs
             int  get_l()const;
             int  get_L()const;
             int  get_x()const;
             int  get_y()const;
             int  get_xr()const;
             int  get_yr()const;
             void set_x(int nx);
             void set_y(int ny);
             
      };
#endif
