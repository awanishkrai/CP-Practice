// Author: Awanish_Rai
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
bool isValid(vector<vector<char>>&labyrinth,int vi,int vj){
    if(labyrinth[vi][vj]!='#' && labyrinth[vi][vj]!='M')return true;
    return false;
}
void bfs(int ui,int uj,vector<vector<char>>&labyrinth,int n,int m){
    
    vector<vector<int>>moves={
        {0,1},
        {0,-1},
        {1,0},
        {-1,0}
    };
    bool found=false;
    
    queue<vector<int>>mq;
    vector<vector<int>>monsterDist(n,vector<int>(m,INT_MAX));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(labyrinth[i][j]=='M'){
                mq.push({0,i,j});
                monsterDist[i][j]=0;
            }
        }
    }
    while(!mq.empty()){
        auto tempNode=mq.front();
        mq.pop();
        int dis=tempNode[0];
        int i=tempNode[1];
        int j=tempNode[2];
        for(auto x:moves){
            int vi=i+x[0];
            int vj=j+x[1];
            if( vi>=0 && vi<n && vj>=0 && vj<m && isValid(labyrinth,vi,vj)){
                if(dis+1<monsterDist[vi][vj]){
                    monsterDist[vi][vj]=dis+1;
                    mq.push({dis+1,vi,vj});
                }
            }
        }
    }
    queue<vector<int>>pq;
    vector<vector<int>>dist(n,vector<int>(m,INT_MAX));
    vector<vector<pair<int ,int>>>parent(n,vector<pair<int,int>>(m,{-1,-1}));
    int endi=-1;
    int endj=-1;
    pq.push({0,ui,uj});
    dist[ui][uj]=0;
    while(!pq.empty()){
        auto node=pq.front();
        int dis=node[0];
        int i=node[1];
        int j=node[2];
        pq.pop();
        if(i==0 || i==labyrinth.size()-1 || j==0 || j==labyrinth[0].size()-1){
            cout<<"YES"<<endl;
            cout<<dis<<endl;
            found=true;
            endi=i;
            endj=j;
            break;
        }
        for(auto temp:moves){
            int vi=i+temp[0];
            int vj=j+temp[1];
            if(isValid(labyrinth,vi,vj)){
                if(dist[vi][vj]>dist[i][j]+1 && dist[i][j]+1<monsterDist[vi][vj]){
                    pq.push({dis+1,vi,vj});
                    dist[vi][vj]=dis+1;
                    parent[vi][vj]={i,j};
                }
            }
        }
    }
    if(found){
    string path="";
    
    while(labyrinth[endi][endj]!='A'){
        auto [tempi,tempj]=parent[endi][endj];
        if(tempi>endi){
            path+='U';
        } 
        else if(tempi<endi){
            path+='D';
        }
        else if(tempj>endj){
            path+='L';
        }
        else if(tempj<endj){
            path+='R';
        }
        endi=tempi;
        endj=tempj;
    }
    reverse(path.begin(),path.end());
    for(char c:path){
        cout<<c;
    }
}
else{
    cout<<"NO"<<endl;
}
}


// Solve function for each test case
void solve() {
    int n,m;
    cin>>n>>m;
    int starti=-1;
    int startj=-1;
    vector<vector<char>>labyrinth(n,vector<char>(m,'.'));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            char k='.';
            cin>>k;
            labyrinth[i][j]=k;
            if(k=='A'){
                starti=i;
                startj=j;
            }
        }
    }
    bfs(starti,startj,labyrinth,n,m);
    
}

// Main
int32_t main() {
    fast_io;

    int T = 1;
    // cin >> T; // Uncomment if multiple test cases

    while (T--) {
        solve();
    }

    return 0;
}
