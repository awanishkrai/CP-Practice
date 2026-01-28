#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fast_io ios::sync_with_stdio(false); cin.tie(NULL);

const int INF = 1e18;

void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n + 1);
    vector<int> d(n + 1, 0);

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
        d[a]++;
        d[b]++;
    }

    bool s = false;
    for (int i = 1; i <= n; i++) {
        if (d[i] == n - 1) {
            s = true;
            break;
        }
    }
    if (s) {
        cout << 0 << '\n';
        return;
    }

    vector<int> sz(n + 1);
    vector<int> l(n + 1);
    vector<int64_t> o(n + 1, 0);

    function<void(int,int)> f = [&](int u, int p) {
        sz[u] = 1;
        l[u] = (d[u] == 1);
        o[u] = 0;
        for (int x : g[u]) {
            if (x == p) continue;
            f(x, u);
            sz[u] += sz[x];
            l[u] += l[x];
            if (sz[x] > 1) o[u] += l[x];
        }
    };
    f(1, 0);

    int ans = INF;
    int64_t tl = l[1];

    for (int i = 1; i <= n; i++) {
        int v = o[i];
        if (i != 1) {
            int r = n - sz[i];
            if (r > 1) v += (tl - l[i]);
        }
        if (v < ans) ans = v;
    }
    cout << ans << '\n';
}

int32_t main() {
    fast_io;
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
