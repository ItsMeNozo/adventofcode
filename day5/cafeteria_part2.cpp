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

struct Interval {
    long long low, high; 
}; 

struct Node {
    Node *left, *right; 
    Interval interval; 
    long long max; 
}; 

Node* newNode(long long low, long long high) {
    Node* node = new Node; 
    node->interval = {low, high}; 
    node->left = node -> right = nullptr; 
    node->max = high; 

    return node; 
}

Node* insert(Node* root, long long low, long long high) {
    if (root == nullptr) {
        return newNode(low, high); 
    }

    // using low as the key
    if (low < root->interval.low) {
        root->left = insert(root->left, low, high); 
    } else {
        root->right = insert(root->right, low, high); 
    }

    if (root->max < high) {
        root->max = high; 
    }

    return root; 
} 

Node* buildIntervalTree(vector<string> lines) {
    Node* root = nullptr; 

    for (long long i = 0; i < lines.size(); ++i) {
        if (lines[i] == "") {
            return root; 
        }

        long long low, high; 
        char delimiter = '-'; 

        stringstream ss(lines[i]);
        
        ss >> low >> delimiter >> high; 
        root = insert(root, low, high); 
    }

    return root; 
}

long long solve(vector<string> lines) {   
    vector<pair<long long, long long>> ranges; 
    
    for (long long i = 0; i < lines.size(); ++i) {
        if (lines[i] == "") {
            break; 
        }

        long long low, high; 
        char delimiter = '-'; 

        stringstream ss(lines[i]);
        
        ss >> low >> delimiter >> high; 
        ranges.push_back({low, high}); 
    }    

    if (ranges.size() == 0) {
        return 0; 
    }

    sort(ranges.begin(), ranges.end());  // sort by low

    long long i = 0; 
    stack<pair<long long, long long>> merged; 

    merged.push(ranges[0]); 

    for (long long i = 1; i < ranges.size(); ++i) {
        pair<long long, long long> latest = merged.top(); 

        if (latest.second >= ranges[i].first) {
            merged.pop(); 
            merged.push({latest.first, max(ranges[i].second, latest.second)}); 
        } else {
            merged.push(ranges[i]); 
        }
    }

    long long idsCount = 0; 

    while (!merged.empty()) {
        pair<long long, long long> p = merged.top(); 
        idsCount += (p.second - p.first) + 1; 

        merged.pop(); 
    }

    return idsCount; 
}

int main()
{
    vector<string> lines = readLinesFromFile("input.txt");

    cout << solve(lines) << "\n";

    return 0; 
}