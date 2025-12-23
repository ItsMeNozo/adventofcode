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

pair<Node*, int> buildIntervalTree(vector<string> lines) {
    Node* root = nullptr; 

    for (int i = 0; i < lines.size(); ++i) {
        if (lines[i] == "") {
            return {root, i}; 
        }

        long long low, high; 
        char delimiter = '-'; 

        stringstream ss(lines[i]);
        
        ss >> low >> delimiter >> high; 
        root = insert(root, low, high); 
    }

    return {root, 0}; 
}

bool isAvailable(Node* root, long long id) {
    // implement find in interval tree
    if (root == nullptr) {
        return false; 
    }

    if (root->interval.low <= id && root->interval.high >= id) {
        return true; 
    } 

    if (root->left != nullptr && root->left->max > id) {
        return isAvailable(root->left, id);
    } else {
        return isAvailable(root->right, id); 
    }
}

// interval search tree
int solve(vector<string> lines) {   
    Node* root; 
    int searchIndex = 0; 
    int ans = 0; 

    tie(root, searchIndex) = buildIntervalTree(lines);

    for (int i = searchIndex + 1; i < lines.size(); ++i) {
        if (isAvailable(root, stoll(lines[i]))) {
            ++ans; 
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