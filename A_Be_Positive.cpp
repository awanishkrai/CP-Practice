// Author: Refactored for clarity
#include <bits/stdc++.h>
using namespace std;

#define fast_io ios::sync_with_stdio(false); cin.tie(NULL);
#define int long long

int32_t main() {
    fast_io;

    int testCases;
    cin >> testCases;

    while (testCases--) {
        int elementCount;
        cin >> elementCount;

        vector<int> numbers(elementCount);
        for (int &x : numbers) cin >> x;

        sort(numbers.begin(), numbers.end());

        int maxDifference = 0;
        for (int idx = 0; idx + 1 < elementCount; idx += 2) {
            int currentDiff = abs(numbers[idx] - numbers[idx + 1]);
            if (currentDiff > maxDifference) {
                maxDifference = currentDiff;
            }
        }

        // Clear logic tree
        if (maxDifference == 0) {
            cout << 0 << "\n";   // All pairs are identical
        } else if (maxDifference == 1) {
            cout << 1 << "\n";   // Minimum non-zero difference
        } else {
            cout << maxDifference << "\n"; // Largest difference found
        }
    }

    return 0;
}
