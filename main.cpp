#include "led-matrix.h"
#include "retro_matrix.h"
#include "pacman.h"

int main(int argc, char* argv[]) {
    RGBMatrix::Options defaults;
    defaults.rows = 64;
    defaults.cols = 64;
    defaults.chain_length = 1;
    Canvas* canvas = rgb_matrix::CreateMatrixFromFlags(&argc, &argv, &defaults);
    if (canvas == NULL) return 1;

    cout << "Wähle ein Spielmodus:\n";
    cout << "1. Standard-Modus\n";
    cout << "2. Pac-Man\n";
    
    int choice;
    cin >> choice;

    if (choice == 2) {
        PacManGame game;
        char input;
        while (game.running) {
            cin >> input; 
            game.update(input);
            drawGame(canvas, game);
            this_thread::sleep_for(chrono::milliseconds(200));
        }
    } else {
        cout << "Starte Standard-Modus...\n";
    }

    delete canvas;
    return 0;
}
