typedef struct {
  int nbj;          // nombre de joueurs max quand envoyé par le jeu et nb joueur réel renvoyé par module
  char nom[6][20];
  int coulj[6];
  char partie[20];
  int full;
  int pourc;
  int son;
} options;

int menufen(options *o);
