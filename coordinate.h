#ifndef COORDINATE_H
	#define COORDINATE_H
	
	#include <algorithm>
	#include <iostream>
	#include <conio.h>
	#include <string>
	#include <vector>
	using namespace std;

	// dichiarazione (forward declaration) delle classi
	class Map; 
	class Element;
	class Invader;
	class Bullet;
	class Player;

	struct Coordinate { //classe coordinate che serve per stabilire le coordinate del giocatore, degli alieni e dei proiettili all'interno di una matrice
	    int y; //coordinata y
	    int x; //coordinata x
		Coordinate() : x(0), y(0) {} //costruttore di default
	    Coordinate(int y, int x) : y(y), x(x) {} //costruttore a due parametri
	    Coordinate(const Coordinate& other) : y(other.y), x(other.x) {} //costruttore di copia
	    Coordinate& operator=(const Coordinate&);
	    bool operator==(const Coordinate&) const;
	    bool operator!=(const Coordinate&) const;
	    Coordinate operator+(const Coordinate&) const;
	    Coordinate operator-(const Coordinate&) const;
	};

#endif