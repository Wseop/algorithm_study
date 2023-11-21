#include <string>
#include <vector>
#include <queue>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/118668
// BFS, dynamic programming

// dp[alp][cop] = 알고력, 코딩력을 습득하기까지 걸린 최소 시간
// 문제를 풀지 않고 그냥 1씩 올리는 경우를 problems에 추가하여 로직 단순화 -> line 33, 34
// 알고력과 코딩력은 150을 넘지 못하므로 이를 넘긴 경우 150으로 조정, dp index 에러 방지

const int INF = 987654321;

struct Power {
    int alp;
    int cop;
    int time;
};

int solution(int alp, int cop, vector<vector<int>> problems) {
    int answer = INF;
    int targetAlp = 0;
    int targetCop = 0;
    vector<vector<int>> dp(151, vector<int>(151, INF));
    queue<Power> q;
    
    for (const vector<int>& p : problems) {
        targetAlp = targetAlp < p[0] ? p[0] : targetAlp;
        targetCop = targetCop < p[1] ? p[1] : targetCop;
    }
    
    problems.push_back({0, 0, 1, 0, 1});
    problems.push_back({0, 0, 0, 1, 1});
    
    dp[alp][cop] = 0;
    q.push({alp, cop, 0});
    while (!q.empty()) {
        Power power = q.front();
        q.pop();
        
        for (const vector<int>& problem : problems) {
            if (power.alp < problem[0] || power.cop < problem[1])
                continue;
            
            int nAlp = power.alp + problem[2];
            int nCop = power.cop + problem[3];
            int nTime = power.time + problem[4];

            if (nAlp > 150)
                nAlp = 150;
            if (nCop > 150)
                nCop = 150;
            
            if (nAlp >= targetAlp && nCop >= targetCop) {
                answer = answer < nTime ? answer : nTime;
                continue;
            }
            
            if (dp[nAlp][nCop] <= nTime)
                continue;
            dp[nAlp][nCop] = nTime;
            q.push({nAlp, nCop, nTime});
        }
    }
    
    return answer;
}
