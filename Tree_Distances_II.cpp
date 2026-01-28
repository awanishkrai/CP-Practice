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
vector<int>dp;
vector<int>sz;
vector<int>ans;
void dfs(vector<vector<int>>&adj,int v,int parent){
    sz[v]=1;
    for(int u:adj[v]){
        if(u==parent)continue;
        dfs(adj,u,v);
        sz[v]+=sz[u];
        dp[v]+=dp[u]+sz[u];
    }
}
void dfs_rerouting(vector<vector<int>>&adj,int v,int parent){
    int n=adj.size();
    
    for(int u:adj[v]){
        
        if(u==parent)continue;
        int dpu=dp[u];
        dp[u]=dp[v]-sz[u]+(n-sz[u]);
        ans[u]=dp[u];
        dfs_rerouting(adj,u,v);
        
        dp[u]=dpu;
    }
    
}

// vector<int> dp, sz, ans;

// void dfs(vector<vector<int>>& adj, int v, int parent) {
//     sz[v] = 1;
//     for (int u : adj[v]) {
//         if (u == parent) continue;
//         dfs(adj, u, v);
//         sz[v] += sz[u];
//         dp[v] += dp[u] + sz[u];
//     }
// }

// void dfs_rerouting(vector<vector<int>>& adj, int v, int parent) {
//     int n = adj.size();
//     for (int u : adj[v]) {
//         if (u == parent) continue;
//         int dpu = dp[u];
//         dp[u] = dp[v] - sz[u] + (n - sz[u]); // ✅ correct rerooting
//         ans[u] = dp[u];
//         dfs_rerouting(adj, u, v);
//         dp[u] = dpu; // restore
//     }
// }

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    dp.assign(n, 0);
    sz.assign(n, 0);
    ans.assign(n, 0);

    for (int i = 0; i < n - 1; i++) { // n-1 edges
        int l, k;
        cin >> l >> k;
        l--; k--;
        adj[l].push_back(k);
        adj[k].push_back(l);
    }

    dfs(adj, 0, -1);
    ans[0] = dp[0];
    dfs_rerouting(adj, 0, -1);

    for (int i = 0; i < n; i++) cout << ans[i] << " ";
    cout << "\n";
}




// void solve() {
//     int n;
//     cin >> n;
//     vector<vector<int>>adj(n);
//     dp.assign(n+1,0);
//     sz.assign(n+1,0);
//     ans.assign(n+1,0);
    
//     for(int i=0;i<n;i++){
//         int l, k;
//         cin>>l>>k;
//         l--;
//         k--;
//         adj[l].pb(k);
//         adj[k].pb(l);
//     }
//     dfs(adj,0,-1);
//         dfs_rerouting(adj,0,-1);
//         for(int i:ans){
//             cout<<i<<" "<<endl; 
//         }
// }

// Main
int32_t main() {
    fast_io;

    int T = 1;
    // cin >> T; // Uncomment if multiple test cases

    while (T--) {
        solve();
    }

    return 0;
}
