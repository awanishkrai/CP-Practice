#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int LOG = 17;

struct PSTNode {
    int left, right, freq;
} tree[40 * MAXN];

int roots[MAXN], nodeCounter = 0;
int n, q, values[MAXN], compressed[MAXN];
vector<int> graph[MAXN];
int up[MAXN][LOG + 1], depth[MAXN];

int build(int l, int r) {
    int id = ++nodeCounter;
    if (l == r) return id;
    int mid = (l + r) / 2;
    tree[id].left = build(l, mid);
    tree[id].right = build(mid + 1, r);
    return id;
}

int add(int prev, int l, int r, int pos) {
    int curr = ++nodeCounter;
    tree[curr] = tree[prev];
    tree[curr].freq++;
    if (l == r) return curr;
    int mid = (l + r) / 2;
    if (pos <= mid)
        tree[curr].left = add(tree[prev].left, l, mid, pos);
    else
        tree[curr].right = add(tree[prev].right, mid + 1, r, pos);
    return curr;
}

int query(int uRoot, int vRoot, int lcaRoot, int parentLcaRoot, int l, int r, int k) {
    if (l == r) return l;
    int leftCount = tree[tree[uRoot].left].freq + tree[tree[vRoot].left].freq
                    - tree[tree[lcaRoot].left].freq - tree[tree[parentLcaRoot].left].freq;
    int mid = (l + r) / 2;
    if (k <= leftCount)
        return query(tree[uRoot].left, tree[vRoot].left, tree[lcaRoot].left, tree[parentLcaRoot].left, l, mid, k);
    return query(tree[uRoot].right, tree[vRoot].right, tree[lcaRoot].right, tree[parentLcaRoot].right, mid + 1, r, k - leftCount);
}

void dfs(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i <= LOG; i++)
        up[u][i] = up[up[u][i - 1]][i - 1];
    roots[u] = add(roots[p], 1, n, compressed[u]);
    for (int v : graph[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = LOG; i >= 0; i--)
        if (depth[u] - (1 << i) >= depth[v]) u = up[u][i];
    if (u == v) return u;
    for (int i = LOG; i >= 0; i--)
        if (up[u][i] != up[v][i]) u = up[u][i], v = up[v][i];
    return up[u][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    vector<int> sortedValues;
    for (int i = 1; i <= n; i++) {
        cin >> values[i];
        sortedValues.push_back(values[i]);
    }

    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    sort(sortedValues.begin(), sortedValues.end());
    sortedValues.erase(unique(sortedValues.begin(), sortedValues.end()), sortedValues.end());

    for (int i = 1; i <= n; i++)
        compressed[i] = lower_bound(sortedValues.begin(), sortedValues.end(), values[i]) - sortedValues.begin() + 1;

    roots[0] = build(1, n);
    dfs(1, 0);

    while (q--) {
        int u, v, k; cin >> u >> v >> k;
        int anc = lca(u, v);
        int parentAnc = up[anc][0];
        int idx = query(roots[u], roots[v], roots[anc], roots[parentAnc], 1, n, k);
        cout << sortedValues[idx - 1] << "\n";
    }
    return 0;
}
