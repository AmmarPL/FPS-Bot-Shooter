# FPS Bot Shooter

FPS Bot Shooter is an exciting first-person shooter game where you battle bots in a terrain that is procedurally generated as you move.

## Gameplay

<div align="center">
  <img src="src/Gameplay.gif" width="75%">
</div>

## About the Game
FPS Bot Shooter is made with OpenGL and places you in a first-person view on a green field filled with trees, rocks, and bots. You can navigate the map using the arrow keys and shoot using your mouse. The display shows the number of kills, bots left, and bullets left.

As you move around the map, the terrain is generated in a fixed radius around you, making the map an infinitely large one.

## Requirements and How to Run
To run this game, you will need modern OpenGL (3.3+) and CMake. For detailed steps on how to run OpenGL projects, visit [OpenGL Tutorial](http://www.opengl-tutorial.org/).

### Installation

1. **Clone the repository:**
   ```sh
   git clone https://github.com/AmmarPL/FPS-Bot-Shooter.git
   ```

2. **Navigate to the project directory:**
   ```sh
   cd FPS-Bot-Shooter
   ```

3. **Build the project using CMake:**
   ```sh
   cmake .
   cmake --build .
   ```

4. **Run the game:**
   ```sh
   ./FPSBotShooter
   ```


