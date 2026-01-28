#include <bits/stdc++.h>
using namespace std;

struct dsu {
    vector<int> parent, sz;
    vector<long long> exp_add; // stored at root
    vector<long long> extra;   // offset from node to its parent/root

    dsu(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        exp_add.assign(n + 1, 0);
        extra.assign(n + 1, 0);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        int p = parent[x];
        parent[x] = find(parent[x]);
        extra[x] += extra[p]; // accumulate offset from old parent
        return parent[x];
    }

    void makeunion(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return;
        if (sz[u] < sz[v]) swap(u, v);
        // attach v under u
        parent[v] = u;
        // IMPORTANT: maintain absolute experiences:
        // For nodes in v-set old total = exp_add[v] + extra[node]
        // After attaching we want exp_add[u] + extra[v] + extra[node] == old total
        // so extra[v] = exp_add[v] - exp_add[u]
        extra[v] = exp_add[v] - exp_add[u];
        sz[u] += sz[v];
    }

    void add(int x, long long val) {
        x = find(x);
        exp_add[x] += val;
    }

    long long gex(int x) {
        int root = find(x);
        return exp_add[root] + extra[x];
    }
};

void solve() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return;
    dsu d(n);
    while (m--) {
        string cmd;
        cin >> cmd;
        if (cmd == "join") {
            int a, b; cin >> a >> b;
            d.makeunion(a, b);
        } else if (cmd == "add") {
            int a; long long v; cin >> a >> v;
            d.add(a, v);
        } else { // get
            int x; cin >> x;
            cout << d.gex(x) << '\n';
        }
    }
}

int main() {
    solve();
    return 0;
}
