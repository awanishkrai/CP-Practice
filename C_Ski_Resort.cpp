#include<bits/stdc++.h>
using namespace std;

void solve() {
    int m, n, k;
    cin >> m >> n >> k;
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }

    long long sol = 0;
    long long count = 0;

    for(int i = 0; i < m; i++) {
        if(a[i] <= k) {
            count++;
        } else {
            if(count >= n) {
                sol += ((count - n + 1)*(count - n + 2))/2;
            }
            count = 0;
        }
    }

    if(count >= n) {
        sol += ((count - n + 1)*(count - n + 2))/2;
    }

    cout << sol << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
