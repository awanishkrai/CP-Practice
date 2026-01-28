#include <bits/stdc++.h>
using namespace std;

int dx[] = {0,1,0,-1}; // N,E,S,W
int dy[] = {1,0,-1,0};

int getDir(int cur, string t) {
    if(t=="left") return (cur+3)%4;
    if(t=="right") return (cur+1)%4;
    if(t=="straight") return cur;
    return (cur+2)%4; // back
}

bool check(vector<pair<string,int>> &v,int sx,int sy,int ex,int ey,int idx=-1,string rep="") {
    int dir=0; // north
    int x=sx,y=sy;
    for(int i=0;i<v.size();i++){
        string turn=v[i].first;
        int d=v[i].second;
        if(i==idx) turn=rep;
        dir=getDir(dir,turn);
        x+=dx[dir]*d;
        y+=dy[dir]*d;
    }
    return (x==ex && y==ey);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n;cin>>n;
    vector<pair<string,int>> v(n);
    for(int i=0;i<n;i++) cin>>v[i].first>>v[i].second;
    int sx,sy,ex,ey;
    cin>>sx>>sy;
    cin>>ex>>ey;
    
    vector<string> all={"left","right","straight","back"};
    
    for(int i=0;i<n;i++){
        string wrong=v[i].first;
        int d=v[i].second;
        for(string cand:all){
            if(cand==wrong) continue;
            if(check(v,sx,sy,ex,ey,i,cand)){
                cout<<"Yes\n";
                cout<<wrong<<" "<<d<<"\n";
                cout<<cand<<" "<<d<<"\n";
                return 0;
            }
        }
    }
    cout<<"No\n";
    return 0;
}
