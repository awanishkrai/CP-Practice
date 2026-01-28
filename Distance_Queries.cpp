#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int LOG = 20;

vector<int> adj[MAXN];
int up[MAXN][LOG];  // Binary lifting table
int depth[MAXN];

void dfs(int v,int p){
    up[v][0]=p;
    for (int i = 1; i < LOG; i++) {
        if (up[v][i-1] != -1)
            up[v][i] = up[up[v][i-1]][i-1];
        else
            up[v][i] = -1;
    }

    for(int u:adj[v]){
        if (u!=p){
        depth[u]=depth[v]+1;
        dfs(u,v);
        }
        
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);
    for(int i=LOG-1;i>=0;i--){
        if(up[u][i] != -1 && depth[up[u][i]] >= depth[v]){
            u=up[u][i];
        }
    }
    for(int i=LOG-1;i>=0;i--){
        if(up[u][i] != -1 && up[u][i]!=up[v][i]){
            u=up[u][i];
            v=up[v][i];
        }
    }
return up[u][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    depth[1] = 0;
    dfs(1, -1);  // Rooted at node 1

    while (q--) {
        int a, b;
        cin >> a >> b;
        int ancestor = lca(a, b);
        int distance = depth[a] + depth[b] - 2 * depth[ancestor];
        cout << distance << '\n';
    }

    return 0;
}
