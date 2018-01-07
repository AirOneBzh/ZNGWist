#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "interface.h"
#include <MLV/MLV_all.h>
#include <string.h>

void bouton(char *nom,int x){
  int carre = MLV_get_desktop_height()*0.65/10;

  MLV_Color fond = MLV_rgba(40,40,40,255);            // variables à changer pour les couleurs du menu
  MLV_Color text = MLV_COLOR_WHITE;
  MLV_Font* font=MLV_load_font("assets/pricedown.ttf",0.65*carre);
  MLV_draw_filled_rectangle(0.5*carre,(1+1.5*x)*carre,8.5*carre,carre,text);
  MLV_draw_text_with_font(carre,(1+1.5*x)*carre,nom,font,fond);
}

void sous_bouton(char *nom,int x,int y,int n,int sel){   // x pour quel bouton vertical y combien sur les boutons horiz et combien boutons horiz total
  int carre = MLV_get_desktop_height()*0.65/10;
  int bx,by; //coords des coins NO des boutons

  MLV_Color lcoul[9]={
    MLV_COLOR_DARK_RED,     //-1
    MLV_rgba(40,40,40,255), // 0 fond
    MLV_COLOR_DARK_GREEN,   // 1
    MLV_COLOR_BLUE,         //   5
    MLV_COLOR_ORANGE,       //   3
    MLV_COLOR_YELLOW,       //   2    joueurs
    MLV_COLOR_GREEN,        //   4
    MLV_COLOR_DEEPPINK,         //   6
    MLV_COLOR_FIREBRICK           //   7
  };

  bx = 5*carre+(4*(y-1)*carre)/n;
  by=(1.1+1.5*x)*carre;
  MLV_Color fond;          // variables à changer pour les couleurs du menu
  MLV_Color text = MLV_COLOR_WHITE;
  fond=lcoul[sel+1];

  MLV_Font* font=MLV_load_font("assets/pricedown.ttf",0.3*carre);    //max 9 caractère
  MLV_draw_text_box_with_font(bx,by,(4*0.8*carre)/n,0.8*carre,nom,font,0.7,text,text,fond,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
}



void aff_menu(char *nom,int carre,options o){

  MLV_Image* header = MLV_load_image("assets/header.png");
  MLV_resize_image(header,9.5*carre,carre);

  int tailleh = MLV_get_desktop_height()*0.65;
  MLV_change_window_size(((1.5*5)+2)*carre,tailleh);
  MLV_Color fond = MLV_rgba(40,40,40,255);        // variables à changer pour les couleurs du menu
  //MLV_Font* font=MLV_load_font("assets/pricedown.ttf",0.65*carre);
  MLV_clear_window(fond);
  MLV_draw_image(header,0.2*carre,0.1*carre);
  //Lancer jeu charger partie
  bouton(nom,1);
  sous_bouton("Charger",1,1,2,0);
  sous_bouton("Stats",1,2,2,0);
  // Règles
  bouton("Règles",2);
  sous_bouton("PDF",2,1,2,0);
  sous_bouton("HTML",2,2,2,0);
  // Joueurs et bots
  bouton("Joueurs",3);
  sous_bouton("3",3,1,4,0);
  sous_bouton("4",3,2,4,1);
  sous_bouton("5",3,3,4,0);
  sous_bouton("6",3,4,4,0);
  //Affichage
  bouton("Options",4);
  sous_bouton("95",4,1,3,0);
  sous_bouton("Son",4,2,3,o.son);
  sous_bouton("Pl.Ec.",4,3,3,o.full);
  //quitter
  bouton("Quitter",5);
  sous_bouton("Autres jeux",5,1,1,0);
  MLV_actualise_window();
}

// menuc nombre d'entrees, menuv titre menu
int menufen(options *o){
  char tmp[3],jnum[2];
  int tailleh = MLV_get_desktop_height()*0.65;
  int carre = tailleh /10,i,f=0;
  char *inom;
  MLV_create_window("Menu","Menu",((1.5*5)+2)*carre,tailleh);
  MLV_Font* font=MLV_load_font("assets/pricedown.ttf",35);
  int w,h;
  w=MLV_get_window_width();
  h=MLV_get_window_height();
  o->pourc=95;
  o->full=1;
  o->son=1;
  o->nbj=4;
  for(i=0;i<6;i++){
    sprintf(o->nom[i],"J%d",i+1);
    o->coulj[i]=i+2;
  }
  aff_menu("Wist",carre,*o);

  coord r,c,rmj,cmj;
  //r coord de retour fct wait_inter rmj " pour menu joueurs
  // r-> c après conversion
  MLV_actualise_window();
  while(1){
    r=wait_inter(1);
    if(c.x>-1){
      c=conv_to_menu(r);
      if(c.x==1){
        if(c.y==2){
          system("xdg-open save/classement.txt");
        }
        if(c.y==0){
          MLV_free_window();
          return 1;
        }
      }

      if(c.x==2){
        if(c.y==0){
          system("xdg-open README.md");
        }
        if(c.y==1){
          system("xdg-open README.pdf");

        }
        if(c.y==2){
          system("xdg-open https://aironebzh.github.io/ZkipBoGA/");
        }
      }
      //joueurs
      if(c.x==3){
        printf("%d %d\n",r.x,c.y);
        if(c.y!=0){
          o->nbj=c.y+2;
          bouton("Joueurs",3);
          for(i=0;i<4;i++){
            sprintf(jnum,"%d",i+3);
            if(i+3==o->nbj){
              sous_bouton(jnum,3,i+1,4,1);
            }
            else{
              sous_bouton(jnum,3,i+1,4,0);
            }
          }
          MLV_actualise_window();
        }
        else{
          MLV_change_window_size(9*carre,(1.5*(o->nbj+1))*carre);
          MLV_clear_window(MLV_rgba(40,40,40,255));
          for(i=0;i<o->nbj;i++){
            bouton(o->nom[i],i);
            sous_bouton("",i,1,1,o->coulj[i]);
          }
          MLV_draw_filled_rectangle(0,0,w,50,MLV_COLOR_WHITE);
          MLV_draw_text_with_font(50,10,"Retour",font,MLV_COLOR_BLACK);
          MLV_draw_text_with_font(50,55,"5 caractère max",font,MLV_COLOR_WHITE);
          MLV_actualise_window();
          while(f==0){
            rmj=wait_inter(1);
            if(rmj.x>-1){
              cmj=conv_to_menj(rmj);
              printf("cmj %d %d\n",rmj.x,rmj.y);
              if(cmj.x==-1){
                f=1;
              }
              if(cmj.x>=1 && cmj.x<=o->nbj){
                if(cmj.y==0){
                  MLV_wait_input_box(
                    w*0.3,h*0.45,
                    w*0.4,h*0.1,
                    MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
                    "Votre nom : ",
                    &inom
                  );
                  strncpy(o->nom[cmj.x-1],inom,5);

                  bouton(o->nom[cmj.x-1],cmj.x-1);
                  sous_bouton("",cmj.x-1,1,1,o->coulj[cmj.x-1]);
                }
                else{
                  o->coulj[cmj.x-1]++;
                  if(o->coulj[cmj.x-1]==8){
                    o->coulj[cmj.x-1]=2;
                  }
                  printf("%d",o->coulj[cmj.x-1]);
                  sous_bouton("",cmj.x-1,1,1,o->coulj[cmj.x-1]);
                }
              }
              MLV_actualise_window();
            }
            else{
              if(rmj.y==2){
                MLV_free_window();
                return 0;
              }
            }
          }
          aff_menu("Wist",carre,*o);
        }
      }

      if(c.x==4){
        if(c.y==1){
          o->pourc-=10;
          if(o->pourc<60){
            o->pourc=95;
          }
          sprintf(tmp,"%d",o->pourc);
          printf("%s\n",tmp);
          sous_bouton(tmp,4,1,3,0);
          MLV_actualise_window();
        }
        if(c.y==2){
          o->son=-o->son;
          sous_bouton("Son",4,2,3,o->son);
          MLV_actualise_window();
        }
        if(c.y==3){
          o->full=-o->full;
          sous_bouton("Pl.Ec.",4,3,3,o->full);
          MLV_actualise_window();
        }

      }
      if(c.x==5){
        MLV_free_window();
        if(c.y==1){
          system("xdg-open https://aironebzh.github.io/");
        }
        return 0;
      }
    }
    else{
      if(r.y==2){
        MLV_free_window();
        return 0;
      }
      if(r.y==3){
        o->full=-o->full;
        sous_bouton("Pl.Ec.",4,3,3,o->full);
        MLV_actualise_window();
      }
    }
  }

  MLV_free_window();
  return 0;


}
