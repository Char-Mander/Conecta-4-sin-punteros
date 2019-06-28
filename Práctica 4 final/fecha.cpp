// LAURA JIMENEZ FERNANDEZ & DAVID LOSILLA CADENAS  
// L2-G12

#include "fecha.h"
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

tFecha fechaActual() { //Funcion que nos permite saber cual es la fecha actual
	return time(0);
}

string stringFecha(tFecha fecha, bool hora) { //Funcion que nos permite pasar un tFecha a un formato valido de dia/mes/año con hora opcional
	ostringstream resultado;
	tm ltm;
	localtime_s(&ltm, &fecha);
	resultado << setfill('0') << setw(4) << 1900 + ltm.tm_year << '/'
		<< setw(2) << 1 + ltm.tm_mon << '/' << setw(2) << ltm.tm_mday;
	if (hora) resultado << " (" << setw(2) << ltm.tm_hour << ':' << setw(2)
		<< ltm.tm_min << ':' << setw(2) << ltm.tm_sec << ')';

	return resultado.str();
}