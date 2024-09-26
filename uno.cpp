#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <unordered_map>

std::string deckValueInput = "0123456789123456789rrss++"; // Fills coloured part of deck
std::string deckWildInput = "wwwwffff";
std::vector<std::string> deckColourInput = {"blue", "red", "green", "yellow"}; // Used in some logic too

class Card {
public:
    std::string type;
    std::string colour;

    Card(std::string t, std::string c) : type(t), colour(c) {}
};

class Deck {
public:
    std::vector<Card> cards;

    void reset() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 25; ++j) {
                cards.push_back(Card(std::string(1, deckValueInput[j]), deckColourInput[i])); // FILLS THE DECK with COLOURED cards
            }
        }
        for (int i = 0; i < 8; ++i) {
            cards.push_back(Card(std::string(1, deckWildInput[i]), "wild")); // FILLS THE DECK with WILD cards
        }
    }
};

Deck deck;
std::vector<Card> discard;

Card draw() {
    if (deck.cards.empty()) {
        deck.cards = discard;
        discard.clear();
    }
    int index = rand() % deck.cards.size();
    Card card = deck.cards[index];
    deck.cards.erase(deck.cards.begin() + index);
    return card;
}

class Player {
public:
    std::string name;
    int wins;

    Player(std::string playername) : name(playername), wins(0) {}

    virtual bool turncheck(Card discardAttempt, Card lastDiscard) {
        if (discardAttempt.colour == "wild") {
            return true;
        }
        if (discardAttempt.colour == lastDiscard.colour) {
            return true;
        }
        if (discardAttempt.type == lastDiscard.type) {
            return true;
        }
        return false;
    }

    virtual int turn(std::vector<Card>& hand, Card lastDiscard) = 0;

    virtual std::string colourselect(std::vector<Card>& hand, Card lastDiscard) = 0;

    virtual ~Player() = default; // Declare virtual destructor 
};

std::string mode(const std::vector<std::string>& v) {
    std::unordered_map<std::string, int> counts;
    for (const auto& elem : v) {
        counts[elem]++;
    }
    auto maxElem = std::max_element(counts.begin(), counts.end(),
        [](const std::pair<std::string, int>& p1, const std::pair<std::string, int>& p2) {
            return p1.second < p2.second;
        }
    );
    return maxElem->first;
}

void startGame(std::vector<Player*> players) {
    deck.reset();
    discard.clear();
    std::vector<std::vector<Card>> hands(players.size());
    for (int i = 0; i < players.size(); ++i) {
        for (int j = 0; j < 7; ++j) {
            hands[i].push_back(draw());
        }
    }

    Card lastDiscard = draw();

    bool skip = false;
    bool draw2 = false;
    bool draw4 = false;

    // Shuffle order of players
    for (int i = 0; i < rand() % players.size(); ++i) {
        std::rotate(players.begin(), players.begin() + players.size() - 1, players.end());
    }

    // GAME LOOP
    while (true) {
        for (int i = 0; i < players.size(); ++i) {
            std::cout << "PLAYER: " << players[i]->name << std::endl;

            // CHECKING CARD EFFECTS
            if (skip) {
                skip = false;
                continue; // Skip turn
            } else if (draw2) {
                for (int j = 0; j < 2; ++j) {
                    hands[i].push_back(draw()); // Draw 2
                }
                draw2 = false;
                continue; // Skip turn
            } else if (draw4) {
                for (int j = 0; j < 4; ++j) {
                    hands[i].push_back(draw()); // Draw 4
                }
                draw4 = false;
                continue; // Skip turn
            }

            int discardIndex = players[i]->turn(hands[i], lastDiscard);

            if (discardIndex == -1) { // Draw and forfeit turn
                hands[i].push_back(draw());
                std::cout << players[i]->name << " draws! Card count: " << hands[i].size() << std::endl;
                continue;
            }

            discard.push_back(lastDiscard);
            lastDiscard = hands[i][discardIndex]; // Updating the last discard
            hands[i].erase(hands[i].begin() + discardIndex); // Remove discard from hand
            std::cout << players[i]->name << " discards: " << lastDiscard.type << " " << lastDiscard.colour
                      << ". Card count: " << hands[i].size() << std::endl;

            // CHECKING FOR VICTORY
            if (hands[i].empty()) {
                std::cout << "The winner is: " << players[i]->name << std::endl;
                players[i]->wins += 1;
                return;
            }

            // CHECKING CARD NEW EFFECT
            if (lastDiscard.colour == "wild") { // Wild: colour select
                lastDiscard.colour = players[i]->colourselect(hands[i], lastDiscard); // Update colour
                if (lastDiscard.type == "f") { // +4
                    draw4 = true;
                }
            } else if (lastDiscard.type == "r") { // Reverse
                // Reverse around pivot i
                std::vector<Player*> revplayers = players;
                std::reverse(revplayers.begin(), revplayers.end());
                while (revplayers[i]->name != players[i]->name) {
                    std::rotate(revplayers.begin(), revplayers.begin() + revplayers.size() - 1, revplayers.end());
                }
                players = revplayers;
            } else if (lastDiscard.type == "s") { // Skip
                skip = true;
            } else if (lastDiscard.type == "+") { // Draw 2
                draw2 = true;
            }
        }
    }
}
