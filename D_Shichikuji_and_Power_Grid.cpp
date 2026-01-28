#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 1e18;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector<pair<int, int>> pos(n);
    for (int i = 0; i < n; ++i) {
        cin >> pos[i].first >> pos[i].second;
    }

    vector<int> c(n); // cost to build power station
    for (int i = 0; i < n; ++i) cin >> c[i];

    vector<int> k(n); // connection coefficient
    for (int i = 0; i < n; ++i) cin >> k[i];

    vector<bool> used(n, false);
    vector<int> minCost(n, INF), from(n, -1);
    for (int i = 0; i < n; ++i) {
        minCost[i] = c[i];
        from[i] = -1; // -1 means connected to virtual node (build station)
    }

    int totalCost = 0;
    vector<int> powerStations;
    vector<pair<int, int>> connections;

    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (v == -1 || minCost[j] < minCost[v])) {
                v = j;
            }
        }

        used[v] = true;
        totalCost += minCost[v];

        if (from[v] == -1) {
            powerStations.push_back(v + 1);
        } else {
            connections.emplace_back(from[v] + 1, v + 1);
        }

        for (int u = 0; u < n; ++u) {
            if (!used[u]) {
                int dist = abs(pos[v].first - pos[u].first) + abs(pos[v].second - pos[u].second);
                int wireCost = dist * (k[v] + k[u]);
                if (wireCost < minCost[u]) {
                    minCost[u] = wireCost;
                    from[u] = v;
                }
            }
        }
    }

    // Output results
    cout << totalCost << "\n";
    cout << powerStations.size() << "\n";
    for (int x : powerStations) cout << x << " ";
    cout << "\n";
    cout << connections.size() << "\n";
    for (auto [a, b] : connections) cout << a << " " << b << "\n";

    return 0;
}
