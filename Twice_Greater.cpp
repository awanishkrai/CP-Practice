// Author: Awanish_Rai
// Template: Codeforces Competitive Programming

#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define fast_io ios::sync_with_stdio(false); cin.tie(NULL);
#define int long long
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(int x){ cerr<<x; }
void _print(string x){ cerr<<'"'<<x<<'"'; }
void _print(char x){ cerr<<'\''<<x<<'\''; }
void _print(bool x){ cerr<<(x?"true":"false"); }
template<class T,class V> void _print(pair<T,V> p){ cerr<<"{"; _print(p.F); cerr<<","; _print(p.S); cerr<<"}"; }
template<class T> void _print(vector<T> v){ cerr<<"["; for(T i:v){ _print(i); cerr<<" "; } cerr<<"]"; }
template<class T> void _print(set<T> v){ cerr<<"{"; for(T i:v){ _print(i); cerr<<" "; } cerr<<"}"; }
template<class T,class V> void _print(map<T,V> v){ cerr<<"{"; for(auto i:v){ _print(i); cerr<<" "; } cerr<<"}"; }

const int MOD=998244353;

int n;
vector<int> a,dp,suf;

int go(int i){
    if(dp[i]!=-1)
        return dp[i];

    int j=upper_bound(all(a),2*a[i])-a.begin();

    int val=1;
    if(j<n)
        val=(val+suf[j])%MOD;

    return dp[i]=val;
}

void solve(){
    cin>>n;

    a.assign(n,0);
    for(int i=0;i<n;i++)
        cin>>a[i];

    dp.assign(n,-1);
    suf.assign(n+1,0);

    for(int i=n-1;i>=0;i--){
        go(i);
        suf[i]=(dp[i]+suf[i+1])%MOD;
    }

    int ans=0;
    for(int i=0;i<n;i++)
        ans=(ans+dp[i])%MOD;

    cout<<ans<<"\n";
}

int32_t main(){
    fast_io;

    int T=1;
    cin>>T;

    while(T--)
        solve();

    return 0;
}