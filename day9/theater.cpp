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
    vector<pair<long long, long long>> location; 

    for (string s : lines) {
        stringstream ss(s); 
        long long x, y;
        char delim = ',';  

        ss >> x >> delim >> y;
        location.push_back({x, y});
    }

    long long largestArea = 0; 
    int n = location.size();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long x1 = location[i].first, y1 = location[i].second;
            long long x2 = location[j].first, y2 = location[j].second;

            long long area = ((abs(x2 - x1) + 1) * (abs(y2 - y1) + 1));
            largestArea = max(largestArea, area);
        }
    }

    return largestArea;
}

int main()
{
    vector<string> lines = readLinesFromFile("input.txt");

    cout << "answer is " << solve(lines) << "\n";

    return 0; 
}