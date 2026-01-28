#include<bits/stdc++.h>
using namespace std;

void solve() {
    int m;
    cin >> m;
    if(m%2 == 1) {
        cout << 0<< endl;
        return;
    }
    m=m/2;
   if(m%2==0){
    cout<<m/2-1<<endl;
   }
   else{
    cout<<m/2<<endl;
   }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    
        solve();
    
    
    return 0;
}
