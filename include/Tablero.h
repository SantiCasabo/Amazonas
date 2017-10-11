#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED
#include <set>

using namespace std;

// devuelve el codigo de la ficha que esta en tal fila, tal columna.
// devuelve -1 si no hay nada
int obtener_codigo_ficha(set<int> &estado, int columna, int fila){
	int casillero= columna * 10 + fila;

	if (estado.count(casillero + 100)) return 100;		// busca R1
	if (estado.count(casillero + 200)) return 200;		// busca R2
	if (estado.count(casillero + 300)) return 300;		// busca R3
	if (estado.count(casillero + 400)) return 400;		// busca R4
	if (estado.count(casillero + 500)) return 500;		// busca A1
	if (estado.count(casillero + 600)) return 600;		// busca A2
	if (estado.count(casillero + 700)) return 700;		// busca A3
	if (estado.count(casillero + 800)) return 800;		// busca A4
	if (estado.count(casillero + 900)) return 900;		// busca X

	return 0;											// no encontro nada

}

bool casilla_ocupada(set<int> &estado, int columna, int fila){

	int casillero= columna * 10 + fila;

	if (estado.count(casillero + 100) ||    // busca R1
		estado.count(casillero + 200) ||    // busca R2
		estado.count(casillero + 300) ||    // busca R3
		estado.count(casillero + 400) ||    // busca R4
		estado.count(casillero + 500) ||    // busca A1
		estado.count(casillero + 600) ||    // busca A2
		estado.count(casillero + 700) ||    // busca A3
		estado.count(casillero + 800) ||    // busca A4
		estado.count(casillero + 900))   	// busca X
			return true;

	return false;

}


// devuelve un set de posiciones validas para una ficha en un lugar(numerico)
void posiciones_validas(set<int> &estado, int codigo_o, set<int> &pos_validas){
	// ubicacion es ficha+x+y   (ficha+columna+fila)
	// 123, 547, etc a las que chequearle las jugadas validas

	int it_col, it_fila; 							// iteradores de fila y columna
	int fila= codigo_o % 10;
	int columna= ((codigo_o - fila) % 100)/10;
	int ficha= codigo_o - fila - columna * 10;   	// 100, 200, etc

	pos_validas.clear();

	//recorre 4 rectas: arriba, abajo, derecha, izquierda

	it_col= columna + 1;		// porque en columna esta la ficha
	while ( it_col <=9 && !casilla_ocupada(estado, it_col, fila)){
		pos_validas.insert(ficha + it_col*10 + fila);
		it_col++;
	}

	it_col= columna - 1;		// porque en columna esta la ficha
	while ( it_col >=0 && !casilla_ocupada(estado, it_col, fila)){
		pos_validas.insert(ficha + it_col*10 + fila);
		it_col--;
	}

	it_fila= fila + 1;			// porque en fila esta la ficha
	while ( it_fila <=9 && !casilla_ocupada(estado, columna, it_fila)){
		pos_validas.insert(ficha + columna * 10 + it_fila);
		it_fila++;
	}

	it_fila= fila - 1;			// porque en fila esta la ficha
	while ( it_fila >=0 && !casilla_ocupada(estado, columna, it_fila)){
		pos_validas.insert(ficha + columna * 10 + it_fila);
		it_fila--;
	}

	//recorre 4 diagonales

	it_fila= fila + 1;			// porque en fila esta la ficha
	it_col= columna + 1;		// porque en columna esta la ficha
	while ( it_col <=9 && it_fila <=9 && !casilla_ocupada(estado, it_col, it_fila)){
		pos_validas.insert(ficha + it_col*10 + it_fila);
		it_fila++;
		it_col++;
	}

	it_fila= fila - 1;			// porque en fila esta la ficha
	it_col= columna + 1;		// porque en columna esta la ficha
	while ( it_col <=9 && it_fila >=0 && !casilla_ocupada(estado, it_col, it_fila)){
		pos_validas.insert(ficha + it_col*10 + it_fila);
		it_fila--;
		it_col++;
	}

	it_fila= fila - 1;			// porque en fila esta la ficha
	it_col= columna - 1;		// porque en columna esta la ficha
	while ( it_col >=0 && it_fila >=0 && !casilla_ocupada(estado, it_col, it_fila)){
		pos_validas.insert(ficha + it_col*10 + it_fila);
		it_fila--;
		it_col--;
	}

	it_fila= fila + 1;			// porque en fila esta la ficha
	it_col= columna - 1;		// porque en columna esta la ficha
	while ( it_col >=0 && it_fila <=9 && !casilla_ocupada(estado, it_col, it_fila)){
		pos_validas.insert(ficha + it_col*10 + it_fila);
		it_fila++;
		it_col--;
	}
}

// busca el destino en el set de jugadas posibles
bool destino_valido(set<int> &estado, int codigo_o, int codigo_d){

	set<int> pos_validas;
	posiciones_validas(estado, codigo_o, pos_validas);
	set<int>::iterator it= pos_validas.begin();

  	for (it; it!=pos_validas.end(); ++it){
    	if (codigo_d == *it) return true;
  	}

  	return false;
}

void mover_ficha(set<int> &estado, int codigo_o, int codigo_d){

	// elimina del set estado actual el origen
	// si es flecha no lo va a poder borrar
	estado.erase(codigo_o);

	estado.insert(codigo_d);

}

#endif // TABLERO_H_INCLUDED