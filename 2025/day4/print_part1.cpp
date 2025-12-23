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

// bruteforce
int solve(vector<string> lines) {   
    int m = lines.size();  // row
    int n = lines[0].size();  // col
    int rolls = 0; 
    vector<vector<int>> directions = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 1}, {1, 0}};

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (lines[i][j] == '@') {
                int rollsCnt = 0; 

                for (vector<int> dir : directions) {
                    int x = i + dir[0]; 
                    int y = j + dir[1]; 

                    if ((x >= 0 && x < m) && (y >= 0 && y < n) && lines[x][y] == '@') {
                        ++rollsCnt; 
                    }
                }

                if (rollsCnt < 4) {
                    ++rolls; 
                }
            }
        }
    }

    return rolls; 
}

int main()
{
    vector<string> lines = readLinesFromFile("input.txt");

    cout << solve(lines) << "\n";

    return 0; 
}