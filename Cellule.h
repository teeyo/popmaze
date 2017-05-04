#ifndef CELLULE_H
#define CELLULE_H
class Cellule {
      private:
              // les coordonnées x et y de la cellule et son identifiant ( le numéro de la cellule allant de 0 jusqu'à 
              // largeur * hauteur du labyrinthe
              int x , y , id ;
              // visitée booléen indiquant si la cellule à déjà été visitée
              // et biensûr les quatre portes ou bien mures de la cellule
              bool visitee , p_nord , p_sud, p_est, p_ouest ;
              // le type de la cellule selon le nombre de mure, exemple :
                    // aucun mure : type 0 , 4 mures : type 1 , sans le mure du nord : type 3 ... etc
              short type ;
      public:
             // constructeur
             Cellule();
             // destructeur
             ~Cellule();
             // les getters et les setters
             int  get_x() const ;
             int  get_y() const;
             int  get_id() const;
             bool get_visitee() const;
             short get_type() const;
             bool get_p_nord() const;
             bool get_p_sud() const;
             bool get_p_est() const;
             bool get_p_ouest() const;
             void  set_p_nord(bool);
             void  set_p_sud(bool);
             void  set_p_est(bool);
             void  set_p_ouest(bool);
             void  set_x(int);
             void  set_y(int);
             void set_id(int);
             void set_type(short);
             void set_visitee(bool);   
      };
#endif
