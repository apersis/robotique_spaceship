#include <SDL2/SDL.h>
#include <unistd.h>
#include "function.h"
#include <time.h>

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 640
#define FPS 60
#define NBRASTEROID 10

void drawHeader();
void drawVaisseau();
void drawAsteroid();
void initTabAsteroid();
int num_alea();
void moveAsteroid();
void loop();

//position du carre dessiné dans drawGame()
int x = 160;
int y = 639;
int compteurloop=0;
int compteurasteroid=0;

void init_game(){
    //mettre votre code d'initialisation ici
    initTabAsteroid();
}

void drawGame(){
    /* Ici je dessine mon jeu
     * exemple position x, y modifiés dans KeyPressed() et utilisés pour
     * pouvoir deplacer la figure à chaque boucle de gameLoop()
     */
    clear();
    drawVaisseau();
    drawAsteroid();
    moveAsteroid();
    drawHeader();
    loop();
    actualize();
    usleep(1000000 / FPS); // 60 images par seconde | 1000000 = 1 seconde
}
void KeyPressed(SDL_Keycode touche){
    /** @brief event.key.keysym.sym renvoi la touche appuyé
     *
     */
    switch (touche) {
        // Voir doc SDL_Keycode pour plus de touches https://wiki.libsdl.org/SDL_Keycode
        // ici exemple ou appuyer sur les touches Q | D modifie x (position du carré dans drawGame())
        case SDLK_q:
    drawSquare(x,y,100);
            //touche q appuyé
            if (x>40){
                x=x-5;
            }
            break;
        case SDLK_d:
            //touche d appuyé
            if (x<280){
                x=x+5;
            }
            break;
        case SDLK_ESCAPE:
            freeAndTerminate();
            break;
        default:
            break;
    }
}
void joyButtonPressed(){
}

void gameLoop() {
    int programLaunched = 1;
    while (programLaunched == 1) {
        // Boucle pour garder le programme ouvert
        // lorsque programLaunched est different de 1
        // on sort de la boucle, donc de la fonction
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // boucle pour la gestion d'évenement
            switch (event.type) {
                /** event.type renvoi le type d'evenement qui se passe
                 * (si on appuie sur une touche, clique de souris...)
                 * en fonction du type d'évènement on à alors
                 * différentes information accessibles
                 * voir doc pour plus d'event https://wiki.libsdl.org/SDL_EventType
                 */
                case SDL_QUIT:
                    // quand on clique sur fermer la fénêtre en haut à droite
                    programLaunched = 0;
                    break;
                case SDL_MOUSEBUTTONUP:
                    /* clique de la souris
                     * event.motion.y | event.motion.x pour les positions de la souris
                     */
                    printf("position de la souris x : %d , y : %d\n", event.motion.x, event.motion.y);
                    break;
                case SDL_KEYDOWN:
                    KeyPressed(event.key.keysym.sym);
                    break;
                case SDL_JOYBUTTONDOWN:
                    break;
                default:
                    break;
            }
        }
        /* coder ici pour que le code s'execute après chaque évenement
         * exemple dessiner un carré avec position int x, int y qu'on peut
         * deplacer lorsqu'on appuie sur une touche
         */
        drawGame();
    }
}

int main(){
    /** @description 3 fonctions dans le main qui permettent de créer l'application et la maintenir ouverte :
     *  init(...) : initialiser la SDL/ fenêtre
     *  gameLoop() : boucle de jeu dans laquelle l'application reste ouverte
     *  freeAndTerminate() : quitte le programme proprement
     */
    srand(time(NULL));
    init(WINDOW_WIDTH, WINDOW_HEIGHT);
    init_game();
    gameLoop();
    printf("Fin du programme\n");
    freeAndTerminate();
}

void drawHeader(){
    drawLine(0,70,320,70);
    drawLine(170,0,170,70);
    changeColor(255,0,0);
    drawRect(190,0,130,60);
    changeColor(0,255,0);
    drawRect(200,10,110,40);
}

void drawVaisseau(){
    changeColor(255,255,255);
    drawLine(x-40,y,x+40,y);
    drawLine(x-40,y,x,y-100);
    drawLine(x+40,y,x,y-100);
}

struct Asteroid{
    int pos_x;
    int pos_x2;
    int pos_y;
    int pos_y2;
    int couleur;
    int taille;
    int etat; // 0 = hors de l'ecran et 1 = a l'ecran
};

struct Asteroid tabAsteroid[NBRASTEROID];

void initTabAsteroid(){
    int i;
    for (i=0;i<NBRASTEROID;i++){
        tabAsteroid[i].pos_x=num_alea(280);
        tabAsteroid[i].pos_y=80;
        tabAsteroid[i].pos_y2=120;
        tabAsteroid[i].pos_x2=tabAsteroid[i].pos_x+40;
        tabAsteroid[i].couleur=1;
        tabAsteroid[i].taille=40;
        tabAsteroid[i].etat=0;
    }
}

void drawAsteroid(){
    for (int i=0;i<NBRASTEROID;i++){
        if (tabAsteroid[i].etat==1){
            drawSquare(tabAsteroid[i].pos_x,tabAsteroid[i].pos_y,tabAsteroid[i].taille);
        }
    }
}

void moveAsteroid(){
    for (int i=0;i<NBRASTEROID;i++){
        if (tabAsteroid[i].etat==1){
            tabAsteroid[i].pos_y=tabAsteroid[i].pos_y+1;
            tabAsteroid[i].pos_y2++;
        }
        if (tabAsteroid[i].pos_y>640){
            tabAsteroid[i].etat=0;
            tabAsteroid[i].pos_y=80;
            tabAsteroid[i].pos_y2=120;
            tabAsteroid[i].pos_x=num_alea(280);
            tabAsteroid[i].pos_x2=tabAsteroid[i].pos_x+40;
        }
    }
}

int num_alea(int nmax){
    int nbr_alea = rand() % nmax;
    return nbr_alea;
}

void loop(){
    compteurloop++;
    if (compteurloop%200==1){
        tabAsteroid[compteurasteroid].etat=1;
        compteurasteroid++;
        if (compteurasteroid>9){
            compteurasteroid=0;
        }
    }
}

void collisionBord(){
    
}