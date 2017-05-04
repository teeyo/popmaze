#include "Joueur.h"
#include "Labyrinthe.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
//_INITIALISATION DU JOUEUR_____________________________________________________
Joueur::Joueur ( int i_x, int i_y, int f_l, int f_L , string fichier ) {
    
    charger_img_joueur(fichier);
    frame_l = f_l;
    frame_L = f_L ;
    x = i_x;
    y = i_y;
    l = img_joueur->w / frame_l;
    L = img_joueur->h / frame_L;
    direction = SUD;
    frame_actuel = 0;
}
//_DESTRUCTEUR__________________________________________________________________
Joueur::~Joueur () {
       if ( img_joueur ) // si le pointeur n'est pas à NULL (pointe toujours sur une adresse)
       delete img_joueur; // on libère le pointage
       img_joueur = NULL; // pour raison de sécurité on le met à NULL

}

//_LES ACCESSEURS_______________________________________________________________

int  Joueur::get_l() const
{
    return l ;
}
int  Joueur::get_L() const
{
    return L ;
}
int  Joueur::get_x() const
{
    return x ;
}
int  Joueur::get_xr() const
{
    return (x + l) ;
}
int  Joueur::get_y() const
{
    return y ;
}
int  Joueur::get_yr() const
{
    return (y + L);
//_LES MODIFICATEURS____________________________________________________________
}
void Joueur::set_x(int nx)
{
     x = nx;
}
void Joueur::set_y(int ny)
{
     y = ny;
}

void Joueur::setDirection( DIRECTION ndirection ) {
     
     direction = ndirection;
}
//_CHARGEMENT DU SPRITE_________________________________________________________
void Joueur::charger_img_joueur( string fichier ) {
     
     img_joueur = IMG_Load( fichier.c_str() );
}
//_FAIRE AVANCER LE JOUEUR______________________________________________________

void Joueur::marcher(int pas) {
     if ( x < 0 )
     x = 0 ;
            
     else if ( x > ecran_l - l )
        x = ecran_l - l;
        
     if ( y < 0 )
          y = 0;
          
     else if ( y > ecran_l - L )
          y = ecran_l - L;
          
        
     switch ( direction ) {
            
            case EST:
                 x += pas;
                 break;
                 
            case OUEST:
                 x -= pas;
                 break;
                 
            case NORD:
                 y -= pas;
                 break;
                 
            case SUD:
                 y += pas;
                 break;
                 
            default:
                    break;
                    
     }
     // passer d'un clip à un autre pour faire croire que le personnage bouge réelement !
     frame_actuel++;
     if ( frame_actuel > frame_l - 1 )
        frame_actuel = 0;
     
}
//_DESSINER LE JOUEUR___________________________________________________________
void Joueur::dessiner( SDL_Surface* ecran ) {
     
     SDL_Rect frameRect;
     
     frameRect.w = l;
     frameRect.h = L;
     frameRect.x = frame_actuel * l;
     frameRect.y = direction * L;
     
     SDL_Rect pos;
     
     pos.x = x;
     pos.y = y;
     
     SDL_BlitSurface ( img_joueur, &frameRect, ecran, &pos );
}
//_GESTION DE COLLISION_________________________________________________________
bool Joueur::collision(Cellule &cell, DIRECTION d )
{
switch (d)
{
       case NORD :
            if ( cell.get_p_nord())
            {
            return true ;
            } else
            {
                  return false ;
                  }
            break ;
       case SUD :
            if ( cell.get_p_sud())
            {
            return true;
            } else
            {
                  return false ;
                  }
            break;
       case EST :
            if ( cell.get_p_est() )
            {
            return true ;
            } else
            {
                  return false ;
                  }
            break ;
       case OUEST :
            if ( cell.get_p_ouest())
            {
            return true ;
            } else
            {
                  return false ;
                  }
            break;
       }  
}
