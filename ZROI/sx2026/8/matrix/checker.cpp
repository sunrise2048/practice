// check.cpp
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static inline long long chebDist(int i, int j, int x, int y) {
    return max(llabs((long long)i - x), llabs((long long)j - y));
}

static vector<long long> buildA_bruteforce(int n, const vector<pair<int,int>>& pts) {
    int m = n + 2; // indices 0..n+1
    vector<long long> A(1LL * m * m, 0);
    for (auto [x, y] : pts) {
        for (int i = 0; i <= n + 1; i++) {
            for (int j = 0; j <= n + 1; j++) {
                A[1LL * i * m + j] += chebDist(i, j, x, y);
            }
        }
    }
    return A;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int T = inf.readInt();
    int id = inf.readInt();
    (void)id;

    for (int tc = 1; tc <= T; tc++) {
        int n = inf.readInt();
        int k = inf.readInt();
        vector<pair<int,int>> truth;
        truth.reserve(k);
        for (int i = 0; i < k; i++) {
            int x = inf.readInt();
            int y = inf.readInt();
            truth.push_back({x, y});
        }

        if (ouf.seekEof()) {
            quitf(_wa, "Test %d: output ended early, expected k and coordinates.", tc);
        }

        long long k2_ll = ouf.readLong();
        if (k2_ll < 1) {
            quitf(_wa, "Test %d: reported k=%lld, but k must be >= 1.", tc, k2_ll);
        }
        if (k2_ll > 1LL * n * n) {
            quitf(_wa, "Test %d: reported k=%lld exceeds n*n=%lld.", tc, k2_ll, 1LL*n*n);
        }
        int k2 = (int)k2_ll;

        vector<pair<int,int>> out;
        out.reserve(k2);

        // simple duplicate check with a flat boolean array
        vector<unsigned char> used(1ULL * n * n, 0);

        for (int i = 0; i < k2; i++) {
            int x = ouf.readInt();
            int y = ouf.readInt();
            if (!(1 <= x && x <= n && 1 <= y && y <= n)) {
                quitf(_wa, "Test %d: output point (%d,%d) out of range [1..%d].", tc, x, y, n);
            }
            long long idx = 1LL * (x - 1) * n + (y - 1); // 0..n*n-1
            if (used[(size_t)idx]) {
                quitf(_wa, "Test %d: duplicate output point (%d,%d).", tc, x, y);
            }
            used[(size_t)idx] = 1;
            out.push_back({x, y});
        }

        // Bruteforce compute and compare A (ONLY for small n/k)
        vector<long long> A_true = buildA_bruteforce(n, truth);
        vector<long long> A_out  = buildA_bruteforce(n, out);

        int m = n + 2;
        for (int i = 0; i <= n + 1; i++) {
            for (int j = 0; j <= n + 1; j++) {
                long long v1 = A_true[1LL * i * m + j];
                long long v2 = A_out [1LL * i * m + j];
                if (v1 != v2) {
                    quitf(_wa,
                          "Test %d: matrix mismatch at (%d,%d): expected %lld, got %lld.",
                          tc, i, j, v1, v2);
                }
            }
        }
    }

    ouf.skipBlanks();
    if (!ouf.seekEof()) {
        quitf(_wa, "Extra tokens in output after processing all tests.");
    }

    quitf(_ok, "All tests passed (bruteforce checker).");
}
