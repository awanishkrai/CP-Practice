#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        // Count frequency of each number
        unordered_map<int, int> freq;
        for (int x : a) freq[x]++;

        // Extract frequencies and sort
        vector<int> counts;
        for (auto &p : freq) counts.push_back(p.second);
        sort(counts.begin(), counts.end());

        int distinct = freq.size();
        int result = 0;

        // Calculate maximum product of frequency * distinct numbers
        for (int c : counts) {
            result = max(result, c * distinct);
            distinct--;
        }

        cout << result << "\n";
    }

    return 0;
}
