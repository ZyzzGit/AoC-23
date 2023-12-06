#include <string>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

int ways_to_beat_record(int time, long long record_distance)
{

    // d = v * t = t_charge * (t - t_charge)  <=>  d = t_charge * t - (t_charge)^2  <=>  (t_charge)^2 - t * t_charge + d = 0
    // Solve t_charge by pq-formula
    double p = -time;
    double q = record_distance + 1.0; // minimum distance we need to achieve
    int t_charge_min = ceil(-p / 2.0 - sqrt(pow(-p / 2.0, 2.0) - q));
    int t_charge_max = floor(-p / 2.0 + sqrt(pow(-p / 2.0, 2.0) - q));

    return t_charge_max - t_charge_min + 1;
}

int main()
{
    // Puzzle input
    vector<int> times = {38, 67, 76, 73};
    vector<int> distances = {234, 1027, 1157, 1236};

    int p1 = 1;
    for (int i = 0; i < times.size(); i++)
    {
        p1 *= ways_to_beat_record(times[i], distances[i]);
    }

    // Apply kerning to input and rerun
    int p2 = ways_to_beat_record(38677673, 234102711571236);

    cout << "part 1: "
         << p1 << "\npart 2: "
         << p2;
}