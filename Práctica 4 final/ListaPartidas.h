// LAURA JIMENEZ FERNANDEZ & DAVID LOSILLA CADENAS  
// L2-G12

#include "Partida.h"

//CONSTANTES Y TIPOS

const int MAX_ELEMENTOS = 100; //Número máximo de partidas en la lista de tipo tArrayPartidas

typedef tPartida tArrayPartidas[MAX_ELEMENTOS]; //Array de partidas

typedef struct {
	int contador;			//contador de los elementos de la lista
	tArrayPartidas partida; // elementos de la lista
}tListaPartidas;  //Definimos el tipo tListaPartidas


//FUNCIONES

void guardar(const tListaPartidas &partidas, std::ofstream &archivo); // Guarda la lista de partidas en el flujo archivo

bool cargar(tListaPartidas &partidas, std::ifstream &archivo); //Carga la lista de partidas desde el flujo archivo

bool insertar(tListaPartidas &partidas, const tPartida &partida); // Dada una partida, si hay espacio en la lista, la añade al final de esta
