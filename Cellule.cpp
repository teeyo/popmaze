#include "Cellule.h"
//________________________________________
// constructeur par défaut
// on initialise les portes en "true" ( cela veut dire qu'elles sont fermée )
// et le type initialisé en 1 cela veut dire que la même chose que la ligne de commentaire en haut
// toutes les portes fermée ( c'est pas une sorte de répitition cela va nous servire par la suite dans l'affichage
// aussi l'attribut visitée est en "false" donc toutes les cellules sont jamais visitées
Cellule::Cellule():visitee(false),type(1),p_nord(true),p_sud(true),p_est(true),p_ouest(true){}
//________________________________________
// desctructeur
Cellule::~Cellule(){}
//________________________________________
// les getters et les setters
int Cellule::get_x() const{
    return x;
    }
//________________________________________ 
int Cellule::get_y() const{
    return y;
    }
//________________________________________    
int Cellule::get_id() const{
    return id;
    }
//________________________________________    
short Cellule::get_type() const{
      return type;
      }
//________________________________________    
bool Cellule::get_visitee() const{
     return visitee;
     }
//________________________________________      
bool Cellule::get_p_nord() const{
     return p_nord;
     }
//________________________________________
bool Cellule::get_p_sud() const{
     return p_sud;
     }
//________________________________________   
bool Cellule::get_p_est() const{
     return p_est;
     }
//________________________________________  
bool Cellule::get_p_ouest() const{
     return p_ouest;
     }
//________________________________________
void Cellule::set_x(int nx){
    x = nx ;
    }
//________________________________________
void Cellule::set_y(int ny){
    y = ny ;
    }
//________________________________________
void Cellule::set_id(int nid){
    id = nid ;
    }
//________________________________________
void Cellule::set_type(short ntype){
      type = ntype;
      }
//________________________________________
void Cellule::set_p_nord(bool np_nord){
     p_nord = np_nord;
     }
//________________________________________
void Cellule::set_p_sud(bool np_sud){
     p_sud = np_sud;
     }
//________________________________________ 
void Cellule::set_p_est(bool np_est){
     p_est =np_est;
     }
//________________________________________     
void Cellule::set_p_ouest(bool np_ouest){
      p_ouest = np_ouest;
     }
//________________________________________
void Cellule::set_visitee(bool nvisitee){
      visitee = nvisitee;
     }
