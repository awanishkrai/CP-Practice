#include <bits/stdc++.h>
using namespace std;

int f(string &s){
    int v=0;
    for(char c:s) v+=c-'a'+1;
    return v;
}

int n,m,B;
vector<int> cst,val;
vector<vector<int>> block;
int ans=0;

void go(int i,int spend,int got,vector<int>&use){
    if(spend>B) return;
    if(i==n){ ans=max(ans,got); return; }
    go(i+1,spend,got,use);
    bool ok=true;
    for(int j:block[i]) if(use[j]){ ok=false; break; }
    if(ok && spend+cst[i]<=B){
        use[i]=1;
        go(i+1,spend+cst[i],got+val[i],use);
        use[i]=0;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    vector<string> s(n);
    for(int i=0;i<n;i++) cin>>s[i];
    cst.resize(n); val.resize(n);
    for(int i=0;i<n;i++) cin>>cst[i];
    for(int i=0;i<n;i++) val[i]=f(s[i]);
    unordered_map<string,int> id;
    for(int i=0;i<n;i++) id[s[i]]=i;
    block.assign(n,{});
    for(int k=0;k<m;k++){
        string a,b;cin>>a>>b;
        int u=id[a],v=id[b];
        block[u].push_back(v);
        block[v].push_back(u);
    }
    cin>>B;
    vector<int> use(n,0);
    go(0,0,0,use);
    cout<<ans<<"\n";
}
