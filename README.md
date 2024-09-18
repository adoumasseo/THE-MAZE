
# MAZE - The RENEWALLS

![Language](https://img.shields.io/badge/Language-C%20-gray)
![Library](https://img.shields.io/badge/Library-SDL2-blue)
![OS](https://img.shields.io/badge/OS-Ubuntu%2023.04-orange)
![License](https://img.shields.io/badge/License-MIT-green)

## Introduction

**MAZE - The RENEWALLS** is a 3D maze escape game built using ray casting technology to transform a 2D map into a fully navigable 3D world. The game offers 10 randomly generated maps, challenging players to find the exit before time runs out. A compass and a 2D mini-map assist the player, and the exit is marked in green. The gameplay focuses on quick decision-making and navigation within the maze, making it an immersive escape game experience.

Development is ongoing, using C and SDL2 on Ubuntu 23.04. You are going to play whitout texture, but key mechanics like raycasting and player navigation have been implemented.

### Key Features:
- **Randomized Maps**: Every playthrough begins in one of 10 unique maps.
- **Time Challenge**: Players need to escape before the timer runs out.
- **Compass & Map**: Use the compass and 2D map for orientation within the maze.
- **Cross-platform**: Built with SDL2, allowing it to run on various operating systems(As soon a you install necessary library).

## Final Project Blog Article
Read more about the development journey and challenges faced during the creation of **MAZE - The RENEWALLS** in the final project blog post [here](#).

## Author(s)
- **[ADOUMASSE Ortniel](https://www.linkedin.com/in/ortniel-adoumasse/)**

## Installation

### Prerequisites
Before installing the game, ensure the following dependencies are installed on your system:
- SDL2
- SDL2_image
- SDL2_ttf
- SDL2_mixer

For Ubuntu users, run the provided `install.sh` script to automatically install the necessary dependencies:
```sh
$ ./install.sh
```

### Steps
1. Clone the repository:
    ```sh
    $ git clone https://github.com/adoumasseo/THE-MAZE.git
    ```

2. Navigate to the project directory:
    ```sh
    $ cd THE-MAZE
    ```

3. Compile the source code:
    ```sh
    $ gcc -o raycaster ./src/* -lSDL2 -lSDL2_ttf -lSDL2_mixer -lm
    ```

4. Run the game:
    ```sh
    $ ./raycaster
    ```

## Usage

Once the game is launched, use the following controls to navigate:
- **WASD** to move.
- **Left Arrow** to rotate left.
- **Right Arrow** to rotate right.
- **ESC** to pause and quit the game.
- **ESC** to quit the maze  when you reach the exit wall
- The compass and 2D map will help you find the exit in the maze.

## Contributing

Contributions are welcome! Please follow these steps:
1. Fork the project.
2. Create a new branch (`git checkout -b feature/your-feature`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the branch (`git push origin feature/your-feature`).
5. Open a Pull Request.

## Related Projects

If you're interested in similar projects, check out:
- [Wolfenstein 3D](https://github.com/id-Software/wolf3d)
- [Raycasting in Games](https://github.com/raycasting/tutorial)

## License

This project is licensed under the MIT License. See the [LICENSE.md](LICENSE.md) file for details.
