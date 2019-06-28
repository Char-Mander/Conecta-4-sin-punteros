// LAURA JIMENEZ FERNANDEZ & DAVID LOSILLA CADENAS  
// L2-G12

#ifndef fecha_h //Realizamos un ifndef para evitar que fecha en algun modulo aparezca definida dos veces, ya que en el modulogestor y mainP4 nos encontrariamos con problemas
#define fecha_h
#include <iostream>


typedef time_t tFecha; //Definimos el tipo tFecha

tFecha fechaActual();//Funcion que nos permite saber cual es la fecha actual

std::string stringFecha(tFecha fecha, bool hora); //Funcion que nos permite pasar un tFecha a un formato valido de dia/mes/año con hora opcional

#endif fecha_h