#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n;
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
        
        long long px, py, qx, qy;
        cin >> px >> py >> qx >> qy;
 
        long long dx = qx - px;
        long long dy = qy - py;
 
        long long squaredDist = dx * dx + dy * dy;
        int dist = (int)sqrt((double)squaredDist);
 
        if (x == 1) {
            int q;
            cin >> q;
            if (dist == q) {
                cout << "Yes" << endl;
            } else {
                cout << "NO" << endl;
            }
        } else {
            vector<int> d;
            d.push_back(dist);
 
            for (int i = 0; i < x; i++) {
                int s;
                cin >> s;
                d.push_back(s);
            }
 
            sort(d.begin(), d.end());
 
            int sum = 0;
            for (int i = 0; i < d.size() - 1; i++) {
                sum += d[i];
            }
            
            if(dist==0 && sum >= d[d.size()-1]) {
    cout << "Yes" << endl;
}
            else if (sum > d.back()) {
                cout << "Yes" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
