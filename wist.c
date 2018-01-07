#include <stdlib.h>
#include <stdio.h>
#include "menu.h"
#include <MLV/MLV_all.h>
#include "wist.h"
#include "interface.h"

void j_suiv(int *j,int nbj){
  *j+=1;
  if(*j==nbj){
    *j=0;
  }
}

int main(int argc,char *argv[]){
  options o;
  int w,h,i,j;
  int nbca[20];
  int tour=0,jou=0,u=0,part=0,jtour=0,coult;
  char dist[3],cdate[30],cpaq[30],cdesc[30];
  coord c;
  date d;
  w=MLV_get_desktop_width();
  h=MLV_get_desktop_height();
  //MLV_Color lcoul[10];
  //jaune orange - vert bleu - rose rouge
  MLV_get_date(NULL,&d.min,&d.h,&d.j,&d.m,&d.a,NULL);
  d.m++;
  sprintf(cdate,"%d/%d/%d %d:%d",d.j,d.m,d.a,d.h,d.min);

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

  if(menufen(&o)==0){
    return 0;
  }
  MLV_get_date(NULL,&d.min,&d.h,&d.j,&d.m,&d.a,NULL);
  d.m=d.m+1;
  sprintf(cdate,"%d/%d/%d %d:%d",d.j,d.m,d.a,d.h,d.min);
  sprintf(cpaq,"paquet de %d cartes",14+o.nbj);
  sprintf(cdesc,"de %d a 10, V D R As",9-(o.nbj-3)*2);

  for(i=1;i<8;i++){
    nbca[i-1]=i;
  }
  for(j=0;j<o.nbj;j++){
    nbca[i]=8;
    i++;
  }
  for(j=7;j>0;j--){
    nbca[i]=j;
    i++;
  }

  if(o.full==1){
    MLV_create_full_screen_window("ZNG Wist","ZNG Wist",w,h);
  }
  else{
    MLV_create_window("ZNG Wist","ZNG Wist",w*o.pourc/100,h*o.pourc/100);
  }

  MLV_Font* font=MLV_load_font("assets/pricedown.ttf",200);
  MLV_Font* font1=MLV_load_font("assets/pricedown.ttf",60);
  MLV_Font* font2=MLV_load_font("assets/digital-7.ttf",60);
  MLV_Font* font3=MLV_load_font("assets/pricedown.ttf",25);
  MLV_draw_line(0.35*w,0,0.35*w,h,MLV_COLOR_WHITE);
  printf("h%d w%d\n",h,w);
  i=0;
  MLV_draw_text_with_font(20,350,cdate,font2,MLV_COLOR_LIGHT_GRAY);
  MLV_draw_text_with_font(20,450,cpaq,font2,MLV_COLOR_LIGHT_GRAY);
  MLV_draw_text_with_font(20,550,cdesc,font2,MLV_COLOR_LIGHT_GRAY);
  MLV_draw_text_box_with_font(50,1300,100,100,"-1",font1,0,MLV_COLOR_LIGHT_GRAY,MLV_COLOR_BLACK,MLV_COLOR_LIGHT_GRAY,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
  MLV_draw_text_box_with_font(200,1300,100,100,"+1",font1,0,MLV_COLOR_LIGHT_GRAY,MLV_COLOR_BLACK,MLV_COLOR_LIGHT_GRAY,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
  MLV_draw_text_box_with_font(350,1300,200,100,"Joueur Suivant",font3,0,MLV_COLOR_LIGHT_GRAY,MLV_COLOR_BLACK,MLV_COLOR_LIGHT_GRAY,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
  MLV_draw_text_box_with_font(600,1300,100,100,"OK",font1,0,MLV_COLOR_LIGHT_GRAY,MLV_COLOR_BLACK,MLV_COLOR_LIGHT_GRAY,MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);

  while(u!='q' && i<15){
    coult=o.coulj[jtour]+1;
    printf("coult%d %d \n",coult,jtour);
    MLV_draw_filled_rectangle(0,0,w*0.34,250,MLV_COLOR_BLACK);
    sprintf(dist,"%s %d",o.nom[jtour],nbca[jtour]);
    MLV_draw_text_with_font(20,0,dist,font,lcoul[3]);
    MLV_draw_rectangle(40,1250,270,175,MLV_COLOR_WHITE);
    if(part==0){
      MLV_draw_filled_rectangle(70,1260,230,30,MLV_COLOR_BLACK);
      MLV_draw_text_with_font(80,1260,"Demande de plis",font3,MLV_COLOR_LIGHT_GRAY);
    }
    else{
      MLV_draw_filled_rectangle(70,1260,230,30,MLV_COLOR_BLACK);
      MLV_draw_text_with_font(100,1260,"Plis réalisés",font3,MLV_COLOR_LIGHT_GRAY);
    }
    MLV_actualise_window();
    MLV_wait_keyboard_or_mouse(NULL,NULL,&u,&c.x,&c.y);
    i++;
    if(c.x>350 && c.x<550 && c.y>1300 && c.y<1400){
      j_suiv(&jou,o.nbj);
    }
    if(c.x>600 && c.x<700 && c.y>1300 && c.y<1400){
      part=1-part;
      if(part==0){
        tour++;
        jtour++;
        if(jtour==o.nbj){
          jtour=0;
        }
      }
    }
  }

  MLV_free_window();
  //MLV get date NULL min heures jj mm aaaa J  J int 0-6

}
