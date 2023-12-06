#include <bits/stdc++.h>

using namespace std;

// 2차원배열 누적합
// 행으로 더한뒤 열로 한번더 더함
// 구간합은 S[i][j] - S[i - k][j] - S[i][j - k] + s[i - k][j - k]

// 주어진 입력을 N * M 크기의 정상적인 체스판과 비교하여 뒤집어야하면 1, 아니면 0인 배열(sums)을 생성
// sums배열 누적합 계산한 뒤 k * k 범위에 맞는 최소 구간합을 출력

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, M, K;
	vector<string> board;
	vector<vector<int>> sums[2];
	int answer = 987654321;

	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		string input;
		cin >> input;
		board.push_back(input);
	}
	
	for (int i = 0; i < 2; i++) {
		sums[i] = vector<vector<int>>(N, vector<int>(M, 0));
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if ((i + j) & 1) {
				if (board[i][j] == 'B') {
					sums[0][i][j] = 1;
					sums[1][i][j] = 0;
				} else {
					sums[0][i][j] = 0;
					sums[1][i][j] = 1;
				}
			} else {
				if (board[i][j] == 'B') {
					sums[0][i][j] = 0;
					sums[1][i][j] = 1;
				} else {
					sums[0][i][j] = 1;
					sums[1][i][j] = 0;
				}
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 1; j < M; j++) {
			sums[0][i][j] += sums[0][i][j - 1];
			sums[1][i][j] += sums[1][i][j - 1];
		}
	}
	for (int j = 0; j < M; j++) {
		for (int i = 1; i < N; i++) {
			sums[0][i][j] += sums[0][i - 1][j];
			sums[1][i][j] += sums[1][i - 1][j];
		}
	}

	for (int s = 0; s < 2; s++) {
		for (int i = K - 1; i < N; i++) {
			for (int j = K - 1; j < M; j++) {
				int result = sums[s][i][j];
				if (i - K >= 0) result -= sums[s][i - K][j];
				if (j - K >= 0) result -= sums[s][i][j - K];
				if (i - K >= 0 && j - K >= 0) result += sums[s][i - K][j - K];
				answer = answer < result ? answer : result;
			}
		}
	}

	cout << answer;

	return 0;
}
