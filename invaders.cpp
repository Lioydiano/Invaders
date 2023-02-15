#include <algorithm>
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <time.h>
#include <thread>
#include <chrono>
#include <future>
// g++ invaders.cpp -o invaders.exe -std=c++17


class Coordinate {
public:
    Coordinate() : x(0), y(0) {}
    Coordinate(int y, int x) : y(y), x(x) {}
    Coordinate(const Coordinate& other) : y(other.y), x(other.x) {}
    Coordinate& operator=(const Coordinate& other) {
        x = other.x;
        y = other.y;
        return *this;
    }
    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Coordinate& other) const {
        return !(*this == other);
    }
    Coordinate operator+(const Coordinate& other) const {
        return Coordinate(y + other.y, x + other.x);
    }
    Coordinate operator-(const Coordinate& other) const {
        return Coordinate(y - other.y, x - other.x);
    }
    int y;
    int x;
};

class Map; // Forward declaration
class Element;
class Invader;
class Bullet;
class Player;


class Map {
    int width;
    int height;
    Player* player;
    std::vector<Invader*> invaders;
    std::vector<Bullet*> bullets;
    std::vector<std::vector<char>> map;

public:
    Map() : map(10, std::vector<char>(10, ' ')), invaders(), player(nullptr) {}
    Map(const Map& other) : map(other.map), invaders(other.invaders), player(other.player) {}
    Map(int width_, int height_) : width(width_), height(height_), map(height_, std::vector<char>(width_, ' ')), invaders(), player(nullptr) {}
    ~Map();

    Player* getPlayer() const;
    void setPlayer(Player*);
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
    void setLine(const Coordinate&, const std::vector<char>&);
    void setLine(const Coordinate&, const std::string&);
    void setChar(const Coordinate&, char);
    void setChar(int, int, char);
    char getChar(const Coordinate& position) const;
    void print() const;

    void moveInvaders();
    void moveBullets();
};


class Element {
protected:
    Coordinate position;
    std::string type;
    char symbol;

public:
    Element() : position(), type("Invader"), symbol('V') {}
    Element(const Coordinate& position_, const std::string& type_, char symbol_) : position(position_), type(type_), symbol(symbol_) {}
    Element(const Element& other) : position(other.position), type(other.type), symbol(other.symbol) {}
    ~Element() {}

    Coordinate getPosition() const {
        return position;
    }
    void setPosition(const Coordinate& position_) {
        position = position_;
    }
    std::string getType() const {
        return type;
    }
    char getSymbol() const {
        return symbol;
    }
};


class Invader : public Element {
public:
    Invader() : Element() {}
    Invader(const Coordinate& position_) : Element(position_, "Invader", 'V') {}
    Invader(const Invader& other) : Element(other) {}
    ~Invader() {}

    bool moveDown(Map&);
};


class Bullet : public Element {
public:
    Bullet() : Element() {}
    Bullet(const Coordinate& position_) : Element(position_, "Bullet", '^') {}
    Bullet(const Bullet& other) : Element(other) {}
    ~Bullet() {}

    void moveUp(Map& map) {
        if (position.y <= 0) {
            if (position.y == 0)
                map.setChar(position, ' ');
            map.removeBullet(this);
            delete this;
            return;
        }
        map.setChar(position, ' ');
        char destination = map.getChar(position + Coordinate(-1, 0));
        position.y -= 1;
        if (destination == ' ') {
            map.setChar(position, symbol);
        } else if (destination == 'V') {
            map.setChar(position, ' '); // Invader is destroyed
            delete map.removeInvader(position);
            map.removeBullet(this);
            delete this;
        } else if (destination == '#') {
            map.setChar(position, ' '); // House is destroyed
        }
    }
};


class Player : public Element {
public:
    Player() : Element() {}
    Player(const Coordinate& position_) : Element(position_, "Player", '$') {}
    Player(const Player& other) : Element(other) {}
    ~Player() {}

    void moveLeft(Map& map) {
        map.setChar(position, ' ');
        position.x -= 1;
        map.setChar(position, symbol);
    }
    void moveRight(Map& map) {
        map.setChar(position, ' ');
        position.x += 1;
        map.setChar(position, symbol);
    }
    void fire(Map& map) {
        map.addBullet(new Bullet(position + Coordinate(-1, 0)));
    }
};

Player* Map::getPlayer() const {
    return player;
}
void Map::setPlayer(Player* player_) {
    player = player_;
}
void Map::addInvader(const Coordinate& position) {
    invaders.push_back(new Invader(position));
    map[position.y][position.x] = 'V';
}
void Map::addInvader(Invader* invader) {
    invaders.push_back(invader);
    map[invader->getPosition().y][invader->getPosition().x] = invader->getSymbol();
}
void Map::addBullet(const Coordinate& position) {
    bullets.push_back(new Bullet(position));
    map[position.y][position.x] = '^';
}
void Map::addBullet(Bullet* bullet) {
    bullets.push_back(bullet);
    map[bullet->getPosition().y][bullet->getPosition().x] = bullet->getSymbol();
}
void Map::addPlayer(const Coordinate& position) {
    player = new Player(position);
}
void Map::addPlayer(Player* player_) {
    player = player_;
}
Invader* Map::removeInvader(const Coordinate& position) {
    Invader* invader = nullptr;
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
void Map::removeInvader(Invader* invader) {
    invaders.erase(std::find(invaders.begin(), invaders.end(), invader));
    map[invader->getPosition().y][invader->getPosition().x] = ' ';
}
Bullet* Map::removeBullet(const Coordinate& position) {
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
void Map::removeBullet(Bullet* bullet) {
    bullets.erase(std::find(bullets.begin(), bullets.end(), bullet));
    map[bullet->getPosition().y][bullet->getPosition().x] = ' ';
}
void Map::setLine(const Coordinate& position, const std::vector<char>& line) {
    for (int i = 0; i < line.size(); ++i)
        map[position.y][position.x + i] = line[i];
}
void Map::setLine(const Coordinate& position, const std::string& line) {
    for (int i = 0; i < line.size(); ++i)
        map[position.y][position.x + i] = line[i];
}
void Map::setChar(const Coordinate& position, char c) {
    map[position.y][position.x] = c;
}
void Map::setChar(int y, int x, char c) {
    map[y][x] = c;
}
char Map::getChar(const Coordinate& position) const {
    return map[position.y][position.x];
}
void Map::print() const {
    std::cout << "\x1b[2J\x1b[3J\x1b[H";
    for (int i = 0; i < width + 2; ++i)
        std::cout << '@';
    std::cout << '\n';
    for (int i = 0; i < height; i++) {
        std::cout << '@';
        for (int j = 0; j < width; j++)
            std::cout << map[i][j];
        std::cout << '@';
        std::cout << '\n';
    }
    for (int i = 0; i < width + 2; ++i)
        std::cout << '@';
    std::cout << std::flush;
}
bool Invader::moveDown(Map& map) {
    if (position.y >= 49) {
        if (position.y == 49)
            map.setChar(position, ' ');
        map.removeInvader(this);
        delete this;
        return true; // Reached the bottom, game over
    }
    map.setChar(position, ' ');
    Coordinate destination_ = position + Coordinate(1, 0);
    char destination = map.getChar(destination_);
    position.y += 1;
    if (destination == ' ') {
        map.setChar(position, symbol);
    } else if (destination == '$') {
        map.setChar(position, '@');
        return true; // Player is dead
    } else if (destination == '^') {
        map.setChar(position, ' '); // Bullet is destroyed
        map.removeInvader(this);
        delete map.removeBullet(position);
        delete this;
    } else if (destination == '#') {
        map.setChar(position, ' '); // House is destroyed
        map.removeInvader(this);
        delete this;
    }
    return false;
}
Map::~Map() {
    for (Invader* invader : invaders) {
        delete invader;
    }
    for (Bullet* bullet : bullets) {
        delete bullet;
    }
    delete player;
}
void Map::moveBullets() { // Move all bullets up
    for (Bullet* bullet : bullets) {
        bullet->moveUp(*this);
    }
}
void Map::moveInvaders() { // Move all invaders down
    for (Invader* invader : invaders) {
        if (invader->moveDown(*this)) {
            std::cout << "Game over!\n";
            exit(0);
        }
    }
}


int main() {
    srand(time(NULL));
    std::ios_base::sync_with_stdio(false);
    std::vector<char> houses(50, '#');
    int houseCount = 50;
    Map map(50, 20);
    map.setLine(Coordinate(18, 0), houses);
    Player* player = new Player(Coordinate(19, 25));
    map.addPlayer(player);
    map.setChar(player->getPosition(), '$');
    map.addBullet(new Bullet(Coordinate(5, 25)));
    std::cout << "\x1b[2J\x1b[3J\x1b[H\x1b[?25l";

    while (true) {
        std::future<int> input = std::async(std::launch::async, getch);
        while (input.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready) {
            map.moveInvaders();
            map.moveBullets();
            if (rand() % 15 == 0) {
                int x = rand() % 50;
                if (map.getChar(Coordinate(0, x)) == ' ') {
                    map.addInvader(new Invader(Coordinate(0, x)));
                }
            }
            map.print();
        }
        char c = input.get();
        if (c == 'a')
            player->moveLeft(map);
        else if (c == 'd')
            player->moveRight(map);
        else if (c == 'f')
            player->fire(map);
        else if (c == 'q')
            exit(0);
    }
}
