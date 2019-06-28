// LAURA JIMENEZ FERNANDEZ & DAVID LOSILLA CADENAS 
// L2-G12

#include  "ListaAccesoPartidas.h"  
#include <string>

using namespace std;

void iniciar(tListaAccesoPartidas &lista){  // Inicia la lista vacía
	lista.contador = 0;
}

bool llena(const tListaAccesoPartidas &lista) {  // Comprueba si la lista está llena
	bool espacioDisponible;

	if (lista.contador < MAX_PAR_US) //Comprobamos si la lista posee menos elementos que el máximo permitido
		espacioDisponible = true;
	else espacioDisponible = false;

	return espacioDisponible;
}

bool insertar(tListaAccesoPartidas &lista, tParIdEn par) {  // Dado un elemento, si la lista no está llena, lo inserta al final de la lista
	bool sePuede;

	sePuede = llena(lista); //comprueba que no esté llena

	if (sePuede){ //si no está llena, inserta la información de la partida par y aumenta el contador
		lista.elementos[lista.contador] = par;
		lista.contador++;
	}
	else cout << '\n' << "No se pueden tener mas partidas en curso" << '\n';

	return sePuede;
}

bool eliminar(tListaAccesoPartidas &lista, const string &id) {  // Dado un id de partida, lo busca en la lista, y si lo encuentra, lo elimina
	bool encontrado = false;
	int pos = 0;

	do { //realizamos una busqueda de la partida con el id indicado
		if (lista.elementos[pos].idpart == id) {  //En caso de encontrar dicha partida procedemos a eliminarla y actualizar el contador
			lista.contador--;
			encontrado = true;
			for (int i = pos; i < lista.contador; i++) {  //Actualizamos la lista
				lista.elementos[i] = lista.elementos[i + 1];
			}
		}
		else pos++;
	} while (!encontrado && pos < lista.contador);

	return encontrado;
}