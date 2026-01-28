#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int LOG = 17;

int n, q;
vector<int> g[MAXN];
int up[MAXN][LOG + 1], depthNode[MAXN];
int subSize[MAXN], cdParent[MAXN];
bool blocked[MAXN];
bool isWhite[MAXN];
multiset<int> best[MAXN];

void dfsLCA(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i <= LOG; i++) up[u][i] = up[up[u][i - 1]][i - 1];
    for (int v : g[u]) if (v != p) {
        depthNode[v] = depthNode[u] + 1;
        dfsLCA(v, u);
    }
}

int LCA(int a, int b) {
    if (depthNode[a] < depthNode[b]) swap(a, b);
    int diff = depthNode[a] - depthNode[b];
    for (int i = LOG; i >= 0; i--)
        if (diff & (1 << i)) a = up[a][i];
    if (a == b) return a;
    for (int i = LOG; i >= 0; i--)
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    return up[a][0];
}

int dist(int a, int b) {
    int l = LCA(a, b);
    return depthNode[a] + depthNode[b] - 2 * depthNode[l];
}

void dfsSize(int u, int p) {
    subSize[u] = 1;
    for (int v : g[u]) if (v != p && !blocked[v]) {
        dfsSize(v, u);
        subSize[u] += subSize[v];
    }
}

int findCentroid(int u, int p, int total) {
    for (int v : g[u]) if (v != p && !blocked[v])
        if (subSize[v] > total / 2)
            return findCentroid(v, u, total);
    return u;
}

void buildCD(int u, int p) {
    dfsSize(u, 0);
    int c = findCentroid(u, 0, subSize[u]);
    cdParent[c] = p;
    blocked[c] = true;
    for (int v : g[c]) if (!blocked[v]) buildCD(v, c);
}

void update(int u) {
    isWhite[u] = !isWhite[u];
    int cur = u;
    while (cur) {
        int d = dist(u, cur);
        if (isWhite[u])
            best[cur].insert(d);
        else {
            auto it = best[cur].find(d);
            if (it != best[cur].end()) best[cur].erase(it);
        }
        cur = cdParent[cur];
    }
}

int query(int u) {
    int res = INT_MAX, cur = u;
    while (cur) {
        if (!best[cur].empty())
            res = min(res, *best[cur].begin() + dist(u, cur));
        cur = cdParent[cur];
    }
    return res == INT_MAX ? -1 : res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    cin >> q;
    depthNode[1] = 0;
    dfsLCA(1, 0);
    buildCD(1, 0);

    while (q--) {
        int t, u;
        cin >> t >> u;
        if (t == 0) update(u);
        else cout << query(u) << "\n";
    }
}
