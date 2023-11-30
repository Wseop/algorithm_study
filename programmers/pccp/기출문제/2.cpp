#include <string>
#include <vector>
#include <queue>
#include <set>
#include <iostream>

using namespace std;

// https://school.programmers.co.kr/learn/courses/19344/lessons/242259
// BFS

// 석유의 영역마다 id를 부여하고 각 영역의 넓이를 저장하기 위한 2차원배열, 1차원배열을 각각 선언
// oil, oilArea

// land를 순회하다가 석유의 위치를 발견하면 그 위치에서 BFS 탐색 진행
// 연결되어 있는 석유 영역에 oilId를 할당하고, oilId의 넓이는 oilArea에 추가

int solution(vector<vector<int>> land) {
    int answer = 0;
    int di[4] = {0, 0, -1, 1};
    int dj[4] = {-1, 1, 0, 0};
    int n = land.size();
    int m = land[0].size();
    vector<vector<bool>> visited(500, vector<bool>(500, false));
    vector<vector<int>> oil(500, vector<int>(500, -1));
    vector<int> oilArea;
    int oilId = 0;
    
    for (int i = 0; i < land.size(); i++) {
        for (int j = 0; j < land[i].size(); j++) {
            if (land[i][j] == 1 && !visited[i][j]) {
                int area = 0;
                queue<pair<int, int>> q;
                
                oil[i][j] = oilId;
                visited[i][j] = true;
                area++;
                q.push({i, j});
                
                while (!q.empty()) {
                    pair<int, int> pos = q.front();
                    q.pop();
                    
                    for (int d = 0; d < 4; d++) {
                        pair<int, int> npos = {pos.first + di[d], pos.second + dj[d]};
                        
                        if (npos.first < 0 || npos.second < 0 || npos.first >= n || npos.second >= m) continue;
                        if (visited[npos.first][npos.second]) continue;
                        if (land[npos.first][npos.second] == 0) continue;
                        
                        oil[npos.first][npos.second] = oilId;
                        visited[npos.first][npos.second] = true;
                        area++;
                        q.push(npos);
                    }
                }
                oilArea.push_back(area);
                oilId++;
            } else if (land[i][j] == 0) {
                visited[i][j] = true;
            }
        }
    }
    
    
    for (int j = 0; j < m; j++) {
        set<int> oilIds;
        int areaSum = 0;
        
        for (int i = 0; i < n; i++) {
            if (oil[i][j] != -1) {
                oilIds.insert(oil[i][j]);
            }
        }
        
        for (int id : oilIds) {
            areaSum += oilArea[id];
        }
        
        answer = answer < areaSum ? areaSum : answer;
    }
    
    return answer;
}
