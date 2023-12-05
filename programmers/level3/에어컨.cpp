#include <string>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/214289#fnref1
// dynamic programming

// 1. 에어컨 OFF -> 온도 변화
// 내부온도 < temperature 일 경우, dp[i + 1][내부온도 + 1]
// 내부온도 == temperature 일 경우, dp[i + 1][내부온도]
// 내부온도 > temperature 일 경우, dp[i + 1][내부온도 - 1]

// 2. 에어컨 ON -> 비용 증가, 온도 변화
// 내부온도가 t1, t2 범위내에 존재하도록 변화를 주어야 함, 온도 변화를 주는 경우와 유지만 하는 경우 각각 2가지씩 존재
// 내부온도 <= t1 일 경우, dp[i + 1][내부온도 + 1], 비용 + a,
// 내부온도 <= t1 일 경우, dp[i + 1][내부온도],     비용 + b,
// 내부온도 >= t2 일 경우, dp[i + 1][내부온도 - 1], 비용 + a,
// 내부온도 >= t2 일 경우, dp[i + 1][내부온도],     비용 + b

int solution(int temperature, int t1, int t2, int a, int b, vector<int> onboard) {
    int answer = 987654321;
    vector<vector<int>> dp(1000, vector<int>(51, 987654321));
    int n = 0;

    // 음수 범위를 양수 범위로 변환 (dp index에 mapping 시키기 위해)
    temperature += 10;
    t1 += 10;
    t2 += 10;
    dp[0][temperature] = 0;
    // 마지막 탑승 시각까지 온도를 맞췄으면 그 이후에는 그냥 꺼도 상관없음
    // 따라서, 마지막 탑승 시각까지만 탐색하도록 index 지정
    for (int i = 0; i < onboard.size(); i++) {
        if (onboard[i]) n = i;
    }
    n++;
    
    for (int i = 0; i < n - 1; i++) {
        for (int inside = 0; inside <= 50; inside++) {
            int curr = dp[i][inside];

            // 탑승해 있는 상태라면 내부온도가 조건에 맞아야 함
            if (onboard[i] && (inside < t1 || inside > t2)) continue;
            
            // 에어컨 off
            if (inside < temperature) {
                dp[i + 1][inside + 1] = min(dp[i + 1][inside + 1], curr);
            }
            if (inside == temperature) {
                dp[i + 1][inside] = min(dp[i + 1][inside], curr);
            }
            if (inside > temperature) {
                dp[i + 1][inside - 1] = min(dp[i + 1][inside - 1], curr);
            }
            // 에어컨 on
            if (inside <= t1) {
                dp[i + 1][inside + 1] = min(dp[i + 1][inside + 1], curr + a);
                dp[i + 1][inside] = min(dp[i + 1][inside], curr + b);
            }
            if (inside >= t2) {
                dp[i + 1][inside - 1] = min(dp[i + 1][inside - 1], curr + a);
                dp[i + 1][inside] = min(dp[i + 1][inside], curr + b);
            }
        }
    }
    
    for (int i = t1; i <= t2; i++) {
        answer = min(answer, dp[n - 1][i]);
    }
    
    return answer;
}
