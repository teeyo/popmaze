#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include "Cellule.h"
#include "SDL/SDL.h"

using namespace std;

class Labyrinthe{
      private:
              // j'utilise qu'un seul attribut entier qui designe la largeur parce que
              // mon code g�n�re un labyrinthe carr� ( largeur = hauteur )
              // donc le tableau de cellules sera de taille [largeur][hauteur]
              int l ;
              // tableau � taille fixe de 15 ligne te 15 colonnes
              Cellule cells[14][14];
      public:
             // constructeur d'initialisation
             Labyrinthe();
             // destructeur
             ~Labyrinthe();
             // fontion qui g�n�re le labyrinthe prend 3 param�tre
             // un tableau de cellules + un tableau memoire pour faire le retour en arri�re
             // et enfin un tableau temporaire pour d�t�rminer ( au hazard ) 
             // la cellule voisine qu'on va occup� � l'�tape suivante
             void generation(int[] , int[]);
             // apr�s avoir g�n�rer le labyrinthe on donnera � chaque cellule un type selon l'�tat de ses mures
             // 4 mures : type = 1 , ... etc
             void affecter_types();
             // fonction qui initialise les cellules plus pr�cis�ment on initialise :
             // l'identifiant de la cellule et ses coordonn�es x et y
             void initialiser_cellules(); 
             // l'accesseur 
             int const get_l();
             // fonction qui va nous donner un nombre al�atoire
             // on a utiliser le passage par r�f�rence pour gagner le temps de copie de la variable
             static void tirage(int , int&);
             // fonction retournant une r�f�rence d'une cellule que ses coordonn�es sont entr�es en param�tres
             Cellule& operator()(int,int);
             Labyrinthe& operator=(Labyrinthe &);
             // fonction qui dessine le labyrinthe sur l'�cran
             void dessiner(SDL_Surface * cases[],SDL_Surface *, const int);
             // fonction qui renvoi un tableau contenant les id des cellules du chemin de solution
             void generer_solution(int memoire[] , int temp[] );
             void dessiner(SDL_Surface * ecran, const int pixel ,int solution[]);
             void set_non_visitee();
             bool verificateur_de_chemin();
             
      };
#endif
