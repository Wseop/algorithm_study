#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/87694
// BFS, 인접리스트

// 주어진 직사각형을 따라 각 좌표에서 이동가능한 인접리스트 정의
// 인접리스트로 한 이유) 직사각형의 좌표만 기억해둘 경우 거리가 1인 좌표를 이동할 때 경로를 따라가지 않고 바로 건너뛰어서 이동하는 케이스가 발생할 수 있음!
// ex.) 두 직사각형이 한칸 간격으로 떨어져있는 경우

// 이동하고자 하는 경로가 다른 직사각형의 내부에 있어서는 안되기 때문에 두 점 사이의 좌표(double)로 이를 판단

struct Pos {
    int x;
    int y;
    int m;
};

int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY) {
    int answer = 0;
    vector<vector<vector<Pos>>> adjacent(51, vector<vector<Pos>>(51));
    vector<vector<int>> visited(51, vector<int>(51, 987654321));
    queue<Pos> q;
    
    for (const vector<int> r : rectangle) {
        int x1 = r[0], y1 = r[1];
        int x2 = r[2], y2 = r[3];
        
        for (int i = x1; i < x2; i++) {
            adjacent[i][y1].push_back({i + 1, y1, 0});
            adjacent[i + 1][y1].push_back({i, y1, 0});
            adjacent[i][y2].push_back({i + 1, y2, 0});
            adjacent[i + 1][y2].push_back({i, y2, 0});
        }
        
        for (int i = y1; i < y2; i++) {
            adjacent[x1][i].push_back({x1, i + 1, 0});
            adjacent[x1][i + 1].push_back({x1, i, 0});
            adjacent[x2][i].push_back({x2, i + 1, 0});
            adjacent[x2][i + 1].push_back({x2, i, 0});
        }
    }
    
    visited[characterX][characterY] = 0;
    q.push({characterX, characterY, 0});
    
    while (!q.empty()) {
        Pos pos = q.front();
        q.pop();
        
        for (const Pos& p : adjacent[pos.x][pos.y]) {
            int nx = p.x;
            int ny = p.y;
            bool innerPos = false;
            
            if (visited[nx][ny] <= pos.m + 1) continue;
            
            for (const vector<int>& r : rectangle) {
                // if ((nx > r[0] && nx < r[2]) && (ny > r[1] && ny < r[3])) {
                //     innerPos = true;
                //     break;
                // }
                double mx = (nx + pos.x) / (double)2;
                double my = (ny + pos.y) / (double)2;
                if ((mx > r[0] && mx < r[2]) && (my > r[1] && my < r[3])) {
                    innerPos = true;
                    break;
                }
            }
            if (innerPos) continue;
            
            visited[nx][ny] = pos.m + 1;
            q.push({nx, ny, pos.m + 1});
        }
    }
    
    answer = visited[itemX][itemY];
    
    return answer;
}
