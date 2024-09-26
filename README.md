# UNO-BOTS

## Problem Statement

The goal of this project was to create virtual players (bots) to compete against each other in a game of UNO. The primary objective was to identify the most effective strategies to win the game by breaking down specific gameplay elements. In real-life party games, aspects such as pacing, mind games, and biases contribute to a player's experience, but these factors do not translate well into AI behavior designed purely to win. Therefore, the challenge was to develop bots that could play UNO against each other and determine which strategy leads to the highest win rate without the influence of human elements.

Simulating games between bots was chosen as the method to derive objective results quickly and efficiently, allowing us to explore the strategies and move sequences that consistently lead to victory.

## Approach

Our approach centered around implementing a **greedy algorithm** to ensure consistency in the bots' behavior. This enabled us to test and compare different strategies by having the bots follow predetermined heuristics. By focusing on certain strategies, we could analyze which playstyle was more effective in securing wins.

We chose **C++** as the programming language to develop the project because it was the most familiar to our team and suitable for creating an efficient simulation environment.

## Software Description

The software is divided into two main C++ files:

1. **uno.cpp**: This file contains the core mechanics of the UNO game. It creates all the UNO cards, sets up the player structure (including bots), and enforces the rules of the game.
2. **behavior.cpp**: This file defines the different bots and the strategies they use. Each bot is named after a group member:
   - **Connor Bot**: Plays randomly, making any legal move without a specific strategy.
   - **Nicholas Bot**: Follows an aggressive strategy, often playing wild cards and frequently changing the color.
   - **Nayeli Bot**: Adopts a safe strategy, avoiding color changes and saving wild cards for last.
   - **Alex Bot**: A balanced strategy between aggressive and safe playstyles. Alex bot changes color through number matching but, like Nayeli, saves wild cards for last.

## How to Run

1. Clone this repository.
   ```bash
   git clone https://github.com/nayeli-umana/UNO-BOTS
   ```
2. Navigate to the project directory.
   ```bash
   cd UNO-BOTS
   ```
3. Compile the project using a C++ compiler.
   ```bash
   g++ -std=c++11 behavior.cpp -o behavior
   ```
4. Run the compiled file.
   ```bash
   ./behavior
   ```

## Upon execution, the program will prompt you to enter:

1. The number of players
2. The specific bots to be included in the game
3. The number of game repetitions (Note: higher repetitions may slow down performance)

## Evaluation Metrics

The effectiveness of the different AI strategies was evaluated by simulating thousands of games. The win rates of each bot were recorded and analyzed to determine which strategy performed the best. The Connor Bot, which plays randomly, served as a baseline to measure whether the developed strategies were more effective than chance.

- **Nayeli Bot** and **Alex Bot** performed comparably well, indicating that safe and balanced strategies are the most effective.
- **Nicholas Bot's** aggressive strategy was less effective.
- **Connor Bot's** random strategy performed the worst, confirming that strategic play significantly increases a bot's chances of winning.

## Team Members:

- Alex Ha
- Nayeli Umana
- Nicholas Haga
- Connor Bither
