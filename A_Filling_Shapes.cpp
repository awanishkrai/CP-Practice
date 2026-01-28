#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    if (n % 2 == 1) {
        cout << 0 << endl;
        return 0;
    }

    int dp[31] = {0};  // n <= 30 from Codeforces constraints
    dp[0] = 1;
    for (int i = 2; i <= n; i += 2) {
        dp[i] = dp[i - 2] * 3;
        for (int j = 0; j <= i - 4; j += 2) {
            dp[i] += dp[j] * 2;
        }
    }

    cout << dp[n] << endl;
    return 0;
}
