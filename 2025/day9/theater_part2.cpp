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

bool validRect(vector<vector<char>>& grid, int maxRow, int maxCol, int minRow, int minCol) {
    for (int i = minCol; i <= maxCol; ++i) {
        if (grid[minRow][i] == 'V') {
            return false; 
        }
    }

    for (int i = minRow; i <= maxRow; ++i) {
        if (grid[i][maxCol] == 'V') {
            return false; 
        }
    }

    for (int i = minCol; i <= maxCol; ++i) {
        if (grid[maxRow][i] == 'V') {
            return false; 
        }
    }

    for (int i = minRow; i <= maxRow; ++i) {
        if (grid[i][minCol] == 'V') {
            return false; 
        }
    }

    return true; 
}

long long solve(vector<string> lines) { 
    vector<pair<long long, long long>> location; 
    long long m = 0, n = 0, sr = INT_MAX, sc = INT_MAX; 

    for (string s : lines) {
        stringstream ss(s); 
        long long x, y;
        char delim = ',';  

        ss >> y >> delim >> x;

        m = max(m, x + 1); 
        n = max(n, y + 1);
        sr = min(sr, x); 
        sc = min(sc, y); 

        location.push_back({x, y});
    }

    long long largestArea = 0; 
    vector<vector<char>> grid(m, vector<char>(n, '.')); 
    
    // mark red tiles
    for (pair<long long, long long> loc : location) {
        long long x = loc.first;
        long long y = loc.second;

        grid[x][y] = '#'; 
    }

    cout << "marked red tiles\n";

    // mark green tiles
    for (int i = 0; i < lines.size() - 1; ++i) {
        for (int j = i + 1; j < lines.size(); ++j) {  
            long long x1 = location[i].first, y1 = location[i].second;
            long long x2 = location[j].first, y2 = location[j].second;

            if (y1 == y2) {
                // horizontal line (same row, different columns)
                for (long long row = min(x1, x2) + 1; row < max(x1, x2); ++row) {
                    grid[row][y1] = 'X'; 
                }
            } 

            if (x1 == x2) {
                // vertical line (same column, different rows)
                for (long long col = min(y1, y2) + 1; col < max(y1, y2); ++col) {
                    grid[x1][col] = 'X'; 
                }
            }
        }
    
    }
    cout << "Now we have the border\n";

    // mark tiles outside the borders as 'V
    queue<pair<int, int>> q;

    for (int i = 0; i < m; ++i) {
        if (grid[i][0] == '.') {
            q.push({i, 0});
            grid[i][0] = 'V';
        }
        if (grid[i][n-1] == '.') {
            q.push({i, n-1});
            grid[i][n-1] = 'V';
        }
    }

    for (int j = 0; j < n; ++j) {
        if (grid[0][j] == '.') {
            q.push({0, j});
            grid[0][j] = 'V';
        }
        if (grid[m-1][j] == '.') {
            q.push({m-1, j});
            grid[m-1][j] = 'V';
        }
    }

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (ny < n && ny >= sc - 1 && nx < m && nx >= sr - 1 && grid[nx][ny] == '.') {
                grid[nx][ny] = 'V';
                q.push({nx, ny});
            }
        }
    }


    cout << "Final grid:\n";

    // form sorted array of areas and i and j
    vector<pair<long long, pair<int, int>>> areas;


    for (int i = 0; i < lines.size() - 1; ++i) {
        for (int j = i + 1; j < lines.size(); ++j) {
            long long x1 = location[i].first, y1 = location[i].second;
            long long x2 = location[j].first, y2 = location[j].second;

            long long area = ((abs(x2 - x1) + 1) * (abs(y2 - y1) + 1));
            areas.push_back({area, {i, j}});            
        }
    }

    sort(areas.rbegin(), areas.rend());

    for (auto& areaPair : areas) {
        long long area = areaPair.first;

        if (area <= largestArea) {
            break;
        }

        int i = areaPair.second.first;
        int j = areaPair.second.second;
        
        int x1 = location[i].first, y1 = location[i].second;
        int x2 = location[j].first, y2 = location[j].second;

        int minRow = min(x1, x2);
        int maxRow = max(x1, x2);
        int minCol = min(y1, y2);
        int maxCol = max(y1, y2);

        bool validArea = validRect(grid, maxRow, maxCol, minRow, minCol); 
        
        if (!validArea) {
            continue;
        }

        return area;  
    }

    return largestArea;
}

int main()
{
    vector<string> lines = readLinesFromFile("input.txt");

    cout << "answer is " << solve(lines) << "\n";

    return 0; 
}