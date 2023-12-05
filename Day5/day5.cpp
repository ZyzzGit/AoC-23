#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <tuple>
#include <algorithm>

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

map<int, int> get_map(vector<tuple<int, int, int>> map_lines)
{
    map<int, int> mp;

    for (tuple<int, int, int> map_line : map_lines)
    {
        int destination_range_start = get<0>(map_line);
        int source_range_start = get<1>(map_line);
        int range_length = get<2>(map_line);

        for (int i = 0; i < range_length; i++)
        {
            mp[source_range_start + i] = destination_range_start + i;
        }
    }

    return mp;
}

vector<int> get_seed_locations(vector<string> almanack)
{
    vector<string> seed_line = split(almanack[0], ' ');
    vector<int> seeds = {};
    for (int i = 1; i < seed_line.size(); i++)
    {
        seeds.push_back(stoi(seed_line[i]));
    }

    vector<map<int, int>> mps = {};
    vector<tuple<int, int, int>> map_lines = {};

    almanack.push_back(""); // to easily recognize end of last map_lines set
    for (int i = 3; i < almanack.size(); i++)
    {
        // When blank line encountered, get the map of previous corresponding map_lines, then reset and continue
        if (almanack[i] == "")
        {
            mps.push_back(get_map(map_lines));
            map_lines.clear();
            i++;
            continue;
        }

        vector<string> map_line = split(almanack[i], ' ');
        map_lines.push_back(make_tuple(stoi(map_line[0]), stoi(map_line[1]), stoi(map_line[2])));
    }

    // Convert, map by map, the seeds to locations
    vector<int> locations = seeds;
    for (map<int, int> mp : mps)
    {
        for (int i = 0; i < locations.size(); i++)
        {
            // Only update number if there exists a mapping for it
            if (mp.count(locations[i]))
            {
                locations[i] = mp[locations[i]];
            }
        }
    }

    return locations;
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

    vector<int> seed_locations = get_seed_locations(lines);
    int p1 = *min_element(seed_locations.begin(), seed_locations.end());
    string p2 = "tbd";

    cout << "part 1: "
         << p1 << "\npart 2: "
         << p2;
}