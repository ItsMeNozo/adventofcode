#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>

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

long long solve(vector<string> ranges)
{
    long long ans = 0; 

    for (string s: ranges) {
        stringstream ss(s);
        string start, end;

        getline(ss, start, '-');
        getline(ss, end, '-');


        long long startNum = stoll(start);
        long long endNum = stoll(end);
        int halfStartSize = start.size() / 2; 

        string halfStart = start.substr(0, max(halfStartSize, 1)); 

        string halfEnd = end.substr(0, (end.size() + 1) / 2); 

        for (long long half = stoll(halfStart); half <= stoll(halfEnd); ++half) {
            string cur = to_string(half); 
            cur += cur; 

            long long invalidNum = stoll(cur); 

            if (invalidNum >= startNum && invalidNum <= endNum) {
                ans += invalidNum; 
            } else if (invalidNum > endNum) {
                break; 
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