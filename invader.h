#ifndef INVADER_H
	#define INVADER_H
	#include "element.h"
	
	
	class Invader : public Element { //classe invader che eredita da element 
	public:
	    Invader() : Element() {} //costruttore di default
	    Invader(const Coordinate& position_) : Element(position_, "Invader", 'V') {} //costruttore dalle coordinate
	    Invader(const Invader& other) : Element(other) {} //costruttore di copia
	    ~Invader() {} //distruttore di invader
		//vedi implementazione metodo
	    bool moveDown(Map&);
	};

#endif