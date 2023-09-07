# FROSTBITE x CELESTE PROJECT

**Authors:** Bryce Grahn, Sudheer Gowan
**Institution:** School of Electrical & Information Engineering, University of the Witwatersrand, Johannesburg, South Africa
**Date:** October 2022

## Installation
- clone the repo
- navigate to executables folder
- Run Frostbit.exe

## Abstract
The purpose of this project is to design and implement a modified version of the Frostbite Atari game from 1983. It has been modified to the form of another video game named Celeste from 2018 [1]. This game has been programmed in C++ and uses SFML to display the game. This project has successfully implemented single and multiplayer versions of Frostbite Bailey, ice blocks, enemies, building an igloo, and a scoring system from the original Atari game. It also successfully deals with collisions between all objects, contains a splash-screen and tutorial screen with instructions, as well as end game and pause screens. Project outcomes have been fulfilled, and all basic functionality, four minor features, and both major features have been implemented. Test cases cover collisions, movement, death, importing of resources, etc. The game has been built using the 3 design layers which have been critically evaluated in this report.

![image](https://github.com/bcgrahn/celeste/assets/99645139/9f0e4658-1a4e-4e82-a7cb-2bbefec56136)
![image](https://github.com/bcgrahn/celeste/assets/99645139/3534f31e-8203-4289-9a04-ba9c938464a5)


## 1. INTRODUCTION
Frostbite was developed in 1983, and this project is an updated version of the original game created. Though keeping true to the original physics, the project is now a keyboard-driven game. It has been programmed in C++ and makes use of different structures in SFML to display the game. This project bridges the gap between old Atari-based games and current platform video games by presenting itself in the form of Celeste [2] from 2018. It successfully implemented the players, enemies, ice blocks - which are shown as clouds, building an igloo – which is shown as a cabin, as well as successfully dealing with collisions between all objects.

## 2. DESIGN
### 2.1. Model of the problem domain
The objective of this project was to design and create a keyboard-driven game based on the Atari game Frostbite. In this game, the user controls the player called Bailey who should jump on rows of ice-blocks floating in an ice lake without touching the water in between the blocks. Only one jump is permitted each time to an adjacent row. Each jump which Bailey completes successfully on a row would add a block onto his igloo structure – which is his safe house. The game is won when all the blocks to this safe house are added, and Bailey can then enter the structure. The game is lost when Frostbite Bailey comes into contact with the water between the ice blocks, falls off the ice blocks, or collides with any water hazard such as snow geese, killer clams, or crabs.

## 3. CODE STRUCTURE
![image](https://github.com/bcgrahn/celeste/assets/99645139/a43d7847-021d-4e5e-8730-04ade414296c)

## 4. CONCLUSION
The design has met all the necessary requirements for basic functionality, has both major features and there are three minor features, all of which have been specified in the brief and above. The players can move left and right, jump and collide with the cloud and enemy objects. A castle can also be built when the players jump on the cloud rows. The players can die when they collide with enemy objects, if the temperature runs out or if they collide with the bounds of the screen






