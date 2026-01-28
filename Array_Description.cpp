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

// void solve() {
//     int n,m;
//     cin >> n>>m;
//     vector<int> a(n);
//     for (auto &x : a) cin >> x;

//     vector<vector<int>>dp;
//     dp.assign(n,vector<int>(m+1,0));  

//     if(a[0]!=0){
//         dp[0][a[0]]=1;
//     }
//     else{
//         for(int i=1;i<=m;i++){  
//             dp[0][i]=1;
//         }
//     }

//     for(int i=1;i<n;i++){       
//         for(int j=1;j<=m;j++){  
//             if(a[i]!=0 ){
//                 if(j==a[i]){
//                     long long val = dp[i-1][j];
//                     if(j-1 >= 1) val = (val + dp[i-1][j-1]) % 1000000007;
//                     if(j+1 <= m) val = (val + dp[i-1][j+1]) % 1000000007;
//                     dp[i][j] = val;
//                 }
//             }
//             else{
//                 long long val = dp[i-1][j];
//                 if(j-1 >= 1) val = (val + dp[i-1][j-1]) % 1000000007;
//                 if(j+1 <= m) val = (val + dp[i-1][j+1]) % 1000000007;
//                 dp[i][j] = val;
//             }
//         }
//     }

//     long long ans = 0;
//     for(int j=1;j<=m;j++){
//         ans = (ans + dp[n-1][j]) % 1000000007;
//     }
//     cout<<ans<<endl;
// }
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    vector<vector<int>> dp;
    dp.assign(n + 1, vector<int>(m + 1, 0));

    if (a[0] != 0) {
        dp[0][a[0]] = 1;
    } else {
        for (int j = 1; j <= m; j++) {
            dp[0][j] = 1;
        }
    }

    for (int i = 1; i < n; i++) { // ✅ changed <=n to <n to avoid a[i] out of range
        for (int j = 1; j <= m; j++) { // ✅ changed 0..m to 1..m to avoid j-1 or dp[...][0]

            if (a[i] != 0) {

                if (a[i] == m) { // ✅ was a[i] == n (wrong)
                    dp[i][a[i]] = (dp[i - 1][a[i]] + dp[i - 1][a[i] - 1]) % MOD;
                }
                else {
                    // ✅ replaced dp[i+1] with dp[i-1]
                    dp[i][a[i]] = (
                        dp[i - 1][a[i]] +
                        dp[i - 1][a[i] - 1] +
                        dp[i - 1][a[i] + 1]
                    ) % MOD;
                }
            }
            else {

                if (j == 1) { // ✅ was j == 0
                    dp[i][j] = (dp[i - 1][j] + dp[i - 1][j + 1]) % MOD;
                }
                else if (j == m) { // ✅ was j == n
                    dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % MOD;
                }
                else {
                    // ✅ removed dp[i+1], replaced with dp[i-1]
                    dp[i][j] = (
                        dp[i - 1][j] +
                        dp[i - 1][j - 1] +
                        dp[i - 1][j + 1]
                    ) % MOD;
                }
            }
        }
    }

    int ans = 0;
    for (int j = 1; j <= m; j++) {
        ans = (ans + dp[n - 1][j]) % MOD;
    }

    cout << ans << endl;
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
