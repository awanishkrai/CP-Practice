#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> edges(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    vector<int> values(n + 1);
    for (int i = 1; i <= n; i++) cin >> values[i];

    const int MAX_LOG = 20;
    vector<vector<int>> ancestor(MAX_LOG, vector<int>(n + 1));
    vector<int> depth(n + 1), enterTime(n + 1), exitTime(n + 1);
    int timer = 0;

    function<void(int,int)> prepareLCA = [&](int node, int parent) {
        enterTime[node] = ++timer;
        ancestor[0][node] = parent;
        for (int k = 1; k < MAX_LOG; k++)
            ancestor[k][node] = ancestor[k-1][node] ? ancestor[k-1][ancestor[k-1][node]] : 0;
        for (int child : edges[node])
            if (child != parent) {
                depth[child] = depth[node] + 1;
                prepareLCA(child, node);
            }
        exitTime[node] = ++timer;
    };

    prepareLCA(1, 0);

    auto isAncestor = [&](int u, int v) {
        return enterTime[u] <= enterTime[v] && exitTime[v] <= exitTime[u];
    };

    auto findLCA = [&](int a, int b) {
        if (a == 0) return b;
        if (b == 0) return a;
        if (isAncestor(a, b)) return a;
        if (isAncestor(b, a)) return b;
        for (int k = MAX_LOG - 1; k >= 0; k--) {
            int potential = ancestor[k][a];
            if (potential && !isAncestor(potential, b)) a = potential;
        }
        return ancestor[0][a];
    };

    unordered_map<int, vector<int>> valueGroups;
    for (int i = 1; i <= n; i++) valueGroups[values[i]].push_back(i);

    ll totalDistance = 0;
    unordered_map<int, vector<int>> virtualTree;

    for (auto &grp : valueGroups) {
        vector<int> groupNodes = grp.second;
        if (groupNodes.size() <= 1) continue;

        sort(groupNodes.begin(), groupNodes.end(), [&](int a,int b){ return enterTime[a] < enterTime[b]; });

        vector<int> stack;
        vector<int> allNodes = groupNodes;
        stack.push_back(groupNodes[0]);

        for (size_t i = 1; i < groupNodes.size(); i++) {
            int current = groupNodes[i];
            int lcaNode = findLCA(current, stack.back());
            if (lcaNode == stack.back()) {
                stack.push_back(current);
                continue;
            }
            while (stack.size() >= 2 && depth[stack[stack.size()-2]] >= depth[lcaNode]) {
                int childNode = stack.back(); stack.pop_back();
                int parentNode = stack.back();
                virtualTree[parentNode].push_back(childNode);
            }
            if (stack.back() != lcaNode) {
                int childNode = stack.back(); stack.pop_back();
                virtualTree[lcaNode].push_back(childNode);
                stack.push_back(lcaNode);
                allNodes.push_back(lcaNode);
            }
            stack.push_back(current);
        }

        while (stack.size() >= 2) {
            int childNode = stack.back(); stack.pop_back();
            int parentNode = stack.back();
            virtualTree[parentNode].push_back(childNode);
        }

        unordered_map<int,int> originalFlag;
        for (int x : groupNodes) originalFlag[x] = 1;

        int groupSize = (int)groupNodes.size();

        function<int(int)> calculateContribution = [&](int node) -> int {
            int count = originalFlag.count(node) ? originalFlag[node] : 0;
            for (int child : virtualTree[node]) {
                int subtreeCount = calculateContribution(child);
                ll edgeLength = depth[child] - depth[node];
                totalDistance += (ll)subtreeCount * (groupSize - subtreeCount) * edgeLength;
                count += subtreeCount;
            }
            return count;
        };

        unordered_set<int> hasParent;
        for (auto &kv : virtualTree) 
            for (int child : kv.second) hasParent.insert(child);

        int rootNode = allNodes[0];
        for (int x : allNodes) if (!hasParent.count(x)) { rootNode = x; break; }

        calculateContribution(rootNode);

        for (int x : allNodes) virtualTree.erase(x);
    }

    cout << totalDistance << "\n";
}
