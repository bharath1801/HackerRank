#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

int dfs(vector<string>& forest, vector<vector<bool>>& visited, int x, int y, int wands) {
    if (x >= 0 && y >=0 && y < forest[0].size() && x < forest.size()) {
        visited[x][y] = true;
        if (forest[x][y] == '*') return wands;
        vector<pair<int,int>> moves;
        if (x-1 >= 0 && forest[x-1][y] != 'X' && !visited[x-1][y]) {
            pair<int,int> move(x-1,y);
            moves.push_back(move);
        }
        if (x+1 < forest.size() && forest[x+1][y] != 'X' && !visited[x+1][y]) {
            pair<int,int> move(x+1,y);
            moves.push_back(move);
        }
        if (y-1 >= 0 && forest[x][y-1] != 'X' && !visited[x][y-1]) {
            pair<int,int> move(x,y-1);
            moves.push_back(move);
        }
        if (y+1 < forest[0].size() && forest[x][y+1] != 'X' && !visited[x][y+1]) {
            pair<int,int> move(x,y+1);
            moves.push_back(move);
        }
        if (!moves.empty()) {
            for (int i = 0; i < moves.size(); ++i) {
                int res = dfs(forest, visited, moves[i].first, moves[i].second, wands + (moves.size() > 1));
                if (res != -1) return res;
            }
        }
    }
    return -1;
}

bool findPath(vector<string>& forest, vector<vector<bool>>& visited, pair<int,int>& start, int K) {
    bool possible = false;
    int res = dfs(forest, visited, start.first, start.second, 0);
    if (res == K) possible = true;
    return possible;
}

int main() {
    int numcases;
    cin >> numcases;
    for (int testcase = 0; testcase < numcases; ++testcase) {
        int N, M, K;
        cin >> N >> M;
        vector<string> matrix;
        vector<vector<bool>> visited;
        pair <int,int> start(-1,-1), exit(-1,-1);
        for (int row = 0; row < N; ++row) {
            string row_string;
            cin >> row_string;
            size_t found;
            if (exit.first == -1 && exit.second == -1 && 
                (found = row_string.find('*')) != string::npos) {
                exit.first  = row;
                exit.second = found;
            }
            if (start.first == -1 && start.second == -1 && 
                (found = row_string.find('M')) != string::npos) {
                start.first  = row;
                start.second = found;
            }
            matrix.push_back(row_string);
            vector<bool> visited_row(M, false);
            visited.push_back(visited_row);
        }
        cin >> K;
        (findPath(matrix, visited, start, K)) ? cout << "Impressed\n" : cout << "Oops!\n";
    }
    return 0;
}
