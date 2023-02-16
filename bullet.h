#ifndef BULLET_H
	#define BULLET_H
	#include "element.h"

	class Bullet : public Element { //classe bullet che serve a rappresentare i proiettili
	public:
	    Bullet() : Element() {} //costruttore di default
	    Bullet(const Coordinate& position_) : Element(position_, "Bullet", '^') {} //costruttore tramite coordinate
	    Bullet(const Bullet& other) : Element(other) {} //costruttore di copia
	    ~Bullet() {} //distruttore di bullet
	
	    void moveUp(Map&);
	};

#endif