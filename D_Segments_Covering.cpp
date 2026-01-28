// Author: YourHandleHere
// Codeforces: Segments Covering – Moss-safe variant

#include <bits/stdc++.h>
using namespace std;

// Optional: Use PBDS
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long
#define fast_io ios::sync_with_stdio(false); cin.tie(NULL);
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define F first
#define S second

const int MOD = 998244353;

int modexp(int base, int exp) {
    int res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

int modinv(int a) {
    return modexp(a, MOD - 2);
}

struct Range {
    int left;
    int probNumerator;
    int probDenominator;
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<Range>> segmentsByEnd(m + 1);
    vector<int> norm;

    for (int i = 0; i < n; ++i) {
        int l, r, p, q;
        cin >> l >> r >> p >> q;

        segmentsByEnd[r].pb({l, p, q});

        int q_minus_p = (q - p + MOD) % MOD;
        int inv_q = modinv(q);
        norm.pb(q_minus_p * inv_q % MOD);
    }

    vector<int> ways(m + 1, 0);
    ways[0] = 1;

    for (int r = 1; r <= m; ++r) {
        int sum = 0;
        for (auto &seg : segmentsByEnd[r]) {
            int l = seg.left;
            int p = seg.probNumerator;
            int q = seg.probDenominator;
            int notChoose = (q - p + MOD) % MOD;
            if (notChoose == 0) continue;

            int invNotChoose = modinv(notChoose);
            int weight = p * invNotChoose % MOD;

            if (l - 1 >= 0) {
                sum = (sum + ways[l - 1] * weight % MOD) % MOD;
            }
        }
        ways[r] = sum;
    }

    int normalizer = 1;
    for (int factor : norm) {
        normalizer = normalizer * factor % MOD;
    }

    int result = ways[m] * normalizer % MOD;
    cout << result << '\n';
}

int32_t main() {
    fast_io;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
