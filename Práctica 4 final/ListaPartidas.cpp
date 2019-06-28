// LAURA JIMENEZ FERNANDEZ & DAVID LOSILLA CADENAS  
// L2-G12

#include "ListaPartidas.h"
#include <fstream>
#include <string>

using namespace std;

void guardar(const tListaPartidas &partidas, std::ofstream &archivo) {  // Guarda la lista de partidas en el flujo archivo
	archivo << partidas.contador << '\n';  //Guardamos en el archivo en primer lugar el contador y posteriormente cada partida mediante el recorrido indicado
	for (int pos = 0; pos< partidas.contador; pos++) {
		guardar(partidas.partida[pos], archivo);
	}
}

bool cargar(tListaPartidas &partidas, std::ifstream &archivo) {  //Carga la lista de partidas desde el flujo archivo
	bool ok = true;
	int pos = 0;

	archivo >> partidas.contador; //Procedemos en primer lugar a cargar del archivo el contador y posteriormente tantas partidas como el contador nos haya indicado
	do {
		ok = cargar(partidas.partida[pos], archivo);
		pos++;
	} while (ok && pos < partidas.contador);

	return ok;
}

bool insertar(tListaPartidas &partidas, const tPartida &partida) {  // Dada una partida, si hay espacio en la lista, la añade al final de esta
	bool ok;
	if (partidas.contador < MAX_ELEMENTOS) { //En caso de que haya espacio disponible para insertar una partida la insertamos
		ok = true;
		partidas.partida[partidas.contador] = partida;
		partidas.contador++;
	}
	else ok = false;

	return ok;
}
