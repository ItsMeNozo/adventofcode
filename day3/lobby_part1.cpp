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
long long solve(vector<string> banks)
{   
    int sum = 0; 

    for (string s: banks) {
        int n = s.size(); 
        int maxJol = 0; 

        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int jol = (s[j] - '0') + 10 * (s[i] - '0'); 
                maxJol = max(maxJol, jol); 
            }
        }
        sum += maxJol; 
    }

    return sum;
}

int main()
{
    vector<string> lines = readLinesFromFile("input.txt");

    cout << solve(lines) << "\n";

    return 0; 
}