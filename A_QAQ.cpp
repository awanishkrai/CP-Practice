#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = s.length();

    vector<int> prefixQ(n, 0);  // Qs before or at i
    vector<int> suffixQ(n, 0);  // Qs after or at i

    // Fill prefix Q count
    prefixQ[0] = (s[0] == 'Q') ? 1 : 0;
    for (int i = 1; i < n; ++i)
        prefixQ[i] = prefixQ[i - 1] + (s[i] == 'Q' ? 1 : 0);

    // Fill suffix Q count
    suffixQ[n - 1] = (s[n - 1] == 'Q') ? 1 : 0;
    for (int i = n - 2; i >= 0; --i)
        suffixQ[i] = suffixQ[i + 1] + (s[i] == 'Q' ? 1 : 0);

    // Count QAQ
    int total = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'A') {
            int leftQ = (i > 0) ? prefixQ[i - 1] : 0;
            int rightQ = (i < n - 1) ? suffixQ[i + 1] : 0;
            total += leftQ * rightQ;
        }
    }

    cout << total << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T; // Uncomment for multiple test cases
    while (T--) {
        solve();
    }
    return 0;
}
