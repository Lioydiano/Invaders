#include "bullet.h"
#include "map.h"

void Bullet::moveUp(Map& map) { //muove di una cella verso l'alto un proiettile
	if (position.y <= 0) { //se è arrivato in cima o fuori alla mappa viene eliminato
	    if (position.y == 0) 
	        map.setChar(position, ' ');
	    map.removeBullet(this);
	    delete this;
	    return;
	}
	map.setChar(position, ' '); //la cella dov'era il proiettila diventa vuota
	char destination = map.getChar(position + Coordinate(-1, 0)); //carattere che c'è nella celle dove dovrebbe spostarsi il proiettile
	position.y -= 1; //diminuisce di uno la posizione
	if (destination == ' ') { //se la cella dove deve andare è vuota allora si sposta senza problemi
	    map.setChar(position, symbol);
	} else if (destination == 'V') { //se c'è un alieno sia l'invasore sia il proiettile vengono distrutti
	    map.setChar(position, ' '); 
	    delete map.removeInvader(position);
	    map.removeBullet(this);
	    delete this;
	} else if (destination == '#') { //se colpisce la barriera della mappa il proiettile si distrugge e anche la barriera
	    map.setChar(position, ' '); 
	}
}