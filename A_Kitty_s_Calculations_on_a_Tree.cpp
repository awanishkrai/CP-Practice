#include <bits/stdc++.h>
using namespace std;

const unsigned long long MOD = 1000000007;
const int LIMIT = 200005;


vector<int> graph[LIMIT];
int parentNode[LIMIT], nodeDepth[LIMIT], firstVisit[LIMIT];


vector<int> eulerOrder;
int segTree[8 * LIMIT], segPos[8 * LIMIT];


int qParent[LIMIT * 4];
unsigned qDepth[LIMIT * 4];
unsigned long long qSum[LIMIT * 4], qWeighted[LIMIT * 4];
vector<int> qChildren[LIMIT * 4];
int qCount = 0;


void explore(int u, int depth) {
    nodeDepth[u] = depth;
    firstVisit[u] = (int)eulerOrder.size();
    eulerOrder.push_back(u);
    for (int v : graph[u]) {
        explore(v, depth + 1);
        eulerOrder.push_back(u);
    }
}


void createSeg(int idx, int l, int r) {
    if (l == r) {
        segTree[idx] = eulerOrder[l];
        segPos[idx] = l;
        return;
    }
    int mid = (l + r) / 2;
    createSeg(idx * 2, l, mid);
    createSeg(idx * 2 + 1, mid + 1, r);

    int left = segTree[idx * 2], right = segTree[idx * 2 + 1];
    if (nodeDepth[left] < nodeDepth[right]) {
        segTree[idx] = left;
        segPos[idx] = segPos[idx * 2];
    } else {
        segTree[idx] = right;
        segPos[idx] = segPos[idx * 2 + 1];
    }
}


int askSeg(int idx, int tl, int tr, int ql, int qr, int &ret) {
    if (tl == ql && tr == qr) {
        ret = segPos[idx];
        return segTree[idx];
    }
    int mid = (tl + tr) / 2;
    if (qr <= mid) return askSeg(idx * 2, tl, mid, ql, qr, ret);
    if (ql > mid) return askSeg(idx * 2 + 1, mid + 1, tr, ql, qr, ret);
    int li, ri;
    int A = askSeg(idx * 2, tl, mid, ql, mid, li);
    int B = askSeg(idx * 2 + 1, mid + 1, tr, mid + 1, qr, ri);
    if (nodeDepth[A] < nodeDepth[B]) {
        ret = li;
        return A;
    } else {
        ret = ri;
        return B;
    }
}


void prepareLCA(int root, int n) {
    eulerOrder.clear();
    explore(root, 0);
    createSeg(1, 0, (int)eulerOrder.size() - 1);
}


int findLCA(int a, int b) {
    int l = firstVisit[a], r = firstVisit[b];
    if (l > r) swap(l, r);
    int idx;
    return askSeg(1, 0, (int)eulerOrder.size() - 1, l, r, idx);
}


void orderNodes(vector<int> &v) {
    sort(v.begin(), v.end(), [](int a, int b) {
        return firstVisit[a] < firstVisit[b];
    });
}


int makeQNode(int base, unsigned depth) {
    ++qCount;
    qParent[qCount] = base;
    qDepth[qCount] = depth;
    qSum[qCount] = 0;
    qWeighted[qCount] = 0;
    qChildren[qCount].clear();
    return qCount;
}


void formQueryTree(vector<int>::iterator L, vector<int>::iterator R, int root) {
    if (L == R) return;
    if (R - L == 1) {
        int x = makeQNode(*L, nodeDepth[*L]);
        qChildren[root].push_back(x);
        return;
    }

    int l = firstVisit[*L];
    int r = firstVisit[*(R - 1)];
    int pos;
    int ancestor = askSeg(1, 0, (int)eulerOrder.size() - 1, l, r, pos);

    auto split = lower_bound(L, R, pos, [](int val, int id) {
        return firstVisit[val] < id;
    });

    int curr;
    if (qParent[root] == ancestor)
        curr = root;
    else {
        curr = makeQNode(ancestor, nodeDepth[ancestor]);
        qChildren[root].push_back(curr);
    }

    if (*split == ancestor) {
        formQueryTree(L, split, curr);
        int mid = makeQNode(ancestor, nodeDepth[ancestor]);
        qChildren[curr].push_back(mid);
        formQueryTree(split + 1, R, curr);
    } else {
        formQueryTree(L, split, curr);
        formQueryTree(split, R, curr);
    }
}


unsigned long long computeTree(int root) {
    if (qChildren[root].empty()) {
        qSum[root] = qParent[root];
        return 0;
    }

    vector<unsigned long long> resVal, sumVec, weightedVec;
    for (int child : qChildren[root]) {
        resVal.push_back(computeTree(child));
        sumVec.push_back(qSum[child]);
        unsigned long long delta = qDepth[child] - qDepth[root];
        weightedVec.push_back((qWeighted[child] + qSum[child] * delta) % MOD);
    }

    qSum[root] = 0;
    qWeighted[root] = 0;
    for (auto v : sumVec) qSum[root] = (qSum[root] + v) % MOD;
    for (auto v : weightedVec) qWeighted[root] = (qWeighted[root] + v) % MOD;

    unsigned long long ans = 0;
    for (auto v : resVal) ans = (ans + v) % MOD;
    for (int i = 0; i < (int)resVal.size(); ++i)
        ans = (ans + weightedVec[i] * ((qSum[root] - sumVec[i] + MOD) % MOD)) % MOD;

    return ans;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, queries;
    cin >> n >> queries;

    for (int i = 1; i <= n; ++i) graph[i].clear();

    
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    
    vector<int> stack = {1};
    parentNode[1] = -1;
    while (!stack.empty()) {
        int curr = stack.back();
        stack.pop_back();
        for (auto it = graph[curr].begin(); it != graph[curr].end();) {
            int nxt = *it;
            if (nxt == parentNode[curr]) {
                it = graph[curr].erase(it);
                continue;
            }
            parentNode[nxt] = curr;
            stack.push_back(nxt);
            ++it;
        }
    }

    prepareLCA(1, n);

    while (queries--) {
        int k;
        cin >> k;
        vector<int> arr(k);
        for (int i = 0; i < k; ++i) cin >> arr[i];

        orderNodes(arr);
        qCount = 0;
        int virtualRoot = makeQNode(0, 0);
        formQueryTree(arr.begin(), arr.end(), virtualRoot);
        virtualRoot = qChildren[virtualRoot][0];
        cout << computeTree(virtualRoot) << "\n";
    }

    return 0;
}
