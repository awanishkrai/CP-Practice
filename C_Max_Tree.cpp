// Author: Awanish_Rai
// Template: Codeforces Competitive Programming

#include <bits/stdc++.h>
using namespace std;

// PBDS (optional, comment if not used)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Fast IO
#define fast_io ios::sync_with_stdio(false); cin.tie(NULL);

// Macros
#define int long long
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second

// Debugging
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

// Debug print helpers
void _print(int x) {cerr << x;}
void _print(string x) {cerr << '"' << x << '"';}
void _print(char x) {cerr << '\'' << x << '\'';}
void _print(bool x) {cerr << (x ? "true" : "false");}
template <class T, class V> void _print(pair<T, V> p) {cerr << "{"; _print(p.F); cerr << ","; _print(p.S); cerr << "}";}
template <class T> void _print(vector<T> v) {cerr << "["; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set<T> v) {cerr << "{"; for (T i : v) {_print(i); cerr << " ";} cerr << "}";}
template <class T, class V> void _print(map<T, V> v) {cerr << "{"; for (auto i : v) {_print(i); cerr << " ";} cerr << "}";}

// Constants
const int MOD = 1e9 + 7;
const int INF = 1e18;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// Modular arithmetic
int mod_add(int a, int b, int m = MOD) { return ((a % m + b % m + m) % m); }
int mod_sub(int a, int b, int m = MOD) { return ((a % m - b % m + m) % m); }
int mod_mul(int a, int b, int m = MOD) { return ((a % m) * (b % m)) % m; }
int mod_pow(int a, int b, int m = MOD) {
    int res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) res = mod_mul(res, a, m);
        a = mod_mul(a, a, m);
        b >>= 1;
    }
    return res;
}
int mod_inv(int a, int m = MOD) {
    return mod_pow(a, m - 2, m);
}

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> g(n+1);
    vector<int> in(n+1);
    for (int i = 0; i < n-1; i++) {
        int u,v; long long x,y;
        cin >> u >> v >> x >> y;
        if (x >= y) {
            g[u].push_back(v);
            in[v]++;
        } else {
            g[v].push_back(u);
            in[u]++;
        }
    }

    vector<int> res(n+1);
    int cur = n;
    vector<int> q;
    for (int i = 1; i <= n; i++) if (!in[i]) q.push_back(i);

    while (!q.empty()) {
        int u = q.back();
        q.pop_back();
        res[u] = cur--;
        for (int v : g[u]) {
            if (--in[v] == 0) q.push_back(v);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << ' ';
        cout << res[i];
    }
    cout << '\n';
}

// Main
int32_t main() {
    fast_io;

    int T = 1;
    cin >> T; // Uncomment if multiple test cases

    while (T--) {
        solve();
    }

    return 0;
}
