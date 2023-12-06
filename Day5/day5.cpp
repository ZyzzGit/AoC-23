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
public:
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

private:
    // Returns <overlap start, overlap length> wrt range_other
    tuple<long long, long long> overlap(long long range_other_start, long long range_other_length)
    {
        if (range_other_start + range_other_length <= source_range_start || source_range_start + range_length <= range_other_start)
        {
            return make_tuple(-1, -1); // no overlap
        }
        else
        {
            long long overlap_start = max(source_range_start, range_other_start);
            long long overlap_length = min({range_other_length - (overlap_start - range_other_start), range_length - (range_other_start - source_range_start), range_length});
            return make_tuple(overlap_start, overlap_length);
        }
    }

public:
    // Returns a vector of ranges, were the first is the mapped range and the rest are the remaining (unmapped) part of the input
    // If no mapping was made (no overlap), returns empty vector
    vector<tuple<long long, long long>> map_range(tuple<long long, long long> range)
    {
        tuple<long long, long long> ol = overlap(get<0>(range), get<1>(range));

        if (ol == make_tuple(-1, -1))
        {
            return {};
        }

        tuple<long long, long long> mapped_range = make_tuple(map(get<0>(ol)), get<1>(ol));
        vector<tuple<long long, long long>> result = {mapped_range};

        // Part of range before overlap
        if (get<0>(range) < get<0>(ol))
        {
            result.push_back(make_tuple(get<0>(range), get<0>(ol) - get<0>(range)));
        }

        // Part of range after overlap
        if (get<0>(ol) + get<1>(ol) < get<0>(range) + get<1>(range))
        {
            result.push_back(make_tuple(get<0>(ol) + get<1>(ol), get<0>(range) + get<1>(range) - (get<0>(ol) + get<1>(ol))));
        }

        return result;
    }
};

vector<vector<range_map>> get_map_sets(vector<string> almanack)
{

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

    return range_map_sets;
}

vector<long long> get_seed_locations(vector<string> almanack)
{
    vector<string> seed_line = split(almanack[0], ' ');
    vector<long long> seeds = {};
    for (int i = 1; i < seed_line.size(); i++)
    {
        seeds.push_back(stoll(seed_line[i]));
    }

    vector<vector<range_map>> range_map_sets = get_map_sets(almanack);

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

long long get_min_location_from_seed_ranges(vector<string> almanack)
{
    vector<string> seed_line = split(almanack[0], ' ');
    vector<tuple<long long, long long>> seed_ranges = {}; // for each seed range, we have <start number, range length>
    for (int i = 1; i < seed_line.size(); i += 2)
    {
        seed_ranges.push_back(make_tuple(stoll(seed_line[i]), stoll(seed_line[i + 1])));
    }

    vector<vector<range_map>> range_map_sets = get_map_sets(almanack);

    // Convert, map set by map set, the seed ranges to location ranges
    vector<tuple<long long, long long>> location_ranges = seed_ranges;
    for (vector<range_map> range_map_set : range_map_sets)
    {
        for (int i = 0; i < location_ranges.size(); i++)
        {
            for (range_map rmap : range_map_set)
            {
                vector<tuple<long long, long long>> map_result = rmap.map_range(location_ranges[i]);

                // Only handle the case were some part of the input range was mapped
                if (!map_result.empty())
                {
                    location_ranges[i] = map_result[0]; // update input range with mapped part
                    for (int j = 1; j < map_result.size(); j++)
                    {
                        location_ranges.push_back(map_result[j]); // place unmapped parts last in input vector and retry mapping them later
                    }
                    break;
                }
            }
        }
    }

    long long min_location = get<0>(location_ranges[0]);
    for (int i = 1; i < location_ranges.size(); i++)
    {
        min_location = min(min_location, get<0>(location_ranges[i]));
    }

    return min_location;
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

    long long p2 = get_min_location_from_seed_ranges(lines);

    cout << "part 1: "
         << p1 << "\npart 2: "
         << p2;
}