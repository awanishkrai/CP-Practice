// Author: Awanish Rai (customized CP template)

#include <bits/stdc++.h>
using namespace std;

#define FAST ios_base::sync_with_stdio(false); cin.tie(0);
#define int long long
#define endl '\n'

// Custom utility functions
namespace Math {
    int gcd(int a, int b) {
        while (b) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    int lcm(int a, int b) {
        return a / gcd(a, b) * b;
    }
}

int count_with_small_primes(int n) {
    if (n <= 0) return 0;
    vector<int> bad_primes = {2, 3, 5, 7};
    int total = 0;

   
    for (int mask = 1; mask < (1 << bad_primes.size()); mask++) {
        int current_lcm = 1;
        int bits = __builtin_popcount(mask);
        bool overflow = false;

        for (int i = 0; i < bad_primes.size(); ++i) {
            if (mask & (1LL << i)) {
                current_lcm = Math::lcm(current_lcm, bad_primes[i]);
                if (current_lcm > n) {
                    overflow = true;
                    break;
                }
            }
        }

        if (!overflow) {
            if (bits % 2 == 1)
                total += (n / current_lcm);
            else
                total -= (n / current_lcm);
        }
    }

    return total;
}

// Counts the number of "good" integers from 1 to n
int count_good(int n) {
    return n - count_with_small_primes(n);
}

void process() {
    int l, r;
    cin >> l >> r;
    cout << count_good(r) - count_good(l - 1) << endl;
}

int32_t main() {
    FAST;
    int T;
    cin >> T;
    while (T--) {
        process();
    }
    return 0;
}
