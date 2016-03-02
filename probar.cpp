#include <iostream>

using std::cin;
using std::cout;
using std::endl;

bool entrada_movida(char[], int);

int main(){
	int size = 5;
	char movement[size];

	cout << "Ingrese el movimiento: ";
	cin >> movement;
	cout << movement;
	cout << endl;

	if (entrada_movida(movement, size)){
		cout << "Funciona";
	}

	return 0;
}

bool entrada_movida(char movement[], int size){// 48 a 57 son numeros = 65 a 72 de la A a la H == 97 a 104
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