// LAURA JIMENEZ FERNANDEZ & DAVID LOSILLA CADENAS  
// L2-G12

#include "Usuario.h"

//CONSTANTES Y TIPOS

const int MAX_USUARIOS = 100; //Número máximo de usuarios que puede tener una lista de tipo tListaUsuarios

typedef tUsuario tArrayListaUsuarios[MAX_USUARIOS]; //Array de usuarios

typedef struct {
	tArrayListaUsuarios listausuarios; //elementos de la lista
	int contador; //contador de usuarios de la lista
}tListaUsuarios;  //Declaramos el tipo tListaUsuarios

//FUNCIONES

bool cargar(tListaUsuarios &usuarios, std::ifstream &archivo);	//Carga la lista de usuarios desde el flujo archivo

void guardar(const tListaUsuarios &usuarios, std::ofstream &archivo); // Guarda la lista de uusarios en el flujo archivo

bool buscarUsuarioEsperando(const tListaUsuarios &usuarios, tNivel nivel, int &pos); // Devuelve la posición del primer usuario del nivel dado que esté esperando para iniciar una partida (si lo hay)

bool insertar(tListaUsuarios &usuarios, const tUsuario &usuario, int&pos); // Añade un usuario en la posición de la lista que le corresponde, ordenadamente (siempre que no haya uno con el mismo nombre)

bool buscar(const tListaUsuarios &usuarios, const std::string &idUser, int &pos); // Dado un identificador de usuario y una lista, comprueba si existe el id en la lista (si existe devuelve su posición)
																				//si no está, devuelve la posición que le correspondería
