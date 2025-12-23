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

    string content;
    string item;
    
    // Read entire file content
    while (getline(file, content))
    {
        stringstream ss(content);
        // Split by comma
        while (getline(ss, item, ','))
        {
            items.push_back(item);
        }
    }

    file.close();
    return items;
}

bool isInvalid(long long x) {
    string s = to_string(x); 
    int n = s.size(); 

    for (int patternSize = 1; patternSize <= n / 2; ++patternSize) {
        if (n % patternSize != 0) continue;
        
        bool isSame = true; 
        string pattern = s.substr(0, patternSize); 

        for (int i = patternSize; i <= n - patternSize; i += patternSize) {
            if (pattern != s.substr(i, patternSize)) {
                isSame = false; 
                break; 
            }
        } 

        if (isSame) {
            return true; 
        }
    }

    return false; 
}

long long solve(vector<string> ranges)
{
    long long ans = 0; 
    unordered_set<long long> sett;  

    for (string s: ranges) {
        stringstream ss(s);
        string start, end;

        getline(ss, start, '-');
        getline(ss, end, '-');


        long long startNum = stoll(start);
        long long endNum = stoll(end);

        for (long long cur = startNum; cur <= endNum; ++cur) {
            if (isInvalid(cur)) {
                ans += cur; 
            }
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