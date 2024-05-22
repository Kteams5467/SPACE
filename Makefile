CC=gcc

CFLAGS=-Iinclude

TARGET=spaceInvaders

$(TARGET): main.o fineGioco.o menu.o Punteggio.o movimento.o
	$(CC) -o $(TARGET) main.o fineGioco.o menu.o Punteggio.o movimento.o -lncurses

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -lncurses

fineGioco.o: src/fineGioco.c include/fineGioco.h
	$(CC) $(CFLAGS) -c src/fineGioco.c -lncurses

menu.o: src/menu.c include/menu.h
	$(CC) $(CFLAGS) -c src/menu.c -lncurses

Punteggio.o: src/Punteggio.c include/Punteggio.h
	$(CC) $(CFLAGS) -c src/Punteggio.c

movimento.o: src/movimento.c include/movimento.h
	$(CC) $(CFLAGS) -c src/movimento.c -lncurses

clean:
	rm -f *.o $(TARGET)