#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::string;

void llenar_tablero(char**);
bool entrada_movida(char[], int);
bool verificar_pieza_mayus(int, int, char**);
bool verificar_pieza_minus(int, int, char**);
char traer_char(int, int, char**);
void mover(int, int, int, int, char, char**, int);
bool mover_peon(int, int, int, int, char**, int);
bool mover_torre(int, int, int, int, char**, int);
bool mover_alfil(int, int, int, int, char**, int);
bool mover_caballo(int, int, int, int, char**, int);
bool mover_dama(int, int, int, int, char**, int);
bool mover_rey(int, int, int, int, char**, int);
void jaque_mate(int, int, char**, int);
void guardar_partida(char**);
void cargar_partida(char**);


int main(int argc, char*argv[]){
	int contador_turnos = 2;
	int size = 8;
	int size_movement = 5;
	char movement[size_movement];
	int ganador = 1;

	char **matriz;
	matriz = (char **)malloc (size*sizeof(char *));

	for (int i=0;i<size;i++){
		matriz[i] = (char *) malloc (size*sizeof(char));
	}

	llenar_tablero(matriz);

	while(ganador == 1){
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

  		move(5, 50);
  		printw("Jugador #1 usa mayusculas");
  		move(6, 50);
  		printw("INGRESA [Z] PARA GUARDAR");
  		move(7, 50);
  		printw("INGRESA [X] PARA CARGAR");

  		move(15, 10);
  		addstr("Ingrese el movimiento: ");
  		getnstr(movement, sizeof(movement) - 1);

  		if (entrada_movida(movement, size_movement)){//lo de abajo depende de esto
  			int x1, y1, x2, y2;

  			if (movement[0] == 90){//guardar
  				guardar_partida(matriz);
  			}

  			if (movement[0] == 88){
  				cargar_partida(matriz);
  			}

			if (contador_turnos % 2 == 0 && movement[0] != 90 && movement[0] != 88){//pieza debe ser mayuscula, turno jugador 1
				//convertir entrada en coordenadas
				x1 = movement[1];
				y1 = movement[0];
				x2 = movement[3];
				y2 = movement[2];

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

				//verificar pieza que esta en esa posicion y que coordenadas no esten fuera.
				if ((verificar_pieza_mayus(x1, y1, matriz))){
					char pieza;
					pieza = traer_char(x1, y1, matriz);
					mover(x1, y1, x2, y2, pieza, matriz, contador_turnos);
				}
			}	
		}else if(!entrada_movida(movement, size_movement)){
  			contador_turnos++;
  			move(15, 10);
  			printw("MOVIMIENTO O FORMATO INVALIDO, INGRESA UNO NUEVO");
  			getch();
  		}
  		refresh();

  		contador_turnos++;

  		int jugador_1 = 0;
  		int jugador_2 = 0;
  		for (int i = 0; i < size; i++){
  			for (int j = 0; j < size; j++){
  				if (matriz[i][j] == 'R'){
  					jugador_1 = 1;
  				}

  				if (matriz[i][j] == 'r'){
  					jugador_2 = 1;
  				}
  			}
  		}

  		if ((jugador_1 == 1) && (jugador_2 == 0)){
  			move(1, 10);
  			printw("El ganador es el jugador #1");
  			getch();
  			ganador = 0;
  		}else if ((jugador_1 == 0) && (jugador_2 == 1)){
  			move(1, 10);
  			printw("El ganador es el jugador #2");
  			getch();
  			ganador = 0;
  		}

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

  		move(5, 50);
  		printw("Jugador #2 usa minusculas");
  		move(6, 50);
  		printw("INGRESA [Z] PARA GUARDAR");
  		move(7, 50);
  		printw("INGRESA [X] PARA CARGAR");

  		move(15, 10);
  		addstr("Ingrese el movimiento: ");
  		getnstr(movement, sizeof(movement) - 1);
  		
  		if (entrada_movida(movement, size_movement)){
  			int x1, y1, x2, y2;

  			if (movement[0] == 90){//guardar
  				guardar_partida(matriz);
  			}

  			if (movement[0] == 88){
  				cargar_partida(matriz);
  			}

  			if (contador_turnos % 2 != 0 && movement[0] != 90 && movement[0] != 88){//pieza debe ser mayuscula, turno jugador 1
				//convertir entrada en coordenadas
				x1 = movement[1];
				y1 = movement[0];
				x2 = movement[3];
				y2 = movement[2];

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

				//verificar pieza que esta en esa posicion y que coordenadas no esten fuera.
				if ((verificar_pieza_minus(x1, y1, matriz))){
					char pieza;
					pieza = traer_char(x1, y1, matriz);
					mover(x1, y1, x2, y2, pieza, matriz, contador_turnos);
				}
			}
  		}else if(!entrada_movida(movement, size_movement)){
  			contador_turnos++;
  			move(15, 10);
  			printw("MOVIMIENTO O FORMATO INVALIDO, INGRESA UNO NUEVO");
  			getch();
  		}
  		refresh();
  		
  		contador_turnos++;

  		int jugador_1 = 0;
  		int jugador_2 = 0;
  		for (int i = 0; i < size; i++){
  			for (int j = 0; j < size; j++){
  				if (matriz[i][j] == 'R'){
  					jugador_1 = 1;
  				}

  				if (matriz[i][j] == 'r'){
  					jugador_2 = 1;
  				}
  			}
  		}

  		if ((jugador_1 == 1) && (jugador_2 == 0)){
  			move(1, 10);
  			printw("El ganador es el jugador #1");
  			getch();
  			ganador = 0;
  		}else if ((jugador_1 == 0) && (jugador_2 == 1)){
  			move(1, 10);
  			printw("El ganador es el jugador #2");
  			getch();
  			ganador = 0;
  		}

		}
	}

  	endwin();
	return 0;
}//fin del main

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

	if (movement[1] >= 48 && movement[1] <= 56){
		nums++;
	}

	if ((movement[0] >= 65 && movement[0] <= 72) || (movement[0] >= 97 && movement[0] <= 104)){
		chars++;
	}

	if (movement[3] >= 48 && movement[3] <= 56){
		nums++;
	}

	if ((movement[2] >= 65 && movement[2] <= 72) || (movement[2] >= 97 && movement[2] <= 104)){
		chars++;	
	}

	if (movement[0] == 90 || movement[0] == 88){
		chars = 2;
		nums = 2;
	}

	if (nums == 2 && chars == 2){
		movim_correcto = true;
	}else{
		movim_correcto = false;
	}

	return movim_correcto;
}

bool verificar_pieza_mayus(int x1, int y1, char** matriz){//revisar posicion
	int revisar = matriz[x1][y1];
	bool pieza_correcta;
	if (revisar >= 65 && revisar <= 90){
		pieza_correcta = true;
	}else{
		pieza_correcta = false;
	}

	return pieza_correcta;
}

bool verificar_pieza_minus(int x1, int y1, char** matriz){//revisar posicion
	int revisar = matriz[x1][y1];
	bool pieza_correcta;
	if (revisar >= 97 && revisar <= 121){
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

void mover(int x1, int y1, int x2, int y2, char pieza, char** matriz, int contador_turnos){
	if (contador_turnos % 2 == 0){
		if (pieza == 'P'){
			if (mover_peon(x1, y1, x2, y2, matriz, contador_turnos)){
				matriz[x2][y2] = 'P';
				matriz[x1][y1] = '.';
				/*cuando peon llega al otro lado*/
				if (x2 == 7){
					char pieza_nueva;
					move(16, 10);
  					addstr("Ingrese pieza a cambiar por peon: ");
  					pieza_nueva = getch();
  					int revisar_char = pieza_nueva;
  					if ((revisar_char == 65) || (revisar_char == 67) || (revisar_char == 84) || (revisar_char == 68)){
  						matriz[x2][y2] = pieza_nueva;
						matriz[x1][y1] = '.';
  					}
				}
				/*JAQUE*/
				for (int i = 0; i < 8; i++){
					for (int j = 0; j < 8; j++){
						if (matriz[i][j] == 'r'){
							x1 = i;
							y1 = j;
						}
					}
				}//buscar al rey

				if ((x1 - 1 >= 0) && (y1 + 1 <= 7)){
					if (matriz[x1 - 1][y1 + 1] == 'P'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
					
				}else if ((x1 - 1 >= 0) && (y1 - 1 >= 0)){
					if (matriz[x1 - 1][y1 - 1] == 'P'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
				}
				/*fin jaque*/

			}
		}else if (pieza == 'T'){
			if (mover_torre(x1, y1, x2, y2, matriz, contador_turnos)){
				matriz[x2][y2] = 'T';
				matriz[x1][y1] = '.';
				/*JAQUE*/
				for (int i = 0; i < 8; i++){
					for (int j = 0; j < 8; j++){
						if (matriz[i][j] == 'r'){
							x1 = i;
							y1 = j;
						}
					}
				}//buscar al rey

				int x1_temp = x1;
				int x2_temp = x2;
				int y1_temp = y1;
				int y2_temp = y2;
				x1_temp++;
				y1_temp++;
				int pieza_encontrada = 0;

				if (y1 == y2 && x1 != x2 && x1 < x2){//verificar si mueve en la misma columna o  misma fila
					x1_temp++;
					for (x1_temp; x1_temp < x2_temp; x1_temp++){
						if (matriz[x1_temp][y1] != '.' && matriz[x1_temp][y1] != 'r'){
							pieza_encontrada++;
						}
					}
				}

				if ((y1 != y2 && x1 == x2 && y1 < y2)){
					y1_temp++;
					for (y1_temp; y1_temp < y2_temp; y1_temp++){
						if (matriz[x1][y1_temp] != '.' && matriz[x1_temp][y1] != 'r'){
						pieza_encontrada++;
						}
					}
				}

				if (y1 == y2 && x1 != x2 && x1 > x2){//verificar si mueve en la misma columna o  misma fila
					x1_temp--;
					for (x1_temp; x1_temp > x2_temp; x1_temp--){
						if (matriz[x1_temp][y1] != '.' && matriz[x1_temp][y1] != 'r'){
							pieza_encontrada++;
						}
					}
				}

				if ((y1 != y2 && x1 == x2 && y1 > y2)){
					y1_temp--;
					for (y1_temp; y1_temp > y2_temp; y1_temp--){
						if (matriz[x1][y1_temp] != '.' && matriz[x1_temp][y1] != 'r'){
							pieza_encontrada++;
						}
					}
				}

				if (y1 != y2 && x1 != x2){
					pieza_encontrada++;
				}


		if(pieza_encontrada == 0){
			move(16, 10);
			printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
			getch();	
			//jaque_mate(x1, x2, matriz, contador_turnos);
		}
				/*fin jaque*/
			}
		}else if (pieza == 'A'){
			if (mover_alfil(x1, y1, x2, y2, matriz, contador_turnos)){
				matriz[x2][y2] = 'A';
				matriz[x1][y1] = '.';
				/*JAQUE*/

				for (int i = 0; i < 8; i++){
					for (int j = 0; j < 8; j++){
						if (matriz[i][j] == 'r'){
							x1 = i;
							y1 = j;
						}
					}
				}//buscar al rey

				int pieza_encontrada = 0;
				int x1_temp = x1;
				int x2_temp = x2;
				int y1_temp = y1;
				int y2_temp = y2;
	
					x1_temp++;
					y1_temp++;
					for (x1_temp; x1_temp < x2_temp; x1_temp++){
						for (y1_temp; y1_temp < y2_temp; y1_temp++){
							if (matriz[x1_temp][y1_temp] != '.' && matriz[x1_temp][y1_temp] != 'A'){
								pieza_encontrada++;
							}
						}
					}

				x1_temp = x1;
				x2_temp = x2;
				y1_temp = y1;
				y2_temp = y2;
				

					x1_temp++;
					y1_temp--;
					for (x1_temp; x1_temp < x2_temp; x1_temp++){
						for (y1_temp; y1_temp > y2_temp; y1_temp--){
							if (matriz[x1_temp][y1_temp] != '.' && matriz[x1_temp][y1_temp] != 'A'){
								pieza_encontrada++;
							}
						}
					}
				
				x1_temp = x1;
				x2_temp = x2;
				y1_temp = y1;
				y2_temp = y2;

				
					x1_temp--;
					y1_temp++;
					for (x1_temp; x1_temp > x2_temp; x1_temp--){
						for (y1_temp; y1_temp < y2_temp; y1_temp++){
							if (matriz[x1_temp][y1_temp] != '.' && matriz[x1_temp][y1_temp] != 'A'){
								pieza_encontrada++;
							}
						}
					}
				

				x1_temp = x1;
				x2_temp = x2;
				y1_temp = y1;
				y2_temp = y2;
				
					x1_temp--;
					y1_temp--;
					for (x1_temp; x1_temp > x2_temp; x1_temp--){
						for (y1_temp; y1_temp > y2_temp; y1_temp--){
							if (matriz[x1_temp][y1_temp] != '.' && matriz[x1_temp][y1_temp] != 'A'){
								pieza_encontrada++;
							}
						}
					}

					if ((y2 == y1 + 1) && (x2 < x1 - 1)){
						pieza_encontrada++;
					}

					if ((y2 == y1 - 1) && (x2 < x1 - 1)){
						pieza_encontrada++;
					}

					if (y2 == y1 + 1 && x2 > x1 - 1){
						pieza_encontrada++;
					}

					if (y2 == y1){
						pieza_encontrada++;
					}
				

				if(pieza_encontrada == 0){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();		
					//jaque_mate(x1, x2, matriz, contador_turnos);
				}

				/*fin jaque*/
			}
		}else if (pieza == 'C'){
			if (mover_caballo(x1, y1, x2, y2, matriz, contador_turnos)){
				matriz[x2][y2] = 'C';
				matriz[x1][y1] = '.';
				/*JAQUE*/
				for (int i = 0; i < 8; i++){
					for (int j = 0; j < 8; j++){
						if (matriz[i][j] == 'r'){
							x1 = i;
							y1 = j;
						}
					}
				}//buscar al rey

				if ((x1 - 2 >= 0) && (y1 + 1 <= 7) && (matriz[x1 - 2][y1 + 1] == 'C')){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();
					jaque_mate(x1, x2, matriz, contador_turnos);
				}else if ((x1 - 2 >= 0) && (y1 - 1 <= 7) && (matriz[x1 - 2][y1 - 1] == 'C')){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();
					jaque_mate(x1, x2, matriz, contador_turnos);
				}else if ((x1 - 1 >= 0) && (y1 + 2 <= 7) && (matriz[x1 - 1][y1 + 2] == 'C')){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();
					jaque_mate(x1, x2, matriz, contador_turnos);
				}else if ((x1 - 1 >= 0) && (y1 - 2 >= 0) && (matriz[x1 - 1][y1 - 2] == 'C')){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();
					jaque_mate(x1, x2, matriz, contador_turnos);
				}else if ((x1 + 1 <= 7) && (y1 + 2 <= 7) && (matriz[x1 + 1][y1 + 2] == 'C')){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();
					jaque_mate(x1, x2, matriz, contador_turnos);
				}else if ((x1 - 1 >= 0) && (y1 - 2 >= 0) && (matriz[x1 - 1][y1 - 2] == 'C')){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();
					jaque_mate(x1, x2, matriz, contador_turnos);
				}else if ((x1 + 2 <= 7) && (y1 + 1 <= 7) && (matriz[x1 + 2][y1 + 1] == 'C')){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();
					jaque_mate(x1, x2, matriz, contador_turnos);
				}else if ((x1 + 2 <= 7) && (y1 - 1 >= 0) && (matriz[x1 + 2][y1 - 1] == 'C')){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();
					jaque_mate(x1, x2, matriz, contador_turnos);
				}/*fin jaque*/

			}
		}else if (pieza == 'D'){
			if (mover_dama(x1, y1, x2, y2, matriz, contador_turnos)){
				matriz[x2][y2] = 'D';
				matriz[x1][y1] = '.';
				/////////////////////JAQUE
				/*JAQUE*/
				for (int i = 0; i < 8; i++){
					for (int j = 0; j < 8; j++){
						if (matriz[i][j] == 'r'){
							x1 = i;
							y1 = j;
						}
					}
				}//buscar al rey

				int x1_temp = x1;
				int x2_temp = x2;
				int y1_temp = y1;
				int y2_temp = y2;
				x1_temp++;
				y1_temp++;
				int pieza_encontrada = 0;

				if (y1 == y2 && x1 != x2 && x1 < x2){//verificar si mueve en la misma columna o  misma fila
					x1_temp++;
					for (x1_temp; x1_temp < x2_temp; x1_temp++){
						if (matriz[x1_temp][y1] != '.' && matriz[x1_temp][y1] != 'r'){
							pieza_encontrada++;
						}
					}
				}

				if ((y1 != y2 && x1 == x2 && y1 < y2)){
					y1_temp++;
					for (y1_temp; y1_temp < y2_temp; y1_temp++){
						if (matriz[x1][y1_temp] != '.' && matriz[x1_temp][y1] != 'r'){
						pieza_encontrada++;
						}
					}
				}

				if (y1 == y2 && x1 != x2 && x1 > x2){//verificar si mueve en la misma columna o  misma fila
					x1_temp--;
					for (x1_temp; x1_temp > x2_temp; x1_temp--){
						if (matriz[x1_temp][y1] != '.' && matriz[x1_temp][y1] != 'r'){
							pieza_encontrada++;
						}
					}
				}

				if ((y1 != y2 && x1 == x2 && y1 > y2)){
					y1_temp--;
					for (y1_temp; y1_temp > y2_temp; y1_temp--){
						if (matriz[x1][y1_temp] != '.' && matriz[x1_temp][y1] != 'r'){
							pieza_encontrada++;
						}
					}
				}

				if (y1 != y2 && x1 != x2){
					pieza_encontrada++;
				}

				x1_temp++;
					y1_temp++;
					for (x1_temp; x1_temp < x2_temp; x1_temp++){
						for (y1_temp; y1_temp < y2_temp; y1_temp++){
							if (matriz[x1_temp][y1_temp] != '.' && matriz[x1_temp][y1_temp] != 'r'){
								pieza_encontrada++;
							}
						}
					}

				x1_temp = x1;
				x2_temp = x2;
				y1_temp = y1;
				y2_temp = y2;
				

					x1_temp++;
					y1_temp--;
					for (x1_temp; x1_temp < x2_temp; x1_temp++){
						for (y1_temp; y1_temp > y2_temp; y1_temp--){
							if (matriz[x1_temp][y1_temp] != '.' && matriz[x1_temp][y1_temp] != 'r'){
								pieza_encontrada++;
							}
						}
					}
				
				x1_temp = x1;
				x2_temp = x2;
				y1_temp = y1;
				y2_temp = y2;

				
					x1_temp--;
					y1_temp++;
					for (x1_temp; x1_temp > x2_temp; x1_temp--){
						for (y1_temp; y1_temp < y2_temp; y1_temp++){
							if (matriz[x1_temp][y1_temp] != '.' && matriz[x1_temp][y1_temp] != 'r'){
								pieza_encontrada++;
							}
						}
					}
				

				x1_temp = x1;
				x2_temp = x2;
				y1_temp = y1;
				y2_temp = y2;
				
					x1_temp--;
					y1_temp--;
					for (x1_temp; x1_temp > x2_temp; x1_temp--){
						for (y1_temp; y1_temp > y2_temp; y1_temp--){
							if (matriz[x1_temp][y1_temp] != '.' && matriz[x1_temp][y1_temp] != 'r'){
								pieza_encontrada++;
							}
						}
					}

					if ((y2 == y1 + 1) && (x2 < x1 - 1)){
						pieza_encontrada++;
					}

					if ((y2 == y1 - 1) && (x2 < x1 - 1)){
						pieza_encontrada++;
					}
				

				if(pieza_encontrada == 0){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();	
					//jaque_mate(x1, x2, matriz, contador_turnos);	
				}

				/*FIN JAQUE REINA*/
			}
		}else if (pieza == 'R'){
			if (mover_rey(x1, y1, x2, y2, matriz, contador_turnos)){
				matriz[x2][y2] = 'R';
				matriz[x1][y1] = '.';
				/////////////////////JAQUE

				for (int i = 0; i < 8; i++){
					for (int j = 0; j < 8; j++){
						if (matriz[i][j] == 'r'){
							x1 = i;
							y1 = j;
						}
					}
				}//buscar al rey

				if ((x1 + 1 < 8) && (y2 == y1)){
					if (matriz[x1 + 1][y1] == 'R'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
				}else if ((x1 - 1 >= 0) && (y2 == y1)){
					
					if (matriz[x1 - 1][y1] == 'R'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}				
				}else if ((y1 + 1 < 8) && (x2 == x1)){
					if (matriz[x1][y1 + 1] == 'R'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
				}else if ((x2 == x1) && (y1 - 1 >= 0)){
					if ((matriz[x1][y1 - 1] == 'R')){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
				}else if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
					if (matriz[x1 + 1][y1 - 1] == 'R'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
				}else if ((y1 + 1 < 8) && (x1 + 1 < 8)){
					if (matriz[x1 + 1][y1 + 1] == 'R'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
				}else if ((y1 + 1 < 8) && (x1 - 1 >= 0)){
					if (matriz[x1 - 1][y1 + 1] == 'R'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
				}else if ((x1 - 1 >= 0) && (y1 - 1 >= 0)){
					if (matriz[x1 - 1][y1 - 1] == 'R'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
				}
			}
		}
	}else{//inicio del jugador numero 2-------------------------------------------------------------------------------------------------------
		if (pieza == 'p'){
			if (mover_peon(x1, y1, x2, y2, matriz, contador_turnos)){
				matriz[x2][y2] = 'p';
				matriz[x1][y1] = '.';
				/////////////////////JAQUE

				if (x2 == 0){
					char pieza_nueva;
					move(16, 10);
  					addstr("Ingrese pieza a cambiar por peon: ");
  					pieza_nueva = getch();
  					int revisar_char = pieza_nueva;
  					if ((revisar_char == 97) || (revisar_char == 99) || (revisar_char == 116) || (revisar_char == 100)){
  						matriz[x2][y2] = pieza_nueva;
						matriz[x1][y1] = '.';
  					}
				}

				/*JAQUE*/
				for (int i = 0; i < 8; i++){
					for (int j = 0; j < 8; j++){
						if (matriz[i][j] == 'R'){
							x1 = i;
							y1 = j;
						}
					}
				}//buscar al rey

				if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
					if (matriz[x1 + 1][y1 - 1] == 'p'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
					
				}else if ((x1 + 1 < 8) && (y1 + 1 < 8)){
					if (matriz[x1 + 1][y1 + 1] == 'p'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
				}
				/*fin jaque*/

			}
		}else if (pieza == 't'){
			if (mover_torre(x1, y1, x2, y2, matriz, contador_turnos)){
				matriz[x2][y2] = 't';
				matriz[x1][y1] = '.';
				/*JAQUE*/
				for (int i = 0; i < 8; i++){
					for (int j = 0; j < 8; j++){
						if (matriz[i][j] == 'R'){
							x1 = i;
							y1 = j;
						}
					}
				}//buscar al rey

				int x1_temp = x1;
				int x2_temp = x2;
				int y1_temp = y1;
				int y2_temp = y2;
				x1_temp++;
				y1_temp++;
				int pieza_encontrada = 0;

				if (y1 == y2 && x1 != x2 && x1 < x2){//verificar si mueve en la misma columna o  misma fila
					x1_temp++;
					for (x1_temp; x1_temp < x2_temp; x1_temp++){
						if (matriz[x1_temp][y1] != '.' && matriz[x1_temp][y1] != 'R'){
							pieza_encontrada++;
						}
					}
				}

				if ((y1 != y2 && x1 == x2 && y1 < y2)){
					y1_temp++;
					for (y1_temp; y1_temp < y2_temp; y1_temp++){
						if (matriz[x1][y1_temp] != '.' && matriz[x1_temp][y1] != 'R'){
						pieza_encontrada++;
						}
					}
				}

				if (y1 == y2 && x1 != x2 && x1 > x2){//verificar si mueve en la misma columna o  misma fila
					x1_temp--;
					for (x1_temp; x1_temp > x2_temp; x1_temp--){
						if (matriz[x1_temp][y1] != '.' && matriz[x1_temp][y1] != 'R'){
							pieza_encontrada++;
						}
					}
				}

				if ((y1 != y2 && x1 == x2 && y1 > y2)){
					y1_temp--;
					for (y1_temp; y1_temp > y2_temp; y1_temp--){
						if (matriz[x1][y1_temp] != '.' && matriz[x1_temp][y1] != 'R'){
							pieza_encontrada++;
						}
					}
				}

				if (y1 != y2 && x1 != x2){
					pieza_encontrada++;
				}


		if(pieza_encontrada == 0){
			move(16, 10);
			printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
			getch();	
			//jaque_mate(x1, x2, matriz, contador_turnos);
		}
		/*fin jaque*/
			}
		}else if (pieza == 'a'){
			if (mover_alfil(x1, y1, x2, y2, matriz, contador_turnos)){
				matriz[x2][y2] = 'a';
				matriz[x1][y1] = '.';
				/*JAQUE*/

				for (int i = 0; i < 8; i++){
					for (int j = 0; j < 8; j++){
						if (matriz[i][j] == 'R'){
							x1 = i;
							y1 = j;
						}
					}
				}//buscar al rey

				int pieza_encontrada = 0;
				int x1_temp = x1;
				int x2_temp = x2;
				int y1_temp = y1;
				int y2_temp = y2;
	
					x1_temp++;
					y1_temp++;
					for (x1_temp; x1_temp < x2_temp; x1_temp++){
						for (y1_temp; y1_temp < y2_temp; y1_temp++){
							if (matriz[x1_temp][y1_temp] != '.' && matriz[x1_temp][y1_temp] != 'a'){
								pieza_encontrada++;
							}
						}
					}

				x1_temp = x1;
				x2_temp = x2;
				y1_temp = y1;
				y2_temp = y2;
				

					x1_temp++;
					y1_temp--;
					for (x1_temp; x1_temp < x2_temp; x1_temp++){
						for (y1_temp; y1_temp > y2_temp; y1_temp--){
							if (matriz[x1_temp][y1_temp] != '.' && matriz[x1_temp][y1_temp] != 'a'){
								pieza_encontrada++;
							}
						}
					}
				
				x1_temp = x1;
				x2_temp = x2;
				y1_temp = y1;
				y2_temp = y2;

				
					x1_temp--;
					y1_temp++;
					for (x1_temp; x1_temp > x2_temp; x1_temp--){
						for (y1_temp; y1_temp < y2_temp; y1_temp++){
							if (matriz[x1_temp][y1_temp] != '.' && matriz[x1_temp][y1_temp] != 'a'){
								pieza_encontrada++;
							}
						}
					}
				

				x1_temp = x1;
				x2_temp = x2;
				y1_temp = y1;
				y2_temp = y2;
				
					x1_temp--;
					y1_temp--;
					for (x1_temp; x1_temp > x2_temp; x1_temp--){
						for (y1_temp; y1_temp > y2_temp; y1_temp--){
							if (matriz[x1_temp][y1_temp] != '.' && matriz[x1_temp][y1_temp] != 'a'){
								pieza_encontrada++;
							}
						}
					}

					if ((y2 == y1 + 1) && (x2 < x1 - 1)){
						pieza_encontrada++;
					}

					if ((y2 == y1 - 1) && (x2 < x1 - 1)){
						pieza_encontrada++;
					}

					if (y2 == y1 + 1 && x2 > x1 - 1){
						pieza_encontrada++;
					}

					if (y2 == y1){
						pieza_encontrada++;
					}

					if (y1 == y2 + 1 && x1 < x2 - 1){
						pieza_encontrada++;
					}
				

				if(pieza_encontrada == 0){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();
					//jaque_mate(x1, x2, matriz, contador_turnos);		
				}

				/*fin jaque*/
			}
		}else if (pieza == 'c'){
			if (mover_caballo(x1, y1, x2, y2, matriz, contador_turnos)){
				matriz[x2][y2] = 'c';
				matriz[x1][y1] = '.';
				/*JAQUE*/
				for (int i = 0; i < 8; i++){
					for (int j = 0; j < 8; j++){
						if (matriz[i][j] == 'R'){
							x1 = i;
							y1 = j;
						}
					}
				}//buscar al rey

				if ((x1 - 2 >= 0) && (y1 + 1 <= 7) && (matriz[x1 - 2][y1 + 1] == 'c')){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();
					//jaque_mate(x1, x2, matriz, contador_turnos);
				}else if ((x1 - 2 >= 0) && (y1 - 1 <= 7) && (matriz[x1 - 2][y1 - 1] == 'c')){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();
					//jaque_mate(x1, x2, matriz, contador_turnos);
				}else if ((x1 - 1 >= 0) && (y1 + 2 <= 7) && (matriz[x1 - 1][y1 + 2] == 'c')){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();
					//jaque_mate(x1, x2, matriz, contador_turnos);
				}else if ((x1 - 1 >= 0) && (y1 - 2 >= 0) && (matriz[x1 - 1][y1 - 2] == 'c')){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();
					//jaque_mate(x1, x2, matriz, contador_turnos);
				}else if ((x1 + 1 <= 7) && (y1 + 2 <= 7) && (matriz[x1 + 1][y1 + 2] == 'c')){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();
					//jaque_mate(x1, x2, matriz, contador_turnos);
				}else if ((x1 - 1 >= 0) && (y1 - 2 >= 0) && (matriz[x1 - 1][y1 - 2] == 'c')){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();
					//jaque_mate(x1, x2, matriz, contador_turnos);
				}else if ((x1 + 2 <= 7) && (y1 + 1 <= 7) && (matriz[x1 + 2][y1 + 1] == 'c')){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();
					//jaque_mate(x1, x2, matriz, contador_turnos);
				}else if ((x1 + 2 <= 7) && (y1 - 1 >= 0) && (matriz[x1 + 2][y1 - 1] == 'c')){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();
					//jaque_mate(x1, x2, matriz, contador_turnos);
				}/*fin jaque*/
			}
		}else if (pieza == 'd'){
			if (mover_dama(x1, y1, x2, y2, matriz, contador_turnos)){
				matriz[x2][y2] = 'd';
				matriz[x1][y1] = '.';
				/*JAQUE*/
				for (int i = 0; i < 8; i++){
					for (int j = 0; j < 8; j++){
						if (matriz[i][j] == 'R'){
							x1 = i;
							y1 = j;
						}
					}
				}//buscar al rey

				int x1_temp = x1;
				int x2_temp = x2;
				int y1_temp = y1;
				int y2_temp = y2;
				x1_temp++;
				y1_temp++;
				int pieza_encontrada = 0;

				if (y1 == y2 && x1 != x2 && x1 < x2){//verificar si mueve en la misma columna o  misma fila
					x1_temp++;
					for (x1_temp; x1_temp < x2_temp; x1_temp++){
						if (matriz[x1_temp][y1] != '.' && matriz[x1_temp][y1] != 'R'){
							pieza_encontrada++;
						}
					}
				}

				if ((y1 != y2 && x1 == x2 && y1 < y2)){
					y1_temp++;
					for (y1_temp; y1_temp < y2_temp; y1_temp++){
						if (matriz[x1][y1_temp] != '.' && matriz[x1_temp][y1] != 'R'){
						pieza_encontrada++;
						}
					}
				}

				if (y1 == y2 && x1 != x2 && x1 > x2){//verificar si mueve en la misma columna o  misma fila
					x1_temp--;
					for (x1_temp; x1_temp > x2_temp; x1_temp--){
						if (matriz[x1_temp][y1] != '.' && matriz[x1_temp][y1] != 'R'){
							pieza_encontrada++;
						}
					}
				}

				if ((y1 != y2 && x1 == x2 && y1 > y2)){
					y1_temp--;
					for (y1_temp; y1_temp > y2_temp; y1_temp--){
						if (matriz[x1][y1_temp] != '.' && matriz[x1_temp][y1] != 'R'){
							pieza_encontrada++;
						}
					}
				}

				if (y1 != y2 && x1 != x2){
					pieza_encontrada++;
				}

				x1_temp++;
					y1_temp++;
					for (x1_temp; x1_temp < x2_temp; x1_temp++){
						for (y1_temp; y1_temp < y2_temp; y1_temp++){
							if (matriz[x1_temp][y1_temp] != '.' && matriz[x1_temp][y1_temp] != 'R'){
								pieza_encontrada++;
							}
						}
					}

				x1_temp = x1;
				x2_temp = x2;
				y1_temp = y1;
				y2_temp = y2;
				

					x1_temp++;
					y1_temp--;
					for (x1_temp; x1_temp < x2_temp; x1_temp++){
						for (y1_temp; y1_temp > y2_temp; y1_temp--){
							if (matriz[x1_temp][y1_temp] != '.' && matriz[x1_temp][y1_temp] != 'R'){
								pieza_encontrada++;
							}
						}
					}
				
				x1_temp = x1;
				x2_temp = x2;
				y1_temp = y1;
				y2_temp = y2;

				
					x1_temp--;
					y1_temp++;
					for (x1_temp; x1_temp > x2_temp; x1_temp--){
						for (y1_temp; y1_temp < y2_temp; y1_temp++){
							if (matriz[x1_temp][y1_temp] != '.' && matriz[x1_temp][y1_temp] != 'R'){
								pieza_encontrada++;
							}
						}
					}
				

				x1_temp = x1;
				x2_temp = x2;
				y1_temp = y1;
				y2_temp = y2;
				
					x1_temp--;
					y1_temp--;
					for (x1_temp; x1_temp > x2_temp; x1_temp--){
						for (y1_temp; y1_temp > y2_temp; y1_temp--){
							if (matriz[x1_temp][y1_temp] != '.' && matriz[x1_temp][y1_temp] != 'R'){
								pieza_encontrada++;
							}
						}
					}

					if ((y2 == y1 + 1) && (x2 < x1 - 1)){
						pieza_encontrada++;
					}

					if ((y2 == y1 - 1) && (x2 < x1 - 1)){
						pieza_encontrada++;
					}
				

				if(pieza_encontrada == 0){
					move(16, 10);
					printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
					getch();	
					//jaque_mate(x1, x2, matriz, contador_turnos);	
				}

				/*FIN JAQUE REINA*/
			}
		}else if (pieza == 'r'){
			if (mover_rey(x1, y1, x2, y2, matriz, contador_turnos)){
				matriz[x2][y2] = 'r';
				matriz[x1][y1] = '.';
				/////////////////////JAQUE

				for (int i = 0; i < 8; i++){
					for (int j = 0; j < 8; j++){
						if (matriz[i][j] == 'R'){
							x1 = i;
							y1 = j;
						}
					}
				}//buscar al rey

				if ((x1 + 1 < 8) && (y2 == y1)){
					if (matriz[x1 + 1][y1] == 'r'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
				}else if ((x1 - 1 >= 0) && (y2 == y1)){
					
					if (matriz[x1 - 1][y1] == 'r'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}				
				}else if ((y1 + 1 < 8) && (x2 == x1)){
					if (matriz[x1][y1 + 1] == 'r'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
				}else if ((x2 == x1) && (y1 - 1 >= 0)){
					if ((matriz[x1][y1 - 1] == 'r')){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
				}else if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
					if (matriz[x1 + 1][y1 - 1] == 'r'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
				}else if ((y1 + 1 < 8) && (x1 + 1 < 8)){
					if (matriz[x1 + 1][y1 + 1] == 'r'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
				}else if ((y1 + 1 < 8) && (x1 - 1 >= 0)){
					if (matriz[x1 - 1][y1 + 1] == 'r'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
				}else if ((x1 - 1 >= 0) && (y1 - 1 >= 0)){
					if (matriz[x1 - 1][y1 - 1] == 'r'){
						move(16, 10);
						printw("HAS PUESTO A TU ADVERSARIO EN JAQUE");
						getch();
						//jaque_mate(x1, x2, matriz, contador_turnos);
					}
				}
				/*fin jaque*/
			}
		}
	}

}

bool mover_peon(int x1, int y1, int x2, int y2, char** matriz, int contador_turnos){
	bool mover = false;
	int revisar = matriz[x2][y2];//revisar si no come a su mismas piezas

	if (contador_turnos % 2 == 0){
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
	}else{
		if ((y1 == y2) && (x2 == x1 - 1) && (matriz[x2][y2] == '.')){//cuando peon solo se mueve una posicion.
			mover = true;
		}else if ((y1 == y2) && (x1 == 6) && (x2 == x1 - 2) && (matriz[x1 - 1][y1] == '.') && (matriz[x1 - 2][y1] == '.')){//peon mueve dos espacios
			mover = true;
		}else if ((y1 == 0) && (y2 == y1 - 1) && (matriz[x2][y2] != '.')){//cuando peon come y esta en orilla izquierda
			mover = true;
		}else if ((y1 == 7) && (y2 == y1 - 1) && (matriz[x2][y2] != '.')){//cuando peon come y esta en orilla derecha
			mover = true;
		}else if ((y1 != 0 || y1 != 7) && (y2 == y1 - 1) && (matriz[x2][y2] != '.')){//cuando peon come y esta en medio.
			mover = true;
		}else{
			mover = false;
		}
	}

	if (contador_turnos % 2 == 0){
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
	}else{
		if (matriz[x2][y2] == 'p'){//verificar que no coma piezas de su mismo color.
			mover = false;
		}else if (matriz[x2][y2] == 't'){
			mover = false;
		}else if (matriz[x2][y2] == 'a'){
			mover = false;
		}else if (matriz[x2][y2] == 'd'){
			mover = false;
		}else if (matriz[x2][y2] == 'c'){
			mover = false;
		}else if (matriz[x2][y2] == 'r'){
			mover = false;
		}
	}	

	return mover;
}

bool mover_torre(int x1, int y1, int x2, int y2, char** matriz, int contador_turnos){
	bool mover = false;
	int pieza_encontrada = 0;
	int x1_temp = x1;
	int x2_temp = x2;
	int y1_temp = y1;
	int y2_temp = y2;
		

	if (y1 == y2 && x1 != x2 && x1 < x2){//verificar si mueve en la misma columna o  misma fila
		x1_temp++;
		for (x1_temp; x1_temp < x2_temp; x1_temp++){
			if (matriz[x1_temp][y1] != '.'){
				pieza_encontrada++;
			}
		}
	}

	if ((y1 != y2 && x1 == x2 && y1 < y2)){
		y1_temp++;
		for (y1_temp; y1_temp < y2_temp; y1_temp++){
			if (matriz[x1][y1_temp] != '.'){
				pieza_encontrada++;
			}
		}
	}

	if (y1 == y2 && x1 != x2 && x1 > x2){//verificar si mueve en la misma columna o  misma fila
		x1_temp--;
		for (x1_temp; x1_temp > x2_temp; x1_temp--){
			if (matriz[x1_temp][y1] != '.'){
				pieza_encontrada++;
			}
		}
	}

	if ((y1 != y2 && x1 == x2 && y1 > y2)){
		y1_temp--;
		for (y1_temp; y1_temp > y2_temp; y1_temp--){
			if (matriz[x1][y1_temp] != '.'){
				pieza_encontrada++;
			}
		}
	}

	if (x1 != x2 && y1 != y2){
		pieza_encontrada++;
	}

	if (contador_turnos % 2 == 0){
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
	}else{
		if (matriz[x2][y2] == 'p'){//verificar que no coma piezas de su mismo color.
			pieza_encontrada++;
		}else if (matriz[x2][y2] == 't'){
			pieza_encontrada++;
		}else if (matriz[x2][y2] == 'a'){
			pieza_encontrada++;
		}else if (matriz[x2][y2] == 'd'){
			pieza_encontrada++;
		}else if (matriz[x2][y2] == 'c'){
			pieza_encontrada++;
		}else if (matriz[x2][y2] == 'r'){
			pieza_encontrada++;
		}
	}

		if(pieza_encontrada == 0){
			mover = true;		
		}else{
			mover = false;
		}	
	return mover;
}

bool mover_alfil(int x1, int y1, int x2, int y2, char** matriz, int contador_turnos){
	bool mover = false;
	int pieza_encontrada = 0;
	int x1_temp = x1;
	int x2_temp = x2;
	int y1_temp = y1;
	int y2_temp = y2;
	

	if (x2 > x1 && y2 > y1){
		x1_temp++;
		y1_temp++;
		for (x1_temp; x1_temp < x2_temp; x1_temp++){
			for (y1_temp; y1_temp < y2_temp; y1_temp++){
				if (matriz[x1_temp][y1_temp] != '.'){
				pieza_encontrada++;
				}
			}
		}
	}

	if (x2 > x1 && y2 < y1){
		x1_temp++;
		y1_temp--;
		for (x1_temp; x1_temp < x2_temp; x1_temp++){
			for (y1_temp; y1_temp > y2_temp; y1_temp--){
				if (matriz[x1_temp][y1_temp] != '.'){
				pieza_encontrada++;
				}
			}
		}
	}

	if (x2 < x1 && y2 > y1){
		x1_temp--;
		y1_temp++;
		for (x1_temp; x1_temp > x2_temp; x1_temp--){
			for (y1_temp; y1_temp < y2_temp; y1_temp++){
				if (matriz[x1_temp][y1_temp] != '.'){
				pieza_encontrada++;
				}
			}
		}
	}

	if (x2 < x1 && y2 < y1){
		x1_temp--;
		y1_temp--;
		for (x1_temp; x1_temp > x2_temp; x1_temp--){
			for (y1_temp; y1_temp > y2_temp; y1_temp--){
				if (matriz[x1_temp][y1_temp] != '.'){
				pieza_encontrada++;
				}
			}
		}
	}

	if ((y2 == y1 + 1) && (x2 < x1 - 1)){
		pieza_encontrada++;
	}

	if ((y2 == y1 - 1) && (x2 < x1 - 1)){
		pieza_encontrada++;
	}

	if (y2 == y1){
		pieza_encontrada = pieza_encontrada + 2;
	}
	

	if (contador_turnos % 2 == 0){
		if (matriz[x2][y2] == 'P'){//verificar que no coma piezas de su mismo color.
			pieza_encontrada = pieza_encontrada + 2;
		}else if (matriz[x2][y2] == 'T'){
			pieza_encontrada = pieza_encontrada + 2;
		}else if (matriz[x2][y2] == 'A'){
			pieza_encontrada = pieza_encontrada + 2;
		}else if (matriz[x2][y2] == 'D'){
			pieza_encontrada = pieza_encontrada + 2;
		}else if (matriz[x2][y2] == 'C'){
			pieza_encontrada = pieza_encontrada + 2;
		}else if (matriz[x2][y2] == 'R'){
			pieza_encontrada = pieza_encontrada + 2;
		}
	}else{
		if (matriz[x2][y2] == 'p'){//verificar que no coma piezas de su mismo color.
			pieza_encontrada = pieza_encontrada + 2;
		}else if (matriz[x2][y2] == 't'){
			pieza_encontrada = pieza_encontrada + 2;
		}else if (matriz[x2][y2] == 'a'){
			pieza_encontrada = pieza_encontrada + 2;
		}else if (matriz[x2][y2] == 'd'){
			pieza_encontrada = pieza_encontrada + 2;
		}else if (matriz[x2][y2] == 'c'){
			pieza_encontrada = pieza_encontrada + 2;
		}else if (matriz[x2][y2] == 'r'){
			pieza_encontrada = pieza_encontrada + 2;
		}
	}	

	if(pieza_encontrada < 2){
		mover = true;		
	}else{
		mover = false;
	}	

	return mover;
}

bool mover_caballo(int x1, int y1, int x2, int y2, char** matriz, int contador_turnos){
	bool mover = false;

	if ((x2 == x1 + 2) && (y2 == y1 + 1)){
		mover = true;
	}else if ((x2 == x1 + 1) && (y2 == y1 + 2)){
		mover = true;
	}else if ((y2 == y1 + 2) && (x2 == x1 - 1)){
		mover = true;
	}else if ((x2 == x1 - 2) && (y2 == y1 + 1)){
		mover = true;
	}else if ((x2 == x1 - 2) && (y2 == y1 - 1)){
		mover = true;
	}else if ((y2 == y1 - 2) && (x2 == x1 - 1)){
		mover = true;
	}else if ((y2 == y1 - 2) && (x2 == x1 + 1)){
		mover = true;
	}else if ((x2 == x1 + 2) && (y2 == y1 - 1)){
		mover = true;
	}else{
		mover = false;
	}

	if (contador_turnos % 2 == 0){
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
	}else{
		if (matriz[x2][y2] == 'p'){//verificar que no coma piezas de su mismo color.
			mover = false;
		}else if (matriz[x2][y2] == 't'){
			mover = false;
		}else if (matriz[x2][y2] == 'a'){
			mover = false;
		}else if (matriz[x2][y2] == 'd'){
			mover = false;
		}else if (matriz[x2][y2] == 'c'){
			mover = false;
		}else if (matriz[x2][y2] == 'r'){
			mover = false;
		}
	}

	return mover;
}

bool mover_dama(int x1, int y1, int x2, int y2, char** matriz, int contador_turnos){
	bool mover = false;
	bool mover_como_alfil = false;
	int pieza_encontrada = 0;
	int x1_temp = x1;
	int x2_temp = x2;
	int y1_temp = y1;
	int y2_temp = y2;
		

	if (y1 == y2 && x1 != x2 && x1 < x2){//verificar si mueve en la misma columna o  misma fila
		x1_temp++;
		for (x1_temp; x1_temp < x2_temp; x1_temp++){
			if (matriz[x1_temp][y1] != '.'){
				pieza_encontrada++;
			}
		}
	}

	if ((y1 != y2 && x1 == x2 && y1 < y2)){
		y1_temp++;
		for (y1_temp; y1_temp < y2_temp; y1_temp++){
			if (matriz[x1][y1_temp] != '.'){
				pieza_encontrada++;
			}
		}
	}

	if (y1 == y2 && x1 != x2 && x1 > x2){//verificar si mueve en la misma columna o  misma fila
		x1_temp--;
		for (x1_temp; x1_temp > x2_temp; x1_temp--){
			if (matriz[x1_temp][y1] != '.'){
				pieza_encontrada++;
			}
		}
	}

	if ((y1 != y2 && x1 == x2 && y1 > y2)){
		y1_temp--;
		for (y1_temp; y1_temp > y2_temp; y1_temp--){
			if (matriz[x1][y1_temp] != '.'){
				pieza_encontrada++;
			}
		}
	}

	if (x1 != x2 && y1 != y2){
		pieza_encontrada++;
	}

	if (x2 != x1 && y1 != y2){
		mover_como_alfil = true;
		if (x2 > x1 && y2 > y1){
		x1_temp++;
		y1_temp++;
		for (x1_temp; x1_temp < x2_temp; x1_temp++){
			for (y1_temp; y1_temp < y2_temp; y1_temp++){
				if (matriz[x1_temp][y1_temp] != '.'){
				pieza_encontrada++;
				}
			}
		}
	}

	if (x2 > x1 && y2 < y1){
		x1_temp++;
		y1_temp--;
		for (x1_temp; x1_temp < x2_temp; x1_temp++){
			for (y1_temp; y1_temp > y2_temp; y1_temp--){
				if (matriz[x1_temp][y1_temp] != '.'){
				pieza_encontrada++;
				}
			}
		}
	}

	if (x2 < x1 && y2 > y1){
		x1_temp--;
		y1_temp++;
		for (x1_temp; x1_temp > x2_temp; x1_temp--){
			for (y1_temp; y1_temp < y2_temp; y1_temp++){
				if (matriz[x1_temp][y1_temp] != '.'){
				pieza_encontrada++;
				}
			}
		}
	}

	if (x2 < x1 && y2 < y1){
		x1_temp--;
		y1_temp--;
		for (x1_temp; x1_temp > x2_temp; x1_temp--){
			for (y1_temp; y1_temp > y2_temp; y1_temp--){
				if (matriz[x1_temp][y1_temp] != '.'){
				pieza_encontrada++;
				}
			}
		}
	}
	}

	

	if (contador_turnos % 2 == 0){
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
	}else{
		if (matriz[x2][y2] == 'p'){//verificar que no coma piezas de su mismo color.
			pieza_encontrada++;
		}else if (matriz[x2][y2] == 't'){
			pieza_encontrada++;
		}else if (matriz[x2][y2] == 'a'){
			pieza_encontrada++;
		}else if (matriz[x2][y2] == 'd'){
			pieza_encontrada++;
		}else if (matriz[x2][y2] == 'c'){
			pieza_encontrada++;
		}else if (matriz[x2][y2] == 'r'){
			pieza_encontrada++;
		}
	}

	if((pieza_encontrada < 2 && mover_como_alfil == true) || (pieza_encontrada == 0)){
		mover = true;		
	}else{
		mover = false;
	}

		
	return mover;
}

bool mover_rey(int x1, int y1, int x2, int y2, char** matriz, int contador_turnos){
	bool mover = false;

	if ((x2 == x1 + 1) && (y2 == y1)){
		mover = true;
	}else if ((x2 == x1 - 1) && (y2 == y1)){
		mover = true;
	}else if ((y2 == y1 + 1) && (x2 == x1)){
		mover = true;
	}else if ((x2 == x1) && (y2 == y1 - 1)){
		mover = true;
	}else if ((x2 == x1 + 1) && (y2 == y1 - 1)){
		mover = true;
	}else if ((y2 == y1 + 1) && (x2 == x1 + 1)){
		mover = true;
	}else if ((y2 == y1 + 1) && (x2 == x1 - 1)){
		mover = true;
	}else if ((x2 == x1 - 1) && (y2 == y1 - 1)){
		mover = true;
	}else{
		mover = false;
	}

	if (contador_turnos % 2 == 0){
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
	}else{
		if (matriz[x2][y2] == 'p'){//verificar que no coma piezas de su mismo color.
			mover = false;
		}else if (matriz[x2][y2] == 't'){
			mover = false;
		}else if (matriz[x2][y2] == 'a'){
			mover = false;
		}else if (matriz[x2][y2] == 'd'){
			mover = false;
		}else if (matriz[x2][y2] == 'c'){
			mover = false;
		}else if (matriz[x2][y2] == 'r'){
			mover = false;
		}
	}

	return mover;
}

void jaque_mate(int x, int y, char** matriz, int contador_turnos){

	/****************comienzo de jaque mate*****************/
	/****************verificar jugador 1 esta en mate*****************/
	if (contador_turnos % 2 != 0){
		/*primer par de coordenadas*/
		int x1 = x - 1;
		int y1 = y - 1;
		/*-------------------------*/
		int pieza_encontrada = 0;
		if (x1 >= 0 && y1 >= 0){
			/*ver si hay peones*/
			if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 1][y1 - 1] == 'p'){
					pieza_encontrada++;
				}
			}

			if ((x1 + 1 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 1][y1 + 1] == 'p'){
					pieza_encontrada++;
				}
			}

			/*ver si hay torres*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			/*ver si hay alfil*/
			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si hay caballos*/
			if ((x1 + 2 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 2][y1 + 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 + 1 < 8) && (y1 + 2 < 8)){
				if (matriz[x1 + 1][y1 + 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 + 2 < 8) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 + 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 + 1 < 8)){
				if (matriz[x1 - 2][y1 + 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 - 1 >= 0)){
				if (matriz[x1 - 2][y1 - 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 - 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 + 1 < 8)){
				if (matriz[x1 + 1][y1 - 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 + 2 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 2][y1 - 1] == 'c'){
					pieza_encontrada++;
				}
			}else{
				pieza_encontrada--;
			}

			/*ver si hay reina*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si esa posicion esta disponible*/
			if (matriz[x1][y1] != '.'){
				pieza_encontrada++;
			}


		}else{//si no se puede mover a posicion
			pieza_encontrada++;
		}/*fin de primera posicion*/

		/*segundo par de coordenadas*/
		x1 = x;
		y1 = y - 1;
		/*-------------------------*/
		if (y1 >= 0){
			/*ver si hay peones*/
			if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 1][y1 - 1] == 'p'){
					pieza_encontrada++;
				}
			}

			if ((x1 + 1 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 1][y1 + 1] == 'p'){
					pieza_encontrada++;
				}
			}

			/*ver si hay torres*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			/*ver si hay alfil*/
			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si hay caballos*/
			if ((x1 + 2 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 2][y1 + 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 + 1 < 8) && (y1 + 2 < 8)){
				if (matriz[x1 + 1][y1 + 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 + 2 < 8) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 + 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 + 1 < 8)){
				if (matriz[x1 - 2][y1 + 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 - 1 >= 0)){
				if (matriz[x1 - 2][y1 - 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 - 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 + 1 < 8)){
				if (matriz[x1 + 1][y1 - 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 + 2 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 2][y1 - 1] == 'c'){
					pieza_encontrada++;
				}
			}else{
				pieza_encontrada--;
			}

			/*ver si hay reina*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si esa posicion esta disponible*/
			if (matriz[x1][y1] != '.'){
				pieza_encontrada++;
			}


		}else{//si no se puede mover a posicion
			pieza_encontrada++;
		}/*fin de segunda posicion*/

		/*tercer par de coordenadas*/
		x1 = x + 1;
		y1 = y - 1;
		/*-------------------------*/
		if (x1 < 8 && y1 >= 0){
			/*ver si hay peones*/
			if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 1][y1 - 1] == 'p'){
					pieza_encontrada++;
				}
			}

			if ((x1 + 1 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 1][y1 + 1] == 'p'){
					pieza_encontrada++;
				}
			}

			/*ver si hay torres*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			/*ver si hay alfil*/
			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si hay caballos*/
			if ((x1 + 2 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 2][y1 + 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 + 1 < 8) && (y1 + 2 < 8)){
				if (matriz[x1 + 1][y1 + 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 + 2 < 8) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 + 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 + 1 < 8)){
				if (matriz[x1 - 2][y1 + 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 - 1 >= 0)){
				if (matriz[x1 - 2][y1 - 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 - 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 + 1 < 8)){
				if (matriz[x1 + 1][y1 - 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 + 2 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 2][y1 - 1] == 'c'){
					pieza_encontrada++;
				}
			}else{
				pieza_encontrada--;
			}

			/*ver si hay reina*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si esa posicion esta disponible*/
			if (matriz[x1][y1] != '.'){
				pieza_encontrada++;
			}


		}else{//si no se puede mover a posicion
			pieza_encontrada++;
		}/*fin de tercera posicion*/

		/*cuarto par de coordenadas*/
		x1 = x - 1;
		y1 = y;
		/*-------------------------*/
		if (x1 >= 0){
			/*ver si hay peones*/
			if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 1][y1 - 1] == 'p'){
					pieza_encontrada++;
				}
			}

			if ((x1 + 1 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 1][y1 + 1] == 'p'){
					pieza_encontrada++;
				}
			}

			/*ver si hay torres*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			/*ver si hay alfil*/
			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si hay caballos*/
			if ((x1 + 2 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 2][y1 + 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 + 1 < 8) && (y1 + 2 < 8)){
				if (matriz[x1 + 1][y1 + 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 + 2 < 8) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 + 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 + 1 < 8)){
				if (matriz[x1 - 2][y1 + 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 - 1 >= 0)){
				if (matriz[x1 - 2][y1 - 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 - 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 + 1 < 8)){
				if (matriz[x1 + 1][y1 - 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 + 2 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 2][y1 - 1] == 'c'){
					pieza_encontrada++;
				}
			}else{
				pieza_encontrada--;
			}

			/*ver si hay reina*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si esa posicion esta disponible*/
			if (matriz[x1][y1] != '.'){
				pieza_encontrada++;
			}


		}else{//si no se puede mover a posicion
			pieza_encontrada++;
		}/*fin de cuarta posicion*/

		/*quinto par de coordenadas*/
		x1 = x + 1;
		y1 = y;
		/*-------------------------*/
		if (x1 < 8){
			/*ver si hay peones*/
			if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 1][y1 - 1] == 'p'){
					pieza_encontrada++;
				}
			}

			if ((x1 + 1 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 1][y1 + 1] == 'p'){
					pieza_encontrada++;
				}
			}

			/*ver si hay torres*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			/*ver si hay alfil*/
			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si hay caballos*/
			if ((x1 + 2 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 2][y1 + 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 + 1 < 8) && (y1 + 2 < 8)){
				if (matriz[x1 + 1][y1 + 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 + 2 < 8) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 + 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 + 1 < 8)){
				if (matriz[x1 - 2][y1 + 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 - 1 >= 0)){
				if (matriz[x1 - 2][y1 - 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 - 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 + 1 < 8)){
				if (matriz[x1 + 1][y1 - 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 + 2 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 2][y1 - 1] == 'c'){
					pieza_encontrada++;
				}
			}else{
				pieza_encontrada--;
			}

			/*ver si hay reina*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si esa posicion esta disponible*/
			if (matriz[x1][y1] != '.'){
				pieza_encontrada++;
			}


		}else{//si no se puede mover a posicion
			pieza_encontrada++;
		}/*fin de quinta posicion*/


		/*sexto par de coordenadas*/
		x1 = x - 1;
		y1 = y + 1;
		/*-------------------------*/
		if (x1 >= 0 && y1 < 8){
			/*ver si hay peones*/
			if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 1][y1 - 1] == 'p'){
					pieza_encontrada++;
				}
			}

			if ((x1 + 1 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 1][y1 + 1] == 'p'){
					pieza_encontrada++;
				}
			}

			/*ver si hay torres*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			/*ver si hay alfil*/
			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si hay caballos*/
			if ((x1 + 2 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 2][y1 + 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 + 1 < 8) && (y1 + 2 < 8)){
				if (matriz[x1 + 1][y1 + 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 + 2 < 8) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 + 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 + 1 < 8)){
				if (matriz[x1 - 2][y1 + 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 - 1 >= 0)){
				if (matriz[x1 - 2][y1 - 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 - 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 + 1 < 8)){
				if (matriz[x1 + 1][y1 - 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 + 2 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 2][y1 - 1] == 'c'){
					pieza_encontrada++;
				}
			}else{
				pieza_encontrada--;
			}

			/*ver si hay reina*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si esa posicion esta disponible*/
			if (matriz[x1][y1] != '.'){
				pieza_encontrada++;
			}


		}else{//si no se puede mover a posicion
			pieza_encontrada++;
		}/*fin de sexta posicion*/

		/*septimo par de coordenadas*/
		x1 = x;
		y1 = y + 1;
		/*-------------------------*/
		if (y1 < 8){
			/*ver si hay peones*/
			if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 1][y1 - 1] == 'p'){
					pieza_encontrada++;
				}
			}

			if ((x1 + 1 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 1][y1 + 1] == 'p'){
					pieza_encontrada++;
				}
			}

			/*ver si hay torres*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			/*ver si hay alfil*/
			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si hay caballos*/
			if ((x1 + 2 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 2][y1 + 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 + 1 < 8) && (y1 + 2 < 8)){
				if (matriz[x1 + 1][y1 + 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 + 2 < 8) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 + 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 + 1 < 8)){
				if (matriz[x1 - 2][y1 + 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 - 1 >= 0)){
				if (matriz[x1 - 2][y1 - 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 - 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 + 1 < 8)){
				if (matriz[x1 + 1][y1 - 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 + 2 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 2][y1 - 1] == 'c'){
					pieza_encontrada++;
				}
			}else{
				pieza_encontrada--;
			}

			/*ver si hay reina*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si esa posicion esta disponible*/
			if (matriz[x1][y1] != '.'){
				pieza_encontrada++;
			}


		}else{//si no se puede mover a posicion
			pieza_encontrada++;
		}/*fin de septima posicion*/

		/*octavo par de coordenadas*/
		x1 = x + 1;
		y1 = y + 1;
		/*-------------------------*/
		if (x1 < 8 && y1 < 8){
			/*ver si hay peones*/
			if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 1][y1 - 1] == 'p'){
					pieza_encontrada++;
				}
			}

			if ((x1 + 1 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 1][y1 + 1] == 'p'){
					pieza_encontrada++;
				}
			}

			/*ver si hay torres*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 't'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			/*ver si hay alfil*/
			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'a'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si hay caballos*/
			if ((x1 + 2 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 2][y1 + 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 + 1 < 8) && (y1 + 2 < 8)){
				if (matriz[x1 + 1][y1 + 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 + 2 < 8) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 + 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 + 1 < 8)){
				if (matriz[x1 - 2][y1 + 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 - 1 >= 0)){
				if (matriz[x1 - 2][y1 - 1] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 - 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 + 1 < 8)){
				if (matriz[x1 + 1][y1 - 2] == 'c'){
					pieza_encontrada++;
				}
			}else if ((x1 + 2 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 2][y1 - 1] == 'c'){
					pieza_encontrada++;
				}
			}else{
				pieza_encontrada--;
			}

			/*ver si hay reina*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'r'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'r'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si esa posicion esta disponible*/
			if (matriz[x1][y1] != '.'){
				pieza_encontrada++;
			}


		}else{//si no se puede mover a posicion
			pieza_encontrada++;
		}/*fin de octava posicion*/

			/*si hay jaque mate*/
		if (pieza_encontrada >= 8){
			move(16, 10);
			printw("JAQUE MATE!");
			getch();
		}
	}/*fin de jugador numero 1*/

	if (contador_turnos % 2 == 0){
		/*primer par de coordenadas*/
		int x1 = x - 1;
		int y1 = y - 1;
		/*-------------------------*/
		int pieza_encontrada = 0;
		if (x1 >= 0 && y1 >= 0){
			/*ver si hay peones*/
			if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 1][y1 - 1] == 'P'){
					pieza_encontrada++;
				}
			}

			if ((x1 + 1 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 1][y1 + 1] == 'P'){
					pieza_encontrada++;
				}
			}

			/*ver si hay torres*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			/*ver si hay alfil*/
			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si hay caballos*/
			if ((x1 + 2 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 2][y1 + 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 + 1 < 8) && (y1 + 2 < 8)){
				if (matriz[x1 + 1][y1 + 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 + 2 < 8) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 + 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 + 1 < 8)){
				if (matriz[x1 - 2][y1 + 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 - 1 >= 0)){
				if (matriz[x1 - 2][y1 - 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 - 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 + 1 < 8)){
				if (matriz[x1 + 1][y1 - 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 + 2 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 2][y1 - 1] == 'C'){
					pieza_encontrada++;
				}
			}else{
				pieza_encontrada--;
			}

			/*ver si hay reina*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si esa posicion esta disponible*/
			if (matriz[x1][y1] != '.'){
				pieza_encontrada++;
			}


		}else{//si no se puede mover a posicion
			pieza_encontrada++;
		}/*fin de primera posicion*/

		/*segundo par de coordenadas*/
		x1 = x;
		y1 = y - 1;
		/*-------------------------*/
		if (y1 >= 0){
			/*ver si hay peones*/
			if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 1][y1 - 1] == 'P'){
					pieza_encontrada++;
				}
			}

			if ((x1 + 1 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 1][y1 + 1] == 'P'){
					pieza_encontrada++;
				}
			}

			/*ver si hay torres*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			/*ver si hay alfil*/
			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si hay caballos*/
			if ((x1 + 2 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 2][y1 + 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 + 1 < 8) && (y1 + 2 < 8)){
				if (matriz[x1 + 1][y1 + 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 + 2 < 8) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 + 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 + 1 < 8)){
				if (matriz[x1 - 2][y1 + 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 - 1 >= 0)){
				if (matriz[x1 - 2][y1 - 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 - 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 + 1 < 8)){
				if (matriz[x1 + 1][y1 - 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 + 2 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 2][y1 - 1] == 'C'){
					pieza_encontrada++;
				}
			}else{
				pieza_encontrada--;
			}

			/*ver si hay reina*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si esa posicion esta disponible*/
			if (matriz[x1][y1] != '.'){
				pieza_encontrada++;
			}


		}else{//si no se puede mover a posicion
			pieza_encontrada++;
		}/*fin de segunda posicion*/

		/*tercer par de coordenadas*/
		x1 = x + 1;
		y1 = y - 1;
		/*-------------------------*/
		if (x1 < 8 && y1 >= 0){
			/*ver si hay peones*/
			if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 1][y1 - 1] == 'P'){
					pieza_encontrada++;
				}
			}

			if ((x1 + 1 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 1][y1 + 1] == 'P'){
					pieza_encontrada++;
				}
			}

			/*ver si hay torres*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			/*ver si hay alfil*/
			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si hay caballos*/
			if ((x1 + 2 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 2][y1 + 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 + 1 < 8) && (y1 + 2 < 8)){
				if (matriz[x1 + 1][y1 + 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 + 2 < 8) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 + 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 + 1 < 8)){
				if (matriz[x1 - 2][y1 + 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 - 1 >= 0)){
				if (matriz[x1 - 2][y1 - 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 - 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 + 1 < 8)){
				if (matriz[x1 + 1][y1 - 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 + 2 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 2][y1 - 1] == 'C'){
					pieza_encontrada++;
				}
			}else{
				pieza_encontrada--;
			}

			/*ver si hay reina*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si esa posicion esta disponible*/
			if (matriz[x1][y1] != '.'){
				pieza_encontrada++;
			}


		}else{//si no se puede mover a posicion
			pieza_encontrada++;
		}/*fin de tercera posicion*/

		/*cuarto par de coordenadas*/
		x1 = x - 1;
		y1 = y;
		/*-------------------------*/
		if (x1 >= 0){
			/*ver si hay peones*/
			if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 1][y1 - 1] == 'P'){
					pieza_encontrada++;
				}
			}

			if ((x1 + 1 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 1][y1 + 1] == 'P'){
					pieza_encontrada++;
				}
			}

			/*ver si hay torres*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			/*ver si hay alfil*/
			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si hay caballos*/
			if ((x1 + 2 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 2][y1 + 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 + 1 < 8) && (y1 + 2 < 8)){
				if (matriz[x1 + 1][y1 + 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 + 2 < 8) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 + 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 + 1 < 8)){
				if (matriz[x1 - 2][y1 + 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 - 1 >= 0)){
				if (matriz[x1 - 2][y1 - 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 - 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 + 1 < 8)){
				if (matriz[x1 + 1][y1 - 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 + 2 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 2][y1 - 1] == 'C'){
					pieza_encontrada++;
				}
			}else{
				pieza_encontrada--;
			}

			/*ver si hay reina*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si esa posicion esta disponible*/
			if (matriz[x1][y1] != '.'){
				pieza_encontrada++;
			}


		}else{//si no se puede mover a posicion
			pieza_encontrada++;
		}/*fin de cuarta posicion*/

		/*quinto par de coordenadas*/
		x1 = x + 1;
		y1 = y;
		/*-------------------------*/
		if (x1 < 8){
			/*ver si hay peones*/
			if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 1][y1 - 1] == 'P'){
					pieza_encontrada++;
				}
			}

			if ((x1 + 1 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 1][y1 + 1] == 'P'){
					pieza_encontrada++;
				}
			}

			/*ver si hay torres*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			/*ver si hay alfil*/
			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si hay caballos*/
			if ((x1 + 2 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 2][y1 + 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 + 1 < 8) && (y1 + 2 < 8)){
				if (matriz[x1 + 1][y1 + 2] == 'A'){
					pieza_encontrada++;
				}
			}else if ((y1 + 2 < 8) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 + 2] == 'A'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 + 1 < 8)){
				if (matriz[x1 - 2][y1 + 1] == 'A'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 - 1 >= 0)){
				if (matriz[x1 - 2][y1 - 1] == 'A'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 - 2] == 'A'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 + 1 < 8)){
				if (matriz[x1 + 1][y1 - 2] == 'A'){
					pieza_encontrada++;
				}
			}else if ((x1 + 2 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 2][y1 - 1] == 'A'){
					pieza_encontrada++;
				}
			}else{
				pieza_encontrada--;
			}

			/*ver si hay reina*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si esa posicion esta disponible*/
			if (matriz[x1][y1] != '.'){
				pieza_encontrada++;
			}


		}else{//si no se puede mover a posicion
			pieza_encontrada++;
		}/*fin de quinta posicion*/


		/*sexto par de coordenadas*/
		x1 = x - 1;
		y1 = y + 1;
		/*-------------------------*/
		if (x1 >= 0 && y1 < 8){
			/*ver si hay peones*/
			if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 1][y1 - 1] == 'P'){
					pieza_encontrada++;
				}
			}

			if ((x1 + 1 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 1][y1 + 1] == 'P'){
					pieza_encontrada++;
				}
			}

			/*ver si hay torres*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			/*ver si hay alfil*/
			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si hay caballos*/
			if ((x1 + 2 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 2][y1 + 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 + 1 < 8) && (y1 + 2 < 8)){
				if (matriz[x1 + 1][y1 + 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 + 2 < 8) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 + 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 + 1 < 8)){
				if (matriz[x1 - 2][y1 + 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 - 1 >= 0)){
				if (matriz[x1 - 2][y1 - 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 - 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 + 1 < 8)){
				if (matriz[x1 + 1][y1 - 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 + 2 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 2][y1 - 1] == 'C'){
					pieza_encontrada++;
				}
			}else{
				pieza_encontrada--;
			}

			/*ver si hay reina*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si esa posicion esta disponible*/
			if (matriz[x1][y1] != '.'){
				pieza_encontrada++;
			}


		}else{//si no se puede mover a posicion
			pieza_encontrada++;
		}/*fin de sexta posicion*/

		/*septimo par de coordenadas*/
		x1 = x;
		y1 = y + 1;
		/*-------------------------*/
		if (y1 < 8){
			/*ver si hay peones*/
			if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 1][y1 - 1] == 'P'){
					pieza_encontrada++;
				}
			}

			if ((x1 + 1 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 1][y1 + 1] == 'P'){
					pieza_encontrada++;
				}
			}

			/*ver si hay torres*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			/*ver si hay alfil*/
			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si hay caballos*/
			if ((x1 + 2 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 2][y1 + 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 + 1 < 8) && (y1 + 2 < 8)){
				if (matriz[x1 + 1][y1 + 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 + 2 < 8) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 + 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 + 1 < 8)){
				if (matriz[x1 - 2][y1 + 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 - 1 >= 0)){
				if (matriz[x1 - 2][y1 - 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 - 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 + 1 < 8)){
				if (matriz[x1 + 1][y1 - 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 + 2 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 2][y1 - 1] == 'C'){
					pieza_encontrada++;
				}
			}else{
				pieza_encontrada--;
			}

			/*ver si hay reina*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si esa posicion esta disponible*/
			if (matriz[x1][y1] != '.'){
				pieza_encontrada++;
			}


		}else{//si no se puede mover a posicion
			pieza_encontrada++;
		}/*fin de septima posicion*/

		/*octavo par de coordenadas*/
		x1 = x + 1;
		y1 = y + 1;
		/*-------------------------*/
		if (x1 < 8 && y1 < 8){
			/*ver si hay peones*/
			if ((x1 + 1 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 1][y1 - 1] == 'P'){
					pieza_encontrada++;
				}
			}

			if ((x1 + 1 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 1][y1 + 1] == 'P'){
					pieza_encontrada++;
				}
			}

			/*ver si hay torres*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'T'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			/*ver si hay alfil*/
			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'A'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si hay caballos*/
			if ((x1 + 2 < 8) && (y1 + 1 < 8)){
				if (matriz[x1 + 2][y1 + 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 + 1 < 8) && (y1 + 2 < 8)){
				if (matriz[x1 + 1][y1 + 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 + 2 < 8) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 + 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 + 1 < 8)){
				if (matriz[x1 - 2][y1 + 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 - 2 >= 0) && (y1 - 1 >= 0)){
				if (matriz[x1 - 2][y1 - 1] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 - 1 >= 0)){
				if (matriz[x1 - 1][y1 - 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((y1 - 2 >= 0) && (x1 + 1 < 8)){
				if (matriz[x1 + 1][y1 - 2] == 'C'){
					pieza_encontrada++;
				}
			}else if ((x1 + 2 < 8) && (y1 - 1 >= 0)){
				if (matriz[x1 + 2][y1 - 1] == 'C'){
					pieza_encontrada++;
				}
			}else{
				pieza_encontrada--;
			}

			/*ver si hay reina*/
			for (x1; x1 < 8; x1++){
				if (matriz[x1][y1] == '.'){
					x1++;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				if (matriz[x1][y1] == '.'){
					x1--;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 >= 0; y1--){
				if (matriz[x1][y1] == '.'){
					y1--;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (y1; y1 < 8; y1++){
				if (matriz[x1][y1] == '.'){
					y1++;
				}else if (matriz[x1][y1] == 'D'){
					pieza_encontrada++;
				}else{
					break;
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1++;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 < 8; y1++){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1++;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 >= 0; x1--){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1--;
						y1--;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			for (x1; x1 < 8; x1++){
				for (y1; y1 >= 0; y1--){
					if (matriz[x1][y1] == '.'){
						x1++;
						y1--;
					}else if (matriz[x1][y1] == 'D'){
						pieza_encontrada++;
					}else{
						break;
					}
				}
			}

			/*ver si esa posicion esta disponible*/
			if (matriz[x1][y1] != '.'){
				pieza_encontrada++;
			}


		}else{//si no se puede mover a posicion
			pieza_encontrada++;
		}/*fin de octava posicion*/

			/*si hay jaque mate*/
		if (pieza_encontrada >= 8){
			move(16, 10);
			printw("JAQUE MATE!");
			getch();
		}
	}/*fin de jugador numero 1*/
		
}

void guardar_partida(char** matriz){
	string guardar = "";
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			guardar += matriz[i][j];
		}
	}

	ofstream juego("partida.txt");
	juego << guardar;
	juego.close();
}

void cargar_partida(char** matriz){
	char* temp = new char[65];
	ifstream juego("partida.txt");
	for (int i = 0; i < 64; i++){
		temp[i] = juego.get();
	}
	juego.close();

	int contador = 0;
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			matriz[i][j] = temp[contador];
			contador++;
		}
	}
}




//g++ -o aje Ajedrez.cpp -lncurses

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
