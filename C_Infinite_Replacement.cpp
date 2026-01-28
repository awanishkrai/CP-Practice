#include<bits/stdc++.h>
using namespace std;
void solve(){
    string s;
    cin >> s;
    int n = s.size();
    int count=0;
    for(int i=0;i<n;i++){
        if(s[i]=='a'){
            count++;
        }
    }
    string k;
    cin >> k;
    int m = k.size();
    int count1=0;
    for(int i=0;i<m;i++){
        if(k[i]=='a'){
            count1++;
        }
    }
    if(count1==0){
        long long ans=pow(2,n);
        cout << ans << endl;
        return ;
    }
    else if(count1==m && count1==1){
        cout<<1<<endl;
    }
    else{
        cout<<-1 << endl;
        return ;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}