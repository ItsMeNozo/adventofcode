#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <unordered_set>

using namespace std;

vector<string> readLinesFromFile(const string &filename)
{
    vector<string> items;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        return items;
    }

    string line;
    
    // Read entire file content
    while (getline(file, line))
    {
        items.push_back(line); 
    }

    file.close();
    return items;
}

int solve(vector<string> lines) { 
    int splitCnt = 0; 
    unordered_set<int> beamsPos;  

    for (int i = 0; i < lines[0].size(); ++i) {
        if (lines[0][i] == 'S') {
            beamsPos.insert(i); 
        }
    }

    for (int i = 1; i < lines.size() - 1; ++i) { // no splitter at bottom
        for (int j = 0; j < lines[0].size(); ++j) {
            if (lines[i][j] == '^' && beamsPos.count(j)) {
                beamsPos.insert(j - 1); 
                beamsPos.insert(j + 1); 
                ++splitCnt; 
                beamsPos.erase(j); 
            }
        }
    }

    return splitCnt; 
}

int main()
{
    vector<string> lines = readLinesFromFile("input.txt");

    cout << solve(lines) << "\n";

    return 0; 
}