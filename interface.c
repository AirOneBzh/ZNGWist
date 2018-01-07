
// Module gérant l'interface graphique
// et les intéractions souris avec celle-ci
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "interface.h"
#include <MLV/MLV_all.h>




// affiche la carte du dessus d'une zone

void reset_fen(){
  MLV_clear_window(MLV_COLOR_WHITE);
  MLV_Image* tapis;
  tapis=MLV_load_image("assets/fond.png");
  int taille=MLV_get_window_height()/11;
  MLV_resize_image(tapis,taille*22,taille*11);
  MLV_draw_image(tapis,0,0);
  MLV_free_image(tapis);
  MLV_actualise_window();
}

// retourne dans x et y les variables correspondant à la case séléctionnée
coord wait_inter(int taille){
  MLV_Keyboard_button keyb;
  MLV_Keyboard_modifier keym;
  int r,u;

  coord c;
  r=MLV_wait_keyboard_or_mouse(&keyb,&keym,&u,&c.x,&c.y);
  if(r==MLV_KEY){
    c.x=-1;
    c.y=-1;
    if(keyb==MLV_KEYBOARD_ESCAPE){
      c.y=0;
    }
    if(keyb==MLV_KEYBOARD_s){
      c.y=1;
    }
    if(keyb==MLV_KEYBOARD_q){
      c.y=2;
    }
    if(keyb==MLV_KEYBOARD_f){
      c.y=3;
    }
    return c;
  }
  else if(r==MLV_MOUSE_BUTTON){

    c.x=c.x/taille;
    c.y=c.y/taille;
    return c;
  }
  return c;
}

coord conv_to_menu(coord c){
  coord r;
  int tailleh = MLV_get_desktop_height()*0.65;
  int carre = tailleh /10;
  if(c.x>46 && c.x<46+8.5*carre){
    if(c.y>232 && c.y<232+carre){
      r.x=1;
      r.y=0;
      if(c.x>465 && c.x<613){
        r.y=1;
      }
      if(c.x>651 && c.x<800){
        r.y=2;
      }
    }
    if(c.y>372 && c.y<372+carre){
      r.x=2;
      r.y=0;
      if(c.x>465 && c.x<613){
        r.y=1;
      }
      if(c.x>651 && c.x<800){
        r.y=2;
      }
    }
    if(c.y>511 && c.y<511+carre){
      r.x=3;
      r.y=0;
      if(c.x>465 && c.x<537){
        r.y=1;
      }
      if(c.x>559 && c.x<628){
        r.y=2;
      }
      if(c.x>653 && c.x<723){
        r.y=3;
      }
      if(c.x>746 && c.x<816){
        r.y=4;
      }
    }
    if(c.y>651 && c.y<651+carre){
      r.x=4;
      r.y=0;
      if(c.x>465 && c.x<564){
        r.y=1;
      }
      if(c.x>582 && c.x<688){
        r.y=2;
      }
      if(c.x>713 && c.x<812){
        r.y=3;
      }
    }
    if(c.y>790 && c.y<790+carre){
      r.x=5;
      r.y=0;
      if(c.x>465 && c.x<762){
        r.y=1;
      }
    }
  }
  return r;
}

coord conv_to_menj(coord c){
  coord r;
  //int tailleh = MLV_get_desktop_height()*0.65;
  //int carre = tailleh /10;
  r.x=0;
  r.y=0;
  if(c.x>46){
    if(c.y>94 && c.y<187){
      r.x=1;
    }
    if(c.y>232 && c.y<328){
      r.x=2;
    }
    if(c.y>371 && c.y<463){
      r.x=3;
    }
    if(c.y>511 && c.y<603){
      r.x=4;
    }
    if(c.y>650 && c.y<747){
      r.x=5;
    }
    if(c.y>789 && c.y<882){
      r.x=6;
    }
    if(r.x!=0 && c.x>468 && c.x<761){
      r.y=1;
    }
  }
  if(c.y<50){
    r.x=-1;
  }
  return r;
}
