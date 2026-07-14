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
int check(int mid,int total){
  if((mid*3)+(mid-1)*2+4==total){
    return 0;
  }
    else if((mid*3)+(mid-1)*2+4>total){
        return 1;
    }
    else{
        return -1;
    }
}
// Solve function for each test case
void solve() {
    int m,n;
    cin >> n>>m;
    int total=n+2*m;
    int count=1;
    int left=total-4;
    if(left%3==0){
        count+=left/3;
        cout<<1<<" "<<count<<endl;
    }
    else{
    int offset=left/3;
    int res=-1;
    int l=0;
    int r=left;
    while(l<=r){
      int mid=(l+r)/2;
      int result=check(mid,total);
      if(result==0){
        res=mid;
        break;
      }
      else{
        if(result==1){
            r=mid-1;
        }
        else{
            l=mid+1;
        }
      }
    }
    if(res==-1){
        cout<<-1<<endl;
    }
    else{
        count+=(res-1);
        cout<<2<<" "<<count<<endl;
    }
}
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
