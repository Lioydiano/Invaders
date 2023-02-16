#include "map.h"
#include "invader.h"
#include "bullet.h"
#include "player.h"


Player* Map::getPlayer() const {
    return player;
}
void Map::setPlayer(Player* player_) {
    player = player_;
}
void Map::addInvader(const Coordinate& position) { //genera un nuovo invasore alle coordinate specificate
    invaders.push_back(new Invader(position));
    map[position.y][position.x] = 'V';
}
void Map::addInvader(Invader* invader) { //aggiunge alla lista degli invasori un invasore già esistente
    invaders.push_back(invader);
    map[invader->getPosition().y][invader->getPosition().x] = invader->getSymbol();
}
void Map::addBullet(const Coordinate& position) { //genera un nuovo proiettile del giocatore alle coordinate specificate
    bullets.push_back(new Bullet(position));
    map[position.y][position.x] = '^';
}
void Map::addBullet(Bullet* bullet) { //aggiunge alla lista dei proiettili un proiettili già esistente
    bullets.push_back(bullet);
    map[bullet->getPosition().y][bullet->getPosition().x] = bullet->getSymbol();
}
void Map::addPlayer(const Coordinate& position) { //genera il giocatore
    player = new Player(position);
}
void Map::addPlayer(Player* player_) { //fa muovere il giocatore
    player = player_;
}
Invader* Map::removeInvader(const Coordinate& position) { //rimuove un invasore dalle coordinate specificate sia dalla lista degli invasori sia dalla mappa ma ti dà la possibilità di riinserirlo
    Invader* invader = nullptr; //un puntatore che non punta a nulla
    for (auto it = invaders.begin(); it != invaders.end(); ++it) {
        if ((*it)->getPosition() == position) {
            invader = *it;
            invaders.erase(it);
            break;
        }
    }
    map[position.y][position.x] = ' ';
    return invader;
}
void Map::removeInvader(Invader* invader) { //rimuove un invasore specifico sia dalla lista degli invasori sia dalla mappa ma ti dà la possibilità di riinserirlo
    invaders.erase(find(invaders.begin(), invaders.end(), invader));
    map[invader->getPosition().y][invader->getPosition().x] = ' ';
}
Bullet* Map::removeBullet(const Coordinate& position) { //rimuove un proiettile dalle coordinate specificate sia dalla lista dei proiettili sia dalla mappa ma ti dà la possibilità di riinserirlo
    Bullet* bullet = nullptr;
    for (auto it = bullets.begin(); it != bullets.end(); ++it) {
        if ((*it)->getPosition() == position) {
            bullet = *it;
            bullets.erase(it);
            break;
        }
    }
    map[position.y][position.x] = ' ';
    return bullet;
}
void Map::removeBullet(Bullet* bullet) { //rimuove un proiettile specifico sia dalla lista dei proiettili sia dalla mappa ma ti dà la possibilità di riinserirlo
    bullets.erase(find(bullets.begin(), bullets.end(), bullet));
    map[bullet->getPosition().y][bullet->getPosition().x] = ' ';
}
void Map::setLine(const Coordinate& position, const vector<char>& line) { //al posto di inizializzare la mappa cella per cella si può fare per riga tramite un vettore di char
    for (int i = 0; i < line.size(); ++i)
        map[position.y][position.x + i] = line[i];
}
void Map::setLine(const Coordinate& position, const string& line) { //al posto di inizializzare la mappa cella per cella si può fare per riga tramite una stringa
    for (int i = 0; i < line.size(); ++i)
        map[position.y][position.x + i] = line[i];
}
void Map::setChar(const Coordinate& position, char c) { //assegna un valore a una cella della mappa tramite una classe di tipo Coordinate
    map[position.y][position.x] = c;
}
void Map::setChar(int y, int x, char c) { //assegna un valore a una cella della mappa tramite le coordinate x e y
    map[y][x] = c;
}
char Map::getChar(const Coordinate& position) const { //ritorna il valore di una cella della mappa
    return map[position.y][position.x];
}
void Map::print() const { //dà in output la mappa (aggiorna il frame)
    cout << "\x1b[2J\x1b[3J\x1b[H"; //ansi escapes codes (il primo pulisce lo schermo, il secondo la memoria del terminale, il terzo porta il cursore (che stampa i caratteri) in alto a sinistra)
    for (int i = 0; i < width + 2; ++i) //bordo della mappa
        cout << '@';
    cout << '\n';
    for (int i = 0; i < height; i++) {
        cout << '@';
        for (int j = 0; j < width; j++)
            cout << map[i][j];
        cout << '@';
        cout << '\n';
    }
    for (int i = 0; i < width + 2; ++i)
        cout << '@';
    cout << flush;
}
Map::~Map() { //distruttore di tipo map viene chiamoto quando lo scope dove è stata dichiarata la mappa muore (quando muore il main -> termina il gioco)
//serve per eliminare dall'heap tutte le variabili new che vengono puntate dai puntatori di map
	for (Invader* invader : invaders) {
        delete invader;
    }
    for (Bullet* bullet : bullets) {
        delete bullet;
    }
    delete player;
}
void Map::moveBullets() { //muove tutti i proiettili di una cella verso l'alto
    for (Bullet* bullet : bullets) {
        bullet->moveUp(*this);
    }
}
void Map::moveInvaders() {//muove tutti gli invasori di una cella verso il basso
    for (Invader* invader : invaders) {
        if (invader->moveDown(*this)) {
            cout << "Game over!\n";
            exit(0);
        }
    }
}