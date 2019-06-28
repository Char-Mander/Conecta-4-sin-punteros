// LAURA JIMENEZ FERNANDEZ & DAVID LOSILLA CADENAS  
// L2-G12

#include "conecta4.h"
#include "fecha.h"

//TIPOS Y CONSTANTES

typedef enum { EnCurso, Terminada } tEstadoPartida;  //Definimos el enumerado tEstadoPartida

typedef struct {
	std::string id; //identificador único de la partida (fecha de inicio más los dos adversarios)
	std::string jugador1, jugador2; //los dos jugadores
	tFecha fechaIni; //fecha de inicio
	tFecha fechaActu; //decha de la última actualización
	tEstadoPartida estadoPartida; //estado partida del tipo enumerado tEstadoPartida
	tConecta4 estadoJuego; //estado del juego, implementado en conecta4.h, que incluye estado, del tipo enumerado tEstado
				           // el turno, del tipo enumerado tTurno, las fichas que hay en el tablero, y el propio tablero, del tipo tFicha(tTurno)
}tPartida; //Definimos el tipo tPartida


//FUNCIONES

void nueva(tPartida &partida, const std::string &jugador1, const std::string &jugador2); //recibe los identificadores y devuelve una partida con todos sus datos rellenos

void guardar(const tPartida &partida, std::ofstream &archivo); //Dado un flujo de archivo de salida, lee los datos que corresponden a una partida

bool cargar(tPartida &partida, std::ifstream &archivo);  //Dado un flujo de archivo de entrada, lee los datos que corresponden a una partida

void abandonar(tPartida &partida); //Modifica el estado  de la partida a Terminada y la fecha de la última actualización

bool aplicarJugada(tPartida &partida, int col); //Aplica la jugada col al juego