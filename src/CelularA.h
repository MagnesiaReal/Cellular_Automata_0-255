#pragma once
#include "State.h"
#include <string>
#include <string.h>
#include <bitset>
#include <stdlib.h>
#include <time.h>

#include <fstream>

class CelularA :
	public State
{

private:
	bool gra1s;
	thread* grafica1s;
	/////////// Nombres de Archivo /////////////
	stringstream no_regla; //Numero de la Regla
	stringstream Datus; //Datos // Se guarda la info para posteriromente obtener la varianza y desviacion estandar (unicamente aplica para las 500 celulas)
	stringstream Imagen;
	////////////////////////////////////////////
	RectangleShape celulita;
	ofstream DatosWrite; // ofsstream para escribir datos dentro de un archivo.
	ofstream GraphicsDates; // Numeros de 1 por iteracion
	// Python se encargara de leer esta informacion.
	View mirar;
	//RectangleShape celulita; // Ocupado en Versiones anteriores
	// Lo podemos guardar como imagen //
	Texture AutomataImg;
	int checksprocess, ird, re, f;
	Texture LoadAuto;// carga de Textura
	RectangleShape imagebg;
	////////////////////////////////////
	//Pixel Array  // MOST EFFICIENTLY
	Uint8* pixeles;
	// PosMouseBefore
	Vector2f Fijar;
	bool yaesAnt;
	//Datos para calcular Varianza y Desviacion Estandar
	bool qualityxd;
	bool finishrender;
	int celus;
	int reg;
	int porcento;
	bool** MatrixReal;
	bitset<8>* Regla;
  Event keyboard_mouse;
  bool moviendo;
  Vector2f AnteriorPos;

public:
	CelularA(RenderWindow* Ventana, stack<State*>* Estadus, string automatas, string regla, string pocento = "", string pos = "", int mode = 1, bool Calidad = false);
	~CelularA();
	void CheckForQuit();
	void EndState();
	void rndtlnperFPS();
	void checkPosReg();
	void savepixel();
  void MoveView(Vector2f movimiento);
	void ZoomView(float fact);

	void CursorPosition();
	void update(const float& Delta);
	void render(RenderTarget* target = NULL);
};

