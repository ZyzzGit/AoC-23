#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <tuple>
#include <numeric>

using namespace std;

// Compares two nodes while ignoring wildcards (*)
bool equal_nodes(string node1, string node2)
{
    for (int i = 0; i < node1.size(); i++)
    {
        if (node1[i] != node2[i] && node1[i] != '*' && node2[i] != '*')
        {
            return false;
        }
    }
    return true;
}

int steps_required(map<string, tuple<string, string>> node_map, string directions, string current_node, string goal_node)
{
    int steps = 0;
    while (true)
    {
        for (char dir : directions)
        {
            if (equal_nodes(current_node, goal_node))
            {
                return steps;
            }
            else if (dir == 'L')
            {
                current_node = get<0>(node_map[current_node]); // go left
            }
            else
            {
                current_node = get<1>(node_map[current_node]); // go right
            }
            steps++;
        }
    }
}

// Assuming each path has only one goal and the goal forms a loop with the start node
long long ghost_steps_required(map<string, tuple<string, string>> node_map, string directions, vector<string> start_nodes)
{
    // LCM of all steps to respective goal <=> all paths simultaneously reach their goal
    long long lcm = 1;
    for (string start_node : start_nodes)
    {
        lcm = std::lcm(lcm, steps_required(node_map, directions, start_node, "**Z"));
    }
    return lcm;
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

    string directions = lines[0];
    map<string, tuple<string, string>> node_map;

    for (int i = 2; i < lines.size(); i++)
    {
        string node = lines[i].substr(0, 3);
        string left = lines[i].substr(7, 3);
        string right = lines[i].substr(12, 3);
        node_map[node] = make_tuple(left, right);
    }

    int p1 = steps_required(node_map, directions, "AAA", "ZZZ");

    vector<string> ghost_start_nodes = {};
    for (auto it = node_map.begin(); it != node_map.end(); it++)
    {
        string node = it->first;
        if (node[2] == 'A')
        {
            ghost_start_nodes.push_back(node);
        }
    }

    long long p2 = ghost_steps_required(node_map, directions, ghost_start_nodes);

    cout << "part 1: "
         << p1 << "\npart 2: "
         << p2;
}