#include "Labyrinthe.h"
#include "Cellule.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <ctime>
#include <iostream>

//_______________________________________________________ 
//Constructeur
Labyrinthe::Labyrinthe():l(14){}
//_______________________________________________________ 
//Destructeur     
Labyrinthe::~Labyrinthe(){} 
//_______________________________________________________ 
// fonction  retournant une référence sur la cellule souhaitée
Cellule& Labyrinthe::operator()(int x , int y ){
        return cells[x][y];
         }
//_______________________________________________________ 
int const Labyrinthe::get_l(){
    return l;
    }
//_______________________________________________________ 
//Initialisation du tableau de cellules                
void Labyrinthe::initialiser_cellules(){
     for (int i = 0 ; i < (l*l) ; i++ ) {
          cells[i%l][i/l].set_id(i);
         cells[i%l][i/l].set_x(i%l);
         cells[i%l][i/l].set_y(i/l);
         }
         }
//_______________________________________________________ 
// Fonction de tirage d'un nombre au hazard
void Labyrinthe::tirage(int max, int &p){
     p = ( rand() % (max));
     }
//_______________________________________________________ 
//Fonction de génération d'un labyrinthe
// cells est un tableau de cellules
// memoire est un tableau qui servira pour stocker les cases visitée ainsi on peut facilement
// faire le retour en arrière 
// temp est un tableau temporaire qui contiendra l'id des cases voisines non-visitée
void Labyrinthe::generation(int memoire[] , int temp[] ){
     // des variables qui vont servir pour des indices des tableaux déjà cités
     int a(0) , b(0) , c(0) , d(0) , i(0);
     //choisir une cellule au hasard à l'aide de la fonction prédéfinie dans "MesFonctions.h"
     tirage(l,a);
     tirage(l,b);
     // Marqué la cellule comme visitée
     cells[a][b].set_visitee(true);
     //Ajouter son identifiant au tableaux qui va servir pour faire le "backtrack" ( retour en arrière )
     memoire[c] = cells[a][b].get_id();
     // J'incrémente le c pour stocker la prochaine cellule dans la case c+1
     c++;
     //boucle qui fera l'exploration exhaustive
     do{ 
         //initialiser le i qui contiendra le nombre des cases voisines non-visitées
         i = 0 ;
        // on testera si les cases adjacentes ont été déjà visitées
        // on va commencer par la cellule de droite >> [a+1][b]
       if ((a + 1) > 0 && (a + 1) <= (l*l) && (cells[a][b].get_x() + 1) < l)
    {
        //si la case n'a jamais été visitée on incremente i et on enregistre sa position
        if (!cells[a+1][b].get_visitee())
        {
        // on stock (a+1) dans le tableau temporaire pour s'en servir par la suite et on incrémente le i 
        temp[i] = (a+1);
        i++;
        }
    }
        // la même chose pour les cases à venir, ici cases de gauche, [a-1][b]
        if ((a - 1) >= 0 && (a - 1) < (l*l) && (cells[a][b].get_x() - 1) >= 0)
    {
        if (!cells[a-1][b].get_visitee())
        {
        temp[i] = (a-1);
        i++;
        }
    }
        // case voisine du sud, [a][b+1]
        if ((a + 1) >= 0 && (a + 1) <= (l*l) && (cells[a][b].get_y()+1) < l)
    {
        if (!cells[a][b+1].get_visitee())
        {
        temp[i] = (b+1);
        i++;
        }
    }
    // case voisine du nord, [a][b-1]
    if ((b - 1) >= 0 && (b - 1) < (l*l) && (cells[a][b].get_y() -1) >= 0)
    {
        if (!cells[a][b-1].get_visitee())
        {
        temp[i] = (b-1);
        i++;
        }
    }
    //si on a detecté qu'au moins il y'a une cellule non visitée
    if (i > 0)
    {
        //on prendra un nombre aléatoire entre 0 et nombre de cases voisine non-visitée
        tirage(i, d);
            //selon la valeur de temp[d] on ouvre les portes correspondantes
            // cas de cellule de droite
            if (temp[d] == (a + 1))
            {
               // pour que la cellule de droite fera parti du jeu il faut détruire son mure d'ouest ainsi que le mure est de
               // la cellule actuelle
                cells[a][b].set_p_est(false);
                cells[a+1][b].set_p_ouest(false);
                a++;
            }
            // de même pour la cellule de gauche
            else if (temp[d] == (a - 1))
            {
                cells[a][b].set_p_ouest(false);
                cells[a-1][b].set_p_est(false);
                a--;
            }
            // la cellule  du nord
            else if (temp[d] == (b - 1))
            {
                cells[a][b].set_p_nord(false);
                cells[a][b-1].set_p_sud(false);
                b--;
            }
            // la cellule du sud
            else if (temp[d] == (b + 1))
            {
                cells[a][b].set_p_sud(false);
                cells[a][b+1].set_p_nord(false);
                b++;
            }
        // Case visitée = fait partie du jeu
        cells[a][b].set_visitee(true);
        // On enregistre son identifiant (trace)
        memoire[c] = cells[a][b].get_id();
        // On increment c
        c++;
    }
    // Si par hazard on trouve aucune case voisine non-visitée
    // On fera un retour en arrière à l'aide du tableau memoire
    else
    {
        // on decremante c
        c--;
        // On obtiendra le x et le y de la cellule depuis son identifiant
        a = memoire[c]%l ;
        b = memoire[c]/l ;
    }
    // on va sortir de la boucle quand toutes les cellules seront visitées 
    // donc le retour en arrière continuera et comme conséquent c va décrémenter jusqu'à
    // ce qu'elle sera = à 0
    }while (c != 0);
}
// fonction qui affecte à chaque cellule son type comme décrit dans le header de la calsse
void Labyrinthe::affecter_types()
{    // on aura besoin de parcourir toutes les cellules
    for (int i=0; i<(l*l); i++)
    {
        // Par défaut lors de l'initialisation des cellules toutes portes sont fermée donc le type de cellule
        // est = 1, donc on va ignorer le cas de toutes les portes fermées dans cette fonction
        // donc on va donner le type de cellule selon si les 4 mures existe ou bien il manque seulement celui du nord...
        if (cells[i%l][i/l].get_p_nord() && cells[i%l][i/l].get_p_sud() && !cells[i%l][i/l].get_p_est() && cells[i%l][i/l].get_p_ouest())
            cells[i%l][i/l].set_type(2); 
            //____________________________________________
        else if (!cells[i%l][i/l].get_p_nord() && cells[i%l][i/l].get_p_sud() && cells[i%l][i/l].get_p_est() && cells[i%l][i/l].get_p_ouest())
            cells[i%l][i/l].set_type(3); 
            //____________________________________________
        else if (cells[i%l][i/l].get_p_nord() && cells[i%l][i/l].get_p_sud() && cells[i%l][i/l].get_p_est() && !cells[i%l][i/l].get_p_ouest())
            cells[i%l][i/l].set_type(4);
            //____________________________________________
        else if (cells[i%l][i/l].get_p_nord() && !cells[i%l][i/l].get_p_sud() && cells[i%l][i/l].get_p_est() && cells[i%l][i/l].get_p_ouest())
            cells[i%l][i/l].set_type(5);
            //____________________________________________
        else if (cells[i%l][i/l].get_p_nord() && !cells[i%l][i/l].get_p_sud() && !cells[i%l][i/l].get_p_est() && cells[i%l][i/l].get_p_ouest())
            cells[i%l][i/l].set_type(6);
            //____________________________________________
        else if (!cells[i%l][i/l].get_p_nord()  && cells[i%l][i/l].get_p_sud() && cells[i%l][i/l].get_p_est() && !cells[i%l][i/l].get_p_ouest())
            cells[i%l][i/l].set_type(7);
            //____________________________________________
        else if (cells[i%l][i/l].get_p_nord() && !cells[i%l][i/l].get_p_sud() && cells[i%l][i/l].get_p_est() && !cells[i%l][i/l].get_p_ouest())
            cells[i%l][i/l].set_type(8);
            //____________________________________________
        else if (!cells[i%l][i/l].get_p_nord()  && cells[i%l][i/l].get_p_sud() && !cells[i%l][i/l].get_p_est()  && cells[i%l][i/l].get_p_ouest())
             cells[i%l][i/l].set_type(9);
             //____________________________________________
        else if (!cells[i%l][i/l].get_p_nord()  && !cells[i%l][i/l].get_p_sud()  && !cells[i%l][i/l].get_p_est()  && cells[i%l][i/l].get_p_ouest() )
             cells[i%l][i/l].set_type(10);
             //____________________________________________
        else if (!cells[i%l][i/l].get_p_nord()  && !cells[i%l][i/l].get_p_sud() && cells[i%l][i/l].get_p_est()  && !cells[i%l][i/l].get_p_ouest())
             cells[i%l][i/l].set_type(11);
             //____________________________________________
        else if (!cells[i%l][i/l].get_p_nord() && cells[i%l][i/l].get_p_sud() && !cells[i%l][i/l].get_p_est() && !cells[i%l][i/l].get_p_ouest())
             cells[i%l][i/l].set_type(12);
             //____________________________________________
        else if (cells[i%l][i/l].get_p_nord() && !cells[i%l][i/l].get_p_sud() && !cells[i%l][i/l].get_p_est() && !cells[i%l][i/l].get_p_ouest())
             cells[i%l][i/l].set_type(13);
             //____________________________________________
        else if (!cells[i%l][i/l].get_p_nord() && !cells[i%l][i/l].get_p_sud()  && cells[i%l][i/l].get_p_est()  && cells[i%l][i/l].get_p_ouest())
             cells[i%l][i/l].set_type(14);
             //____________________________________________
        else if (cells[i%l][i/l].get_p_nord() && cells[i%l][i/l].get_p_sud() && !cells[i%l][i/l].get_p_est()  && !cells[i%l][i/l].get_p_ouest())
             cells[i%l][i/l].set_type(15);
//             //____________________________________________
//        // après avoir tester le labyrinthe il se peut qu'une case n'aura aucun mure donc on lui donne type 0
        else if (!cells[i%l][i/l].get_p_nord() && !cells[i%l][i/l].get_p_sud() && !cells[i%l][i/l].get_p_est() && !cells[i%l][i/l].get_p_ouest())
            cells[i%l][i/l].set_type(1);

    }
}
// La fonction d'affichage du labyrinthe ( dessin ou bien bliter les surfaces déjà chargées
void Labyrinthe::dessiner(SDL_Surface * cases[], SDL_Surface * ecran, const int pixel)
{
     SDL_Surface *desert(NULL);
     desert = IMG_Load("pix/sand.png");
     SDL_Rect positionCase ;
     positionCase.x = 0 ;
     positionCase.y =0 ;
     SDL_BlitSurface(desert, NULL, ecran, &positionCase);
     for (int i=0; i<(l*l); i++)
    {   
        // On fait sortir les coordonnées réels sur l'écran à partir de ceux de la cellule
        positionCase.x = ((cells[i/l][i%l].get_x() * pixel)); 
        positionCase.y = ((cells[i/l][i%l].get_y() * pixel));                                                               
        // On dessine la cellule sur la surface écran
        SDL_BlitSurface(cases[cells[i/l][i%l].get_type()], NULL, ecran, &positionCase);
    }
    SDL_Flip(ecran);
    SDL_FreeSurface(desert);
}

//_SURCHARGE DE L'OPERATEUR = __________________________________________________
Labyrinthe& Labyrinthe::operator=(Labyrinthe & lab){
            for(int i = 0 ; i < l*l ; i++ ){
                    cells[i%l][i/l] = lab(i%l,i/l) ;
                    }
            }
//_FONCTION QUI REND LES CELLULES NON VISITEES__________________________________
void Labyrinthe::set_non_visitee(){
     for (int i = 0 ; i < l*l ; i++ ){
         cells[i%l][i/l].set_visitee(false);
         }
     }

//_FONCTION DE GENERATION DE SOLUTION___________________________________________
void Labyrinthe::generer_solution(int memoire[] , int temp[] ){
     for(int i = 0 ; i < (l*l) ; i++ )
     {
             memoire[i] = 0 ;
             }
     set_non_visitee();
     // des variables qui vont servir pour des indices des tableaux déjà cités
     int a(0) , b(0) , c(0) , d(0) , i(0);
     bool rester(true);
     // Marqué la cellule comme visitée
     cells[a][b].set_visitee(true);
     //Ajouter son identifiant au tableaux qui va servir pour faire le "backtrack" ( retour en arrière )
     memoire[c] = cells[a][b].get_id();
     // J'incrémente le c pour stocker la prochaine cellule dans la case c+1
     //boucle qui fera l'exploration exhaustive
     do{ 
         //initialiser le i qui contiendra le nombre des cases voisines non-visitées
         i = 0 ;
        // on testera si les cases adjacentes ont été déjà visitées
        // on va commencer par la cellule de droite >> [a+1][b]
       if ((a + 1) > 0 && (a + 1) <= (l*l) && (cells[a][b].get_x() + 1) < l)
    {
        //si la case n'a jamais été visitée on incremente i et on enregistre sa position
        if (!cells[a+1][b].get_visitee() and !cells[a][b].get_p_est())
    { 
        temp[i] = cells[a+1][b].get_id();
        i++;
        }
    }
        if ((a - 1) >= 0 && (a - 1) < (l*l) && (cells[a][b].get_x() - 1) >= 0)
    {
        if (!cells[a-1][b].get_visitee() and !cells[a][b].get_p_ouest())
        {
        temp[i] = cells[a-1][b].get_id();
        i++;
        }
    }
        if ((b + 1) >= 0 && (b + 1) <= (l*l) && (cells[a][b].get_y()+1) < l)
    {
        if (!cells[a][b+1].get_visitee() and !cells[a][b].get_p_sud())
        {
        temp[i] = cells[a][b+1].get_id();
        i++;
        }
    }
    if ((b - 1) >= 0 && (b - 1) < (l*l) && (cells[a][b].get_y() -1) >= 0)
    {
        if (!cells[a][b-1].get_visitee() and !cells[a][b].get_p_nord())
        {
        temp[i] = cells[a][b-1].get_id();
        i++;
        }
    }
    if (i > 0)
    {
        ++c;
        tirage(i, d);
        a = temp[d] % l ;
        b = temp[d] / l ;
        cells[a][b].set_visitee(true);
        memoire[c] = cells[a][b].get_id();
    }
    else
    {
        --c==0?c=0:1;
        a = memoire[c]%l ;
        b = memoire[c]/l ;
    }
    }while (memoire[c]<(l*l-1));
}

// La fonction d'affichage du labyrinthe ( dessin ou bien bliter les surfaces déjà chargées
void Labyrinthe::dessiner(SDL_Surface * ecran, const int pixel ,int solution[])
{
     TTF_Font * police; 
     SDL_Rect pos;
     SDL_Surface * chemin(NULL) , *message(NULL) ;
     SDL_Color couleur = {0,0,0};
     police = TTF_OpenFont("font/font10.ttf",42);
     message = TTF_RenderText_Blended(police,"TAB : Nouvelle partie",couleur);
     pos.x = (ecran->w - message->w ) / 2 ;
     pos.y = (ecran->h - message->h ) / 2;
     chemin = IMG_Load("pix/balise.png");
     SDL_Rect positionCase ;
     for (int i=0; i<(l*l); i++)
    {   
        if ( solution[i] > 0 ) 
        {
             if ( solution[i] == (l*l-1) ){
             break;
             }
        // On fait sortir les coordonnées réels sur l'écran à partir de ceux de la cellule
        positionCase.x = (cells[solution[i]%l][solution[i]/l].get_x() * pixel); 
        positionCase.y = (cells[solution[i]%l][solution[i]/l].get_y() * pixel);                                                               
        // On dessine la cellule sur la surface écran
        SDL_BlitSurface(chemin, NULL, ecran, &positionCase); 
        SDL_Flip(ecran);
        SDL_Delay(150);
        }
    }
    SDL_FreeSurface(chemin);
    SDL_Delay(1000);
    SDL_BlitSurface(message,NULL,ecran,&pos);
    SDL_FreeSurface(message);
    SDL_Flip(ecran);
    TTF_CloseFont(police);
}

//_Fonction de vérification de labyrinthe_______________________________________

bool Labyrinthe::verificateur_de_chemin(){
     bool resultat(true);
     for( int i = 0 ; i < (l*l) ; i++ ) {
          if ( cells[i%l][i/l].get_type() == 1 ){
          resultat = false;
          }
          }
          return resultat;
     }
