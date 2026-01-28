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
struct segment_tree{
    vector<int>tree;
    int n;
    segment_tree(vector<int>& arr, int k){
    n = k;
    tree.resize(4 * k);
    built(arr, 0, 0, k - 1);
}

    void built(vector<int>& arr,int node,int start,int end){
        if(start==end) {
            tree[node]=arr[start];
            return;
        }
        int mid=(start+end)/2;
        built(arr,2*node+1,start,mid);
        built(arr,2*node+2,mid+1,end);
        tree[node]=min(tree[2*node+1],tree[2*node+2]);
    }
    void update(int ind,int val,int node,int start,int end){
        if(start==end){
            tree[node]=val;
            return;
        }
        int mid=(start+end)/2;
        if(ind<=mid){
            update(ind,val,2*node+1,start,mid);
        }
        else{
            update(ind,val,2*node+2,mid+1,end);
        }
        tree[node]=min(tree[2*node+1],tree[2*node+2]);
    }
    int query(int l,int r,int node,int start,int end){
        if(r<start || l>end)return LLONG_MAX;
        if (l <= start && end <= r)return tree[node];
        int mid=(start+end)/2;
        int left=query(l,r,2*node+1,start,mid);
        int right=query(l,r,2*node+2,mid+1,end);
        return min(left,right);
    }
    void update(int ind,int val){
        update(ind,val,0,0,n-1);
    }
    int query(int l,int r){
        return query(l,r,0,0,n-1);
    }
    
};
void solve() {
    int n,m;
    cin >>n>>m;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    segment_tree st(a,n);
    for(int i=0;i<m;i++){
        int u,b,c;
        cin>>u>>b>>c;
        if(u==1){
            st.update(b,c);
        }
        else{
           cout<<st.query(b,c-1)<<endl;
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
