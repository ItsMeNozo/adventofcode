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

long long solve(vector<string> ranges)
{
    long long ans = 0; 
    unordered_set<long long> sett;  

    for (string s: ranges) {
        stringstream ss(s);
        string start, end;

        getline(ss, start, '-');
        getline(ss, end, '-');

        cout << start << " " << end << "\n"; 


        long long startNum = stoll(start);
        long long endNum = stoll(end);

        int halfStartSize = start.size() / 2; 
        int halfEndSize = (end.size() + 1) / 2; 
        int startSize = start.size(); 
        int n = min(halfEndSize, startSize); 

        for (int size = 1; size <= n; ++size) {
            string cur = start.substr(0, size);

            if (cur.size() > end.size() / 2) {
                break; 
            }

            for (long long num = stoll(cur); num < endNum; ++num) {
                string repeatStr = to_string(num); 
                bool foundInvalid = true; 

                if (repeatStr.size() > end.size() / 2) {
                    break; 
                }

                for (int repeat = start.size() / cur.size(); repeat <= (end.size() + 1) / repeatStr.size(); ++repeat ) {
                    string invalid; 

                    if (repeat < 2) {
                        continue; 
                    }

                    for (int i = 0; i < repeat; ++i) {
                        invalid += repeatStr;  
                    }

                    long long invalidNum = stoll(invalid); 

                    if (invalidNum >= startNum && invalidNum <= endNum && sett.find(invalidNum) == sett.end()) {
                        ans += invalidNum; 
                        sett.insert(invalidNum); 
                    } else {
                        foundInvalid = false; 
                        break; 
                    }
                }

                if (!foundInvalid) {
                    break; 
                }
            }
        }
        
        for (int size = 1; size <= halfEndSize; ++size) {
            string cur = end.substr(0, size);
            
            for (long long num = stoll(cur); num > 0; --num) {
                string repeatStr = to_string(num); 
                bool foundInvalid = true; 

                for (int repeat = end.size() / cur.size(); repeat >= start.size() / cur.size(); --repeat) {
                    string invalid; 

                    if (repeat < 2) {
                        break; 
                    }

                    for (int i = 0; i < repeat; ++i) {
                        invalid += repeatStr; 
                    }

                    long long invalidNum = stoll(invalid); 

                    if (invalidNum >= startNum && invalidNum <= endNum && sett.find(invalidNum) == sett.end()) {
                        ans += invalidNum; 
                        sett.insert(invalidNum); 
                    } else {
                        foundInvalid = false; 
                        break; 
                    }
                }
                if (!foundInvalid) {
                    break; 
                }
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