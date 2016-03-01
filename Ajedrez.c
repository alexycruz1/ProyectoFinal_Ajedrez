#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void llenar_tablero(char**);


int main(){
	int contador_turnos = 2;
	int size = 8;

	char **matriz;
	matriz = (char **)malloc (size*sizeof(char *));

	for (int i=0;i<size;i++){
		matriz[i] = (char *) malloc (size*sizeof(char));
	}

	llenar_tablero(matriz);

	while(getch() != 'j'){
		int y = 10;
		int x = 5;
		clear();
	if (contador_turnos % 2 == 0){
		initscr();
  		(void)echo();
  		move(0, 10);
  		printw("Es turno del jugador #1: ");
  		move(x,y);
  		move(x++, y);
  	for (int i = 0; i < size; i++){
    	for (int j = 0; j < size; j++){
      		start_color();
      		init_pair(1, COLOR_BLUE, COLOR_BLACK);
      		attron(COLOR_PAIR(1));
      		printw("[%c] ", matriz[i][j]);
      		refresh();
    	}
    	printw("\n");
    	move(x++, y);
  	}
  	refresh();
  	getch();
  	contador_turnos++;	
	}else{
		initscr();
  		(void)echo();
  		move(0, 10);
  		printw("Es turno del jugador #2: ");
  		move(x,y);
  		move(x++, y);
  	for (int i = 0; i < size; i++){
    	for (int j = 0; j < size; j++){
      		start_color();
      		init_pair(1, COLOR_GREEN, COLOR_BLACK);
      		attron(COLOR_PAIR(1));
      		printw("[%c] ", matriz[i][j]);
      		refresh();
    	}
    	printw("\n");
    	move(x++, y);
  	}
  	refresh();
  	getch();
  	contador_turnos++;
	}
	}

  	endwin();
	return 0;
  } 

  void llenar_tablero(char** matriz){
	int size = 8;

	//llenado jugador 1
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (i == 1){//peones
				matriz[i][j] = 'P';
			}else if((i == 0 && j == 0) || (i == 0 && j == size - 1)){//torres
				matriz[i][j] = 'T';
			}else if ((i == 0 && j == 1) || (i == 0 && j == size - 2)){//Caballos
				matriz[i][j] = 'C';
			}else if ((i == 0 && j == 2) || (i == 0 && j == size - 3)){//Alfiles
				matriz[i][j] = 'A';
			}else if ((i == 0 && j == 3)){//Dama
				matriz[i][j] = 'D';
			}else if ((i == 0 && j == 4)){//Rey
				matriz[i][j] = 'R';
			}
		}
	}

	//llenado jugador 2
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (i == size - 2){//peones
				matriz[i][j] = 'P';
			}else if((i == size - 1 && j == 0) || (i == size - 1 && j == size - 1)){//torres
				matriz[i][j] = 'T';
			}else if ((i == size - 1 && j == 1) || (i == size - 1 && j == size - 2)){//Caballos
				matriz[i][j] = 'C';
			}else if ((i == size - 1 && j == 2) || (i == size - 1 && j == size - 3)){//Alfiles
				matriz[i][j] = 'A';
			}else if ((i == size - 1 && j == 3)){//Dama
				matriz[i][j] = 'D';
			}else if ((i == size - 1 && j == 4)){//rey
				matriz[i][j] = 'R';
			}else if(i == 2 || i == 3 || i == 4 || i == 5 || i == 6){
				matriz[i][j] = '.';
			}
		}
	}
}//gcc -o aje Ajedrez.c -lncurses
