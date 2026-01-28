#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    list<int> A;
    A.push_back(0); 
    auto it = A.begin(); 

    for(int i = 1; i <= n; i++) {
        if(s[i-1] == 'L') {
            it = A.insert(it, i); 
        } else { 
            it++;
            it = A.insert(it, i); 
        }
    }

    for(auto x : A) cout << x << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
