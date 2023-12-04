#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

vector<string> pad(vector<string> strs, char c)
{
    for (int i = 0; i < strs.size(); i++)
    {
        strs[i] = (c + strs[i] + c);
    }
    int width = strs[0].size();
    strs.insert(strs.begin(), string(width, c));
    strs.push_back(string(width, c));
    return strs;
}

// Returns the part numbers adjacent to symbol at padded engine_schematic[posy][posx]
vector<int> get_adjacent_part_numbers(int posy, int posx, vector<string> engine_schematic)
{
    vector<int> adjacent = {};
    for (int i = posy - 1; i <= posy + 1; i++)
    {
        for (int j = posx - 1; j <= posx + 1; j++)
        {
            if (isdigit(engine_schematic[i][j]))
            {
                int number_start_pos = j;
                while (isdigit(engine_schematic[i][number_start_pos - 1]))
                {
                    number_start_pos--;
                }
                while (isdigit(engine_schematic[i][j])) // move j to first non-digit item (number_end_pos + 1)
                {
                    j++;
                }
                adjacent.push_back(stoi(engine_schematic[i].substr(number_start_pos, j - number_start_pos)));
            }
        }
    }
    return adjacent;
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

    // Start with padding the schematic to avoid going out of bounds when checking for neighbours
    // => indexes will go from 1 to size-2 when traversing rows or columns
    vector<string> engine_schematic = pad(lines, '.');

    int p1 = 0; // part number sum
    int p2 = 0; // gear ratio sum
    for (int i = 1; i < engine_schematic.size() - 1; i++)
    {
        string row = engine_schematic[i];
        for (int j = 1; j < row.size() - 1; j++)
        {
            if (row[j] == '.' || isdigit(row[j]))
            {
                continue;
            }

            // If symbol, find and add adjacent part numbers
            vector<int> part_numbers = get_adjacent_part_numbers(i, j, engine_schematic);
            for (int part_number : part_numbers)
            {
                p1 += part_number;
            }

            // If symbol is gear, also add gear ratio
            if (row[j] == '*' && part_numbers.size() == 2)
            {
                p2 += part_numbers[0] * part_numbers[1];
            }
        }
    }

    cout << "part 1: "
         << p1 << "\npart 2: "
         << p2;
}