#include <bits/stdc++.h>

using namespace std;

// 10의 배수의 갯수 구하기
// 10은 2 * 5로 구성되어 있으며, 2의 배수는 5보다 훨씬 많기 때문에 그냥 5의 배수를 구해주면 됨
// 25의 경우 5 * 5 이므로 한번 더 세줘야함
// 따라서, 5의 배수의 갯수, 25의 배수의 갯수, 125의 배수의 갯수를 더해주면 됨

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	int count = 0;

	cin >> n;

	count += n / 5;
	count += n / 25;
	count += n / 125;

	cout << count;

	return 0;
}
