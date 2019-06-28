// LAURA JIMENEZ FERNANDEZ & DAVID LOSILLA CADENAS  
// L2-G12

#include "fecha.h"
#include "ListaAccesoPartidas.h"


//CONSTANTES Y TIPOS

const int NRN = 5;//N�mero de partidas ganadas/perdidas (racha) necesarias para subir/bajar de nivel 

typedef enum {Principiante, Medio, Experto} tNivel; //tipo enumerado tNivel

typedef enum {Gana, Pierde, Empata} tResultado; //tipo enumerado tResultado

typedef struct {
	std::string nombre; //nombre de un usuario, �NICO en el gestor
	std::string pas; // contrase�a del usuario
	tNivel nivel; //nivel de juego 
	int racha; //�ltima racha del usuario
	bool esperando; //si est� esperando o no un adversario para empezar una nueva partida
	int ganadas, perdidas, empatadas;//n�mero de partidas ganadas, perdidas, o empatadas
	tFecha ultConexion; // fecha de la �ltima conexi�n
	std::string avisos; //avisos que le env�a el gestor
	tListaAccesoPartidas lista; //lista de acceso a las partidas en curso
}tUsuario;


//FUNCIONES

bool cargar(tUsuario &usuario, std::ifstream &archivo); //Dado un flujo de archivo, lee los datos de un usuario

void guardar(const tUsuario &usuario, std::ofstream &archivo); //Dado un flujo de archivo, escribe en �l los datos del usuario

void iniciar(tUsuario &usuario, const std::string &id, const std::string &pas); //Recibe un nombre  de usuario y una contrase�a, e inicia todos los campos del usuario

bool iniciarSesion(tUsuario &usuario, const std::string &clave); // Recibe una contrase�a y un usuario, y se comprueba si la contrase�a es correcta o no

void actualizarAvisos(tUsuario &usu, const std::string &aviso); // Actualiza el campo de avisos, a�adiendo al final una nueva l�nea con el nuevo aviso

void limpiarAvisos(tUsuario &usu); // Actualiza el campo avisos, dejando el string vac�o

bool nuevaPartida(tUsuario &usuario, const tParIdEn &par); //Si el usuario no ha utilizado todas las partidas en curso que puede tener, inserta en su lista de partidas en curso
															//la informaci�n de acceso a la partida par, y actualiza el estado de espera	

void aplicarFinPartida(tUsuario &usuario, const std::string &idPart, tResultado resultado); // Modifica los cambios afectados al final de una partida en curso con el resultado dado