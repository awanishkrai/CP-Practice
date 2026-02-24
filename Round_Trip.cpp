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

void bfs(vector<vector<int>>& adj, int start, vector<int>& path, bool &found, vector<bool>& visited) {
    int n = adj.size();
    vector<int> parent(n, -1);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while(!q.empty() && !found) {
       
        int u = q.front(); q.pop();
         
        debug(u);
        for(int v : adj[u]) {
           
            if(!visited[v]) {
               cout<<v<<" ";
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
            else  if(parent[u] != v) {
                found = true;
                debug(found);
                int x = u;
                path.push_back(x);
                return;
            }
             
            
        }
        cout<<endl;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--; 
        adj[a].pb(b);
        adj[b].pb(a);
    }

    vector<bool> visited(n, false);
    vector<int> path;
    bool found = false;

    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            bfs(adj, i, path, found, visited);
            if(found) break; 
        }
    }

    if(found) {
        cout << path.size() << "\n";
        for(int node : path) cout << node + 1 << " ";
        cout << "\n";
    } else {
        cout << "IMPOSSIBLE\n";
    }
}

int32_t main() {
    fast_io;
    int T = 1;
    while(T--) solve();
    return 0;
}
