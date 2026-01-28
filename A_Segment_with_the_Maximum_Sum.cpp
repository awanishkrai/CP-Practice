// Author: YourHandleHere
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


struct Node {
    int prefix;
    int suffix;
    int sum;
    int max_sum;
};

const int MAXN = 1e5 + 5;
Node t[4 * MAXN];
int a[MAXN];

Node merge(Node l, Node r) {
    Node res;
    res.sum = l.sum + r.sum;
    res.prefix = max(l.prefix, l.sum + r.prefix);
    res.suffix = max(r.suffix, r.sum + l.suffix);
    res.max_sum = max({l.max_sum, r.max_sum, l.suffix + r.prefix});
    return res;
}

void build(int node, int l, int r) {
    if (l == r) {
        int val = a[l];
        t[node] = {max(0LL, val), max(0LL, val), val, max(0LL, val)};
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    t[node] = merge(t[2 * node], t[2 * node + 1]);
}

void update(int node, int l, int r, int idx, int val) {
    if (l == r) {
        t[node] = {max(0LL, val), max(0LL, val), val, max(0LL, val)};
        return;
    }
    int mid = (l + r) / 2;
    if (idx <= mid) {
        update(2 * node, l, mid, idx, val);
    } else {
        update(2 * node + 1, mid + 1, r, idx, val);
    }
    t[node] = merge(t[2 * node], t[2 * node + 1]);
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    build(1, 0, n - 1);
    cout << t[1].max_sum << "\n";

    while (m--) {
        int i;
        int v;
        cin >> i >> v;
        a[i] = v; // update the array value
        update(1, 0, n - 1, i, v);
        cout << t[1].max_sum << "\n";
    }
}

int32_t main() {
    fast_io;
    int T = 1;
    while (T--) solve();
    return 0;
}
