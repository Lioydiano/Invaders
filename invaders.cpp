#include <time.h>
#include <thread>
#include <chrono>
#include <future>
#include "map.h"
#include "invader.h"
// g++ invaders.cpp -o invaders.exe -std=c++17
using namespace std;


int main() {
    srand(time(NULL)); //randomizza il random (altrimenti gli alieni cadono sempre nello stesso punto)
    ios_base::sync_with_stdio(false); //desincronizza l'input e l'output standard, migliorando il refresh
    vector<char> houses(50, '#'); //dichiarazione di un vettore di asterischi (la barriera)
    int houseCount = 50; //dichiarazione del numero di celle della barriera rimaste
    Map map(50, 20); //dichiarazione della mappa di gioco
    map.setLine(Coordinate(18, 0), houses); //setta la posizione della barriera
    Player* player = new Player(Coordinate(19, 25)); //crea un nuovo giocatore al centro della mappa
    map.addPlayer(player); //aggiunge il giocatore alla mappa
    map.setChar(player->getPosition(), '$'); //aggiunge il carattere che rappresenta il giocatore alla mappa
    cout << "\x1b[2J\x1b[3J\x1b[H\x1b[?25l"; //ansi escapes codes (primi tre uguali al precedente ansi escapes codes mentre il quarto nasconde il cursore)

    while (true) { 
        future<int> input = async(launch::async, getch); //crea un future di tipo int alla quale viene assegnato il futuro risultato della funzione getch lanciata in modo asincrono
        while (input.wait_for(chrono::milliseconds(100)) != future_status::ready) { //attende per 100 millisecondi la risposta in input, se non è ancora pronta allora esegue il contenuto del while
            //refresha la mappa aggiornata (alieni mossi verso il basso, proiettili verso l'alto)
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
        //in base all'input dell'utente il programma muove il giocatore, spara o termina la partita
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