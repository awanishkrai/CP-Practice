// Author: YourHandleHere
// Template: Codeforces Competitive Programming

#include <bits/stdc++.h>
using namespace std;

// PBDS (optional, comment if not used)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Fast IO
#define fast_io ios::sync_with_stdio(false); cin.tie(NULL);

// Macros
#define int long long
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second

// Debugging
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

// Debug print helpers
void _print(int x) {cerr << x;}
void _print(string x) {cerr << '"' << x << '"';}
void _print(char x) {cerr << '\'' << x << '\'';}
void _print(bool x) {cerr << (x ? "true" : "false");}
template <class T, class V> void _print(pair<T, V> p) {cerr << "{"; _print(p.F); cerr << ","; _print(p.S); cerr << "}";}
template <class T> void _print(vector<T> v) {cerr << "["; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set<T> v) {cerr << "{"; for (T i : v) {_print(i); cerr << " ";} cerr << "}";}
template <class T, class V> void _print(map<T, V> v) {cerr << "{"; for (auto i : v) {_print(i); cerr << " ";} cerr << "}";}

// Constants
const int MOD = 1e9 + 7;
const int INF = 1e18;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// Modular arithmetic
int mod_add(int a, int b, int m = MOD) { return ((a % m + b % m + m) % m); }
int mod_sub(int a, int b, int m = MOD) { return ((a % m - b % m + m) % m); }
int mod_mul(int a, int b, int m = MOD) { return ((a % m) * (b % m)) % m; }
int mod_pow(int a, int b, int m = MOD) {
    int res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) res = mod_mul(res, a, m);
        a = mod_mul(a, a, m);
        b >>= 1;
    }
    return res;
}
int mod_inv(int a, int m = MOD) {
    return mod_pow(a, m - 2, m);
}

int n, m;
vector<vector<int>> adj;
vector<pair<int, int>> path;
vector<char> ps;
pair<int, int> start;
pair<int, int> end1;


bool valid(int i, int j) {
    return (i >= 0 && j >= 0 && i < n && j < m && adj[i][j] != 0);
}

void bfs(int i, int j) {
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    map<pair<int, int>, pair<int, int>> parent;
    queue<pair<int, int>> q;
    q.push({i, j});
    visited[i][j] = true;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    char dir[] = {'U', 'D', 'R', 'L'};

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();

        if (x == end1.first && y == end1.second)
            break;

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (valid(nx, ny) && !visited[nx][ny]) {
                visited[nx][ny] = true;
                parent[{nx, ny}] = {x, y};
                q.push({nx, ny});
            }
        }
    }

    // Reconstruct path
    pair<int, int> curr = end1;
    if (!visited[end1.first][end1.second]) return;  // No path

    while (curr != start) {
        pair<int, int> prev = parent[curr];
        if (curr.first == prev.first + 1) ps.pb('D');
        else if (curr.first == prev.first - 1) ps.pb('U');
        else if (curr.second == prev.second + 1) ps.pb('R');
        else if (curr.second == prev.second - 1) ps.pb('L');
        curr = prev;
    }

    reverse(ps.begin(), ps.end());
}

void solve() {
    cin >> n >> m;
    adj.assign(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            if (c == '#') {
                adj[i][j] = 0;
            } else if (c == '.') {
                adj[i][j] = 1;
            } else if (c == 'A') {
                adj[i][j] = 1;
                start = {i, j};
            } else if (c == 'B') {
                adj[i][j] = 1;
                end1 = {i, j};
            }
        }
    }

    bfs(start.first, start.second);

    if (ps.empty()) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        cout << ps.size() << "\n";
        for (char ch : ps) cout << ch;
        cout << "\n";
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

