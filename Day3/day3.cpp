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

bool is_symbol(char item)
{
    return item != '.' && !isdigit(item);
}

bool contains_symbol(string items)
{
    for (char item : items)
    {
        if (is_symbol(item))
        {
            return true;
        }
    }
    return false;
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

int sum_part_numbers(vector<string> engine_schematic)
{
    // Start with padding the schematic to avoid going out of bounds when checking for neighbours
    // => indexes will go from 1 to size-2 when traversing rows or columns
    engine_schematic = pad(engine_schematic, '.');

    int sum = 0;
    for (int i = 1; i < engine_schematic.size() - 1; i++)
    {
        string row = engine_schematic[i];
        for (int j = 1; j < row.size() - 1; j++)
        {
            string number = "";
            while (isdigit(row[j]))
            {
                number.push_back(row[j]);
                j++;
            }

            if (number == "")
            {
                continue;
            }

            // If number is a number, check if it is a part number; check the number frame for symbols
            int number_start_pos = j - number.size();
            if (
                contains_symbol(engine_schematic[i - 1].substr(number_start_pos - 1, number.size() + 2)) || // upper part of frame
                is_symbol(row[number_start_pos - 1]) ||                                                     // left element
                is_symbol(row[j]) ||                                                                        // right element
                contains_symbol(engine_schematic[i + 1].substr(number_start_pos - 1, number.size() + 2))    // lower part of frame
            )
            {
                sum += stoi(number);
            }
        }
    }

    return sum;
}

int sum_gear_ratios(vector<string> engine_schematic)
{
    engine_schematic = pad(engine_schematic, '.');

    int sum = 0;
    for (int i = 1; i < engine_schematic.size() - 1; i++)
    {
        string row = engine_schematic[i];
        for (int j = 1; j < row.size() - 1; j++)
        {
            if (row[j] != '*')
            {
                continue;
            }

            vector<int> part_numbers = get_adjacent_part_numbers(i, j, engine_schematic);

            if (part_numbers.size() == 2)
            {
                sum += part_numbers[0] * part_numbers[1];
            }
        }
    }

    return sum;
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

    int p1 = sum_part_numbers(lines);
    int p2 = sum_gear_ratios(lines);

    cout << "part 1: "
         << p1 << "\npart 2: "
         << p2;
}