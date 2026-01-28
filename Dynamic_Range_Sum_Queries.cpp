#include <bits/stdc++.h>
using namespace std;


int prefsum(int ind, vector<int>& fenwick) {
    int sum = 0;
    while (ind > 0) {
        sum += fenwick[ind];
        ind -= (ind & -ind);
    }
    return sum;
}

void update(int ind, int v, vector<int>& fenwick, vector<int>& a) {
    int n = fenwick.size() - 1;
    int diff = v - a[ind];
    a[ind] = v;
    while (ind <= n) {
        fenwick[ind] += diff;
        ind += (ind & -ind);
    }
}

int r(int l, int r, vector<int>& fenwick) {
    return prefsum(r, fenwick) - prefsum(l - 1, fenwick);
}

void solve() {
    int n, q;
    cin >> n >> q;
    
    vector<int> a(n + 1), fenwick(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        int ind = i;
        int v = a[i];
        while (ind <= n) {
            fenwick[ind] += v;
            ind += (ind & -ind);
        }
    }

    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;
        if (x == 1) {
            update(y, z, fenwick, a);
        } else {
            cout << r(y, z, fenwick) << "\n";
        }
    }
}

int32_t main() {

    int T = 1;
    //cin>>T;
    while (T--) solve();
    return 0;
}
