// LAURA JIMENEZ FERNANDEZ & DAVID LOSILLA CADENAS  
// L2-G12

#include "Gestor.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

bool arrancar(tGestor &gestor) { //Inicializa el gestor, cargando la información del sistema (abre los archivos, carga las listas, etc.)

	ifstream archivopart, archivousu; //Variables ifstream utilizadas para leer los archivos.txt de usuarios y partidas 
	bool ok = true;

	archivopart.open("partidas.txt"); //Abrimos los archivos .txt de partidas y usuarios
	archivousu.open("usuarios.txt");
	if (archivopart.is_open() && archivousu.is_open()) {  //En caso de que estos se hayan podido abrir correctamente procedemos a su carga en las listas
		ok = cargar(gestor.usuarios, archivousu);
		
		switch (ok) {
		case true: ok = cargar(gestor.partidas, archivopart); 
			if (!ok) cout << "El archivo 'partidas' ha dado problemas"; 
			else generarAccesos(gestor);
			break;
		case false: cout << '\n' << "El archivo 'usuarios' ha dado problemas " << '\n'; 
			break;
		}		
		archivopart.close();  //Cerranmos los archivos .txt despues de su carga
		archivousu.close();
	}
	else ok = false;  //Actualizamos la variable bool ok para informar de si la carga se ha realizado con exito o no

	return ok;
}

void generarAccesos(tGestor &gestor) { //Recorre la lista de partidas, y para las que están en curso, añaden el id y el índice a la lista de partidas en curso de cada uno de los adversarios
	tParIdEn part;
	int pos = gestor.usuarios.contador;

	for (int contador = 0; contador < gestor.partidas.contador; contador++) { //Recorremos la lista de partidas para buscar aquellas que están en curso
		if (gestor.partidas.partida[contador].estadoPartida != Terminada) {
			part.enlace = contador;
			part.idpart = gestor.partidas.partida[contador].id;
			pos = gestor.usuarios.contador;
			buscar(gestor.usuarios, gestor.partidas.partida[contador].jugador1, pos);	//Buscamos la posición del jugador1		
			insertar(gestor.usuarios.listausuarios[pos].lista, part);  //Guardamos los datos de acceso a la partida para este usuario
			pos = gestor.usuarios.contador;
			buscar(gestor.usuarios, gestor.partidas.partida[contador].jugador2, pos); //Buscamos la posición del jugador2
			insertar(gestor.usuarios.listausuarios[pos].lista, part);		//Guardamos los datos de acceso a la partida para este usuario
		}
	}
}

void apagar(tGestor &gestor) { // Apaga el gestor, abriendo los ficheros para guardar las listas de usuarios y de partidas del sistema
ofstream archivopart, archivousu;

archivousu.open("usuarios.txt");  //Abrimos los archivos .txt en los que vamos a guardar las listas y procedemos a guardarlas
archivopart.open("partidas.txt");

guardar(gestor.usuarios, archivousu);
guardar(gestor.partidas, archivopart);

archivousu.close();  //Cerramos los archivos .txt
archivopart.close();

}

//FUNCIONES QUE USAN EL MENU REGISTRO DEL MAIN

bool iniciarSesion(tGestor &gestor, const string &idUsu, const string &clave) {  //Funcion que lleva a cabo el inicio de sesion de un usuario dado su nombre y su clave
	bool correcto, encontrado;
	int pos = gestor.usuarios.contador;
	
	encontrado = buscar(gestor.usuarios, idUsu, pos); //Determinamos si el usuario existe y en caso afirmativo indicamos su posicion po pos

	switch (encontrado) { //En caso de que sea encontrado comprobamos su clave
	case true: correcto = iniciarSesion(gestor.usuarios.listausuarios[pos], clave);
		if (!correcto) {
		cout << '\n' << "Error. Clave incorrecta. " << '\n';
		system("pause");
	}
		else gestor.posusu = pos; //Si todo es correcto seleccionamos al usuario como usuario seleccionado
		cout << '\n' << "Ha iniciado sesion correctamente. " << '\n'; //Informamos de que la sesion se ha iniciado correctamente
			break;
	case false: correcto = false;
		cout << '\n' << "Error. El usuario no existe. " << '\n';  //Informamos de que el usuario no existe
		system("pause"); break;
	}
		return correcto;
}

bool crearCuenta(tGestor &gestor, const string &idUsu, const string &clave) {  //Funcion que crea una cuenta nueva dado un nombre de usuario y una contraseña
	bool sePuede = true, encontrado; 
	int  indice = 0;
	gestor.posusu = 0;
	int pos = gestor.usuarios.contador;

	encontrado = buscar(gestor.usuarios, idUsu, pos); //Buscamos si existe ya el usuario que se dea crear

	if (gestor.usuarios.contador < MAX_USUARIOS) { //Comprobamos si no se ha llegado al limite de usuarios ya
		do {  
			if (encontrado)
				sePuede = false;
			else gestor.posusu++;
		} while (!encontrado && gestor.posusu < gestor.usuarios.contador); //Buscamos la posicion en la que se debera insertar el usuario nuevo para conservar el orden de la lista
	}
	else sePuede = false;

	switch (sePuede) {  //En caso de que todo sea correcto procedemos a crear este nuevo usuario e insertarlo en su posicion correspondiente
	case true:iniciar(gestor.usuarios.listausuarios[gestor.posusu], idUsu, clave);
		insertar(gestor.usuarios, gestor.usuarios.listausuarios[gestor.usuarios.contador], gestor.posusu);
		gestor.usuarios.contador++; break;
	case false: if (gestor.usuarios.contador >= MAX_USUARIOS) //Informamos de que a sido imposible crear el usuario por que se ha alcanzado el limite o por que ya existe
		cout << '\n' << "No pueden crearse mas usuarios" << '\n';
			else cout << '\n' << "El usuario ya existe." << '\n';

			system("pause"); break;
	}

	return sePuede;
}

bool tieneAvisos(const tGestor &gestor, string &aviso) { //Funcion que determina si el usuario tiene avisos
	bool tiene = true; //Variable bool que nos servira para determinar si tiene o no avisos el usuario
	ostringstream aux; //Flujo auxiliar que nos servira para determinar de una forma mas sencilla si tiene avisos el usuario
	aux << '\n';
	if (gestor.usuarios.listausuarios[gestor.posusu].avisos != aux.str()) { //Determinamos si tiene o no avisos el usuario
		cout << '\n' << "Tiene avisos: " << '\n';
		aviso = gestor.usuarios.listausuarios[gestor.posusu].avisos;
	}
	else tiene = false;

	return tiene;
}

void limpiarAvisos(tGestor &gestor) {  //Funcion que limpia los avisos del usuario borrando todos
	limpiarAvisos(gestor.usuarios.listausuarios[gestor.posusu]);
}

string resumenActividad(const tGestor &gestor) { //Funcion que devuelve un resumen de la actividad del usuario (racha, ganadas, perdidas,...)
	ostringstream actividad; //Flujo que nos servira para devolver el resumen de actividad del usuario

	actividad << "Partidas ganadas: " << gestor.usuarios.listausuarios[gestor.posusu].ganadas << '\n';
	actividad << "Partidas perdidas: " << gestor.usuarios.listausuarios[gestor.posusu].perdidas << '\n';
	actividad << "Partidas empatadas: " << gestor.usuarios.listausuarios[gestor.posusu].empatadas << '\n';
	actividad << "Nivel: ";

	switch (gestor.usuarios.listausuarios[gestor.posusu].nivel) { //Convertimos el tipo tNivel a un string que podamos mostrar por pantalla facilmente
	case Principiante: actividad << "Principiante "; break;
	case Medio: actividad << "Medio "; break;
	case Experto: actividad << "Experto "; break;
	}

	actividad << '\n' << "Racha: ";

	if (gestor.usuarios.listausuarios[gestor.posusu].racha > 0) //DInformamos de si el usuario lleva una racha de gandas, de perdidas o ninguna racha
		actividad << gestor.usuarios.listausuarios[gestor.posusu].racha << " ganadas";
	else if (gestor.usuarios.listausuarios[gestor.posusu].racha == 0)
		actividad << "No lleva ninguna racha actualmente (0)";
	else actividad << -gestor.usuarios.listausuarios[gestor.posusu].racha << " perdidas";

	actividad << '\n';

	if (gestor.usuarios.listausuarios[gestor.posusu].esperando) //Informamos de si el usuario esta esperando una partida o no
		actividad << "Esta esperando actualmente un adversario para jugar una nueva partida ";
	else actividad << "No esta esperando ningun adversario";
	actividad << '\n';

	return actividad.str(); //Devolvemos el resumen de actividad
}

void mostrarActividad(const tGestor &gestor) {  //Funcion que se encarga de mostrar por pantalla la actividad del usuario
	ostringstream actividad;

	actividad << resumenActividad(gestor);
	cout << '\n' << "ACTIVIDAD:" << '\n' << '\n' << actividad.str();  //Mostramos por pantalla la actividad
}

//FUNCIONES DEL MENÚ USUARIO
int partidasUsuario(const tGestor &gestor) {  //Funcion que devuelve el numero de partidas en curso que tiene el usuario
	return gestor.usuarios.listausuarios[gestor.posusu].lista.contador;
}

string cabecera(const tGestor &gestor, int posEnCurso) {  //Funcion que muestra la informacion de una partida del usuario
	ostringstream informacion;
	bool hora = true;

	if (esSuTurno(gestor))	informacion << "  *" << "       ";  //Comprobamos si es o no el turno del usuario para mostrarlo con '*'
	else informacion << "          ";

	informacion << setw(15) << left << gestor.partidas.partida[posEnCurso].jugador1 << setw(15) << left << gestor.partidas.partida[posEnCurso].jugador2 << stringFecha(gestor.partidas.partida[posEnCurso].fechaActu, hora) << '\n' << '\n';

	return informacion.str();
}

void ordenar_Fecha(tGestor &gestor) { //Funcion que ordena las partidas de un usuario por fecha
tParIdEn aux;
bool inter = true;
int i = 0;
while ((i < gestor.usuarios.listausuarios[gestor.posusu].lista.contador-1) && inter) {
	inter = false;
	// Desde el último hasta el siguiente a i...
	for (int j = gestor.usuarios.listausuarios[gestor.posusu].lista.contador-1; j > i; j--) {
		if (gestor.partidas.partida[gestor.usuarios.listausuarios[gestor.posusu].lista.elementos[j].enlace].fechaActu< gestor.partidas.partida[gestor.usuarios.listausuarios[gestor.posusu].lista.elementos[j-1].enlace].fechaActu) {
			tParIdEn tmp;
			tmp = gestor.usuarios.listausuarios[gestor.posusu].lista.elementos[j];
			gestor.usuarios.listausuarios[gestor.posusu].lista.elementos[j] = gestor.usuarios.listausuarios[gestor.posusu].lista.elementos[j-1];
			gestor.usuarios.listausuarios[gestor.posusu].lista.elementos[j-1] = tmp;
			inter = true;
		}
	}
		if (inter) {
		i++;
		}
	}
}

void ordenar_Turno(tGestor &gestor) { //Funcion que ordena las partidas de un usuario por turno
	int pos;
	tParIdEn nuevo;
	
	for (int i = 1; i < gestor.usuarios.listausuarios[gestor.posusu].lista.contador; i++) { //Realizzamos un recorrido de la lista de usuarios		
		apuntaPartida(gestor, i);
		if (esSuTurno(gestor)) {  //En caso de que en una partida el usuario tenga el turno revisamos si las partidas anteriores tambien tienen el turno
			pos = 0;			
			apuntaPartida(gestor, pos);
			while (pos < i && esSuTurno(gestor)) { //Buscamos el primer elemento del que no sea su turno (si lo hay)
				pos++;
				apuntaPartida(gestor, pos);
			}			
			nuevo = gestor.usuarios.listausuarios[gestor.posusu].lista.elementos[i];
			for (int j = i; j > pos; j--) {  //Reordenamos la lista de partidas en caso de que sea necesario
				gestor.usuarios.listausuarios[gestor.posusu].lista.elementos[j] = gestor.usuarios.listausuarios[gestor.posusu].lista.elementos[j - 1];
			}
			gestor.usuarios.listausuarios[gestor.posusu].lista.elementos[pos] = nuevo;
		}
	}
}

bool nuevaPartida(tGestor &gestor) { //Funcion que crea una nueva partida
	bool encontrado, ok;
	int pos = gestor.posusu;
	int contador = partidasUsuario(gestor);
	tParIdEn datos;
	ostringstream aviso;


	if (!gestor.usuarios.listausuarios[gestor.posusu].esperando && contador < MAX_PAR_US) { //Determinamos si el usuario esta ya esperando una partida o si ha alcanzado el maximo numero de partidas permitido
		encontrado = buscarUsuarioEsperando(gestor.usuarios, gestor.usuarios.listausuarios[gestor.posusu].nivel, pos); //Buscamos un usuario esperando del mismo nivel

		if (encontrado) { //Si este es encontrado
			nueva(gestor.partidas.partida[gestor.partidas.contador], gestor.usuarios.listausuarios[gestor.posusu].nombre, gestor.usuarios.listausuarios[pos].nombre);
			datos.enlace = gestor.partidas.contador;
			datos.idpart = gestor.partidas.partida[gestor.partidas.contador].id;
			gestor.partidas.contador++;
			nuevaPartida(gestor.usuarios.listausuarios[pos], datos); // inserta los datos de la partida en la lista del adversario
			aviso << "Se ha creado una nueva partida contra " << gestor.usuarios.listausuarios[gestor.posusu].nombre << " en la fecha " << stringFecha(fechaActual(), false);
			actualizarAvisos(gestor.usuarios.listausuarios[pos], aviso.str());
			nuevaPartida(gestor.usuarios.listausuarios[gestor.posusu], datos); // inserta los datos de la partida en la lista del usuario de la sesión
			ok = true;
		}
		else { // si no se encuentra ningun jugador esperando del mismo nivel
			gestor.usuarios.listausuarios[gestor.posusu].esperando = true;
			cout << '\n' << "Estas esperando a un adversario para jugar una partida" << '\n';
			ok = false;
		}
	}
	else {  //En caso de haber alcanzado el maximo de partidas en curso
		ok = false;
		cout << '\n' << "Te has excedido con el numero de partidas en curso o bien ya estas esperando a un adversario" << '\n' << '\n';
	}

	
	return ok;
}

void apuntaPartida(tGestor &gestor, int posParEnCurso) {  //Funcion que actualiza el campo gestor.indpart indicando cual es la partida seleccionada por el usuario
	gestor.indpart = gestor.usuarios.listausuarios[gestor.posusu].lista.elementos[posParEnCurso].enlace;
}

//FUNCIONES DEL MENÚ PARTIDA
void mostrarPartida(const tGestor &gestor) {  //Funcion que muestra una partida 
	mostrar(gestor.partidas.partida[gestor.indpart].estadoJuego, gestor.partidas.partida[gestor.indpart].jugador1, gestor.partidas.partida[gestor.indpart].jugador2);
}

bool esSuTurno(const tGestor &gestor) {  //Funcion que determina si es el turno del usuario seleccionado en una partida
	 bool turno; 
	 //Comprobamos si es el turno del usuario en la partida seleccionada
	 if ((gestor.usuarios.listausuarios[gestor.posusu].nombre == gestor.partidas.partida[gestor.indpart].jugador1 && gestor.partidas.partida[gestor.indpart].estadoJuego.turno == Jugador1) ||
		 (gestor.usuarios.listausuarios[gestor.posusu].nombre == gestor.partidas.partida[gestor.indpart].jugador2 && gestor.partidas.partida[gestor.indpart].estadoJuego.turno == Jugador2))
		 turno = true;
	 else turno = false;

	 return turno;
}

void jugarPartida(tGestor &gestor, int col) { //funcion que dado un movimiento aplica la jugada y actualiza los adversarios si es necesario
	int pos = gestor.usuarios.contador - 1;
	bool encontrado = false;
	bool hora = false;
	string adversario;	
	ostringstream aviso;
		if (gestor.usuarios.listausuarios[gestor.posusu].nombre == gestor.partidas.partida[gestor.indpart].jugador1) //Determinamos si el adversario es el jugador1 o el jugador2
			adversario = gestor.partidas.partida[gestor.indpart].jugador2;
		else adversario = gestor.partidas.partida[gestor.indpart].jugador1;

		buscar(gestor.usuarios, adversario, pos); //Busacmos al adversario en la lista de partidas para determinar su posicion (pos)

		if (aplicarJugada(gestor.partidas.partida[gestor.indpart], col)) { //En caso de que se haya podio aplicar la jugada:
			switch (gestor.partidas.partida[gestor.indpart].estadoJuego.estado) {  //En funcion del estado del juego actualizamos los datos de la partida
			case Ganador: 	gestor.partidas.partida[gestor.indpart].estadoPartida = Terminada;
				aplicarFinPartida(gestor.usuarios.listausuarios[gestor.posusu], gestor.partidas.partida[gestor.indpart].id, Gana); //el usuario de la sesión gana
				aviso << "Ha perdido la partida contra " << gestor.usuarios.listausuarios[gestor.posusu].nombre << " el " << stringFecha(gestor.partidas.partida[gestor.indpart].fechaActu, hora);
				actualizarAvisos(gestor.usuarios.listausuarios[pos], aviso.str());
				aplicarFinPartida(gestor.usuarios.listausuarios[pos], gestor.partidas.partida[gestor.indpart].id, Pierde); // el adversario, en cambio, pierde
				break;
			case Bloqueo:	gestor.partidas.partida[gestor.indpart].estadoPartida = Terminada;
				aplicarFinPartida(gestor.usuarios.listausuarios[gestor.posusu], gestor.partidas.partida[gestor.indpart].id, Empata); //en estado de Bloqueo ambos empatan
				aviso << "Ha empatado la partida contra " << gestor.usuarios.listausuarios[gestor.posusu].nombre << " el " << stringFecha(gestor.partidas.partida[gestor.indpart].fechaActu, hora);
				actualizarAvisos(gestor.usuarios.listausuarios[pos], aviso.str());
				aplicarFinPartida(gestor.usuarios.listausuarios[pos], gestor.partidas.partida[gestor.indpart].id, Empata);
				break;
				
			}
		}
		else cout << '\n' << "No se pudo aplicar la jugada." << '\n';  //Informamos de que no se pue

}

void abandonarPartida(tGestor &gestor) {  //Funcion que aplica la decision del usuario de abandonar una partida
	int pos;
	bool hora = false;
	string adversario;
	ostringstream aviso;
	if (gestor.usuarios.listausuarios[gestor.posusu].nombre == gestor.partidas.partida[gestor.indpart].jugador1) //Determinamos quien es el adversario
		adversario = gestor.partidas.partida[gestor.indpart].jugador2;
	else adversario = gestor.partidas.partida[gestor.indpart].jugador1;

	if (adversario > gestor.usuarios.listausuarios[gestor.posusu].nombre)
		pos = gestor.usuarios.contador;		//para que la posterior búsqueda tenga que dar menos vueltas si el adversario está después del usuario de la sesión
	else pos = gestor.posusu;

		buscar(gestor.usuarios, adversario, pos); //busca la posición del adversario en la lista de usuarios	
		abandonar(gestor.partidas.partida[gestor.indpart]); //abandona la partida, cambiando el estado a terminada
		//cambia los datos de los usuarios según hayan ganado o perdido
		aplicarFinPartida(gestor.usuarios.listausuarios[gestor.posusu], gestor.partidas.partida[gestor.indpart].id, Pierde);
		aplicarFinPartida(gestor.usuarios.listausuarios[pos], gestor.partidas.partida[gestor.indpart].id, Gana);
		gestor.partidas.partida[gestor.indpart].estadoPartida = Terminada;
		aviso << "Ha ganado por abandono una partida contra " << gestor.usuarios.listausuarios[gestor.posusu].nombre << " el " << stringFecha(gestor.partidas.partida[gestor.indpart].fechaActu, hora) << ".";
		actualizarAvisos(gestor.usuarios.listausuarios[pos], aviso.str()); //Deja un aviso (de que ha ganado la partida) en la sesión del adversario
		cout << '\n' << "Ha elegido abandonar la partida" << '\n'; //Informamos de que se ha decidido abandonar la partida
		system("pause");
}