#include "Inicio.h"


void Inicio::initBottonus()
{
	this->Botones["Iniciar"] = new Bottonus(50, 640, 170, 50, &this->font, "Iniciar :)", Color(50, 50, 50, 255), Color(90, 90, 90, 255), Color(200, 200, 200, 255));
	this->Botones["Salir"] = new Bottonus(240, 640, 250, 50, &this->font, "Abandonar :(", Color(50, 50, 50, 255), Color(90, 90, 90, 255), Color(200, 200, 200, 255));
	this->Botones["Normal"] = new Bottonus(50, 170+350, 150, 50, &this->font, "Normal", Color(50, 20, 20, 255), Color(90, 60, 60, 255), Color(200, 170, 170, 255));
	this->Botones["Random"] = new Bottonus(230, 170 + 350, 200, 50, &this->font, "Aleatorio", Color(50, 20, 20, 255), Color(90, 60, 60, 255), Color(200, 170, 170, 255));
	this->Botones["Select"] = new Bottonus(460, 170 + 350, 170, 50, &this->font, "Elejir", Color(50, 20, 20, 255), Color(90, 60, 60, 255), Color(200, 170, 170, 255));
	this->Botones["Calidad"] = new Bottonus(460, 45 + 350, 170, 50, &this->font, "HD", Color(35, 40, 50, 255), Color(75, 80, 90, 255), Color(185, 190, 200, 255));
}

void Inicio::initTextBox()
{
	this->Textos["Celulas"] = new TextBox(50, 50 + 350, &this->font, Color(50, 50, 20, 255), Color(90, 90, 60, 255), Color(200, 200, 170, 255), "No. Celulas:");
	this->Textos["Regla"] = new TextBox(50, 110 + 340, &this->font, Color(50, 50, 20, 255), Color(90, 90, 60, 255), Color(200, 200, 170, 255), "No. Regla:");
	this->Textos["Rand"] = new TextBox(50, 240 + 340, &this->font, Color(50, 50, 20, 255), Color(90, 90, 60, 255), Color(200, 200, 170, 255), "Porcentaje:");
	// TEXTO ESPECIAL // FUNCIONES ESPECIALES PARA EL
	this->Textos["Select"] = new TextBox(50, 240 + 340, &this->font, Color(50, 50, 20, 255), Color(90, 90, 60, 255), Color(200, 200, 170, 255), "Cadena:", 8);
}

void Inicio::initWindow()
{

	VideoMode VentanaRes(1920, 1080);
	string titulo = "AutomataCelularxd By Garrido Rojas Marco Antonio";
	unsigned framerate_limit = 120;
	Uint32 Stylus = Style::Default;
	bool Vsync = false;
	
	//------------------------------Dimensiones-NameGame-windowsmode-
	this->Ventana = new RenderWindow(VentanaRes, titulo, Stylus);
	this->Ventana->setFramerateLimit(framerate_limit);
	this->Ventana->setVerticalSyncEnabled(Vsync);
}

Inicio::Inicio()
{
	
	this->acaso = 0;
	this->mode = 1;
	this->initWindow();
	//Iniciando Bienvenida//
	this->font.loadFromFile("Gameplay.ttf");
	this->cualytiy.setFont(font);
	this->cualytiy.setString(" = OFF");
	this->cualytiy.setPosition(Vector2f(630, 50 + 350));
	this->Indicaciones.setFont(font);
	this->Indicaciones.setString("Cellular Automata by Garrido Rojas Marco \nInstrucciones de uso:");
	this->Indicaciones.setLineSpacing(1.3);
	this->Indicaciones.setPosition(Vector2f(50, 20));
	this->Indicaciones2.setFont(font);
	this->Indicaciones2.setLineSpacing(1.5);
	this->Indicaciones2.setLetterSpacing(1.2);
	this->Indicaciones2.setCharacterSize(16);
	this->Indicaciones2.setString("@ Esc === regresar\n@ G === Ver Grafica 1's\n@ +,- === +Zoom, -Zoom\n@ LeftClickMouse === mover Automata Actual\nLos botones de Var. y Desv. son para las 88 Reglas\n@ HD = 10 pixel/cell    @ Low=1 pixel/cell\n A Low Quiality tiene una capasidad de 16384 celulas\n A High Quality tiene una capasidad de 1638 celulas");
	this->Indicaciones2.setPosition(Vector2f(50, 130));
	///////////////////////
	this->initBottonus();
	this->initTextBox();
}

Inicio::~Inicio()
{
}

void Inicio::EndApp() {
	puts("Simulacro Terminado xddd END APP");
	this->Ventana->close();
}

void Inicio::updateDelta()
{
	this->Delta = this->deltaclock.restart().asSeconds();
}

void PyGrafica1(bool* estoy)
{
	system("python grafica.py");
	*estoy = false;
	puts("Se elimino con exito");
}

void Inicio::UpdateSFMLEvents()
{
	while (this->Ventana->pollEvent(this->Eventus)) {
		// Si se cierra la ventana se termina el programa
		if (this->Eventus.type == Event::Closed) {
			this->Ventana->close();
		}
		else if (this->Eventus.type == Event::TextEntered)
		{
			if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
				for (auto& it : this->Textos) {
					it.second->setClearText();
				}
			}
			else if (this->Eventus.text.unicode > 47 and this->Eventus.text.unicode < 58) {
				for (auto& it : this->Textos) {
					it.second->setTexto(this->Eventus.text.unicode);
					cout << this->Eventus.text.unicode << endl;
				}
			}
		}
		else if (!this->states.empty()) { // SFML Events para segundo State}
			/*if (Keyboard::isKeyPressed(Keyboard::Key::G) and !this->gra1s) {
				this->gra1s = true;
				this->grafica1s = new thread(&PyGrafica1, &this->gra1s);
				cout << "La id hilogra1 es: " << this->grafica1s->get_id() << endl;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::V) and !this->gra2s) {
				this->gra2s = true;
				this->grafica2s = new thread(&PyGrafica2, &this->gra2s);
				cout << "La id hilogra2 es: " << this->grafica2s->get_id() << endl;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::D) and !this->gra3s) {
				this->gra3s = true;
				this->grafica3s = new thread(&PyGrafica3, &this->gra3s);
				cout << "La id hilogra3 es: " << this->grafica3s->get_id() << endl;
			}*/
			//Hasta que termine el renderizado se podra mover //
			if (this->states.top()->isnotrender()) {
				if (Keyboard::isKeyPressed(Keyboard::Key::Subtract)) {
					this->states.top()->ZoomView(1.2);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Key::Add)) {
					this->states.top()->ZoomView(0.8);
				}
				if (Mouse::isButtonPressed(Mouse::Button::Left)) {
					this->states.top()->MoveView(this->CursorusView);
				}
				else
					this->states.top()->CursorPosition();
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
				delete this->states.top();
				this->states.pop();
			}
		}
	}
}


void Inicio::UpdateButonus()
{
	for (auto& it : this->Botones) {
		it.second->update(CursorusView);
	}
	if (this->Botones["Calidad"]->esPresionado()) {
		if (this->HD) {
			this->HD = false;
			this->cualytiy.setString(" = OFF");
		}
		else {
			this->HD = true;
			this->cualytiy.setString(" = ON");
		}
	}
	else if (this->Botones["Normal"]->esPresionado()) {
		this->mode = 1;
	}
	else if (this->Botones["Random"]->esPresionado()) {
		this->mode = 2;
	}
	else if (this->Botones["Select"]->esPresionado()) {
		this->mode = 3;
	}
	else if (this->Botones["Iniciar"]->esPresionado()) {
		this->Ventana->clear();
		this->Ventana->display();
		this->states.push(new CelularA(this->Ventana, &this->states, this->Textos["Celulas"]->getStringText(), this->Textos["Regla"]->getStringText(), this->Textos["Rand"]->getStringText(), this->Textos["Select"]->getStringText(), this->mode, this->HD));
		cout << (string)this->Textos["Regla"]->getStringText();
		cout << (string)this->Textos["Celulas"]->getStringText();
	}
	else if (this->Botones["Salir"]->esPresionado()) {
		this->Ventana->close();
	}
	
}

void Inicio::UpdateTextBox()
{
	for (auto& it : this->Textos) {
		if (it.first != "Rand" && it.first != "Select" && this->mode == 1) {
			it.second->update(CursorusView);
		}
		else if (it.first != "Select" && this->mode == 2) {
			it.second->update(CursorusView);
		}
		else if (it.first != "Rand" && this->mode == 3) {
			it.second->update(CursorusView);
		}
	}
}

void Inicio::LockCursorPos()
{
	CursorusView = this->Ventana->mapPixelToCoords(Mouse::getPosition(*this->Ventana));
}
// Como es un programa compuesto unicamente de 2 States y no de N states se Geneneran 2 IF's; uno para el state principal y otro para el segundo State
void Inicio::update()
{
	
	if (this->states.empty()) { // Funciones para el State principal
	  this->LockCursorPos();// Posicion del Mouse
	  this->UpdateSFMLEvents(); // Se actualiza para todo State Eventos de cualquier tipo programado	
		this->UpdateButonus(); // Se acutalizan los botones, se verifica si hubo evento o no
		this->UpdateTextBox(); // Se actualizan las cajas de texto , se verifica si hubo evento o no
	}
	if (!this->states.empty()) { // Update Segundo State
		this->states.top()->update(this->Delta); // update delta o mas bien Fps (1/Delta)
		if (this->states.top()->getQuit()) {// Si estado ya no exite regresa al menu principal
			this->states.top()->EndState(); // borra estado  de la fas de la tierra	
			delete this->states.top();// deletea el estado dinamico
			this->states.pop(); // resetea la pila o mas bien elimina elemento de la pila
		}
	}
}

void Inicio::renderTextBox()
{
	for (auto& it : this->Textos) {
		if (it.first != "Rand" && it.first != "Select" && this->mode == 1) {
			it.second->render(this->Ventana);
		}
		else if (it.first != "Select" && this->mode == 2) {
			it.second->render(this->Ventana);
		}
		else if (it.first != "Rand" && this->mode == 3) {
			it.second->render(this->Ventana);
		}
	}
}

void Inicio::renderBotonus()
{
	for (auto& it : this->Botones) {
		it.second->render(this->Ventana);
	}
}

void Inicio::render()
{
	
	if (this->states.empty()) { // Funciones para State principal
		this->Ventana->clear(); // Se limpia para todo State
		// renderizando los botones
		this->Ventana->draw(this->Indicaciones);
		this->Ventana->draw(this->Indicaciones2);
		this->Ventana->draw(this->cualytiy);
		this->renderBotonus();
		this->renderTextBox();
		this->Ventana->display();// Funcion Display
	}
	if (!this->states.empty()) { // Funciones Para State secundario
		this->states.top()->render(this->Ventana);
	}
	 
}

void Inicio::run() // Loop de la aplicacion , se ejecuta infinitamente.
{
	while (this->Ventana->isOpen()) {
		this->updateDelta();
		this->update();
		this->render();
	}
}
