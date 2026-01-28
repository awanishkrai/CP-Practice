#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fast_io ios::sync_with_stdio(false); cin.tie(NULL);

int32_t main() {
    fast_io;

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> groups(n);
        vector<int> freq(m + 1, 0);

        // Input and frequency counting
        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;
            groups[i].resize(k);
            for (int j = 0; j < k; j++) {
                cin >> groups[i][j];
                freq[groups[i][j]]++;
            }
        }

        // Check if every number from 1..m is covered
        bool fullyCovered = true;
        for (int x = 1; x <= m; x++) {
            if (freq[x] == 0) {
                fullyCovered = false;
                break;
            }
        }
        if (!fullyCovered) {
            cout << "NO\n";
            continue;
        }

        int redundantCount = 0;
        for (auto &g : groups) {
            bool hasUnique = false;
            for (int val : g) {
                if (freq[val] == 1) { // unique element
                    hasUnique = true;
                    break;
                }
            }
            if (!hasUnique) redundantCount++;
        }

        cout << (redundantCount >= 2 ? "YES\n" : "NO\n");
    }

    return 0;
}
