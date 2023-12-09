#include "../auxiliary.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> difference(vector<int> vec)
{
    vector<int> diff = {};
    for (int i = 1; i < vec.size(); i++)
    {
        diff.push_back(vec[i] - vec[i - 1]);
    }
    return diff;
}

// Returns history[history.size()]
int predict_next(vector<int> history)
{
    bool all_zeros = std::all_of(history.begin(), history.end(), [](int i)
                                 { return i == 0; });

    if (all_zeros)
    {
        return 0;
    }
    else
    {
        // next value - last value = next value of difference of history
        return predict_next(difference(history)) + history[history.size() - 1];
    }
}

// Returns history[-1]
int predict_previous(vector<int> history)
{
    bool all_zeros = std::all_of(history.begin(), history.end(), [](int i)
                                 { return i == 0; });

    if (all_zeros)
    {
        return 0;
    }
    else
    {
        // first value - prev value = prev value of difference of history
        return history[0] - predict_previous(difference(history));
    }
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
        vector<int> history = {};
        for (string number : split(line, ' '))
        {
            history.push_back(stoi(number));
        }
        p1 += predict_next(history);
        p2 += predict_previous(history);
    }

    cout << "part 1: "
         << p1 << "\npart 2: "
         << p2;
}