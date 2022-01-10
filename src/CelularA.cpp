#include "CelularA.h"


CelularA::CelularA(RenderWindow* Ventana, stack<State*>* Estadus, string automatas, string regla, string pocento, string pos, int mode, bool Calidad) : State(Ventana, Estadus)
{
  this->moviendo = false;
	this->checksprocess = 0;
	this->ird = 0;
	this->re = 0;
	this->f = 0;
	this->Window->clear(); // Limpiando Ventana por si acaso
	//Si no existen los directorios predeterminados crea los mismos directorios para evitar errores
	system("mkdir ReglaTxt");
	system("mkdir ReglaTxt500");
	system("mkdir Imgs");
	system("mkdir Imgs500");
	system("mkdir Datos");
	system("mkdir Datos500");
	//Si ya existen simplemente no los crea
	
	this->celus = stoi(automatas);
	this->reg = stoi(regla);
	//Semilla para el RANDOM RANDOM
	srand(time(NULL));
	//Estableciendo una vista optima
	this->mirar = View(FloatRect(this->celus * 5 - (1980 * this->celus * 5 / 1080), 0, 1980 * this->celus * 10 / 1080, this->celus * 10));

	//estableciendo Bitset dinamico con el numero binario de la regla
	this->Regla = new bitset<8>(stoi(regla));
	cout << endl << this->Regla << endl << stoi(regla) << endl; // checando si se puede imprimir //
	// arreglo de pixeles RGB (x3) con  Opacidad (x4) Calidad de imagen .bpm 
	if (Calidad)
		this->pixeles = new Uint8[this->celus * this->celus * 400];
	else
		this->pixeles = new Uint8[this->celus * this->celus * 4];

	this->qualityxd = Calidad;
	// Matriz dinamica // Estableciendo sus filas
	this->MatrixReal = new bool* [stoi(automatas)];
	// Matriz dinamica // Estableciendo sus columnas o celdas por fila
	for (int i = 0; i < stoi(automatas); i++) {
		this->MatrixReal[i] = new bool[stoi(automatas)];
	}
	// Inicializando matriz en Falso (0)
	for (int i = 0; i < this->celus; i++)
		for (int j = 0; j < this->celus; j++) {

			this->MatrixReal[j][i] = false;

		}
	//Porcentaje De 1 que se desea obtener, en caso de que se haya elejido la opcion ALEATORIO
	if (pocento != "" and mode == 2) {
		this->porcento = stoi(pocento);
		if (this->porcento <= 100 and this->porcento >= 0) {
			for (int i = 0; i < this->porcento * this->celus / 100;) {
				int jr = rand() % this->celus;
				if (this->MatrixReal[jr][0] == false) {
					this->MatrixReal[jr][0] = true;
					i++;
				}
			}
		}
		//// Nombres der archivo ////
		if (this->celus == 500) {
			this->Datus << "Datos500/datosRg" << regla << "-" << automatas << "c" << pocento << "r.gg";
			this->no_regla << "ReglaTxt500/Rg" << regla << "-" << automatas << "c" << pocento << "r.gg";
			this->Imagen << "Imgs500/Rg" << regla << "-" << automatas << "c" << pocento << "r.bmp";
		}
		else {
			this->Datus << "Datos/datosRg" << regla << "-" << automatas << "c" << pocento << "r.gg";
			this->no_regla << "ReglaTxt/Rg" << regla << "-" << automatas << "c" << pocento << "r.gg";
			this->Imagen << "Imgs/Rg" << regla << "-" << automatas << "c" << pocento << "r.bmp";
		}

	} // Cadena de unos que se desean obtener segun la posicion, en caso de que se haya elegido SELECCIONAR
	else if (pos != "" and mode == 3) {
		for (long unsigned int i = 0; i < pos.size() and (int)i < this->celus; i++) {
			if (pos.c_str()[i] == '1') {
				puts("Si se conto 1");
				this->MatrixReal[i][0] = true;
			}
			else if (pos.c_str()[i] == '0') {
				puts("Si se conto 0");
			}
			else {
				cout << "Este no es un 0 :v es: " << pos.c_str()[i] << endl;
			}
		}
		//// Nombres der archivo ////
		if (this->celus == 500) {
			this->Datus << "Datos500/datosRg" << regla << "-" << automatas << "cs.gg";
			this->no_regla << "ReglaTxt500/Rg" << regla << "-" << automatas << "cs.gg";
			this->Imagen << "Imgs500/Rg" << regla << "-" << automatas << "cs.bmp";
		}
		else {
			this->Datus << "Datos/datosRg" << regla << "-" << automatas << "cs.gg";
			this->no_regla << "ReglaTxt/Rg" << regla << "-" << automatas << "cs.gg";
			this->Imagen << "Imgs/Rg" << regla << "-" << automatas << "cs.bmp";
		}
	}
	else {// Modo NORMAL solo hay un 1 en medio de toda la primer fila
		this->MatrixReal[stoi(automatas) / 2][0] = true;
		//// Nombres de archivo ////
		if (this->celus == 500) {
			this->Datus << "Datos500/datosRg" << regla << "-" << automatas << "c.gg";
			this->no_regla << "ReglaTxt500/Rg" << regla << "-" << automatas << "c.gg";
			this->Imagen << "Imgs500/Rg" << regla << "-" << automatas << "c.bmp";
		}
		else {
			this->Datus << "Datos/datosRg" << regla << "-" << automatas << "c.gg";
			this->no_regla << "ReglaTxt/Rg" << regla << "-" << automatas << "c.gg";
			this->Imagen << "Imgs/Rg" << regla << "-" << automatas << "c.bmp";
		}
	}
	// Se guardan las celulas en formato de texto donde . representa las celulas en 0 y los 1's que hay en el automata
	this->DatosWrite.open(this->no_regla.str().c_str());
	// Se guardan los 1's por evolucion que hay en este documento
	this->GraphicsDates.open(this->Datus.str().c_str());
  
}

CelularA::~CelularA()
{
	//Destruyendo todo alv
	this->mirar = View(FloatRect(0, 0, 1920, 1080));
	this->Window->setView(this->mirar);
	delete this->Regla;
	delete this->pixeles;
	for (int i = 0; i < this->celus; i++) {
		delete this->MatrixReal[i];
	}
	delete this->MatrixReal;
}


void CelularA::CheckForQuit()
{
}

void CelularA::EndState()
{
	//Funciones prueba Desactivada
}

void CelularA::rndtlnperFPS()
{
	if (this->qualityxd) {
		if (this->ird < this->celus) {
			for (int repetir = 0; repetir < 10; repetir++) {
				for (int j = 0; j < this->celus; j++) {
					if (this->MatrixReal[j][this->ird]) {
						//Mostrar poco a poco el automata
						if (repetir == 9) {
							this->celulita.setFillColor(Color(255 - (j * 255 / this->celus), 255 - (this->ird * 255 / this->celus), j * 255 / this->celus, 255));
							this->celulita.setSize(Vector2f(10, 10));
							this->celulita.setPosition(j * 10, this->ird * 10);
							this->Window->draw(this->celulita);// Dibujando en ventana
						}
						//Actualizar pixeles para imagen bmp de baja  resolución
						for (int reps = 0; reps < 10; reps++) {
							this->pixeles[this->re] = 255 - (j * 255 / this->celus); //red
							this->pixeles[this->re + 1] = 255 - (this->ird * 255 / this->celus); //green
							this->pixeles[this->re + 2] = j * 255 / this->celus; //blue
							this->pixeles[this->re + 3] = 255; //alpha
							this->re += 4; // recorriendo pixel por pixel de 4 parametros
						}

					}
					else {

						// pixeles en negro alv
						for (int reps = 0; reps < 10; reps++) {
							this->pixeles[this->re] = 0; //r
							this->pixeles[this->re + 1] = 0; //g
							this->pixeles[this->re + 2] = 0; //b
							this->pixeles[this->re + 3] = 255; //a
							this->re += 4;
						}
					}
				}
			}
			this->ird++;
		}
	}
	else {
		if (this->ird < this->celus) {
			for (int j = 0; j < this->celus; j++) {
				if (this->MatrixReal[j][this->ird]) {
					//Mostrar poco a poco el automata
					this->celulita.setFillColor(Color(255 - (j * 255 / this->celus), 255 - (this->ird * 255 / this->celus), j * 255 / this->celus, 255));
					this->celulita.setSize(Vector2f(10, 10));
					this->celulita.setPosition(j * 10, this->ird * 10);
					Window->draw(this->celulita);
					//Actualizar pixeles para imagen bmp de baja  resolución
					this->pixeles[this->re] = 255 - (j * 255 / this->celus); //red
					this->pixeles[this->re + 1] = 255 - (this->ird * 255 / this->celus); //green
					this->pixeles[this->re + 2] = j * 255 / this->celus; //blue
					this->pixeles[this->re + 3] = 255; //alpha
					this->re += 4; // recorriendo pixel por pixel de 4 parametros

				}
				else {

					// pixeles en negro alv
					this->pixeles[this->re] = 0; //r
					this->pixeles[this->re + 1] = 0; //g
					this->pixeles[this->re + 2] = 0; //b
					this->pixeles[this->re + 3] = 255; //a
					this->re += 4;
				}
			}
			this->ird++;
		}
	}
}

void CelularA::checkPosReg()
{	// Toma de deciciones
	for (int i = 1; i < this->celus; i++){
		for (int j = 0; j < this->celus; j++) { // Si esta apuntando al inicio de la fila pregunta por el final
			if (j == 0) {
				if (this->MatrixReal[this->celus - 1][i - 1] == true && this->MatrixReal[j][i - 1] == true && this->MatrixReal[j + 1][i - 1] == true)
				{
					this->MatrixReal[j][i] = this->Regla->test(7);
				}
				else if (this->MatrixReal[this->celus - 1][i - 1] == true && this->MatrixReal[j][i - 1] == true && this->MatrixReal[j + 1][i - 1] == false)
				{
					this->MatrixReal[j][i] = this->Regla->test(6);
				}
				else if (this->MatrixReal[this->celus - 1][i - 1] == true && this->MatrixReal[j][i - 1] == false && this->MatrixReal[j + 1][i - 1] == true)
				{
					this->MatrixReal[j][i] = this->Regla->test(5);
				}
				else if (this->MatrixReal[this->celus - 1][i - 1] == true && this->MatrixReal[j][i - 1] == false && this->MatrixReal[j + 1][i - 1] == false)
				{
					this->MatrixReal[j][i] = this->Regla->test(4);
				}
				else if (this->MatrixReal[this->celus - 1][i - 1] == false && this->MatrixReal[j][i - 1] == true && this->MatrixReal[j + 1][i - 1] == true)
				{
					this->MatrixReal[j][i] = this->Regla->test(3);
				}
				else if (this->MatrixReal[this->celus - 1][i - 1] == false && this->MatrixReal[j][i - 1] == true && this->MatrixReal[j + 1][i - 1] == false)
				{
					this->MatrixReal[j][i] = this->Regla->test(2);
				}
				else if (this->MatrixReal[this->celus - 1][i - 1] == false && this->MatrixReal[j][i - 1] == false && this->MatrixReal[j + 1][i - 1] == true)
				{
					this->MatrixReal[j][i] = this->Regla->test(1);
				}
				else if (this->MatrixReal[this->celus - 1][i - 1] == false && this->MatrixReal[j][i - 1] == false && this->MatrixReal[j + 1][i - 1] == false)
				{
					this->MatrixReal[j][i] = this->Regla->test(0);
				}
			}
			else if (j == this->celus - 1) { // Si esta en el Final de la fila pregunta por el inicio
				if (this->MatrixReal[j - 1][i - 1] == true && this->MatrixReal[j][i - 1] == true && this->MatrixReal[0][i - 1] == true)
				{
					this->MatrixReal[j][i] = this->Regla->test(7);
				}
				else if (this->MatrixReal[j - 1][i - 1] == true && this->MatrixReal[j][i - 1] == true && this->MatrixReal[0][i - 1] == false)
				{
					this->MatrixReal[j][i] = this->Regla->test(6);
				}
				else if (this->MatrixReal[j - 1][i - 1] == true && this->MatrixReal[j][i - 1] == false && this->MatrixReal[0][i - 1] == true)
				{
					this->MatrixReal[j][i] = this->Regla->test(5);
				}
				else if (this->MatrixReal[j - 1][i - 1] == true && this->MatrixReal[j][i - 1] == false && this->MatrixReal[0][i - 1] == false)
				{
					this->MatrixReal[j][i] = this->Regla->test(4);
				}
				else if (this->MatrixReal[j - 1][i - 1] == false && this->MatrixReal[j][i - 1] == true && this->MatrixReal[0][i - 1] == true)
				{
					this->MatrixReal[j][i] = this->Regla->test(3);
				}
				else if (this->MatrixReal[j - 1][i - 1] == false && this->MatrixReal[j][i - 1] == true && this->MatrixReal[0][i - 1] == false)
				{
					this->MatrixReal[j][i] = this->Regla->test(2);
				}
				else if (this->MatrixReal[j - 1][i - 1] == false && this->MatrixReal[j][i - 1] == false && this->MatrixReal[0][i - 1] == true)
				{
					this->MatrixReal[j][i] = this->Regla->test(1);
				}
				else if (this->MatrixReal[j - 1][i - 1] == false && this->MatrixReal[j][i - 1] == false && this->MatrixReal[0][i - 1] == false)
				{
					this->MatrixReal[j][i] = this->Regla->test(0);
				}
			}
			else { // Si esta en cualquier lugar de la fila pregunta por i y j lugar
				if (this->MatrixReal[j - 1][i - 1] == true && this->MatrixReal[j][i - 1] == true && this->MatrixReal[j + 1][i - 1] == true)
				{
					this->MatrixReal[j][i] = this->Regla->test(7);
				}
				else if (this->MatrixReal[j - 1][i - 1] == true && this->MatrixReal[j][i - 1] == true && this->MatrixReal[j + 1][i - 1] == false)
				{
					this->MatrixReal[j][i] = this->Regla->test(6);
				}
				else if (this->MatrixReal[j - 1][i - 1] == true && this->MatrixReal[j][i - 1] == false && this->MatrixReal[j + 1][i - 1] == true)
				{
					this->MatrixReal[j][i] = this->Regla->test(5);
				}
				else if (this->MatrixReal[j - 1][i - 1] == true && this->MatrixReal[j][i - 1] == false && this->MatrixReal[j + 1][i - 1] == false)
				{
					this->MatrixReal[j][i] = this->Regla->test(4);
				}
				else if (this->MatrixReal[j - 1][i - 1] == false && this->MatrixReal[j][i - 1] == true && this->MatrixReal[j + 1][i - 1] == true)
				{
					this->MatrixReal[j][i] = this->Regla->test(3);
				}
				else if (this->MatrixReal[j - 1][i - 1] == false && this->MatrixReal[j][i - 1] == true && this->MatrixReal[j + 1][i - 1] == false)
				{
					this->MatrixReal[j][i] = this->Regla->test(2);
				}
				else if (this->MatrixReal[j - 1][i - 1] == false && this->MatrixReal[j][i - 1] == false && this->MatrixReal[j + 1][i - 1] == true)
				{
					this->MatrixReal[j][i] = this->Regla->test(1);
				}
				else if (this->MatrixReal[j - 1][i - 1] == false && this->MatrixReal[j][i - 1] == false && this->MatrixReal[j + 1][i - 1] == false)
				{
					this->MatrixReal[j][i] = this->Regla->test(0);
				}
			}
		}
	}
	// Guardando Info en un Archivo .gg
	string esta= "";
	int r1s = 0, c1s = 0;
	for (int i = 0; i < this->celus; i++) {
		c1s = i+1;
		for (int j = 0; j < this->celus; j++) {
			if (this->MatrixReal[j][i]) {
				r1s += 1;
				esta += "0";
			}
			else
				esta += ".";
			
		}
		this->GraphicsDates << c1s << " " << r1s << endl ;
		this->DatosWrite << esta << endl;
		esta = "";
		r1s = 0;
	}
	this->DatosWrite.close();
}

void CelularA::savepixel()
{
	///////////// EXPERIMENTOS ABANDONADOS ///////////////////////////////////////////////////////////////////////////////////////////////////
	/*for (int i = 0; i < this->celus; i++)
		for (int j = 0; j < this->celus; j++) {
			if (this->MatrixReal[i][j]) {
				this->celulita.setFillColor(Color( 255 - (j * 255 / this->celus), 255 - (i * 255 / this->celus), j*255/this->celus, 255));
				this->celulita.setSize(Vector2f(10, 10));
				this->celulita.setPosition(i * 10, j * 10);
				
				Window->draw(this->celulita);
			}
			else {

			}
		}*/

	//string Arraybmp[1000000];
	//int a = 0;
	//cv::Mat src1;
	//cv::Mat srcOut;
	//src1 = cv::imread("Supreme.bmp");
	//cv::imshow("base", src1);
	//stringstream nameimg;
	//for (int i = 0; i < this->celus; i++)
	//	for (int j = 0; j < this->celus; j++) {

	//		if (this->MatrixReal[i][j]) {
	//			
	//			for (int f = 0; f < this->celus * this->celus * 4; f += 4) {
	//				this->pixeles[f] = 255 - (j * 255 / this->celus); // obviously, assign the values you need here to form your color
	//				this->pixeles[f + 1] = 255 - (i * 255 / this->celus);
	//				this->pixeles[f + 2] = j * 255 / this->celus;
	//				this->pixeles[f + 3] = 255;
	//			}
	//	
	//			this->AutomataImg.create(10, 10);
	//			this->AutomataImg.update(this->pixeles);
	//			nameimg << "Imgs/Su" << i << j << ".bmp";
	//			this->AutomataImg.copyToImage().saveToFile(nameimg.str());
	//			nameimg.str("");
	//		}
	//	}
	//int f = 0; // Numero de pixeles que se ira recorriendo
	//for (int i = 0; i < this->celus; i++) // recorriendo celulas Por columna
	//	for (int repetir = 0; repetir < 10; repetir++) { // Se repite 10 veces la misma Fila
	//		for (int j = 0; j < this->celus; j++) { // recorriendo celulas por fila

	//			if (this->MatrixReal[j][i]) { //Asignando pixel 1 con color si la posicion tiene un Verdadero (1)
	//				for (int re = f; re < f + 40; re += 4) {
	//					this->pixeles[re] = 255 - (j * 255 / this->celus); //r
	//					this->pixeles[re + 1] = 255 - (i * 255 / this->celus); //g
	//					this->pixeles[re + 2] = j * 255 / this->celus; //b
	//					this->pixeles[re + 3] = 255; //a
	//				}
	//			}
	//			else { // Asignando 0 con color Negro si la posicion de la matriz era Falso (0)
	//				for (int re = f; re < f + 40; re += 4) {
	//					this->pixeles[re] = 0; //r
	//					this->pixeles[re + 1] = 0; //g
	//					this->pixeles[re + 2] = 0; //b
	//					this->pixeles[re + 3] = 255; //a
	//				}
	//			}
	//			f += 40;

	//		}
	//	}
	// Finalizada la asignacion de pixeles se crea una Textura que guardara la imagen generada por la regla y por el numero de celulas en celdas de 10x10 pixeles (max size 16384x16384)
	puts("Guardando imagen LOADING...xd");
	if(this->qualityxd)
		this->AutomataImg.create(this->celus*10, this->celus*10);
	else
		this->AutomataImg.create(this->celus, this->celus);
	puts("Se creo la calidad de la imagen");
	this->AutomataImg.update(this->pixeles);
	if (this->AutomataImg.copyToImage().saveToFile(this->Imagen.str().c_str())) { 
		puts("La imagen del automata se guardo Con exito xd");
	}
	
}

void CelularA::MoveView(Vector2f movimiento){

}

void CelularA::ZoomView(float fact)
{
	this->mirar.zoom(fact); // Facor de zoom con +  y -
}

void CelularA::CursorPosition()
{
  this->CursorusView = this->Window->mapPixelToCoords(Mouse::getPosition(*this->Window));
}

void PyGrafica1(bool* estoy, stringstream* Datos)
{
	char este[100] = "python grafica.py ";
	strcat(este, Datos->str().c_str());
	puts(este);
	system(este);
	*estoy = false;
	puts("Se elimino con exito");
}

// Funcion que actualiza el State Celula
void CelularA::update(const float& Delta)
{

	if (Keyboard::isKeyPressed(Keyboard::Key::G) and !this->gra1s) {
		this->gra1s = true;
		this->grafica1s = new thread(&PyGrafica1, &this->gra1s,&this->Datus);
		cout << "La id hilogra1 es: " << this->grafica1s->get_id() << endl;
	}
	if (this->checksprocess == 0) { // Para ahorrar RAM la asignacion de 0's y 1's se hace 1 sola vez
		this->checkPosReg(); // obteniendo estado cada celula en la matriz
		puts("ya cheque las posiciones 1 vez");
		this->checksprocess = 1;
	}

  while(this->Window->pollEvent(this->keyboard_mouse)){
    
    if (Keyboard::isKeyPressed(Keyboard::Key::Subtract)) {
      this->ZoomView(1.2);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::Add)) {
      this->ZoomView(0.8);
    }

    if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
      this->YaTermine = true;
    }

    switch (this->keyboard_mouse.type) {
      case Event::MouseButtonPressed:
        if(this->keyboard_mouse.mouseButton.button == 0){
          this->moviendo = true;
          std::cout << "MouseButtonPressed" << std::endl;
          this->CursorPosition();
          this->AnteriorPos = this->CursorusView;  
        }
        break;
      case Event::MouseButtonReleased:
        if(this->keyboard_mouse.mouseButton.button == 0){
          this->moviendo = false;
          std::cout << "MouseButtonRelease" << std::endl;
        }
        break;
      case Event::MouseMoved:
        if(this->moviendo) {
          // Nuevo cursor
          this->CursorPosition();
          const Vector2f cursornew = this->CursorusView;
          // Moviendo vista segun la ventana
          this->mirar.setCenter(this->mirar.getCenter() + (this->AnteriorPos - cursornew));
          this->Window->setView(this->mirar);
          // Guardando la nueva posicion de la nueva vista como vieja 
          this->CursorPosition();
          this->AnteriorPos = this->CursorusView;
        } else {
          this->CursorPosition();
				  cout << "X and Y: " << this->CursorusView.x << "\t" << this->CursorusView.y << endl;
        }
      default:
        break;
    }
  }
    
  
	
}
// Funcion que renderisa o muestra en pantalla lo que se ha obtenido
void CelularA::render(RenderTarget* target)
{
	// esta es la vista
	target->setView(this->mirar);

	if (this->checksprocess == 1) { // aqui se implementa el automata que hace todas las mediciones antes de ser mostrado en pantalla y las guarda en una imagen para aumentar el rendimiento de la pc
		this->rndtlnperFPS();
		this->Window->display();
		if (this->ird >= this->celus)
			this->checksprocess = 2;
	}
	else if (this->checksprocess == 2) {
		this->savepixel();
		this->checksprocess = 3;
	}
	else if (this->checksprocess == 3){// pasa a la segunda bandera // Se ejecuta una sola vez para ahorrar Ram y carga en una imagen para mostrarla en pantalla
		if (this->LoadAuto.loadFromFile(this->Imagen.str().c_str())) {
			puts("Background listo y funcionando!!");
			this->imagebg.setSize(Vector2f(this->celus * 10, this->celus * 10));
			this->imagebg.setTexture(&this->LoadAuto);
			this->checksprocess = 125;
			this->isfinishrender = true;
		}
		else {
			cout << "Todavia no se carga la imagen alv :'v" << endl;
		}
	}
	else { // Se muestra en pantalla la imagen generada por la regla y por el numero de celulas
		this->Window->clear();
		target->draw(this->imagebg);
		this->Window->display();
	}
	
}
