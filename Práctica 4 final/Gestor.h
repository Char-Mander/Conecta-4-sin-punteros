// LAURA JIMENEZ FERNANDEZ & DAVID LOSILLA CADENAS  
// L2-G12

#include "ListaUsuarios.h"
#include "ListaPartidas.h"

//TIPOS

typedef struct {
	tListaPartidas partidas; //única copia de partidas de la aplicación
	tListaUsuarios usuarios; // lista de usuarios del sistema
	int posusu; //índice del usuario que inicia sesión en la lista de usuarios
	int indpart; //partida seleccionada por el usuario de la sesión
}tGestor;  //Definimos el tipo tGestor

//FUNCIONES

bool arrancar(tGestor &gestor); //Inicializa el gestor, cargando la información del sistema (abre los archivos, carga las listas, etc.)

void generarAccesos(tGestor &gestor); //Recorre la lista de partidas, y para las que están en curso, añaden el id y el indice a la lista de partidas en curso de cada uno de los adversarios

void apagar(tGestor &gestor); // Apaga el gestor, abriendo los ficheros para guardar las listas de usuarios y de partidas del sistema

//FUNCIONES DEL MENÚ REGISTRO

bool iniciarSesion(tGestor &gestor, const std::string &idUsu, const std::string &clave); //Funcion que lleva a cabo el inicio de sesion de un usuario dado su nombre y su clave

bool crearCuenta(tGestor &gestor, const std::string &idUsu, const std::string &clave);  //Funcion que crea una cuenta nueva dado un nombre de usuario y una contraseña

bool tieneAvisos(const tGestor &gestor, std::string &aviso);  //Funcion que determina si el usuario tiene avisos

void limpiarAvisos(tGestor &gestor); //Funcion que limpia los avisos del usuario borrando todos

std::string resumenActividad(const tGestor &gestor);  //Funcion que devuelve un resumen de la actividad del usuario (racha, ganadas, perdidas,...)

void mostrarActividad(const tGestor &gestor); //Funcion que se encarga de mostrar por pantalla la actividad del usuario

//FUNCIONES DEL MENÚ USUARIO

int partidasUsuario(const tGestor &gestor); //Funcion que devuelve el numero de partidas en curso que tiene el usuario

std::string cabecera(const tGestor &gestor, int posEnCurso); //Funcion que muestra la informacion de una partida del usuario

void ordenar_Fecha(tGestor &gestor); //Funcion que ordena las partidas de un usuario por fecha

void ordenar_Turno(tGestor &gestor); //Funcion que ordena las partidas de un usuario por turno

bool nuevaPartida(tGestor &gestor);  //Funcion que crea una nueva partida

void apuntaPartida(tGestor &gestor, int posParEnCurso);  //Funcion que actualiza el campo gestor.indpart indicando cual es la partida seleccionada por el usuario

//FUNCIONES DEL MENÚ PARTIDA

void mostrarPartida(const tGestor &gestor);  //Funcion que muestra una partida 

bool esSuTurno(const tGestor &gestor);  //Funcion que determina si es el turno del usuario seleccionado en una partida

void jugarPartida(tGestor &gestor, int col); //funcion que dado un movimiento aplica la jugada y actualiza los adversarios si es necesario

void abandonarPartida(tGestor &gestor);  //Funcion que aplica la decision del usuario de abandonar una partida

