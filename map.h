#ifndef MAP_H
	#define MAP_H
	#include "player.h"
	
	class Map { //classe mappa che rappresenta il campo di gioco ma anche con altre funzioni
	    int width; //lunghezza
	    int height; //altezza
	    Player* player; //puntatore di tipo Player
	    vector<Invader*> invaders; //vettore di puntatori di tipo Invader
	    vector<Bullet*> bullets; //vettore di puntatori di tipo Bullet
	    vector<vector<char>> map; //vettore di vettore di char (matrice di char -> il campo di gioco)
	
	public:
	    Map() : map(10, vector<char>(10, ' ')), invaders(), player(nullptr) {} //costruttore di default
	    Map(const Map& other) : map(other.map), invaders(other.invaders), player(other.player) {}
	    Map(int width_, int height_) : width(width_), height(height_), map(height_, vector<char>(width_, ' ')), invaders(), player(nullptr) {} //costruttore a due parametri
	    ~Map(); //distruttore
		//metodi get/set di player
	    Player* getPlayer() const; 
	    void setPlayer(Player*);
	    //vedi inizializzazione dei metodi
	    void addInvader(const Coordinate&);
	    void addInvader(Invader*);
	    void addBullet(const Coordinate&);
	    void addBullet(Bullet*);
	    void addPlayer(const Coordinate&);
	    void addPlayer(Player*);
	    Invader* removeInvader(const Coordinate&);
	    void removeInvader(Invader*);
	    Bullet* removeBullet(const Coordinate&);
	    void removeBullet(Bullet*);
	    void setLine(const Coordinate&, const vector<char>&);
	    void setLine(const Coordinate&, const string&);
	    void setChar(const Coordinate&, char);
	    void setChar(int, int, char);
	    char getChar(const Coordinate& position) const;
	    void print() const;
	
	    void moveInvaders();
	    void moveBullets();
	};

#endif