#include "invader.h"
#include "map.h"

bool Invader::moveDown(Map& map) { //metodo che fa muovere un invader specifico verso il basso
    if (position.y >= 19) { 
        if (position.y == 19) //se arriva in fondo alla mappa hai perso
            map.setChar(position, ' ');
        map.removeInvader(this);
        delete this;
        return true; // ritorna true se l'alieno arriva in fondo alla mappa
    }
    map.setChar(position, ' '); //svuota la cella perché l'alieno si sta muovendo 
    Coordinate destination_ = position + Coordinate(1, 0); //nuova posizione dell'alieno
    char destination = map.getChar(destination_); //prende il carattere che c'è nella coordinata dove vuole arrivare l'alieno
    position.y += 1; //aumenta di 1 la coordinata y
    if (destination == ' ') { //se dove deve arrivare l'alieno è vuoto allora sposta l'alieno
        map.setChar(position, symbol); 
    } else if (destination == '$') { //se dove deve arrivare c'è il giocatore allora hai perso e il giocatore muore (ritorna true)
        map.setChar(position, '@');
        return true; 
    } else if (destination == '^') { //se la destinazione è dove c'è un proiettile allora l'alieno viene distrutto e anche il proiettile
        map.setChar(position, ' '); 
        map.removeInvader(this);
        delete map.removeBullet(position);
        delete this;
    } else if (destination == '#') { //se la destinazione è la barriera allora distrugge un blocco della barriera e l'alieno muore
        map.setChar(position, ' '); 
        map.removeInvader(this);
        delete this;
    }
    return false;
}