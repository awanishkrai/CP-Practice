#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int LOG = 20;

vector<int> adj[MAXN];
int up[MAXN][LOG];
int depth[MAXN];
int countPaths[MAXN];

void dfs(int v, int p) {
    up[v][0] = p;
    for (int i = 1; i < LOG; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];

    for (int u : adj[v]) {
        if (u != p) {
            depth[u] = depth[v] + 1;
            dfs(u, v);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = LOG - 1; i >= 0; --i)
        if (depth[u] - (1 << i) >= depth[v])
            u = up[u][i];
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; --i)
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    return up[u][0];
}

void dfsCount(int v, int p) {
    for (int u : adj[v]) {
        if (u != p) {
            dfsCount(u, v);
            countPaths[v] += countPaths[u];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Tree edges
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Preprocess LCA
    depth[1] = 0;
    dfs(1, 1);

    // Path updates
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        int ancestor = lca(a, b);
        countPaths[a]++;
        countPaths[b]++;
        countPaths[ancestor]--;
        if (up[ancestor][0] != ancestor) // avoid subtracting from root's parent
            countPaths[up[ancestor][0]]--;
    }

    // Post DFS to accumulate counts
    dfsCount(1, 1);

    for (int i = 1; i <= n; ++i)
        cout << countPaths[i] << " ";
    cout << "\n";

    return 0;
}
