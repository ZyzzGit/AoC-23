#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

int get_calibration_value(string str)
{
    vector<int> digits;
    for (char &c : str)
    {
        if (isdigit(c))
        {
            digits.push_back(c - '0');
        }
    }

    return 10 * digits[0] + digits[digits.size() - 1];
}

vector<string> str_digits = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int get_calibration_value_v2(string str)
{
    vector<int> digits;
    for (int i = 0; i < str.size(); i++)
    {
        if (isdigit(str[i]))
        {
            // Check if character i is a digit
            digits.push_back(str[i] - '0');
        }
        else
        {
            // Check if any substring starting on index i represents a digit
            int space = str.size() - i;
            for (int length = 3; length <= min(space, 5); length++)
            {
                string substr = str.substr(i, length);
                int position = find(str_digits.begin(), str_digits.end(), substr) - str_digits.begin();
                if (position < str_digits.size())
                {
                    digits.push_back(position + 1);
                    break;
                }
            }
        }
    }

    return 10 * digits[0] + digits[digits.size() - 1];
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
    for (string line : lines)
    {
        p1 += get_calibration_value(line);
        p2 += get_calibration_value_v2(line);
    }

    cout << "part 1: "
         << p1 << "\npart 2: "
         << p2;
}
