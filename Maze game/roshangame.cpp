#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <conio.h>  // For _getch() on Windows
using namespace std;

// Symbols
const char WALL = 219;
const char PATH = ' ';
const char PLAYER_SYMBOL = 'P';
const char EXIT = 'E';
const char COLLECTIBLE = '*';
const char ENEMY_SYMBOL = 'X';

const int MAZE_SIZE = 15;
const int MAX_MOVES = 50;

// Base class for any entity on the maze
class Entity {
public:
    int x, y;
    Entity(int x, int y) : x(x), y(y) {}
    virtual char getSymbol() const = 0;
};

class Player : public Entity {
public:
    Player(int x, int y) : Entity(x, y) {}
    char getSymbol() const override { return PLAYER_SYMBOL; }
};

class Enemy : public Entity {
public:
    Enemy(int x, int y) : Entity(x, y) {}
    char getSymbol() const override { return ENEMY_SYMBOL; }
};

class MazeGame {
private:
    char maze[MAZE_SIZE][MAZE_SIZE];
    Player* player;
    vector<Enemy> enemies;
    int exitX, exitY;
    int score = 0;
    int level = 1;
    int moves = 0;

public:
    MazeGame() {
        srand(static_cast<unsigned int>(time(0)));
        generateMaze();
    }

    ~MazeGame() {
        delete player;
    }

    void clearScreen() {
        static bool firstTime = true;
        if (firstTime) {
            firstTime = false;
        } else {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
        }
    }

    void generateMaze() {
        for (int i = 0; i < MAZE_SIZE; ++i) {
            for (int j = 0; j < MAZE_SIZE; ++j) {
                if (i == 0 || j == 0 || i == MAZE_SIZE - 1 || j == MAZE_SIZE - 1 || rand() % 6 == 0)
                    maze[i][j] = WALL;
                else
                    maze[i][j] = PATH;
            }
        }

        player = new Player(1, 1);
        maze[player->x][player->y] = player->getSymbol();

        exitX = MAZE_SIZE - 2;
        exitY = MAZE_SIZE - 2;
        maze[exitX][exitY] = EXIT;

        // Place collectibles
        for (int i = 0; i < 5; ++i) {
            int x, y;
            do {
                x = rand() % MAZE_SIZE;
                y = rand() % MAZE_SIZE;
            } while (maze[x][y] != PATH);
            maze[x][y] = COLLECTIBLE;
        }

        // Place enemies
        enemies.clear();
        for (int i = 0; i < level + 2; ++i) {
            int x, y;
            do {
                x = rand() % MAZE_SIZE;
                y = rand() % MAZE_SIZE;
            } while (maze[x][y] != PATH);
            enemies.emplace_back(x, y);
            maze[x][y] = enemies.back().getSymbol();
        }
    }

    void drawMaze() {
        clearScreen();
        cout << "+";
        for (int i = 0; i < MAZE_SIZE; ++i) cout << "-";
        cout << "+" << endl;

        for (int i = 0; i < MAZE_SIZE; ++i) {
            cout << "|";
            for (int j = 0; j < MAZE_SIZE; ++j) {
                cout << maze[i][j];
            }
            cout << "|" << endl;
        }

        cout << "+";
        for (int i = 0; i < MAZE_SIZE; ++i) cout << "-";
        cout << "+" << endl;

        cout << "Score: " << score << " | Level: " << level << " | Moves Left: " << (MAX_MOVES - moves) << endl;
        cout << "Controls: W/A/S/D to move, Q to quit, L to load" << endl;
    }

    void movePlayer(char input) {
        int dx = 0, dy = 0;
        if (input == 'w' || input == 'W') dx = -1;
        else if (input == 's' || input == 'S') dx = 1;
        else if (input == 'a' || input == 'A') dy = -1;
        else if (input == 'd' || input == 'D') dy = 1;
        else return;

        int newX = player->x + dx;
        int newY = player->y + dy;

        if (newX < 0 || newY < 0 || newX >= MAZE_SIZE || newY >= MAZE_SIZE) return;
        if (maze[newX][newY] == WALL) return;

        if (maze[newX][newY] == COLLECTIBLE) score++;
        else if (maze[newX][newY] == ENEMY_SYMBOL) {
            cout << endl << "GAME OVER: You were caught by an enemy!" << endl;
            exit(0);
        } else if (maze[newX][newY] == EXIT) {
            level++;
            moves = 0;
            delete player;
            generateMaze();
            return;
        }

        maze[player->x][player->y] = PATH;
        player->x = newX;
        player->y = newY;
        maze[player->x][player->y] = player->getSymbol();

        moves++;
        if (moves >= MAX_MOVES) {
            cout << endl << "GAME OVER: You ran out of moves!" << endl;
            exit(0);
        }
    }

    void moveEnemies() {
        for (auto& enemy : enemies) {
            int dx = 0, dy = 0;
            switch (rand() % 4) {
                case 0: dx = -1; break;
                case 1: dx = 1; break;
                case 2: dy = -1; break;
                case 3: dy = 1; break;
            }

            int nx = enemy.x + dx;
            int ny = enemy.y + dy;

            if (nx < 0 || ny < 0 || nx >= MAZE_SIZE || ny >= MAZE_SIZE) continue;
            if (maze[nx][ny] == PATH || maze[nx][ny] == PLAYER_SYMBOL) {
                if (maze[nx][ny] == PLAYER_SYMBOL) {
                    cout << endl << "GAME OVER: You were caught by an enemy!" << endl;
                    exit(0);
                }

                maze[enemy.x][enemy.y] = PATH;
                enemy.x = nx;
                enemy.y = ny;
                maze[nx][ny] = enemy.getSymbol();
            }
        }
    }

    void saveMazeToFile(const string& filename) {
        ofstream file(filename);
        if (!file) {
            cerr << "Error: Could not open file for saving." << endl;
            return;
        }

        for (int i = 0; i < MAZE_SIZE; ++i) {
            for (int j = 0; j < MAZE_SIZE; ++j)
                file << maze[i][j];
            file << endl;
        }

        file << player->x << ' ' << player->y << endl;
        file << exitX << ' ' << exitY << endl;
        file << score << ' ' << level << ' ' << moves << endl;

        file << enemies.size() << endl;
        for (auto& e : enemies)
            file << e.x << ' ' << e.y << endl;

        file.close();
        cout << "Game saved successfully!" << endl;
    }

    void loadMazeFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error: Could not open file for loading." << endl;
            return;
        }

        for (int i = 0; i < MAZE_SIZE; ++i) {
            for (int j = 0; j < MAZE_SIZE; ++j)
                file >> noskipws >> maze[i][j];
            file.ignore();
        }

        int px, py;
        file >> px >> py;
        player = new Player(px, py);

        file >> exitX >> exitY;
        file >> score >> level >> moves;

        int numEnemies;
        file >> numEnemies;
        enemies.clear();
        for (int i = 0; i < numEnemies; ++i) {
            int ex, ey;
            file >> ex >> ey;
            enemies.emplace_back(ex, ey);
        }

        file.close();
        cout << "Game loaded successfully!" << endl;
    }

    void play() {
        while (true) {
            drawMaze();
            char input = _getch();
            if (input == 'q' || input == 'Q') {
                cout << "Exiting game. Save progress? (y/n): ";
                char ch = _getch();
                if (ch == 'y' || ch == 'Y')
                    saveMazeToFile("save.txt");
                break;
            } else if (input == 'l' || input == 'L') {
                loadMazeFromFile("save.txt");
                continue;
            }

            movePlayer(input);
            moveEnemies();
        }
    }
};

int main() {
    MazeGame game;
    game.play();
    return 0;
}
