#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void llenar_tablero(char**);
void ciclo_juego();
bool entrada_movida(char[], int);
bool verificar_pieza(char[], int, int);


int main(int argc, char*argv[]){
	ciclo_juego();

  	endwin();
	return 0;
}//fin del main


void ciclo_juego(){//juego completo
	int contador_turnos = 2;
	int size = 8;
	int size_movement = 5;
	char movement[size_movement];
	char pasar;
	int ganador = 1;

	char **matriz;
	matriz = (char **)malloc (size*sizeof(char *));

	for (int i=0;i<size;i++){
		matriz[i] = (char *) malloc (size*sizeof(char));
	}

	llenar_tablero(matriz);

	while(ganador){
		int y = 10;
		int x = 5;
		clear();

		if (contador_turnos % 2 == 0){
			initscr();
  			(void)echo();

  			move(0, 10);
  			start_color();
      		init_pair(1, COLOR_BLUE, COLOR_BLACK);
      		attron(COLOR_PAIR(1));
  			printw("Es turno del jugador #1");
  			move(4, 10);
  			printw(" A   B   C   D   E   F   G   H");

  			refresh();
  			move(x,y);
  			refresh();
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
  		move(13, 10);
  		printw(" A   B   C   D   E   F   G   H");

  		int pos_coordenada1 = 5;
  		for (int i = 0; i < 8; i++){
  			move(pos_coordenada1, 8);
  			printw("%i",8 - i);
  			pos_coordenada1++;
  		}

  		pos_coordenada1 = 5;
  		for (int i = 0; i < 8; i++){
  			move(pos_coordenada1, 42);
  			printw("%i",8 - i);
  			pos_coordenada1++;
  		}

  		move(15, 10);
  		addstr("Ingrese el movimiento: ");
  		getnstr(movement, sizeof(movement) - 1);
  		printw(movement);
  		entrada_movida(movement, size_movement);
  		

  		refresh();

  		contador_turnos++;	
		}else{
			initscr();
  			(void)echo();

  			move(0, 10);
  			printw("Es turno del jugador #2");
  			move(4, 10);
  			printw(" A   B   C   D   E   F   G   H");

  			refresh();
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
  		move(13, 10);
  		printw(" A   B   C   D   E   F   G   H");

  		int pos_coordenada1 = 5;
  		for (int i = 0; i < 8; i++){
  			move(pos_coordenada1, 8);
  			printw("%i",8 - i);
  			pos_coordenada1++;
  		}

  		pos_coordenada1 = 5;
  		for (int i = 0; i < 8; i++){
  			move(pos_coordenada1, 42);
  			printw("%i",8 - i);
  			pos_coordenada1++;
  		}

  		move(15, 10);
  		addstr("Ingrese el movimiento: ");
  		getnstr(movement, sizeof(movement) - 1);
  		entrada_movida(movement, size_movement);

  		refresh();
  		
  		contador_turnos++;
		}
	}
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
				matriz[i][j] = 'p';
			}else if((i == size - 1 && j == 0) || (i == size - 1 && j == size - 1)){//torres
				matriz[i][j] = 't';
			}else if ((i == size - 1 && j == 1) || (i == size - 1 && j == size - 2)){//Caballos
				matriz[i][j] = 'c';
			}else if ((i == size - 1 && j == 2) || (i == size - 1 && j == size - 3)){//Alfiles
				matriz[i][j] = 'a';
			}else if ((i == size - 1 && j == 3)){//Dama
				matriz[i][j] = 'd';
			}else if ((i == size - 1 && j == 4)){//rey
				matriz[i][j] = 'r';
			}else if(i == 2 || i == 3 || i == 4 || i == 5 || i == 6){
				matriz[i][j] = '.';
			}
		}
	}
}

bool entrada_movida(char movement[], int size){// 48 a 57 son numeros = 65 a 72 de la A a la H == 97 a 104 minusculas
	int nums = 0;
	int chars = 0;
	char temp;
	bool movim_correcto = false;

	if (movement[0] >= 48 && movement[0] <= 57){
		nums++;
	}

	if ((movement[1] >= 65 && movement[1] <= 72) || (movement[1] >= 97 && movement[1] <= 104)){
		chars++;
	}

	if (movement[2] >= 48 && movement[2] <= 57){
		nums++;
	}

	if ((movement[1] >= 65 && movement[1] <= 72) || (movement[1] >= 97 && movement[1] <= 104)){
		chars++;	
	}

	if (nums == 2 && chars == 2){
		movim_correcto = true;
	}else{
		movim_correcto = false;
	}

	return movim_correcto;
}

bool verificar_pieza(char movement[], int size, int contador_turnos){//65 a 72 de la A a la H == 97 a 104 minusculas
	int cont_piezaExiste = 0
	int x1, y1, x2, y2;

	if (contador_turnos % 2 == 0){//pieza debe ser mayuscula, turno jugador 1
		int revisar_mayus = movement[1];
		if ((revisar_mayus >= 65 && revisar_mayus <= 72) && ()){
			x1 = movement[0];
			y1 = movement[1];
		}

		

	}else{

	}
}


//gcc -o aje Ajedrez.c -lncurses

/*	   A  B  C  D  E  F  G  H
	8 [T][C][A][D][R][A][C][T] 8
	7 [P][P][P][P][P][P][P][P] 7
	6 [.][.][.][.][.][.][.][.] 6
	5 [.][.][.][.][.][.][.][.] 5
	4 [.][.][.][.][.][.][.][.] 4
	3 [.][.][.][.][.][.][.][.] 3
	2 [P][P][P][P][P][P][P][P] 2
	1 [T][C][A][D][R][A][C][T] 1
	   A  B  C  D  E  F  G  H*/
