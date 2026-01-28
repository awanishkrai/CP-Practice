#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int editCost(const string &s, int pos) {
    string docker = "docker";
    int cost = 0;
    for (int i = 0; i < 6; ++i)
        if (s[pos + i] != docker[i]) cost++;
    return cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n;
        cin >> n;

        int len = s.size();
        vector<int> costs;
        vector<int> positions;

        // All possible starting positions for "docker"
        for (int i = 0; i + 5 < len; ++i) {
            costs.push_back(editCost(s, i));
            positions.push_back(i);
        }

        int m = costs.size();
        vector<int> dp(m + 2, INF);
        dp[0] = 0;

        // DP: dp[k] = min cost to place k non-overlapping "docker"
        for (int i = 0; i < m; ++i) {
            int pos_i = positions[i];
            int cost_i = costs[i];
            for (int k = m; k >= 1; --k) {
                // Find previous "docker" that doesn't overlap
                for (int j = i - 1; j >= 0; --j) {
                    if (positions[j] + 5 < pos_i) {
                        dp[k] = min(dp[k], dp[k - 1] + cost_i);
                        break;
                    }
                }
                if (k == 1) dp[k] = min(dp[k], cost_i);
            }
        }

        // Prefix min to ensure dp[k] is non-increasing in cost
        for (int k = 1; k <= m; ++k) {
            dp[k] = min(dp[k], dp[k - 1] + 6);
        }

        // Count how many attendees accept each count k
        vector<int> delta(m + 5, 0);
        for (int i = 0; i < n; ++i) {
            int l, r;
            cin >> l >> r;
            l = min(l, m);
            r = min(r, m);
            if (l > r) continue;
            delta[l]++;
            delta[r + 1]--;
        }

        // Prefix sum to compute count of attendees satisfied by each k
        vector<int> count(m + 2, 0);
        int cur = 0, max_people = 0;
        for (int k = 0; k <= m; ++k) {
            cur += delta[k];
            count[k] = cur;
            max_people = max(max_people, cur);
        }

        // Find minimal cost for the max_people
        int answer = INF;
        for (int k = 0; k <= m; ++k) {
            if (count[k] == max_people) {
                answer = min(answer, dp[k]);
            }
        }

        cout << answer << '\n';
    }

    return 0;
}
