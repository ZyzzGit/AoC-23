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
    string p2 = "tbd";

    cout << "part 1: "
         << p1 << "\npart 2: "
         << p2;
}