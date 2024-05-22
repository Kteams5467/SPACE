/* Space Invaders

   GRUPPO Zappia, Ponassi, Parodi

   Il gioco funziona muovendo la navicella in basso nello schermo rappresentata da "^" e sparando con la barra spaziatrice. mentre si spara bisogna fare attenzione a schivare i colpi delle navicelle nemiche. il punteggio viene incrementato ogni volta che si uccide una navicella nemica. le navicelle nemiche pero si possono muovere spostandosi ogni volta verso il basso una volta raggiunto il  bordo dello schermo.
Ogni 3 colpi sparati la navicella ricarica altri 3 colpi usando 3 punti del giocatore.

*/

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "fineGioco.h"
#include "menu.h"
#include "Punteggio.h"
#include "movimento.h"

#define MAX_BOMBE 1000

/* Space Invaders */

/**il main gestisce all'inizio l'input dell'utente per decidere se vuole giocare, modificare le impostazioni, cancellare il vecchio punteggio migliore o uscire dal gioco, se sceglie di giocare il main si occupa di gestire il nuovo input dell'utente che questa volta gestisce il movimento del player, degli alieni e i loro corrispettivi proiettili. dentro il main sono presente poi le altre funzioni chiamate dagli headers
*/
int main() {

   int punteggio=0, vincita=-1, punteggioMax;
   
   int opzioni_generali=15000, opzioni_alieni=12, opzioni_proiettili=3, opzioni_bombe=10, opzioni_casualitaBomba=5;   

   unsigned int sceltaInizio;
   
   initscr();
   clear();
   noecho();
   cbreak();
   nodelay(stdscr,1);
   keypad(stdscr,1);
   srand(time(NULL)); 

   //Selezione all'avvio del gioco
   do{
      start_color();
      init_pair(1,COLOR_GREEN,COLOR_BLACK);
      attron(COLOR_PAIR(1));
      sceltaInizio = getch();
      move(0,(COLS/2)-12);
      addstr("--------------------");
      move(1,(COLS/2)-12);
      addstr("|--SPACE INVADERS--|");
      move(2,(COLS/2)-12);
      addstr("--------------------");
         move(15,(COLS/2)-9);
         addstr("1) GIOCA");
         move(19,(COLS/2)-9);
         addstr("2) OPZIONI");
         move(23,(COLS/2)-15);
         addstr("3) CANCELLA BEST SCORE");
         move(27,(COLS/2)-9);
         addstr("4) ESCI");
      attroff(COLOR_PAIR(1));
      
      refresh();
      
   switch(sceltaInizio){
      case '1':{
         goto Gioco;
         }
      case '2':{
         menu(&opzioni_generali, &opzioni_alieni, &opzioni_proiettili, &opzioni_bombe, &opzioni_casualitaBomba);
         break;
         }
      case '3':{
         cancellaScore();
         break;
         }
      default:{
         break;
         }
      }
      
   } while (sceltaInizio != '4');

   if (sceltaInizio == '4'){
      clear();
      endwin();
      return 0;
   }
   
//Inizio del gioco
Gioco:   

punteggioMax = caricaPunteggio();

   clear();

   movimenti(&punteggio, &vincita, &punteggioMax, &opzioni_generali, &opzioni_alieni, &opzioni_proiettili, &opzioni_bombe, &opzioni_casualitaBomba);

   fineGioco(vincita, punteggio, punteggioMax);
   endwin();
   return 0;
}