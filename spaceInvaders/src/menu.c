#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

/** Funzione che gestisce le *opzioni del menu a disposizione dell'utente permettendoli di modificare ciascuna di esse che comprendono la velocita del gioco ma anche la possibilità di uscire da esso e ritornarci nel momento in cui il giocatore ha finito di modificare le impostazioni
 * @param *opzioni_generali gestisce la velocità generale del gioco
 * @param *opzioni_alieni gestisce la velocità degli alieni
 * @param *opzioni_proiettili gestisce la velocità dei proiettili della navicella
 * @param *opzioni_bombe gestisce la velocità delle bombe
 * @param *opzioni_casualitaBomba gestisce la frequenza con cui vengono generate le bombe degli alieni
*/ 

int menu(int *opzioni_generali, int *opzioni_alieni, int *opzioni_proiettili, int *opzioni_bombe, int *opzioni_casualitaBomba) {

   char opzione, buf[30];
   int nuovo;

   clear();
   echo();
   nocbreak();
   nodelay(stdscr,0);

   init_pair(6,COLOR_CYAN,COLOR_BLACK);
   attron(COLOR_PAIR(6));
   move(1,0);
   addstr("1. Cambia la velocita di gioco generale");
   move(2,0);
   addstr("2. Cambia la velocita di movimento degli alieni:");
   move(3,0);
   addstr("3. Cambia la velocita del proiettile del player: ");
   move(4,0);
   addstr("4. Cambia la velocita della bomba degli alieni: ");
   move(5,0);
   addstr("5. Cambia la frequenza di caduta delle bombe degli alieni:");
   move(6,0);
   addstr("6. Ritorna al gioco");
   move(7,0);
   addstr("7. Esci dal gioco");
   move(8,0);
   addstr("Inserisci la tua scelta: ");
   refresh();
   attroff(COLOR_PAIR(6));

   while(1) {
      move(8,25);
      opzione = getch();
      move(9,0);
      deleteln();
      move(10,0);
      deleteln();
      move(11,0);
      deleteln();

      if (opzione == '1') {
         sprintf(buf,"Valore corrente: %d\n", *opzioni_generali);

         move(9,0);
         addstr(buf);
         move(10,0);
         addstr("Inserisci il nuovo valore: ");
         move(10,27);
         refresh();
         getch();
         getstr(buf);

         nuovo = atoi(buf);

         /* Verificare la presenza di un nuovo valore valido */
         if (nuovo < 0) {
            move(11,0);
            addstr("ERRORE: Valore non valido");
         }
         else {
            *opzioni_generali = nuovo;
         }  
      }
      else if (opzione == '2') {
         sprintf(buf,"Valore corrente: %d\n", *opzioni_alieni);

         move(9,0);
         addstr(buf);
         move(10,0);
         addstr("Inserisci il nuovo valore: ");
         move(10,27);
         refresh();
         getch();
         getstr(buf);

         nuovo = atoi(buf);
             move(10,0);
             addstr("Inserisci il nuovo valore: ");
             move(10,27);
             refresh();
             getch();
             getstr(buf);
             getch();

      /* Verificare la presenza di un nuovo valore valido */
         if (nuovo <= 0) {
            move(11,0);
            addstr("ERRORE: Valore non valido ");
         }
         else {
            *opzioni_alieni = nuovo;
         }  
      }
      else if (opzione == '3') {
         sprintf(buf,"Valore corrente: %d\n", *opzioni_proiettili);

         move(9,0);
         addstr(buf);
         move(10,0);
         addstr("Inserisci il nuovo valore: ");
         move(10,27);
         refresh();
         getch();
         getstr(buf);

         nuovo = atoi(buf);

         /* Verificare la presenza di un nuovo valore valido */
         if (nuovo <= 0) {
            move(11,0);
            addstr("ERRORE: Valore non valido ");
         }
         else {
            *opzioni_proiettili = nuovo;
         }  
      }
      else if (opzione == '4') {
         sprintf(buf,"Valore corrente: %d\n", *opzioni_bombe);

         move(9,0);
         addstr(buf);
         move(10,0);
         addstr("Inserisci il nuovo valore: ");
         move(10,27);
         refresh();
         getch();
         getstr(buf);

         nuovo = atoi(buf);

         /* Verificare la presenza di un nuovo valore valido */
         if (nuovo <= 0) {
            move(11,0);
            addstr("ERRORE: Valore non valido ");
         }
         else {
            *opzioni_bombe = nuovo;
         }  
      }
      else if (opzione == '5') {
         sprintf(buf,"Valore corrente: %d\n", *opzioni_casualitaBomba);

         move(9,0);
         addstr(buf);
         move(10,0);
         addstr("Inserisci il nuovo valore: ");
         move(10,27);
         refresh();
         getch();
         getstr(buf);

         nuovo = atoi(buf);

         /* Verificare la presenza di un nuovo valore valido */
         if (nuovo > 100 || nuovo < 0) {
            move(11,0);
            addstr("ERRORE: Valore non valido ");
         }
         else {
            *opzioni_casualitaBomba = nuovo;
         }  
      }
      else if (opzione == '6') {
         break;
      }
      else if (opzione == '7') {
         endwin();
         exit(0);
      }
      else {
         move(9,0);
         addstr("ERRORE: Selezione non valida");
         move(8,19);
         addstr(" ");
         refresh();        
      }
   }
   
   clear();
   noecho();
   cbreak();
   nodelay(stdscr,1);

   return *opzioni_generali, *opzioni_alieni, *opzioni_proiettili, *opzioni_bombe , *opzioni_casualitaBomba;
   
}
