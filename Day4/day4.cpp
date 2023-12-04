#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

vector<string> split(string str, char separator)
{
    stringstream strstream(str);
    string segment;
    vector<string> result;

    while (getline(strstream, segment, separator))
    {
        result.push_back(segment);
    }

    return result;
}

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

int points(string card)
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

    if (win_count > 0)
    {
        return pow(2, win_count - 1);
    }

    return 0;
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

    string p2 = "tbd";

    cout << "part 1: "
         << p1 << "\npart 2: "
         << p2;
}