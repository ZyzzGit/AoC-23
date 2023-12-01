#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

string line;
vector<string> lines;
int main()
{
    ifstream file("input.txt");
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    string p1 = "tbd";
    string p2 = "tbd";

    cout << "part 1: "
         << p1 << "\npart 2: "
         << p2;
}