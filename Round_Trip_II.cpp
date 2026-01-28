#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fast_io ios::sync_with_stdio(false); cin.tie(0);

int n;
vector<vector<int>> a;
vector<int> color;
vector<int> parent;
int c_start = -1, c_end = -1;

bool dfs(int v) {
    color[v] = 1;
    for (int u : a[v]) {
        if (color[u] == 0) {
            parent[u] = v;
            if (dfs(u)) return true;
        } else if (color[u] == 1 && parent[v] != u) {
            c_end = v;
            c_start = u;
            return true;
        }
    }
    color[v] = 2;
    return false;
}

void solve() {
    int m;
    cin >> n >> m;

    a.assign(n, vector<int>());
    color.assign(n, 0);
    parent.assign(n, -1);
    c_start = -1;

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        a[x].push_back(y);
        
    }

    vector<int> path;
    for (int i = 0; i < n; ++i) {
        if (color[i] == 0 && dfs(i)) {
            break;
        }
    }

    if (c_start == -1) {
        cout << "No cycle found\n";
        return;
    }

    path.push_back(c_start);
    for (int v = c_end; v != c_start; v = parent[v])
        path.push_back(v);
    path.push_back(c_start);
   
cout<<path.size()<<endl;
    for (int k : path)
        cout << k + 1 << " ";
    cout << '\n';
}

int32_t main() {
    fast_io;
    int T = 1;
    // cin >> T;
    while (T--) solve();
    return 0;
}
