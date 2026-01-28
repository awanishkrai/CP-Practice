#include <bits/stdc++.h>
using namespace std;

double f(double x) {
    return x * x + sqrt(x);
}

int main() {
    double C;
    cin >> C;
    
    double l = 0.0, r = max(1.0, sqrt(C)) + 10.0; // safe upper bound
    for (int i = 0; i < 100; i++) { // 100 iterations ensure precision
        double mid = (l + r) / 2.0;
        if (f(mid) > C) {
            r = mid;
        } else {
            l = mid;
        }
    }
    
    cout << fixed << setprecision(10) << l << "\n";
    return 0;
}
