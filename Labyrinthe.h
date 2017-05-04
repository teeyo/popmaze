#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include "Cellule.h"
#include "SDL/SDL.h"

using namespace std;

class Labyrinthe{
      private:
              // j'utilise qu'un seul attribut entier qui designe la largeur parce que
              // mon code génère un labyrinthe carré ( largeur = hauteur )
              // donc le tableau de cellules sera de taille [largeur][hauteur]
              int l ;
              // tableau à taille fixe de 15 ligne te 15 colonnes
              Cellule cells[14][14];
      public:
             // constructeur d'initialisation
             Labyrinthe();
             // destructeur
             ~Labyrinthe();
             // fontion qui génère le labyrinthe prend 3 paramètre
             // un tableau de cellules + un tableau memoire pour faire le retour en arrière
             // et enfin un tableau temporaire pour détérminer ( au hazard ) 
             // la cellule voisine qu'on va occupé à l'étape suivante
             void generation(int[] , int[]);
             // après avoir génèrer le labyrinthe on donnera à chaque cellule un type selon l'état de ses mures
             // 4 mures : type = 1 , ... etc
             void affecter_types();
             // fonction qui initialise les cellules plus précisément on initialise :
             // l'identifiant de la cellule et ses coordonnées x et y
             void initialiser_cellules(); 
             // l'accesseur 
             int const get_l();
             // fonction qui va nous donner un nombre aléatoire
             // on a utiliser le passage par référence pour gagner le temps de copie de la variable
             static void tirage(int , int&);
             // fonction retournant une référence d'une cellule que ses coordonnées sont entrées en paramètres
             Cellule& operator()(int,int);
             Labyrinthe& operator=(Labyrinthe &);
             // fonction qui dessine le labyrinthe sur l'écran
             void dessiner(SDL_Surface * cases[],SDL_Surface *, const int);
             // fonction qui renvoi un tableau contenant les id des cellules du chemin de solution
             void generer_solution(int memoire[] , int temp[] );
             void dessiner(SDL_Surface * ecran, const int pixel ,int solution[]);
             void set_non_visitee();
             bool verificateur_de_chemin();
             
      };
#endif
