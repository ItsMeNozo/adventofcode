#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

vector<string> readLinesFromFile(const string &filename)
{
    vector<string> lines;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        return lines;
    }

    string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();
    return lines;
}

int solve(vector<string> dials)
{
    int s = 50, ans = 0;

    for (string d : dials)
    {
        char pref = d[0];
        int num = stoi(d.substr(1));
        int rem = num % 100;

        if (pref == 'L')
        {
            s -= rem;
            if (s < 0)
            {
                s = 100 + s;
            }
        }
        else
        {
            s += rem;
            s = s % 100;
        }

        if (s == 0)
        {
            ++ans;
        }
    }

    return ans;
}

int main()
{
    vector<string> lines = readLinesFromFile("input.txt");

    cout << solve(lines) << "\n";

    return 0; 
}