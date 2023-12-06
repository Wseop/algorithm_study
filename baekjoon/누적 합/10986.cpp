#include <bits/stdc++.h>

using namespace std;

// 누적합 개념
// S[i] = A[0] + A[1] + ... + A[i] 로 저장
// i ~ j 구간의 합 = S[j] - S[i - 1]

// 나머지의 합을 구하면 되므로 누적합의 나머지로 저장
// S[j] - S[i - 1] == 0이 되어야 하므로 누적합의 나머지가 같은 구간을 선택하는 방법의 갯수를 구하면 됨

long long comb(long long n) {
	return n * (n - 1) / 2;
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, M;
	vector<int> counts;
	long long sum = 0;
	long long answer = 0;

	cin >> N >> M;
	counts = vector<int>(M, 0);
	for (int i = 0; i < N; i++) {
		long long input;
		cin >> input;
		sum += input;
		counts[sum % M]++;
	}

	answer += counts[0];
	for (int i = 0; i < M; i++) {
		answer += comb(counts[i]);
	}

	cout << answer;

	return 0;
}
