#include <string>
#include <vector>
#include <iostream>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/131129
// dynamic programming

// dp[n] : n점일때, 최소횟수이면서 최대 싱글 or 불을 기록
// 1 ~ 20 사이의 점수를 각각 싱글, 더블, 트리플한 것과 불을 포함한 모든 경우의 수 계산하며, 문제의 조건에 맞는 경우만 dp에 업데이트

const int INF = 987654321;

vector<int> solution(int target) {
    vector<int> answer;
    vector<pair<int, int>> dp(target + 1, {INF, 0});
    
    dp[0] = {0, 0};

    for (int i = 0; i < target; i++) {
        int count = dp[i].first;
        int sb = dp[i].second;
        
        for (int score = 1; score <= 20; score++) {
            if (i + score <= target) {
                if (dp[i + score].first > count + 1) {
                    dp[i + score] = {count + 1, sb + 1};
                } else if (dp[i + score].first == count + 1 && dp[i + score].second < sb + 1) {
                    dp[i + score] = {count + 1, sb + 1};
                }
            }
            
            if (i + score * 2 <= target) {
                if (dp[i + score * 2].first > count + 1) {
                    dp[i + score * 2] = {count + 1, sb};
                } else if (dp[i + score * 2].first == count + 1 && dp[i + score * 2].second < sb) {
                    dp[i + score * 2] = {count + 1, sb};
                }
            }
            
            if (i + score * 3 <= target) {
                if (dp[i + score * 3].first > count + 1) {
                    dp[i + score * 3] = {count + 1, sb};
                } else if (dp[i + score * 3].first == count + 1 && dp[i + score * 3].second < sb) {
                    dp[i + score * 3] = {count + 1, sb};
                }
            }
            
            if (i + 50 <= target) {
                if (dp[i + 50].first > count + 1) {
                    dp[i + 50] = {count + 1, sb + 1};
                } else if (dp[i + 50].first == count + 1 && dp[i + 50].second < sb + 1) {
                    dp[i + 50] = {count + 1, sb + 1};
                }
            }
        }
    }

    answer = {dp[target].first, dp[target].second};
    
    return answer;
}
