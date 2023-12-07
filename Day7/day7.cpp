#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
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

// Returns a list of sorted integers (large first), were each element corresponds to the count of duplicates of an element in cs
// E.g. cs={'A','K','1','A','J'} => {2, 1, 1, 1} since we have 2 'A', 1 'K', etc...
vector<int> count_duplicates(char cs[], size_t size)
{
    vector<int> counts = {};

    vector<char> cs_sorted(size);
    partial_sort_copy(cs, cs + size, begin(cs_sorted), end(cs_sorted));
    int i = 0;
    while (i < size)
    {
        int start_pos = i;
        while (i < size && cs_sorted[i] == cs_sorted[start_pos])
        {
            i++;
        }
        counts.push_back(i - start_pos);
    }

    sort(counts.begin(), counts.end(), greater<>());
    return counts;
}

int value(char card)
{
    if (isdigit(card))
    {
        return card - '0';
    }
    else
    {
        vector<char> symbols = {'T', 'J', 'Q', 'K', 'A'};
        return 10 + find(symbols.begin(), symbols.end(), card) - symbols.begin();
    }
}

struct hand
{
    char cards[5];
    int bid;

    hand(string cs, int b)
    {
        strcpy(cards, cs.c_str());
        bid = b;
    }

    bool operator<(hand &h2)
    {
        vector<int> ds1 = count_duplicates(cards, sizeof(cards) / sizeof(char));
        vector<int> ds2 = count_duplicates(h2.cards, sizeof(h2.cards) / sizeof(char));

        if (ds1[0] != ds2[0])
        {
            return ds1[0] < ds2[0];
        }
        else if (ds1.size() > 1 && ds2.size() > 1 && ds1[1] != ds2[1])
        {
            return ds1[1] < ds2[1];
        }
        else
        {
            for (int i = 0; i < sizeof(cards) / sizeof(char); i++)
            {
                if (cards[i] != h2.cards[i])
                {
                    return value(cards[i]) < value(h2.cards[i]);
                }
            }
        }

        return false;
    }
};

string line;
vector<string> lines;
int main()
{
    ifstream file("input.txt");
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    vector<hand> all_hands = {};
    for (string line : lines)
    {
        vector<string> cards_bid = split(line, ' ');
        all_hands.push_back(hand(cards_bid[0], stoi(cards_bid[1])));
    }

    sort(all_hands.begin(), all_hands.end());

    int p1 = 0;
    for (int i = 0; i < all_hands.size(); i++)
    {
        int rank = i + 1;
        p1 += all_hands[i].bid * rank;
    }

    string p2 = "tbd";

    cout << "part 1: "
         << p1 << "\npart 2: "
         << p2;
}