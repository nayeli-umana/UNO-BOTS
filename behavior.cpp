////////// UPDATED CODE

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include <string>
#include <limits>

#include "uno.cpp"

using namespace std;

class Connor : public Player
{
public:
    Connor() : Player("Connor") {}

    int turn(std::vector<Card> &hand, Card lastDiscard) override
    {
        while (true)
        {
            int discardAttempt = rand() % (hand.size() + 1);
            for (int i = 0; i < static_cast<int>(hand.size()); ++i)
            {
                if (hand[i].colour == lastDiscard.colour || hand[i].type == lastDiscard.type)
                {
                    return i;
                }
            }
            for (int i = 0; i < static_cast<int>(hand.size()); ++i)
            {
                if (hand[i].colour == lastDiscard.colour || hand[i].type == lastDiscard.type)
                {
                    return i;
                }
            }
            return -1;

            if (turncheck(hand[discardAttempt], lastDiscard))
            {
                return discardAttempt;
            }
        }
    }

    std::string colourselect(std::vector<Card> &hand, Card lastDiscard) override
    {
        return deckColourInput[rand() % 4];
    }
};

class Nayeli : public Player
{
public:
    Nayeli() : Player("Nayeli") {}

    int turn(std::vector<Card> &hand, Card lastDiscard) override
    {
        for (int i = 0; i < static_cast<int>(hand.size()); ++i)
        {
            if (hand[i].colour == lastDiscard.colour && std::isdigit(hand[i].type[0]))
            {
                return i;
            }
        }
        for (int i = 0; i < static_cast<int>(hand.size()); ++i)
        {
            if (hand[i].type == lastDiscard.type && std::isdigit(hand[i].type[0]))
            {
                return i;
            }
        }
        for (int i = 0; i < static_cast<int>(hand.size()); ++i)
        {
            if (hand[i].colour == lastDiscard.colour || hand[i].type == lastDiscard.type)
            {
                return i;
            }
        }
        for (int i = 0; i < static_cast<int>(hand.size()); ++i)
        {
            if (hand[i].colour == "wild")
            {
                return i;
            }
        }
        return -1; // Draw
    }

    std::string colourselect(std::vector<Card> &hand, Card lastDiscard) override
    {
        std::vector<std::string> listForConvenience;
        for (const auto &card : hand)
        {
            if (card.colour == "wild")
            {
                continue;
            }
            listForConvenience.push_back(card.colour);
        }
        if (listForConvenience.empty())
        {
            return deckColourInput[rand() % 4];
        }
        return mode(listForConvenience);
    }

    std::string mode(const std::vector<std::string> &v)
    {
        std::unordered_map<std::string, int> counts;
        for (const auto &elem : v)
        {
            counts[elem]++;
        }
        auto maxElem = std::max_element(counts.begin(), counts.end(),
                                        [](const std::pair<std::string, int> &p1, const std::pair<std::string, int> &p2)
                                        {
                                            return p1.second < p2.second;
                                        });
        return maxElem->first;
    }
};

class Nicholas : public Player
{
public:
    Nicholas() : Player("Nicholas") {}

    int turn(std::vector<Card> &hand, Card lastDiscard) override
    {
        for (int i = 0; i < static_cast<int>(hand.size()); ++i)
        {
            if (hand[i].type == lastDiscard.type && hand[i].colour != lastDiscard.colour && std::isdigit(hand[i].type[0]))
            {
                return i;
            }
        }
        for (int i = 0; i < static_cast<int>(hand.size()); ++i)
        {
            if (hand[i].type == lastDiscard.type && hand[i].colour != lastDiscard.colour)
            {
                return i;
            }
        }
        for (int i = 0; i < static_cast<int>(hand.size()); ++i)
        {
            if (hand[i].colour == "wild")
            {
                return i;
            }
        }
        for (int i = 0; i < static_cast<int>(hand.size()); ++i)
        {
            if (hand[i].type == lastDiscard.type && std::isdigit(hand[i].type[0]))
            {
                return i;
            }
        }
        for (int i = 0; i < static_cast<int>(hand.size()); ++i)
        {
            if (hand[i].colour == lastDiscard.colour)
            {
                return i;
            }
        }
        return -1; // Draw
    }

    std::string colourselect(std::vector<Card> &hand, Card lastDiscard) override
    {
        std::vector<std::string> listForConvenience;
        for (const auto &card : hand)
        {
            if (card.colour == "wild" || card.colour == lastDiscard.colour)
            {
                continue;
            }
            listForConvenience.push_back(card.colour);
        }
        if (listForConvenience.empty())
        {
            return deckColourInput[rand() % 4];
        }
        return mode(listForConvenience);
    }

    std::string mode(const std::vector<std::string> &v)
    {
        std::unordered_map<std::string, int> counts;
        for (const auto &elem : v)
        {
            counts[elem]++;
        }
        auto maxElem = std::max_element(counts.begin(), counts.end(),
                                        [](const std::pair<std::string, int> &p1, const std::pair<std::string, int> &p2)
                                        {
                                            return p1.second < p2.second;
                                        });
        return maxElem->first;
    }
};

class Alex : public Player
{
public:
    Alex() : Player("Alex") {}

    int turn(std::vector<Card> &hand, Card lastDiscard) override
    {
        for (int i = 0; i < static_cast<int>(hand.size()); ++i)
        {
            if (hand[i].type == lastDiscard.type && std::isdigit(hand[i].type[0]))
            {
                return i;
            }
        }
        for (int i = 0; i < static_cast<int>(hand.size()); ++i)
        {
            if (hand[i].colour == lastDiscard.colour && std::isdigit(hand[i].type[0]))
            {
                return i;
            }
        }
        for (int i = 0; i < static_cast<int>(hand.size()); ++i)
        {
            if (hand[i].colour == lastDiscard.colour && std::isdigit(hand[i].type[0]))
            {
                return i;
            }
        }
        for (int i = 0; i < static_cast<int>(hand.size()); ++i)
        {
            if (hand[i].colour == lastDiscard.colour || hand[i].type == lastDiscard.type)
            {
                return i;
            }
        }
        for (int i = 0; i < static_cast<int>(hand.size()); ++i)
        {
            if (hand[i].colour == "wild")
            {
                return i;
            }
        }
        return -1; // Draw
    }

    std::string colourselect(std::vector<Card> &hand, Card lastDiscard) override
    {
        std::vector<std::string> listForConvenience;
        for (const auto &card : hand)
        {
            if (card.colour == "wild")
            {
                continue;
            }
            listForConvenience.push_back(card.colour);
        }
        if (listForConvenience.empty())
        {
            return deckColourInput[rand() % 4];
        }
        return mode(listForConvenience);
    }

    std::string mode(const std::vector<std::string> &v)
    {
        std::unordered_map<std::string, int> counts;
        for (const auto &elem : v)
        {
            counts[elem]++;
        }
        auto maxElem = std::max_element(counts.begin(), counts.end(),
                                        [](const std::pair<std::string, int> &p1, const std::pair<std::string, int> &p2)
                                        {
                                            return p1.second < p2.second;
                                        });
        return maxElem->first;
    }
};

// Make a list of players
int main()
{
    srand(static_cast<unsigned>(time(0)));

    std::vector<Player *> players;
    int playerCount;
    std::cout << "How many players?\n";
    std::cin >> playerCount;
    for (int i = 0; i < playerCount; i++)
    {
        std::cout << "Select 0 for Connor, 1 for Nayeli, 2 for Nicholas, 3 for Alex\n";
        int playerSelect;
        std::cin >> playerSelect;
        if (playerSelect == 0)
        {
            players.push_back(new Connor);
        }
        else if (playerSelect == 1)
        {
            players.push_back(new Nayeli);
        }
        else if (playerSelect == 2)
        {
            players.push_back(new Nicholas);
        }
        else if (playerSelect == 3)
        {
            players.push_back(new Alex);
        }
    }

    int gameNumber;
    std::cout << "How many games? \n";
    std::cin >> gameNumber;

    for (int i = 0; i < gameNumber; ++i)
    { // Play n games
        startGame(players);
    }

    for (const auto &player : players)
    { // Print win stats
        std::cout << player->name << " wins: " << player->wins << std::endl;
    }

    // Clean up allocated memory
    for (const auto &player : players)
    {
        delete player;
    }

    return 0;
}
