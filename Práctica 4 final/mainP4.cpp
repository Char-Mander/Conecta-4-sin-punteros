// LAURA JIMENEZ FERNANDEZ & DAVID LOSILLA CADENAS  
// L2-G12

#include "Gestor.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>


using namespace std;

void menuRegistro(tGestor &gestor); //Funci�n que controla el desarrollo del men� registro

void mostrarDatosUsu(tGestor &gestor); //Funci�n que muestra por pantalla los datos del usuario

void menuUsuario(tGestor &gestor);  //Funci�n que muestra y controla el men� usuario

void mostrarMenuReg(); //Funci�n que muestra por pantalla el men� registro

void mostrarPartidasEnCurso(tGestor &gestor); //Funci�n que muestra por pantalla las partidas que el usuario tiene en curso

void elegirPartida(tGestor &gestor); //Funci�n que nos permite elegir la partida que deseamos ver

void leerJugada(int &col); //Funci�n que se encarga de leer la jugada

void menuPartida(tGestor &gestor);  //Funci�n que controla el men� de la partida

int main() {
	tGestor gestor;
	string aviso;

	bool ok;	
	ok = arrancar(gestor); //Realizamos el arranque del gestor y comprobamos si se ha realizado correctamente	
	if (ok) {
		menuRegistro(gestor); //Si el gestor se ha iniciado correctamente, accedemos al men� registro
		apagar(gestor); //Apagamos el gestor
	}
	return 0;
}

void menuRegistro(tGestor &gestor) { //Funci�n que controla el desarrollo del men� registro
	int opcion;	
	string nombre, clave;

	do {  //Nos mantendremos en este men� mientras que la opci�n elegida sea distinta de 0 (salir)
		mostrarMenuReg();
		cin >> opcion;
		while (opcion < 0 || opcion > 2) {  //Comprobamos que se est� introduciendo una opci�n posible
			cout << '\n' << "Por favor, introduzca una opcion valida: ";
			cin >> opcion;
		}

		if (opcion != 0) {  //En caso de que la opci�n sea distinta de 0, solicitamos el nombre de usuario y la clave para acceder a una sesi�n, o crear una cuenta nueva
			system("cls");
			cout << '\n' << '\n' << "ACCESO" << endl;
			cout << '\n' << "Nombre de usuario: ";
			cin >> nombre;
			cout << "Clave: ";
			cin >> clave;
		}
		if (opcion == 1 && iniciarSesion(gestor, nombre, clave)) {	//En caso de que la opci�n seleccionada sea '1', procedemos al inicio de sesi�n	
			system("PAUSE");
			system("CLS");
			mostrarDatosUsu(gestor);
			system("PAUSE");
			system("CLS");
			menuUsuario(gestor);
			system("PAUSE");			
		}
		if (opcion == 2 && crearCuenta(gestor, nombre, clave)) { //En caso de que la opci�n sea '2', procedemos a crear una cuenta con el nombre de usuario y clave proporcionada
			cout << '\n' << "Ha creado la cuenta correctamente" << '\n';
			system("pause");
			system("cls");
			mostrarDatosUsu(gestor);
			system("pause");
			system("CLS");
			menuUsuario(gestor);
			system("pause");			
		}			
	}while (opcion != 0);
}

void mostrarDatosUsu(tGestor &gestor) { //Funci�n que muestra por pantalla los datos del usuario
	char borraravisos;

	if (tieneAvisos(gestor, gestor.usuarios.listausuarios[gestor.posusu].avisos)) { //En caso de que tenga avisos, los muestra por pantalla
		cout << '\n' << gestor.usuarios.listausuarios[gestor.posusu].avisos << '\n' << '\n' << "Elija si desea borrar los avisos: [S/N] ";
		cin >> borraravisos;
		while (borraravisos != 'S' && borraravisos != 'N'&& borraravisos!= 's' && borraravisos!= 'n') { 
			cout << '\n' << "Introduzca una opcion valida ";
			cin >> borraravisos;
		}
		borraravisos = toupper(borraravisos);  //Utilizamos toupper() para as� solo tener que comprobar el char de la letra may�scula
		switch (borraravisos) {		//En caso de que lo solicite, el usuario borra los avisos del usuario
		case 'S': limpiarAvisos(gestor);
			break;		
		case 'N': break;
		}
	}
	system("CLS");
	mostrarActividad(gestor); //Mostramos la actividad del usuario
	cout << '\n' << '\n';
}

void menuUsuario(tGestor &gestor) {  //Funci�n que muestra y controla el men� usuario
	int opcion;	

	do {  //Nos mantendremos en este bucle mientras que la opci�n elegida no sea '0' (salir)
		system("cls");
		cout << '\n' << "MENU USUARIO" << endl;  //Mostramos el men� de usuario con las partidas en curso del usuario

		mostrarPartidasEnCurso(gestor);

		cout << '\n' << "1. Ver partida ";
		cout << '\n' << "2. Nueva partida ";
		cout << '\n' << "3. Partidas por actualizacion";
		cout << '\n' << "4. Partidas por turno y fecha";
		cout << '\n' << "0. Salir";
		cout << '\n' << "Elija una opcion: ";
		cin >> opcion;
		while (opcion < 0 || opcion > 4) {
			cout << '\n' << "Por favor, introduzca una opcion valida: ";
			cin >> opcion;
		}

		switch (opcion) {
		case 1: system("CLS");   //En caso de que el usuario eliga la opci�n uno le mostramos las partidas en curso para que eliga cu�l quiere que le mostremos
			mostrarPartidasEnCurso(gestor);
			elegirPartida(gestor);
			break;
		case 2:if (nuevaPartida(gestor))   //En caso de que solicite una nueva partida, buscamos un usuario de su nivel y que est� en espera para crear una nueva
		 cout << '\n' << "La partida se ha creado correctamente " << '\n';                   //partida; en caso de no encontrarlo, se deja al usuario en espera
		system("pause"); break;
		case 3: ordenar_Fecha(gestor); break;  //Con la opci�n '3' ordenamos por fecha
		case 4: ordenar_Fecha(gestor); ordenar_Turno(gestor); break;  //En la opci�n '4' primero ordenamos por fecha la partida y posteriormente la ordenamos por
		            // turno, para asi poder tener esta ordenada por turnos (primero aquellas partidas en las que el usuario de la sesi�n tiene el turno) y dentro de cada grupo, ordenadas por fecha
		case 0: cout << '\n' << "Ha elegido salir" << '\n'; break;   //Informamos al usuario de que a elegido salir
		}		
	} while (opcion != 0);
}

void mostrarMenuReg() {  //Funci�n que muestra por pantalla el men� registro
	system("CLS");
	cout << '\n' << "MENU REGISTRO";
	cout << '\n' << "1.- Acceder a mi cuenta";
	cout << '\n' << "2.- Registrarse";
	cout << '\n' << "0.- Salir" << '\n';

}

void mostrarPartidasEnCurso(tGestor &gestor) { //Funci�n que muestra por pantalla las partidas que el usuario tiene en curso
	ostringstream mostrar;  //Flujo que facilitar� el visionado de las partidas en curso del usuario
	int contador=partidasUsuario(gestor);

	mostrar << "";	
	cout << '\n' << '\n';
	cout << "#   T      " << "JUGADOR 1" << "      " << "JUGADOR 2" << "       " << "FECHA " << '\n';
	cout << setfill('-') << setw(80) << " " << '\n';

	for (int i = 0; i < contador; i++) {  //Realizamos un recorrido por la lista de partidas en curso del usuario a�adiendo estas al flujo, para as� poder mostrarlas con mayor facilidad
		mostrar << i + 1 << " ";
		apuntaPartida(gestor, i);
		mostrar << cabecera(gestor, gestor.indpart);
	}
	cout << mostrar.str(); //Mostramos el contenido del flujo
}

void elegirPartida(tGestor &gestor) { //Funci�n que nos permite elegir la partida que deseamos ver
	int ind;
	bool encontrado = false;
	int contador = partidasUsuario(gestor); //Actualizamos el contador al n�mero de partidas en curso que tiene el usuario

	cout << '\n' << "Seleccione partida (0 para salir): ";  //Solicitamos la partida
	cin >> ind;
	cout << '\n' << '\n';

	while (ind > contador || ind < 0) {  //Comprobamos que el n�mero de partida introducida es v�lida
		cout << '\n' << "Introduzca un numero valido: ";
		cin >> ind;
	}
	if(ind != 0) {  //En caso de que la opci�n no sea '0' (salir), procedemos a mostrar la partida y acceder al men� de la partida 
		ind--;
		apuntaPartida(gestor, ind);		
		system("cls");
		mostrarPartida(gestor);
		menuPartida(gestor);		
	}
	else cout << '\n' << "Ha seleccionado salir. " << '\n';
}

void leerJugada(int &col) {  //Funci�n que se encarga de leer la jugada
	cout << '\n' << "Por favor, introduzca el numero de columna en la que quiere colocar la ficha: ";
	cin >> col;
	while (col > COLS || col < 0) {  //Comprobamos que la columna es v�lida; en caso contrario, pedimos que introduzca una que s� sea v�lida
		cout << '\n' << "Introduzca una columna valida:";
		cin >> col;
	}
	col--;
}

void menuPartida(tGestor &gestor) {  //Funci�n que controla el men� de la partida
	int opcion = 1;
	int col = 0;
	bool finpart = false;

	while (opcion != 0 && !finpart) {
		if (gestor.partidas.partida[gestor.indpart].estadoPartida == EnCurso) { //Mientras que la partida se encuentre en curso, mostraremos las opciones del men�
			cout << '\n' << "1. Jugar ";
			cout << '\n' << "2. Abandonar ";
			cout << '\n' << "0. Salir ";
			cout << '\n' << " Elija una opcion: ";
			cin >> opcion;
			
			while (opcion < 0 || opcion>2) { //Comprobamos que la opci�n escogida sea v�lida
				cout << "Elija una opcion valida: ";
				cin >> opcion;
			}
		}
		else {	//Si la partida termina, salimos del men�		
			system("PAUSE");
			finpart = true;
		}
		

		switch (opcion) {
		case 1: if (esSuTurno(gestor) && gestor.partidas.partida[gestor.indpart].estadoPartida != Terminada) { 
				leerJugada(col);              //En caso de que el usuario desee jugar, comprobamos si es su turno; en caso afirmativo, le permitimos jugar
				jugarPartida(gestor, col);
				system("cls");
				mostrarPartida(gestor);
			}
				else if (!esSuTurno(gestor)) { //Si no es su turno, le informamos de que debe esperar
					system("cls");
					cout << '\n' << "No puedes poner ficha, no es tu turno." << '\n' << '\n';
					mostrarPartida(gestor);
				}				
			break;
		case 2: 
			if (gestor.partidas.partida[gestor.indpart].estadoPartida != Terminada) { //Permitimos al usuario abandonar la partida cuando esta est� en curso
				abandonarPartida(gestor);
				finpart = true;
			}			
		case 0: cout << '\n' << "Ha elegido salir" << '\n'; break; //Informamos de que el usuario ha decidido salir
		}
	}
}