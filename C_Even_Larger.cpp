#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    if (n % 2 == 0) { 
        a.push_back(0); // append a[n+1] = 0 for safety
        n++;
    }

    long long c = 0; // total operations

    for (int i = 1; i < n; i += 2) {
        // Step 1: bring neighbors <= a[i]
        if (a[i-1] > a[i]) {
            int k = a[i-1] - a[i];
            c += k;
            a[i-1] -= k;
        }
        if (i + 1 < n && a[i+1] > a[i]) {
            int k = a[i+1] - a[i];
            c += k;
            a[i+1] -= k;
        }

        // Step 2: ensure sum of neighbors <= a[i]
        if (i + 1 < n && (a[i-1] + a[i+1]) > a[i]) {
            int extra = (a[i-1] + a[i+1]) - a[i];

            // Prefer reducing larger neighbor first
            if (a[i-1] >= a[i+1]) {
                 int reduce_right = min(extra, a[i+1]);
                a[i+1] -= reduce_right;
                c += reduce_right;
               
                extra -= reduce_right;
            }
            if (extra > 0) {
                 int reduce_left = min(extra, a[i-1]);
                a[i-1] -= reduce_left;
                c += reduce_left;
               
            }
        }
    }

    cout << c << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--)
    solve();
    return 0;
}
