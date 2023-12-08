#include "../auxiliary.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>

using namespace std;

bool contains(vector<string> strs, string searched_str)
{
    for (string str : strs)
    {
        if (str == searched_str)
        {
            return true;
        }
    }

    return false;
}

int count_wins(string card)
{
    card = split(card, ':')[1];
    vector<string> number_sets = split(card, '|');
    vector<string> winning_numbers = split(number_sets[0], ' ');
    vector<string> card_numbers = split(number_sets[1], ' ');

    int win_count = 0;
    for (string number : card_numbers)
    {
        if (isdigit(number[0]) && contains(winning_numbers, number))
        {
            win_count++;
        }
    }

    return win_count;
}

int points(string card)
{
    int win_count = count_wins(card);

    if (win_count > 0)
    {
        return pow(2, win_count - 1);
    }

    return win_count;
}

int count_scratchcards(vector<string> cards)
{
    vector<int> counts(cards.size(), 1); // counts[x] = amount of card[x]

    for (int i = 0; i < cards.size(); i++)
    {
        int win_count = count_wins(cards[i]);
        // For the following win_count cards (or until end of table)
        for (int j = i + 1; j < min(i + 1 + win_count, (int)cards.size()); j++)
        {
            counts[j] += counts[i]; // for each of current card i, win a card j
        }
    }

    return reduce(counts.begin(), counts.end()); // total sum of scratchcards
}

string line;
vector<string> lines;
int main()
{
    ifstream file("input.txt");
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    int p1 = 0;

    for (string card : lines)
    {
        p1 += points(card);
    }

    int p2 = count_scratchcards(lines);

    cout << "part 1: "
         << p1 << "\npart 2: "
         << p2;
}