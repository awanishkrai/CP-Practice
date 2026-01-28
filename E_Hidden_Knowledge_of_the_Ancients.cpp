#include <bits/stdc++.h>
using namespace std;

long long countValidSubarrays(const vector<int>& nums, int maxDistinct, int minLen, int maxLen) {
    int n = nums.size();
    unordered_map<int, int> freqMap;
    long long total = 0;
    int left = 0;

    for (int right = 0; right < n; ++right) {
        freqMap[nums[right]]++;

        while ((int)freqMap.size() > maxDistinct) {
            freqMap[nums[left]]--;
            if (freqMap[nums[left]] == 0) freqMap.erase(nums[left]);
            ++left;
        }

        int validStart = max(left, right - maxLen + 1);
        int possibleStart = right - minLen + 1;
        if (validStart <= possibleStart) {
            total += possibleStart - validStart + 1;
        }
    }

    return total;
}

void processTestCase() {
    int n, k, l, r;
    cin >> n >> k >> l >> r;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];

    long long exactK = countValidSubarrays(arr, k, l, r) - countValidSubarrays(arr, k - 1, l, r);
    cout << exactK << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) processTestCase();

    return 0;
}
