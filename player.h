#ifndef PLAYER_H
	#define PLAYER_H
	#include "element.h"
	
	class Player : public Element { //classe player
	public:
	    Player() : Element() {} //costruttore di default
	    Player(const Coordinate& position_) : Element(position_, "Player", '$') {} //costruttore mediante una classe di tipo Coordinate
	    Player(const Player& other) : Element(other) {} //costruttore di copia
	    ~Player() {} //distruttore 
	
	    void moveLeft(Map& map); //muove il giocatore verso sinistra
	    void moveRight(Map& map); //muove il giocatore verso destra
	    void fire(Map&); // spara un proiettile (Bullet)
	};

#endif