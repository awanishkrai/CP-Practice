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
class dsu{
    public:
    vector<int> parent,size,mn,mx;
    dsu(int n){
        parent.resize(n+1);
        size.assign(n+1,1);
        mn.resize(n+1);
        mx.resize(n+1);
        iota(parent.begin(),parent.end(),0);
        iota(mn.begin(),mn.end(),0);
        iota(mx.begin(),mx.end(),0);
    }
        int find(int u){
            if(parent[u]==u)return u;
            return parent[u]=find(parent[u]);
        }
        void makeunion(int u,int v){
            u=find(u);
            v=find(v);
            if(u==v)return;
            if(size[u]<size[v])swap(u,v);
            parent[v]=u;
            size[u]+=size[v];
            mn[u]=min(mn[u],mn[v]);
            mx[u]=max(mx[u],mx[v]);
        }
       tuple<int,int,int>getinf(int x){
        x=find(x);
        return {mn[x],mx[x],size[x]};
       }
    };

// Solve function for each test case
void solve() {
    int n,query;
    cin >> n >>query;
    dsu d(n);
    vector<int> a(n);
    for(int i=0;i<query;i++){
        string s;
        int u,v,x;
        cin>>s;
        if(s=="union"){
            cin>>u>>v;
            d.makeunion(u,v);
        }
        else{
            cin>>x;
            
            auto[mn,mx,sz]=d.getinf(x);
            cout<<mn<<" "<<mx<<" "<<sz<<" "<<endl;
        }
    }

    
}

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
