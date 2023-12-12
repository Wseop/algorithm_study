#include <bits/stdc++.h>

using namespace std;

// 모든 i, j쌍에 대해서 최단 경로를 계산하는 문제
// 시작점이 i(1 <= i <= n)인 경우 가능한 모든 경로를 BFS로 탐색
// 현재 도시를 a, 다음 도시를 b라고 할 때, 현재까지 사용한 비용(c) + cost[a][b] < answer[i][b] 인 경우만 큐에 추가하면서 진행 (answer는 INF로 초기화)

const int INF = 987654321;

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	vector<vector<int>> adjacent;
	vector<vector<int>> cost;
	vector<vector<int>> answer;

	cin >> n >> m;
	adjacent = vector<vector<int>>(n + 1);
	cost = vector<vector<int>>(n + 1, vector<int>(n + 1, INF));
	answer = vector<vector<int>>(n + 1, vector<int>(n + 1, INF));
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		if (cost[a][b] > c) {
			cost[a][b] = c;
			adjacent[a].push_back(b);
		}
	}

	for (int i = 1; i <= n; i++) {
		queue<pair<int, int>> q;
		q.push({ i, 0 });

		while (!q.empty()) {
			int a = q.front().first;
			int c = q.front().second;
			q.pop();

			for (int b : adjacent[a]) {
				if (answer[i][b] > c + cost[a][b]) {
					answer[i][b] = c + cost[a][b];
					q.push({ b, c + cost[a][b] });
				}
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		answer[i][i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (answer[i][j] == INF) cout << 0 << " ";
			else cout << answer[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}
