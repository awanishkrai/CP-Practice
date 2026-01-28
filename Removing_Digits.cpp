#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int dp[1000001]; // up to 1e6

int min_steps(int n) {
    if (n == 0) return 0;
    if (dp[n] != -1) return dp[n];

    int ans = INF;
    int x = n;
    while (x > 0) {
        int d = x % 10;
        if (d > 0) {
            ans = min(ans, 1 + min_steps(n - d));
        }
        x /= 10;
    }

    return dp[n] = ans;
}

void solve() {
    int n;
    cin >> n;
    memset(dp, -1, sizeof(dp)); // initialize dp to -1
    cout << min_steps(n) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
    return 0;
}
