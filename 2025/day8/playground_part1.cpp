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

struct Edge {
    int p1, p2; 
    double dist; 

    bool operator<(const Edge& other) const {
        return dist < other.dist; 
    }
}; 

long long solve(vector<string> lines) { 
    vector<vector<int>> pos; 
    int numPairs = 1000; 

    for (string s : lines) {
        stringstream ss(s); 
        int x, y, z;
        char delim = ',';  

        ss >> x >> delim >> y >> delim >> z; 

        pos.push_back({x, y, z}); 
    }

    priority_queue<Edge> maxH; 
    int n = lines.size(); 

    for (int i = 0; i < n - 1; ++i) {
        double x1 = pos[i][0], y1 = pos[i][1], z1 = pos[i][2]; 

        for (int j = i + 1; j < n; ++j) {
            double x2 = pos[j][0], y2 = pos[j][1], z2 = pos[j][2]; 
            double dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1)); 
            
            maxH.push({i, j, dist}); 
            int maxHSize = maxH.size();

            if (maxHSize > numPairs) {
                maxH.pop(); 
            }
        }
    }

    vector<int> parentTracker(n, -1); 

    while (!maxH.empty()) {
        Edge top = maxH.top(); 
        
        maxH.pop(); 

        if (parentTracker[top.p1] == -1 && parentTracker[top.p2] == -1) {
            parentTracker[top.p1] = top.p1; 
            parentTracker[top.p2] = top.p1; 
        } else if (parentTracker[top.p1] == -1) {
            parentTracker[top.p1] = parentTracker[top.p2];
        } else if (parentTracker[top.p2] == -1) {
            parentTracker[top.p2] = parentTracker[top.p1];
        } else {
            // both have parents -> connect those 2 circuits together to make 1 big circuit
            int p1Parent = parentTracker[top.p1];

            for (int i = 0; i < n; ++i) {
                if (parentTracker[i] == p1Parent) {
                    parentTracker[i] = parentTracker[top.p2]; 
                }
            }
        }
    }

    vector<int> parentCnt(n, 0); 

    for (int x : parentTracker) {
        if (x == -1) continue;

        ++parentCnt[x]; 
    }

    sort(parentCnt.begin(), parentCnt.end(), greater<int>()); 

    long long prod = 1; 

    for (int i = 0; i < 3; ++i) {
        prod *= parentCnt[i]; 
    }


    return prod; 
}

int main()
{
    vector<string> lines = readLinesFromFile("input.txt");

    cout << "answer is " << solve(lines) << "\n";

    return 0; 
}