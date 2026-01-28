#include <bits/stdc++.h>
using namespace std;

// DFS to compute fv (product_of_children) and hv (best_subtree_value)
void dfs(int v, int parent,
         const vector<vector<int>> &adj,
         vector<long long> &fv,  // product_of_children
         vector<long long> &hv)  // best_subtree_value
{
    long long product = 1; // fv = product of children's hv
    vector<pair<long double,int>> gain_ratios; // (gain, child)

    // 1. Visit children first (post-order DFS)
    for (int u : adj[v]) {
        if (u == parent) continue;
        dfs(u, v, adj, fv, hv);

        product *= hv[u]; // multiply child's best result
        long double gain = (long double)fv[u] / hv[u];
        gain_ratios.push_back({gain, u});
    }

    fv[v] = product; // store product_of_children for v

    // CASE 1: v stays alone
    long long best = product;

    // CASE 2: v + some children (star)
    sort(gain_ratios.rbegin(), gain_ratios.rend()); // sort descending by gain
    long long current = product;
    int s = 0;
    for (auto [gain, child] : gain_ratios) {
        current = current / hv[child] * fv[child]; // replace hv with fv
        s++; // added one child to component
        best = max(best, current * (s + 1)); // (s+1) = v + s children
    }

    // CASE 3: v + one child w + some grandchildren
    for (auto [gain, w] : gain_ratios) {
        long long current2 = product / hv[w] * fv[w];

        // collect grandchildren of w
        vector<pair<long double,int>> grand_ratios;
        for (int c : adj[w]) {
            if (c == v) continue; // avoid parent
            long double g2 = (long double)fv[c] / hv[c];
            grand_ratios.push_back({g2, c});
        }
        sort(grand_ratios.rbegin(), grand_ratios.rend());

        long long current3 = current2;
        int t = 0;
        for (auto [g2, c] : grand_ratios) {
            current3 = current3 / hv[c] * fv[c];
            t++;
            best = max(best, current3 * (t + 2)); // +2 = v + w
        }
    }

    hv[v] = best; // best result for subtree rooted at v
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--; // make 0-indexed
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<long long> fv(n), hv(n);
    dfs(0, -1, adj, fv, hv);

    cout << hv[0] << "\n"; // answer = best result at root
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
