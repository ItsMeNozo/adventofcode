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

int batteryNum = 12; 
long long maxJol = 0; 

// curI is used for traversing s while nextBattery is used for setting batteriesSet
void recurseSlowestSolution(string s, int curSize, int curI, long long batteriesSet, int nextBattery) {
    if (s.size() - curI == batteryNum - nextBattery) {
        int rem = s.size() - curI; 

        for (int i = nextBattery; i < batteryNum; ++i) {
            batteriesSet = batteriesSet * 10 + (s[curI++] - '0'); 
        }

        maxJol = max(maxJol, batteriesSet); 
        return; 
    }

    if (curSize == batteryNum) {
        maxJol = max(maxJol, batteriesSet); 
        return; 
    }

    recurseSlowestSolution(s, curSize, curI + 1, batteriesSet, nextBattery);  // not take the curI

    batteriesSet = batteriesSet * 10 + (s[curI] - '0'); 

    recurseSlowestSolution(s, curSize + 1, curI + 1, batteriesSet, nextBattery + 1);  // take the curI
}

// O(N) time
long long findLargestUsingStackSolution(string s) {
    int n = s.size(); 
    int toRemove = n - batteryNum; 
    stack<int> st; 

    for (int i = 0; i < n; ++i) {
        long long dig = s[i] - '0'; 

        while (!st.empty() && dig > st.top() && toRemove > 0) {
           --toRemove; 
           st.pop(); 
        }

        st.push(dig); 
    }

    // remove redundant
    while (st.size() > batteryNum) {
        st.pop(); 
    }
    
    long long largest = 0;
    long long i = 0;  

    while (!st.empty()) {
        largest = largest + pow(10, i++) * st.top(); 
        st.pop(); 
    }

    return largest; 
}

long long solve(vector<string> banks)
{   
    long long sum = 0; 

    for (string s: banks) {
        // maxJol = 0; 
        cout << "string curr: " << s << "\n"; 

        // recurseSlowestSolution(s, 0, 0, 0, 0); 
        // sum += maxJol; 

        sum += findLargestUsingStackSolution(s); 
    }

    return sum;
}

int main()
{
    vector<string> lines = readLinesFromFile("input.txt");

    cout << solve(lines) << "\n";

    return 0; 
}