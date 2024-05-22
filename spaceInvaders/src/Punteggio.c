#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

#include "Punteggio.h"

/** Questa funzione apre un file di testo in scrittura nel quale viene salvato il punteggio ottenuto dal player prima di morire nel caso in cui esso sia maggiore del vecchio punteggio migliore
*@param punteggio è il punteggio ottenuto dal player prima della morte e serve per il controllo del punteggio migliore
*@param punteggioMax è il punteggio migliore ottenuto dal player in tutte le sue partite e serve anche questo per il controllo del punteggio migliore
*/
void salvaPunteggio(int punteggio, int punteggioMax){

  FILE *score;
  score = fopen("score.dat", "w");

  if (score == NULL) {
      printf("Errore nell'apertura del file");
      return;
  }

  else if(punteggio>punteggioMax){
    
      fprintf(score, "%d", punteggio);
    
    }

  else{
    
      fprintf(score, "%d", punteggioMax);
    
    }
  
  fclose(score);
}

/** La funzione apre un file di testo in lettura dal quale prende il valore salvato dalla funzione trovatasi nell'altro source code e lo restituisce nel main permettendo la visualizzazione in esso del punteggio massimo raggiunto dal giocatore
 * @return punteggioMax è il punteggio massimo raggiunto dal giocatore
*/
int caricaPunteggio(){

  int punteggioMax = 0;

  FILE *score;
  score = fopen("score.dat", "r");

  if (score == NULL) {
      printf("Errore nell'apertura del file");
      return punteggioMax;
  }

    while(fscanf(score, "%d", &punteggioMax)==1){};

  fclose(score);
  return punteggioMax;
}

/** Questa funzione permette a scelta dell'utente di eliminare il vecchio punteggio migliore salvato in un file di testo da un altra funzione presente in un altro source code 
*/
void cancellaScore(){

  int input;

       clear();
       nodelay(stdscr,0);
       init_pair(10,COLOR_RED,COLOR_BLACK);
       attron(COLOR_PAIR(10));
       move(23,(COLS/2)-25);
       addstr("SICURO DI VOLER CANCELLARE IL PUNTEGGIO?");
       move(26,(COLS/2)-15);
       addstr("1) SI");
       move(26,(COLS/2)-5);
       addstr("2) NO");
       attroff(COLOR_PAIR(10));
       refresh();

  while(1){

     move(27,(COLS/2)-8);

     input = getch();

     if(input == '1'){

        FILE *score;

           score = fopen( "score.dat", "w" );
           fprintf(score, "%d", 0);
           fclose(score);
           break;
        }

      else if(input != '1'){
         break;
    }
  }

   clear();
   noecho();
   cbreak();
   nodelay(stdscr,1);
}