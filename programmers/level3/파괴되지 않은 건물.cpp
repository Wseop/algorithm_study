#include <string>
#include <vector>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/92344
// 누적합

// 누적합 문제를 2차원 배열로 확장하여 적용하는 것이 핵심
// https://tech.kakao.com/2022/01/14/2022-kakao-recruitment-round-1/

// line 29~32
// (0, 0) ~ (2, 2) 범위일 경우
// [n, 0, 0, -n]
// [0, 0, 0, 0]
// [0, 0, 0, 0]
// [-n, 0, 0, n]

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int answer = 0;
    vector<vector<int>> sum(board.size() + 1, vector<int>(board[0].size() + 1, 0));
    
    for (const vector<int>& s : skill) {
        int type = s[0];
        int r1 = s[1], r2 = s[3];
        int c1 = s[2], c2 = s[4];
        int degree = type == 1 ? -s[5] : s[5];

        sum[r1][c1] += degree;
        sum[r1][c2 + 1] -= degree;
        sum[r2 + 1][c1] -= degree;
        sum[r2 + 1][c2 + 1] += degree;
    }
    
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            sum[i][j + 1] += sum[i][j];
        }
    }
    for (int j = 0; j < board[0].size(); j++) {
        for (int i = 0; i < board.size(); i++) {
            sum[i + 1][j] += sum[i][j];
        }
    }
    
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            board[i][j] += sum[i][j];
            if (board[i][j] >= 1) answer++;
        }
    }
    
    return answer;
}
