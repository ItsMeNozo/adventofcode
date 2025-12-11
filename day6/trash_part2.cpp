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
    vector<vector<char>> mat(n - 1);
    long long total = 0; 

    for (int i = 0; i < n - 1; ++i) {
        for (char c: lines[i]) {
            mat[i].push_back(c); 
        } 
    }

    vector<int> spacePos; 
    vector<char> ops; 

    for (int i = 0; i < lines[n - 1].size(); ++i) {
        char cur = lines[n - 1][i]; 
        if (cur == '*' || cur == '+') {
            ops.push_back(cur); 
            spacePos.push_back(i - 1); 
        }
    }

    int prev = spacePos[0]; 
    spacePos.push_back(mat[0].size()); 

    for (int t = 1; t < spacePos.size(); ++t) {
        char op = ops[t - 1];
        long long res = (op == '*' ? 1 : 0); 

        for (int i = spacePos[t] - 1; i > prev; --i) {
            long long num = 0; 
            long long mul = 1; 

            for (int j = n - 2; j >= 0; --j) {
                if (mat[j][i] == ' ') {
                    continue; 
                }
                num += (((mat[j][i] - '0')) * mul);
                mul *= 10;  
            }

            if (op == '*') {
                res *= num; 
            } else {
                res += num; 
            }
        }

        total += res; 
        prev = spacePos[t]; 
    }



    return total; 
}

int main()
{
    vector<string> lines = readLinesFromFile("input.txt");

    cout << solve(lines) << "\n";

    return 0; 
}