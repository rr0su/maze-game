README - Maze Game Project
Student Name: Roshan gurung
 Student ID: 10310
 Course: BSc (Hons) Cyber Security and Digital Forensics
 Module: Programming in C++
 Assignment Title: Maze Game with OOP, Inheritance, and File I/O
 Submission Date: 21-04-2025

📌 Project Overview
This project implements a C++ Maze Game, where the player navigates through a randomly generated maze. The game incorporates Object-Oriented Programming (OOP) principles such as inheritance and file I/O operations to save and load the game state. The game features:
Randomized Maze Generation: The maze is generated each time a new game starts, with walls, paths, collectibles, and enemies.
Player Movement: The player (P) can move using the W, A, S, and D keys.
Collectibles & Enemies: Collect items (*) to gain points and avoid enemies (X) that move randomly.
Multiple Levels: Each new level introduces increased difficulty with more enemies and obstacles.
File I/O: Save and load the game state using a text file (save.txt).

🧩 Key Features
Save and Load Game State:
Save your current progress with the S key to save.txt.
Load a saved game using the L key.
If the save file is missing or corrupted, the game will handle errors gracefully.
OOP and Inheritance:
The game utilizes a base class (MazeBase) and a derived class (MazeGame) for implementing game logic.
Game Controls:
W: Move Up
A: Move Left
S: Move Down
D: Move Right
S: Save Game
L: Load Game
Q: Quit Game

🖥 How to Run
Prerequisites:
A C++ compiler (like g++ or Visual Studio) is required to compile the code.
Steps to Run:
Compile the Code:
            For MinGW (g++): g++ roshangame.cpp -o roshangame.exe
Run the Game: ./roshangame.exe

🗂 Project Files
roshangame.cpp: The main C++ source code for the maze game.
roshangame.txt: Game state file where progress is saved.
README.odt This documentation file.

🛠 Error Handling
If the save file (roshangame.txt) is corrupted or missing, the game will display an error message and allow you to start a new game.
The program also handles basic input errors and unexpected file issues, ensuring smoother gameplay.


Additional Information
Game Design: The game was designed to be a simple 2D maze game that incorporates basic game mechanics such as player movement, collision detection, collectibles, and enemies. As the player progresses, the difficulty increases with the introduction of new levels and additional enemies.
Game Flow: The game starts at level 1, and as the player collects enough points and reaches the exit, they progress to higher levels. The player can move in four directions (W/A/S/D), and the game ends either when the player reaches the exit, runs out of moves, or is caught by an enemy.
Error Handling: In case of an invalid move or file-related errors (such as when the save file is missing or corrupted), the game will notify the player and prevent the game from crashing.

Acknowledgements
I would like to thank the following:
Professor Aashish Acharya for providing clear guidance and resources throughout the module.
The C++ Community for the wealth of tutorials and documentation that made it easier to implement file I/O and error handling in my game.
Stack Overflow and Cplusplus.com for helping me resolve specific issues with C++ syntax and game logic.


📅 Submission Deadline
Submission Date: 21st April 2025
Submission Method: 
