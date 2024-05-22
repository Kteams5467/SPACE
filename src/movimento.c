#include <time.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

#include "movimento.h"
#include "menu.h"

#define MAX_BOMBE 1000

struct giocatore {
  int riga,colonna;
  char simbolo;
};

struct alieni {
  int riga,colonna;
  int pr,pc;
  int vivo; /* 1=vivo 0=distrutta */
  char direzione; /* 'l'=sinistra 'r'=destra */
  char simbolo;
};

struct proiettile {
  int riga,colonna;
  int attivo; /* 1=attivo 0=inattivo */
  char simbolo;
};

struct bomba {
  int riga,colonna;
  int attivo; /* 1=attivo 0=inattivo */
  int loop; /* serve per prevenire che gli alieni lampeggino al lancio della bomba */
  char simbolo;
};


int movimenti(int *punteggio, int *vincita, int *punteggioMax, int *opzioni_generali, int *opzioni_alieni, int *opzioni_proiettili, int *opzioni_bombe, int *opzioni_casualitaBomba){
  struct giocatore tank;
   struct alieni alieni[30];
   struct proiettile proiettile[3];
   struct bomba bomba[MAX_BOMBE];
   unsigned int input, loops=0, i=0, j=0, Attualiproiettili=0, Attualibombe=0, Attualialieni=30;
   int random=0;
   char mostraPunteggio[30], mostraPunteggioMax[30];

  /* Posizione del player */
   tank.riga = LINES - 1;
   tank.colonna = COLS / 2;

   tank.simbolo = '^';
  
  /* Inizializzazione degli alieni */
   for (i=0; i<10; i++) {
      alieni[i].riga = 1;
      alieni[i].colonna = i*3;
      alieni[i].pr = 0;
      alieni[i].pc = 0;
      alieni[i].simbolo = 'W';
      alieni[i].vivo = 1;
      alieni[i].direzione = 'r';
   }
   for (i=10; i<20; i++) {
      alieni[i].riga = 2;
      alieni[i].colonna = (i-10)*3;
      alieni[i].pr = 0;
      alieni[i].pc = 0;
      alieni[i].simbolo = 'W';
      alieni[i].vivo = 1;
      alieni[i].direzione = 'r';
   }
   for (i=20; i<30; i++) {
      alieni[i].riga = 3;
      alieni[i].colonna = (i-20)*3;
      alieni[i].pr = 0;
      alieni[i].pc = 0;
      alieni[i].simbolo = 'W';
      alieni[i].vivo = 1;
      alieni[i].direzione = 'r';
   }

  /* Crea l'oggetto proiettile */
   for (i=0; i<3; i++) {
      proiettile[i].attivo = 0;
      proiettile[i].simbolo = '|';
   }

   /* Crea l'oggetto bomba degli alieni */
   for (i=0; i<MAX_BOMBE; i++) {
      bomba[i].attivo = 0;
      bomba[i].simbolo = 'u';
      bomba[i].loop = 0;
  }

  init_pair(2,COLOR_GREEN,COLOR_BLACK);
   attron(COLOR_PAIR(2));
   move(0,(COLS/2)-9);
   addstr("--SPACE INVADERS--");
   move (0,1);
   addstr("SCORE: ");
   move(0,10);
   addstr("BEST SCORE: ");
   move(0,COLS-19);
   addstr("m = menu  x = esci");
   attroff(COLOR_PAIR(2));

  while(1) {

      init_pair(3,COLOR_GREEN,COLOR_BLACK);
      attron(COLOR_PAIR(3));
      move(0,(COLS/2)-9);
      addstr("--SPACE INVADERS--");
      move (0,1);
      addstr("SCORE: ");
      move(0,10);
      addstr("BEST SCORE: ");
      move(0,COLS-19);
      addstr("m = menu  x = esci");
      attroff(COLOR_PAIR(3));

      /* Mostra il punteggio massimo raggiunto*/
      sprintf(mostraPunteggioMax, "%d", *punteggioMax);
      move(0,23);
      addstr(mostraPunteggioMax);

      /* Mostra il punteggio */
      sprintf(mostraPunteggio, "%d", *punteggio);
      move(0,8);
      addstr(mostraPunteggio);

      /* Muove il tank */
      move(tank.riga,tank.colonna);
      addch(tank.simbolo);

      /* muove le bombe */
      if (loops % *opzioni_bombe == 0)
      for (i=0; i<MAX_BOMBE; i++) {
         if (bomba[i].attivo == 1) {
            if (bomba[i].riga < LINES) {
               if (bomba[i].loop != 0) {
                  move(bomba[i].riga-1,bomba[i].colonna);
                  addch(' ');
               }
               else
                  ++bomba[i].loop;

               init_pair(4,COLOR_RED,COLOR_BLACK);
               attron(COLOR_PAIR(4));
               move(bomba[i].riga,bomba[i].colonna);
               addch(bomba[i].simbolo);
               attroff(COLOR_PAIR(4));

               ++bomba[i].riga;
            }
            else {
               bomba[i].attivo = 0;
               bomba[i].loop = 0;
               --Attualibombe;
               move(bomba[i].riga - 1,bomba[i].colonna);
               addch(' ');
            }
         }
      }

      /* muove i proiettili */
      if (loops % *opzioni_proiettili == 0)
      for (i=0; i<3; i++) {
         if (proiettile[i].attivo == 1) {
            if (proiettile[i].riga > 0) {
               if (proiettile[i].riga < LINES - 2) {
                  move(proiettile[i].riga + 1,proiettile[i].colonna);
                  addch(' ');
               }

               for (j=0; j<30; ++j) {
                  if (alieni[j].vivo == 1 && alieni[j].riga == proiettile[i].riga && alieni[j].pc == proiettile[i].colonna) {
                     *punteggio += 20;
                     alieni[j].vivo = 0;
                     proiettile[i].attivo = 0;
                     --Attualiproiettili;
                     --Attualialieni;
                     move(alieni[j].pr,alieni[j].pc);
                     addch(' ');
                     break;
                  }
               }

               if (proiettile[i].attivo == 1) {

                  init_pair(5,COLOR_CYAN,COLOR_BLACK);
                  attron(COLOR_PAIR(5));
                  move(proiettile[i].riga,proiettile[i].colonna);
                  addch(proiettile[i].simbolo);
                  attroff(COLOR_PAIR(5));

                  --proiettile[i].riga;
               }
            }
            else {
               proiettile[i].attivo = 0;
               --Attualiproiettili;
               move(proiettile[i].riga + 1,proiettile[i].colonna);
               addch(' ');
            }
         }
      }     

      /* muove gli alieni */
      if (loops % *opzioni_alieni == 0)
      for (i=0; i<30; i++) {
         if (alieni[i].vivo == 1) {
            move(alieni[i].pr,alieni[i].pc);
            addch(' ');

            move(alieni[i].riga,alieni[i].colonna);
            addch(alieni[i].simbolo);

            alieni[i].pr = alieni[i].riga;
            alieni[i].pc = alieni[i].colonna;

          /* Controlla se gli alieni possono rilasciare la bomba*/
            random = 1+(rand()%100);
            if ((*opzioni_casualitaBomba - random) >= 0 && Attualibombe < MAX_BOMBE
            ) {
               for (j=0; j<MAX_BOMBE;j++) {
                  if (bomba[j].attivo == 0) {
                     bomba[j].attivo = 1;
                     Attualibombe++;
                     bomba[j].riga = alieni[i].riga + 1;
                     bomba[j].colonna = alieni[i].colonna;
                     break;
                  }
               }
            }

            /* Imposta gli alieni nella posizione seguente (destra e sinistra) */
            if (alieni[i].direzione == 'l')
               --alieni[i].colonna;
            else if (alieni[i].direzione == 'r')
               ++alieni[i].colonna;

            /* Imposta gli alieni nella posizione seguente (quando raggiungono il limite dello schermo  si spostano verso l'alto e il basso) */
            if (alieni[i].colonna == COLS - 2) {
               ++alieni[i].riga;
               alieni[i].direzione = 'l';
            }
            else if (alieni[i].colonna == 0) {
               ++alieni[i].riga;
               alieni[i].direzione = 'r';
            }
         }
      }


      /* Guarda se hai vinto o perso il gioco*/
      if (Attualialieni == 0) {
         *vincita = 1;
         break;
      }
      for (i=0; i<30; i++) {
         if (alieni[i].riga == LINES-1) {
            *vincita = 0;
            break;
         }
      }
      for (i=0; i<MAX_BOMBE
      ; i++) {
         if (bomba[i].riga == tank.riga && bomba[i].colonna == tank.colonna) {
            *vincita = 0;
            break;
         }
      }    

      move(0,COLS-1);
      refresh();
      usleep(*opzioni_generali);
      loops++;

      input = getch();
      move(tank.riga,tank.colonna);
      addch(' ');

      /* prende input */
      if (input == 'x')
         *vincita = 2;
      else if (input == KEY_LEFT)
         --tank.colonna;
      else if (input == KEY_RIGHT)
         ++tank.colonna;
      else if (input == ' ' && Attualiproiettili < 3) {
         for (i=0; i<3; i++) {
            if (proiettile[i].attivo == 0) {
               proiettile[i].attivo = 1;
               ++Attualiproiettili;
               --*punteggio;
               proiettile[i].riga = LINES - 2;
               proiettile[i].colonna = tank.colonna;
               break;
            }
         }
      }
      else if (input == 'm')
         menu(opzioni_generali, opzioni_alieni, opzioni_proiettili, opzioni_bombe, opzioni_casualitaBomba); 

      if (*vincita != -1)
         break;

      /* Verificare la posizione valida del serbatoio */
      if (tank.colonna > COLS-2)
         tank.colonna = COLS - 2;
      else if (tank.colonna < 0)
         tank.colonna = 0;     
   }
  return vincita, punteggio, punteggioMax;
}