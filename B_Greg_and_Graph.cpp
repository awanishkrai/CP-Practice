#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;
typedef long long ll;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> adj[i][j];

    vector<int> del_order(n);
    for (int i = 0; i < n; ++i) {
        cin >> del_order[i];
        del_order[i]--; // make 0-based
    }

    vector<vector<ll>> dist(n, vector<ll>(n));
    // Initialize distances
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dist[i][j] = adj[i][j];

    vector<bool> added(n, false);
    vector<ll> ans;

    // reverse process
    for (int k = n - 1; k >= 0; --k) {
        int vk = del_order[k];
        added[vk] = true;

        // Floyd-Warshall update with new node vk
        for (int i = 0; i < n; ++i) {
            if (!added[i]) continue;
            for (int j = 0; j < n; ++j) {
                if (!added[j]) continue;
                dist[i][j] = min(dist[i][j], dist[i][vk] + dist[vk][j]);
            }
        }

        // Compute sum of shortest paths among added nodes
        ll total = 0;
        for (int i = 0; i < n; ++i)
            if (added[i])
                for (int j = 0; j < n; ++j)
                    if (added[j])
                        total += dist[i][j];

        ans.push_back(total);
    }

    // reverse answer to match original order
    for (int i = n - 1; i >= 0; --i)
        cout << ans[i] << " ";
    cout << endl;

    return 0;
}
