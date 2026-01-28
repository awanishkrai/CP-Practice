// Author: YourHandleHere
// Template: Codeforces Competitive Programming

#include <bits/stdc++.h>
using namespace std;

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

string s;  // Global string for DP
int dp[20][2][4];  // position, tight, non-zero count

// Digit DP
int countDigitDP(int pos, bool tight, int cnt) {
    if (cnt > 3) return 0;          // More than 3 non-zero digits
    if (pos == s.length()) return 1; // Valid number if length reached

    if (dp[pos][tight][cnt] != -1)
        return dp[pos][tight][cnt];

    int limit = tight ? s[pos] - '0' : 9;
    int ans = 0;

    for (int digit = 0; digit <= limit; digit++) {
        int newCnt = cnt + (digit != 0);
        bool newTight = tight && (digit == limit);
        ans += countDigitDP(pos + 1, newTight, newCnt);
    }

    return dp[pos][tight][cnt] = ans;
}

// Subtract one from a string number (like "1000" → "999")
string stringSubtractOne(string s) {
    int n = s.size();
    int i = n - 1;

    while (i >= 0 && s[i] == '0') {
        s[i] = '9';
        i--;
    }

    if (i >= 0) s[i]--;

    // Remove leading zero if any (e.g., "0999")
    if (s[0] == '0') s = s.substr(1);
    return s;
}

// Count valid numbers <= numStr
int countClassy(string numStr) {
    s = numStr;
    memset(dp, -1, sizeof(dp));
    return countDigitDP(0, 1, 0);
}

int32_t main() {
    fast_io;

    int T;
    cin >> T;
    while (T--) {
        string L, R;
        cin >> L >> R;

        int total = countClassy(R);
        string M = stringSubtractOne(L);
        int subtract = countClassy(M);
        cout << total - subtract << '\n';
    }

    return 0;
}
