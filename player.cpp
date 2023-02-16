#include "player.h"
#include "map.h"
#include "bullet.h"


void Player::moveLeft(Map& map) { //muove il giocatore verso sinistra
    map.setChar(position, ' ');
    position.x -= 1;
    map.setChar(position, symbol);
}
void Player::moveRight(Map& map) { //muove il giocatore verso destra
    map.setChar(position, ' ');
    position.x += 1;
    map.setChar(position, symbol);
}
void Player::fire(Map& map) { //fa sparare il giocatore
    map.addBullet(new Bullet(position + Coordinate(-1, 0)));
}