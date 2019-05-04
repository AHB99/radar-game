# Radar
A 2D Game where only flashes of a radar reveal the player and enemy positions. Developed with C++ and SDL2.

## Game Overview
In *Radar*, the player controls their character via arrow-keys to collect as many coins as they can. At the same time, they must dodge the enemies that travel across the board.

However, the whole game-screen is obscured by a blue radar, that flashes off periodically. Hence, the player is faced with the challenge of not being able to see the screen most of the time. In order to survive, the player must familiarize themself with the rhythm of the radar, the enemies, and their very own character.

### Key Mechanics
#### The Radar's Behaviour
A deep blue surface is applied to the game-screen, and during a radar flash, this surface fades out of opacity, and back again. 
As time progresses, the frequency of the flashes decreases, challenging the player further. However, collecting coins not only scores points, but also increases the frequency of the radar as a reward.
The code is designed to ensure the radar frequency will not reach unplayable levels, in either direction.

#### Random Game Generation
Every round is unique as all game elements are randomly spawned upon loading the game. Enemies traverse different paths, move in different directions, and collecting the coin causes it to jump randomly across the board.
The code is designed to ensure the random spawning will not cause unplayable or glitched game rounds.


#### Enemy Behaviour
Once spawned, enemies traverse the game-board along fixed paths. As time progresses, the speed of the enemies gradually increases, raising the game's difficulty. Unlike the radar's frequency, collecting coins does not reduce this.
Furthermore, coins are deliberately programmed to randomly spawn only on the same paths as the enemies, forcing the player to have to risk crossing an enemy's path.


## Language and Libraries
* C++11
* [SDL2](https://www.libsdl.org/download-2.0.php) VC++ Development Library (version 2.0.8 x86 used)
* [SDL2_image Extension Library](https://www.libsdl.org/projects/SDL_image/) VC++ Development Library (version 2.0.3 x86 used)
* [SDL2_ttf TrueTypeFont Extension Library](https://www.libsdl.org/projects/SDL_ttf/) VC++ Development Library (version 2.0.15 x86 used)

## Installation
Clone the repository to your desired location.

```
git clone https://github.com/AHB99/radar-game
```
Download the above SDL2 libraries.

Include the lib and include directories with compilation. 

Link against:
```
SDL2.lib
SDL2main.lib
SDL2_image.lib
SDL2_ttf.lib
```

When running, ensure all .dll files are in the **same** directory as the .exe file after compilation.

## Class Structure
Below is an overview of the class structure used to implement *Radar*.

* Game.h: The overall game functionality. Loads and runs the various mechanisms.
* GameObject.h: Abstract parent of game elements.
  * Player.h
  * Enemy.h
  * Coin.h
* RTexture.h: To abstract the SDL2 boilerplate for graphics.
* Radar.h: The flashing radar. Handles its flashing cycle.
* EnemyBelt.h: Coordinates the spawning and motion of enemies and coins.


## Other Resources
* [Cantarell TrueType Font](https://www.fontsquirrel.com/fonts/cantarell).
* [Source Code Pro Font](https://www.fontsquirrel.com/fonts/source-code-pro).
* All sprites designed by me.

## Further Improvements
Additional features to be implemented include **Obstacles** generated throughout the game-board that will block the player, causing the added difficulty for the user to know where they're moving when they can't see the board. A challenge is posed by this as the Obstacles must not be spawned on enemy pathways.
Also, a **3-hearts Live System** will be developed to allow greater leeway for the player.

