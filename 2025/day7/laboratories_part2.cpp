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

long long dfs(vector<string>& lines, vector<vector<long long>>& memo, int i, int j) {
    if (memo[i][j] != -1) {
        return memo[i][j]; 
    }

    if (i == lines.size() - 1) {
        return 1; 
    }

    long long result = 0; 

    if (lines[i][j] != '^') {
        result = dfs(lines, memo, i + 1, j); 
    } else {
        result = dfs(lines, memo, i + 1, j - 1) + dfs(lines, memo, i + 1, j + 1); 
    }
    
    memo[i][j] = result; 

    return result; 
}

long long solve(vector<string> lines) { 
    // perform DFS
    vector<vector<long long>> memo(lines.size(), vector<long long>(lines[0].size(), -1)); 

    for (int i = 0; i < lines[0].size(); ++i) {
        if (lines[0][i] == 'S') {
            return dfs(lines, memo, 1, i); 
            break; 
        }
    }

    return 0; 
    
}

int main()
{
    vector<string> lines = readLinesFromFile("input.txt");

    cout << solve(lines) << "\n";

    return 0; 
}