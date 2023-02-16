#ifndef ELEMENT_H
	#define ELEMENT_H
	#include "coordinate.h"
	
	class Element { //classe element
	protected:
	    Coordinate position; //posizione dell'elemento
	    string type; 
	    char symbol; //il carattere che rappresenta l'elemento nel gioco
	
	public:
	    Element() : position(), type("Invader"), symbol('V') {} //costruttore di default
	    Element(const Coordinate& position_, const string& type_, char symbol_) : position(position_), type(type_), symbol(symbol_) {} //costruttore tramite una classe Coordinate
	    Element(const Element& other) : position(other.position), type(other.type), symbol(other.symbol) {} //costruttore di copia
	    ~Element() {}
		//metodi get/set
	    Coordinate getPosition() const;
	    void setPosition(const Coordinate&);
	    string getType() const;
	    char getSymbol() const;
	};

#endif