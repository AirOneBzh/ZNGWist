typedef struct {
  int nbj;          // nombre de joueurs max quand envoyé par le jeu et nb joueur réel renvoyé par module
  int ia[4];       // ia[0] nombre, ia[1,2,3]=1,2,3 niveau de chacune ia 0 -> pas une ia   si deux joueurs +1 bot -> [1]=0 [2]=1,2,3 pour l'instant uniquement 1
  char nom[4][20];
  char partie[20];
  int full;
  int pourc;
  int son;
} options;

int menufen(options *o);
