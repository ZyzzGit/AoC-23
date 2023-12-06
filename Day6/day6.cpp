#include <string>
#include <vector>
#include <iostream>

using namespace std;

int ways_to_beat_record(int time, int record_distance)
{
    int count = 0;
    for (int t_charge = 1; t_charge < time; t_charge++) // try all combinations not resulting in speed = 0
    {
        int distance = t_charge * (time - t_charge); // distance = speed after charge * time left
        if (distance > record_distance)
        {
            count++;
        }
    }

    return count;
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

    string p2 = "tbd";

    cout << "part 1: "
         << p1 << "\npart 2: "
         << p2;
}