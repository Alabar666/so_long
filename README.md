# so_long

A 2D game project developed for the 42 School, using the MiniLibX library.

## Overview

The `so_long` project is a simple 2D game where the player must navigate through a map, collect items, and reach the exit while avoiding enemies. The game was developed as part of the 42 School curriculum, with the objective of understanding basic game mechanics and graphical rendering using the MiniLibX library.

## Features

- **2D Game Rendering** using MiniLibX
- **Player Movement** across a grid-based map
- **Collectible Items** that must be gathered before exiting
- **Enemies** that the player must avoid
- **Customizable Maps** created using simple text files

## Installation

1. Clone the repository:

    ```sh
    git clone https://github.com/Alabar666/so_long.git
    ```

2. Navigate to the project directory:

    ```sh
    cd so_long
    ```

3. Compile the game:

    ```sh
    make
    ```

4. Run the game with a map file:

    ```sh
    ./so_long maps/sample_map.ber
    ```

## How to Play

- Use the arrow keys to move the character.
- Collect all the items (`C`) on the map.
- Avoid the enemies (`M`) and reach the exit (`E`).

## Example Gameplay

### Stand Animation

![Stand Animation](gifs/stand.mp4)

The character's idle animation when not moving.

### Kill Goblin Animation

![Kill Goblin Animation](gifs/killgoblin.mp4)

An animation showing the action of killing a goblin.

### Lose Animation

![Lose Animation](gifs/lose.mp4)

An animation that plays when the player loses the game.

### Victory Animation

![Victory Animation](gifs/victory.mp4)

An animation that plays when the player wins the game.

## Map Format

Maps are simple `.ber` files that represent the game grid. Each character in the file corresponds to a different element:

- `1` - Wall
- `0` - Empty Space
- `P` - Player Start Position
- `C` - Collectible Item
- `E` - Exit
- `M` - Enemy

## Contributing

Contributions are welcome! Feel free to submit a pull request or open an issue.
