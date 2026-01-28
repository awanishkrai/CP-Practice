#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
const int64 MOD = 998244353;

int64 modinv(int64 a) {
    int64 res = 1, b = a, e = MOD-2;
    while (e) {
        if (e & 1) res = (__int128)res * b % MOD;
        b = (__int128)b * b % MOD;
        e >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<int> parent(N+1, 0);
    for (int i = 2; i <= N; ++i) cin >> parent[i];
    vector<int64> A(N+1);
    for (int i = 1; i <= N; ++i) cin >> A[i];
    vector<vector<int>> children(N+1);
    for (int i = 2; i <= N; ++i) children[parent[i]].push_back(i);
    vector<bool> leaf(N+1, false);
    for (int i = 1; i <= N; ++i) leaf[i] = children[i].empty();

    vector<int64> f(N+1, 0), prod(N+1, 1);
    vector<int> zero_cnt(N+1, 0);

    for (int v = N; v >= 1; --v) {
        if (leaf[v]) f[v] = A[v] % MOD;
        else {
            int64 p = 1; int z = 0;
            for (int c : children[v]) {
                if (f[c] == 0) z++;
                else p = (__int128)p * f[c] % MOD;
            }
            prod[v] = p;
            zero_cnt[v] = z;
            f[v] = (A[v] + (z ? 0 : p)) % MOD;
        }
    }

    while (Q--) {
        int v; int64 x;
        cin >> v >> x;
        x %= MOD;
        A[v] = x;

        int64 old_f = f[v];
        int64 new_f = leaf[v] ? A[v] : (A[v] + (zero_cnt[v] ? 0 : prod[v])) % MOD;
        if (old_f == new_f) {
            cout << f[1] << "\n";
            continue;
        }

        f[v] = new_f;
        int cur = v;

        while (parent[cur]) {
            int p = parent[cur];
            int64 old_c = old_f, new_c = new_f;

            if (old_c == 0 && new_c != 0) { zero_cnt[p]--; prod[p] = prod[p] * new_c % MOD; }
            else if (old_c != 0 && new_c == 0) { zero_cnt[p]++; prod[p] = prod[p] * modinv(old_c) % MOD; }
            else if (old_c != 0 && new_c != 0) prod[p] = prod[p] * new_c % MOD * modinv(old_c) % MOD;

            int64 old_fp = f[p];
            int64 new_fp = (A[p] + (zero_cnt[p] ? 0 : prod[p])) % MOD;
            if (new_fp == old_fp) break;

            f[p] = new_fp;
            cur = p; old_f = old_fp; new_f = new_fp;
        }

        cout << f[1] << "\n";
    }

    return 0;
}
