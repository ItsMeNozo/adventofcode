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

long long solve(vector<string> lines) { 
    int n = lines.size(); 
    vector<vector<long long>> mat(n - 1); 
    long long total = 0; 

    for (int i = 0; i < n - 1; ++i) {
        stringstream ss(lines[i]); 
        long long num; 

        while (ss >> num) {
            mat[i].push_back(num); 
        }
    }

    stringstream ss(lines[n - 1]); 
    char op; 
    vector<char> ops; 

    while (ss >> op) {
        ops.push_back((char)op); 
    }
    
    for (int j = 0; j < mat[0].size(); ++j) {
        char op = ops[j]; 
        long long res = (op == '*' ? 1 : 0);

        for (int i = 0; i < mat.size(); ++i) {
            if (op == '*') {
                res *= mat[i][j]; 
            } else {
                res += mat[i][j]; 
            }
        }

        total += res; 
    }
    return total; 
}

int main()
{
    vector<string> lines = readLinesFromFile("input.txt");

    cout << solve(lines) << "\n";

    return 0; 
}