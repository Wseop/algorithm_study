#include <string>
#include <vector>
using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/161988
// dynamic programming

// 변수 타입에 주의!
// dp[n] = max(dp[n - 1] + arr[n], arr[n])

long long solution(vector<int> sequence) {
    long long answer = 0;
    vector<int> arr1;
    vector<int> arr2;
    vector<long long> dp1(sequence.size(), 0);
    vector<long long> dp2(sequence.size(), 0);
    
    for (int i = 0; i < sequence.size(); i++) {
        int num = sequence[i];
        
        if (i & 1) {
            arr1.push_back(num);
            arr2.push_back(-num);
        } else {
            arr1.push_back(-num);
            arr2.push_back(num);
        }
    }
    dp1[0] = arr1[0];
    dp2[0] = arr2[0];
    answer = dp1[0] < dp2[0] ? dp2[0] : dp1[0];
    
    for (int i = 1; i < sequence.size(); i++) {
        dp1[i] = dp1[i - 1] + arr1[i] < arr1[i] ? arr1[i] : dp1[i - 1] + arr1[i];
        answer = answer < dp1[i] ? dp1[i] : answer;
        
        dp2[i] = dp2[i - 1] + arr2[i] < arr2[i] ? arr2[i] : dp2[i - 1] + arr2[i];
        answer = answer < dp2[i] ? dp2[i] : answer;
    }
    
    return answer;
}
