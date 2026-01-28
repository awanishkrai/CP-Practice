// Author: Awanish_Rai
// Template: Codeforces Competitive Programming

#include <bits/stdc++.h>
using namespace std;


void solve() {
    int length;
    cin >> length;
    string str;
    cin >> str;

    auto calculate_swaps = [&](char ch) -> long long {
        vector<int> positions;
        for (int i = 0; i < length; i++) {
            if (str[i] == ch) positions.push_back(i);
        }

        if (positions.empty()) return 0;

        int mid = positions.size() / 2;
        long long swaps = 0;
        long long center_pos = positions[mid];

        for (int i = 0; i < positions.size(); i++) {
            long long target_pos = center_pos - mid + i;
            swaps += abs(positions[i] - target_pos);
        }

        return swaps;
    };

    long long swaps_a = calculate_swaps('a');
    long long swaps_b = calculate_swaps('b');

    cout << min(swaps_a, swaps_b) << "\n";
}



int32_t main() {
    

    int T = 1;
     cin >> T; 
    while (T--) {
        solve();
    }

    return 0;
}
