#include <iostream>

using std::cin;
using std::cout;
using std::endl;

bool verificar_pieza(char[], int, int);

int main(){
	int size = 5;
	char movement[size];

	cout << "Ingrese el movimiento: ";
	cin >> movement;
	cout << endl;

	verificar_pieza(movement, size, 2);

	for (int i = 0; i < 8; ++i){
		if (i == 0){
			cout << "Bien hecho";
		}else{
			break;
		}
	}
	

	return 0;
}

bool verificar_pieza(char movement[], int size, int contador_turnos){//65 a 72 de la A a la H == 97 a 104 minusculas
	int x1, y1, x2, y2;

		x1 = movement[0];
		y1 = movement[1];
		x2 = movement[2];
		y2 = movement[3];
		x1 = x1 - 49;
		y1 = y1 - 97;
		x2 = x2 - 49;
		y2 = y2 - 97;

		x1 = (7 - x1);
		x2 = (7 - x2);
		int pieza = 'P';
		cout << pieza;
		cout << endl;

		cout << x1 << "-" << y1 << "-" << x2 << "-" << y2;
	
}

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
