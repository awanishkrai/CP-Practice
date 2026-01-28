#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;
    while (testCases--) {
        int productGinti, voucherGinti;
        cin >> productGinti >> voucherGinti;
        vector<int> products(productGinti), vouchers(voucherGinti);
        for (auto &product : products) cin >> product;
        for (auto &voucher : vouchers) cin >> voucher;

        sort(products.rbegin(), products.rend());
        sort(vouchers.begin(), vouchers.end());

        long long kulKharcha = 0;
        int sthiti = 0;

        for (int voucher : vouchers) {
            int remaining = productGinti - sthiti;
            if (remaining <= 0) break;

            int len = min(voucher, remaining);
            long long groupJod = 0;
            long long sabseSasta = LLONG_MAX;

            for (int i = 0; i < len; i++) {
                groupJod += products[sthiti];
                sabseSasta = min(sabseSasta, products[sthiti]);
                sthiti++;
            }

            if (len == voucher) 
                kulKharcha += (groupJod - sabseSasta);
            else 
                kulKharcha += groupJod;
        }

        while (sthiti < productGinti) kulKharcha += products[sthiti++];

        cout << kulKharcha << "\n";
    }

    return 0;
}
