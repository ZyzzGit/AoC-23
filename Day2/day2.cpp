#include "../auxiliary.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> all_colors = {"red", "green", "blue"};
vector<int> rgb_bag = {12, 13, 14}; // 12 red, 13 green, 14 blue cubes in the bag

vector<vector<int>> str_to_game(string gamestr)
{
    vector<vector<int>> game;
    int rgb_start_pos = gamestr.find(':') + 1;

    vector<string> rgblist = split(gamestr.substr(rgb_start_pos), ';');

    for (string rgb : rgblist)
    {
        vector<int> rgb_count = {0, 0, 0};
        for (string color : split(rgb, ','))
        {
            vector<string> num_color = split(color, ' '); // num_color = {"", <number>, <color>}
            int color_pos = find(all_colors.begin(), all_colors.end(), num_color[2]) - all_colors.begin();
            rgb_count[color_pos] = stoi(num_color[1]);
        }
        game.push_back(rgb_count);
    }

    return game;
}

// Returns the maximum amount of each color observed in the game
vector<int> max_rgb(vector<vector<int>> game)
{
    vector<int> max_rgb = {0, 0, 0};

    for (int color = 0; color < all_colors.size(); color++)
    {
        for (int rgb = 0; rgb < game.size(); rgb++)
        {
            max_rgb[color] = max(max_rgb[color], game[rgb][color]);
        }
    }

    return max_rgb;
}

bool is_possible(vector<int> max_rgb)
{
    // For each color r,g,b; check if the max amount shown in game is not bigger than specified in rgb_bag
    for (int color = 0; color < all_colors.size(); color++)
    {
        if (max_rgb[color] > rgb_bag[color])
        {
            return false;
        }
    }

    return true;
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
    int p2 = 0;
    for (int i; i < lines.size(); i++)
    {
        vector<int> rgb = max_rgb(str_to_game(lines[i]));
        if (is_possible(rgb))
        {
            p1 += i + 1; // since the game IDs starts at 1
        }
        int power = rgb[0] * rgb[1] * rgb[2];
        p2 += power;
    }

    cout << "part 1: "
         << p1 << "\npart 2: "
         << p2;
}