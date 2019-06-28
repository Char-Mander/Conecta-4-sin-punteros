// LAURA JIMENEZ FERNANDEZ & DAVID LOSILLA CADENAS  
// L2-G12

#include <iostream>

//TIPOS Y CONSTANTES

const int MAX_PAR_US = 10; // Máximo de partidas en curso que un usuario puede tener

typedef struct{
	std::string idpart; // identificador de la partida(en curso)
	int enlace; // Índice en el que se encuentra la partida en la lista de partidas del gestor
}tParIdEn;  //Definimos el tipo tParIdEn

typedef tParIdEn tArrayPartidasEnCurso[MAX_PAR_US];  //Definimos el tipo tArrayPartidasEnCurso

typedef struct{
	tArrayPartidasEnCurso elementos; // elementos de la lista de partidas en curso
	int contador; //contador de elementos de dicha lista
}tListaAccesoPartidas;  //Definimos el tipo tListaAccesoPartidas

//FUNCIONES

void iniciar(tListaAccesoPartidas &lista); // Inicia la lista vacía

bool llena(const tListaAccesoPartidas &lista); // Comprueba si la lista está llena

bool insertar(tListaAccesoPartidas &lista, tParIdEn par); // Dado un elemento, si la lista no está llena, lo inserta al final de la lista

bool eliminar(tListaAccesoPartidas &lista, const std::string &id); // Dado un id de partida, lo busca en la lista, y si lo encuentra, lo elimina