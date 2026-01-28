#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string L, R;
ll dp[20][2][2][20][20];
int len;

ll recur(int pos, int tight_low, int tight_high, int left, int right, string &lo, string &hi, vector<int> &digits) {
    if (pos > right) return 1;

    if (dp[pos][tight_low][tight_high][left][right] != -1)
        return dp[pos][tight_low][tight_high][left][right];

    int lo_limit = tight_low ? (lo[pos] - '0') : 0;
    int hi_limit = tight_high ? (hi[pos] - '0') : 9;

    ll ans = 0;
    for (int d = lo_limit; d <= hi_limit; d++) {
        digits[pos] = digits[right - pos + left] = d;
        if (pos == right - pos + left && pos != right) continue; // already processed
        if (digits[pos] != digits[right - pos + left]) continue;

        int new_tight_low = tight_low && (d == lo_limit);
        int new_tight_high = tight_high && (d == hi_limit);
        ans += recur(pos + 1, new_tight_low, new_tight_high, left, right, lo, hi, digits);
    }

    return dp[pos][tight_low][tight_high][left][right] = ans;
}

ll count_palindromes(string lo, string hi) {
    ll total = 0;

    for (int length = lo.size(); length <= hi.size(); length++) {
        string lo_padded = string(length - lo.size(), '0') + lo;
        string hi_padded = string(length - hi.size(), '0') + hi;

        memset(dp, -1, sizeof(dp));
        vector<int> digits(length, 0);
        total += recur(0, 1, 1, 0, length - 1, lo_padded, hi_padded, digits);
    }

    return total;
}

string minus_one(string s) {
    int n = s.size();
    int i = n - 1;
    while (i >= 0 && s[i] == '0') {
        s[i] = '9';
        i--;
    }
    if (i >= 0) s[i]--;
    if (s[0] == '0') s = s.substr(1); // remove leading zero
    return s.empty() ? "0" : s;
}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        string i, j;
        cin >> i >> j;

        string i_minus_1 = minus_one(i);
        ll res = count_palindromes(i, j) - count_palindromes(i_minus_1, i_minus_1);
        cout << "Case " << tc << ": " << res << '\n';
    }
}
