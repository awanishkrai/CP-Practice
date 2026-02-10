// Author: Awanish_Rai
// Template: Codeforces Competitive Programming

#include <bits/stdc++.h>
using namespace std;

#define fast_io ios::sync_with_stdio(false); cin.tie(NULL);
#define int long long

const int INF = 1e18;

// cord[i] = {x, {minY, maxY}}
vector<pair<int,pair<int,int>>> cord;

// dp[i][0] = min cost when ending at minY of cord[i]
// dp[i][1] = min cost when ending at maxY of cord[i]
int dp[200005][2];

// Recursive DP
int findMin(int i, int top){

    // base case: last group
    if(i == (int)cord.size() - 1)
        return 0;

    if(dp[i][top] != -1)
        return dp[i][top];

    int currX = cord[i].first;
    int nextX = cord[i+1].first;
    int currY = (top == 0 ? cord[i].second.first : cord[i].second.second);
    int nextLow = cord[i+1].second.first;
    int nextHigh = cord[i+1].second.second;
    int verticalSpan = nextHigh - nextLow;
    int horizontal = abs(nextX - currX);

    // Option 1: end at high of next group
    int goHigh = horizontal + abs(currY - nextHigh) + verticalSpan + findMin(i+1, 1);

    // Option 2: end at low of next group
    int goLow  = horizontal + abs(currY - nextLow)  + verticalSpan + findMin(i+1, 0);

    return dp[i][top] = min(goHigh, goLow);
}

// Solve function for each testcase
void solve() {
    int n, sx, sy, ex, ey;
    cin >> n >> sx >> sy >> ex >> ey;

    vector<int> x(n), y(n);
    for(int i = 0; i < n; i++)
        cin >> x[i];
    for(int i = 0; i < n; i++)
        cin >> y[i];

    // min-heap to sort by x
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    for(int i = 0; i < n; i++)
        pq.push({x[i], y[i]});
    

    // compress same x -> store minY, maxY
    map<int, pair<int,int>> mp;
    while(!pq.empty()){
        auto m = pq.top(); pq.pop();
        if(mp.find(m.first) == mp.end())
            mp[m.first] = {m.second, m.second};
        else {
            mp[m.first].first  = min(mp[m.first].first, m.second);
            mp[m.first].second = max(mp[m.first].second, m.second);
        }
    }

    // transfer to cord vector
    cord.clear();
    for(auto s : mp)
        cord.push_back({s.first, s.second});

    // reset dp
    memset(dp, -1, sizeof(dp));

    // find starting index
    int startIndex = 0;
    for(int i = 0; i < cord.size(); i++){
        if(cord[i].first == sx){
            startIndex = i;
            break;
        }
    }
    int start_v=sx-cord[startIndex].first;

    // start can be at lowY or highY
    int result = min(
        abs(start_v+sy - cord[startIndex].second.first)  + findMin(startIndex, 0),
        abs(start_v+sy - cord[startIndex].second.second) + findMin(startIndex, 1)
    );

    cout << result << "\n";
}

// Main
int32_t main(){
    fast_io;

    int T;
    cin >> T;
    while(T--)
        solve();

    return 0;
}
