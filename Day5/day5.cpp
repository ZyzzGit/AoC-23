#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
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

class range_map
{
    long long destination_range_start;
    long long source_range_start;
    long long range_length;

public:
    range_map(long long drs, long long srs, long long rl)
    {
        destination_range_start = drs;
        source_range_start = srs;
        range_length = rl;
    }

public:
    bool contains(long long key)
    {
        return source_range_start <= key && key < (source_range_start + range_length);
    }

public:
    // Make sure the map contains the key before calling; always returns a value
    long long map(long long key)
    {

        return key + (destination_range_start - source_range_start);
    }
};

vector<long long> get_seed_locations(vector<string> almanack)
{
    vector<string> seed_line = split(almanack[0], ' ');
    vector<long long> seeds = {};
    for (int i = 1; i < seed_line.size(); i++)
    {
        seeds.push_back(stoll(seed_line[i]));
    }

    vector<vector<range_map>> range_map_sets = {}; // each set of range maps is equivalent to a "single regular map"
    vector<range_map> range_maps = {};

    almanack.push_back(""); // to easily recognize end of last map_lines set
    for (int i = 3; i < almanack.size(); i++)
    {
        // When blank line encountered, append the set corresponding to the previous range maps, then reset and continue
        if (almanack[i] == "")
        {
            range_map_sets.push_back(range_maps);
            range_maps.clear();
            i++;
            continue;
        }

        vector<string> map_line = split(almanack[i], ' ');
        range_maps.push_back(range_map(stoll(map_line[0]), stoll(map_line[1]), stoll(map_line[2])));
    }

    // Convert, map set by map set, the seeds to locations
    vector<long long> locations = seeds;
    for (vector<range_map> range_map_set : range_map_sets)
    {
        for (int i = 0; i < locations.size(); i++)
        {
            // Try all range maps in the set, if no map contains the number then keep it
            for (range_map rmap : range_map_set)
            {
                if (rmap.contains(locations[i]))
                {
                    locations[i] = rmap.map(locations[i]);
                    break;
                }
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

    vector<long long> seed_locations = get_seed_locations(lines);
    long long p1 = *min_element(seed_locations.begin(), seed_locations.end());
    string p2 = "tbd";

    cout << "part 1: "
         << p1 << "\npart 2: "
         << p2;
}