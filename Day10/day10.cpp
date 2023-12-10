#include "../auxiliary.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

tuple<tuple<int, int>, tuple<int, int>> connecting_pipes(vector<string> pipe_network, tuple<int, int> pipe_pos)
{
    int pos_y = get<0>(pipe_pos);
    int pos_x = get<1>(pipe_pos);
    char pipe = pipe_network[pos_y][pos_x];
    vector<tuple<int, int>> neighbouring_pipes = {make_tuple(pos_y - 1, pos_x), make_tuple(pos_y + 1, pos_x), make_tuple(pos_y, pos_x - 1), make_tuple(pos_y, pos_x + 1)};

    switch (pipe)
    {
    case '|':
        return make_tuple(make_tuple(pos_y - 1, pos_x), make_tuple(pos_y + 1, pos_x));
    case '-':
        return make_tuple(make_tuple(pos_y, pos_x - 1), make_tuple(pos_y, pos_x + 1));
    case 'L':
        return make_tuple(make_tuple(pos_y - 1, pos_x), make_tuple(pos_y, pos_x + 1));
    case 'J':
        return make_tuple(make_tuple(pos_y - 1, pos_x), make_tuple(pos_y, pos_x - 1));
    case '7':
        return make_tuple(make_tuple(pos_y + 1, pos_x), make_tuple(pos_y, pos_x - 1));
    case 'F':
        return make_tuple(make_tuple(pos_y + 1, pos_x), make_tuple(pos_y, pos_x + 1));
    case 'S':
        // Remove all neighbouring pipes not connecting to this pipe
        for (auto it = neighbouring_pipes.begin(); it != neighbouring_pipes.end();)
        {
            tuple<tuple<int, int>, tuple<int, int>> connecting_pipes_of_neighbour = connecting_pipes(pipe_network, *it);
            if (get<0>(connecting_pipes_of_neighbour) != pipe_pos && get<1>(connecting_pipes_of_neighbour) != pipe_pos)
                it = neighbouring_pipes.erase(it);
            else
                ++it;
        }
        return make_tuple(neighbouring_pipes[0], neighbouring_pipes[1]);
    default:
        // Non pipe (ground '.') received => indicate by returning false positions
        // (may happen when connecting_pipes is called from the 'S' case)
        return make_tuple(make_tuple(-1, -1), make_tuple(-1, -1));
    }
}

int loop_length(vector<string> pipe_network, tuple<int, int> start)
{
    vector<tuple<int, int>> loop_unrolled = {start};
    tuple<int, int> next = get<0>(connecting_pipes(pipe_network, start));

    while (next != start)
    {
        loop_unrolled.push_back(next);

        // Update next pipe with the connecting one not already in loop_unrolled
        tuple<tuple<int, int>, tuple<int, int>> connecting = connecting_pipes(pipe_network, next);
        if (get<0>(connecting) != loop_unrolled[loop_unrolled.size() - 2])
        {
            next = get<0>(connecting);
        }
        else
        {
            next = get<1>(connecting);
        }
    }

    return loop_unrolled.size();
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

    // Double pad to avoid segmentation faults
    vector<string> pipe_network = pad(pad(lines, '.'), '.');

    tuple<int, int> start_pos;
    for (int i = 0; i < pipe_network.size(); i++)
    {
        for (int j = 0; j < pipe_network[0].size(); j++)
        {
            if (pipe_network[i][j] == 'S')
            {
                start_pos = make_tuple(i, j);
            }
        }
    }

    int p1 = ceil(loop_length(pipe_network, start_pos) / 2.0);
    string p2 = "tbd";

    cout << "part 1: "
         << p1 << "\npart 2: "
         << p2;
}