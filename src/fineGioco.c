#include "fineGioco.h"
#include "Punteggio.h"
#include <ncurses.h>

/** Questa funzione determina se la partita è stata vinta o persa e stampa il messaggio adeguato in base a ciascuna delle due circostanze
*@param vincita è la variabile che determina la vincita o la sconfitta in base al valore che assume che può essere 0 o 1, il valore viene preso da main e viene passato alla funzione per permettere la stampa
*@param punteggio è il punteggio che viene passato da main questo valore viene passato poi in un altra funzione in un altro source code che salva in un file di testo il punteggio massimo raggiunto dal giocatore
*@param punteggioMax è il punteggio massimo raggiunto dal giocatore gia salvato in precedenza da un altra funzione in un altro source code che viene passato di nuovo alla funzione salvaPunteggio per controllare che il nuovo punteggio sia maggiore del vecchio prima di sovrascriverlo
*/
void fineGioco(int vincita, int punteggio, int punteggioMax){

  nodelay(stdscr, 0);

   if (vincita == 0) {
      clear();
      salvaPunteggio(punteggio, punteggioMax);
      init_pair(7, COLOR_RED, COLOR_BLACK);
      attron(COLOR_PAIR(7));
      move((LINES/2)-2,(COLS/2)-13);
      addstr("----------------------------------------");
      move((LINES/2)-1,(COLS/2)-13);
      addstr("|");
      move((LINES/2),(COLS/2)-13);
      addstr("|");
      move((LINES/2)-1,(COLS/2)-5);
      addstr("HAI PERSO!");
      move((LINES/2)-1,(COLS/2)+26);
      addstr("|");
      move((LINES/2),(COLS/2)+26);
      addstr("|");
      move((LINES/2),(COLS/2)-11);
      addstr("SCHIACCIA QUALUNQUE TASTO PER USCIRE");
      move((LINES/2)+1,(COLS/2)-13);
      addstr("----------------------------------------");
      move(0,COLS-1);
      refresh();
      getch();
      attroff(COLOR_PAIR(7));
   }

   else if (vincita == 1) {
      clear();
      salvaPunteggio(punteggio, punteggioMax);
      init_pair(8, COLOR_BLUE, COLOR_BLACK);
      attron(COLOR_PAIR(8));
      move((LINES/2)-2,(COLS/2)-5);
      addstr("--------------------");
      move((LINES/2)-2,(COLS/2)-13);
      addstr("----------------------------------------");
      move((LINES/2)-1,(COLS/2)-13);
      addstr("|");
      move((LINES/2),(COLS/2)-13);
      addstr("|");
      move((LINES/2)-1,(COLS/2)-5);
      addstr("|HAI VINTO!!!!|");
      move((LINES/2)-1,(COLS/2)+26);
      addstr("|");
      move((LINES/2),(COLS/2)+26);
      addstr("|");
      addstr("SCHIACCIA QUALUNQUE TASTO PER USCIRE");
      move((LINES/2)+1,(COLS/2)-13);
      addstr("----------------------------------------");
      move(0,COLS-1);
      refresh();
      getch();
      attroff(COLOR_PAIR(8));
   }
  
}