#include <bits/stdc++.h>
using namespace std;

#define int long long
#define all(x) x.begin(), x.end()
#define mod_mul(a, b, m) ((a % m) * (b % m)) % m
#define fast_io ios::sync_with_stdio(false); cin.tie(NULL);

const int MOD = 1e9 + 7;

// Product mod function
int prod(vector<int> &v) {
    int res = 1;
    for (int x : v) {
        res *=x;
        res %= MOD;
    }
    return res;
}

// Check if number is divisible by k


// Count min operations to make product divisible by k
int min_ops(vector<int> &a, int k) {
    // Check if product is already divisible by k
    int has_k = 0;
    for (int x : a) {
        if (x % k == 0) {
            has_k = 1;
            break;
        }
    }
    if (has_k) return 0;

    int min_ops = INT_MAX;
    for (int x : a) {
        int ops = 0;
        int val = x;
        while (val % k != 0 && ops <= 10) { // Max 10 to avoid long loops
            val++;
            ops++;
        }
        if (val % k == 0)
            min_ops = min(min_ops, ops);
    }
    return min_ops;
}


void solve() {
    int t; cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (auto &x : a) cin >> x;

        cout << min_ops(a, k) << '\n';
    }
}

int32_t main() {
    fast_io;
    solve();
    return 0;
}
