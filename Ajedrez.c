#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void llenar_tablero(char**);
void ciclo_juego();
bool entrada_movida(char[], int);
bool verificar_pieza_mayus(int, int, char**);
char traer_char(int, int, char**);
void mover(int, int, int, int, char, char**);
bool mover_peon(int, int, int, int, char**);
bool mover_torre(int, int, int, int, char**);



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

  		if (entrada_movida(movement, size_movement)){//lo de abajo depende de esto
  			int x1, y1, x2, y2;

		if (contador_turnos % 2 == 0){//pieza debe ser mayuscula, turno jugador 1
			//convertir entrada en coordenadas
			x1 = movement[0];
			y1 = movement[1];
			x2 = movement[2];
			y2 = movement[3];

			x1 = x1 - 49;
			if (y1 >= 65 && y1 <= 72){
				y1 = y1 - 65;
			}else{
				y1 = y1 - 97; 
			}

			x2 = x2 - 49;
			if (y2 >= 65 && y2 <= 72){
				y2 = y2 - 65;
			}else{
				y2 = y2 - 97; 
			}

			x1 = (7 - x1);
			x2 = (7 - x2);

		//verificar pieza que esta en esa posicion.
			if (verificar_pieza_mayus(x1, y1, matriz)){
				char pieza;
				pieza = traer_char(x1, y1, matriz);
				mover(x1, y1, x2, y2, pieza, matriz);
			}

		}else{

		}	
  		}
  		
  		


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

bool verificar_pieza_mayus(int x1, int y1, char** matriz){//revisar posicion, esta malo
	int revisar = matriz[x1][y1];
	bool pieza_correcta;
	if (revisar >= 65 && revisar <= 90){
		pieza_correcta = true;
	}else{
		pieza_correcta = false;
	}

	return pieza_correcta;
}

char traer_char(int x1, int y1, char** matriz){
	char pieza;
	pieza = matriz[x1][y1];

	return pieza;
}

void mover(int x1, int y1, int x2, int y2, char pieza, char** matriz){
	if (pieza == 'P'){
		if (mover_peon(x1, y1, x2, y2, matriz)){
			matriz[x2][y2] = 'P';
			matriz[x1][y1] = '.';
		}
	}else if (pieza == 'T'){
		if (mover_torre(x1, y1, x2, y2, matriz)){
			matriz[x2][y2] = 'T';
			matriz[x1][y1] = '.';
		}
	}
}

bool mover_peon(int x1, int y1, int x2, int y2, char** matriz){
	bool mover = false;
	int revisar = matriz[x2][y2];//revisar si no come a su mismas piezas
	if ((y1 == y2) && (x2 == x1 + 1) && (matriz[x2][y2] == '.')){//cuando peon solo se mueve una posicion.
		mover = true;
	}else if ((y1 == y2) && (x1 == 1) && (x2 == x1 + 2) && (matriz[x1 + 1][y1] == '.') && (matriz[x1 + 2][y1] == '.')){//peon mueve dos espacios
		mover = true;
	}else if ((y1 == 0) && (y2 == y1 + 1) && (matriz[x2][y2] != '.')){//cuando peon come y esta en orilla izquierda
		mover = true;
	}else if ((y1 == 7) && (y2 == y1 + 1) && (matriz[x2][y2] != '.')){//cuando peon come y esta en orilla derecha
		mover = true;
	}else if ((y1 != 0 || y1 != 7) && (y2 == y1 + 1) && (matriz[x2][y2] != '.')){//cuando peon come y esta en medio.
		mover = true;
	}else{
		mover = false;
	}

	if (matriz[x2][y2] == 'P'){//verificar que no coma piezas de su mismo color.
		mover = false;
	}else if (matriz[x2][y2] == 'T'){
		mover = false;
	}else if (matriz[x2][y2] == 'A'){
		mover = false;
	}else if (matriz[x2][y2] == 'D'){
		mover = false;
	}else if (matriz[x2][y2] == 'C'){
		mover = false;
	}else if (matriz[x2][y2] == 'R'){
		mover = false;
	}

	return mover;
}

bool mover_torre(int x1, int y1, int x2, int y2, char** matriz){
	bool mover = false;
	int pieza_encontrada = 0;
	int x1_temp = x1;
	int x2_temp2 = x2;
	x1_temp++;

	if (matriz[x2][y2] == 'P'){//verificar que no coma piezas de su mismo color.
		pieza_encontrada++;
	}else if (matriz[x2][y2] == 'T'){
		pieza_encontrada++;
	}else if (matriz[x2][y2] == 'A'){
		pieza_encontrada++;
	}else if (matriz[x2][y2] == 'D'){
		pieza_encontrada++;
	}else if (matriz[x2][y2] == 'C'){
		pieza_encontrada++;
	}else if (matriz[x2][y2] == 'R'){
		pieza_encontrada++;
	}

	if ((y1 == y2)){//verificar si mueve en la misma columna
		for (x1_temp; x1_temp < x2_temp2; x1_temp++){
			if (matriz[x1_temp][y1] != '.'){
				pieza_encontrada++;
			}
		}

		if(pieza_encontrada == 0){
			mover = true;		
		}else{
			mover = false;
		}	
	}

	return mover;
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
