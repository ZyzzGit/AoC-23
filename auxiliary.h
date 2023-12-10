#include <string>
#include <sstream>
#include <vector>

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

vector<string> pad(vector<string> strs, char c)
{
    for (int i = 0; i < strs.size(); i++)
    {
        strs[i] = (c + strs[i] + c);
    }
    int width = strs[0].size();
    strs.insert(strs.begin(), string(width, c));
    strs.push_back(string(width, c));
    return strs;
}