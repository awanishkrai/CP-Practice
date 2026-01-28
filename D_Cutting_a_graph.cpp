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
struct DSU {
    vector<int> parent, size;

    void init(int v) {
        parent.assign(v, 0);
        iota(parent.begin(), parent.end(), 0);
        size.assign(v, 1);
    }

    int find(int a) {
        if (parent[a] == a) return a;
        return parent[a] = find(parent[a]);
    }

    bool merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b]; // ✅ fixed
        return true;
    }
};


void solve(){
    int n, m, t;
    cin >> n >> m >> t;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
    }

    vector<tuple<int, int, int>> query;
    for (int i = 0; i < t; i++) {
        string s;
        int a, b;
        cin >> s >> a >> b;
        if (s == "ask") {
            query.pb({0, a, b});
        } else {
            query.pb({1, a, b});
        }
    }

    DSU d;
    d.init(n + 1); // Assuming 1-based node labels

    vector<bool> p;
    for (int i = t - 1; i >= 0; i--) {
        int type = get<0>(query[i]);
        int a = get<1>(query[i]);
        int b = get<2>(query[i]);
        if (type == 0) {
            p.pb(d.find(a) == d.find(b));
        } else {
            d.merge(a, b);
        }
    }

    reverse(p.begin(), p.end());

    int idx = 0;
    for (int i = 0; i <p.size(); i++) {
    
            cout << (p[idx++] ? "YES" : "NO") << '\n';
    }
}


int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int T = 1;
    // cin >> T; // Uncomment if multiple test cases
    while (T--) {
        solve();
    }
    
    return 0;
}