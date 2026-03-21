#include <bits/stdc++.h>
#include "matrix.h"
using namespace std;

namespace {

int T, id;
int n, k;
vector<vector<long long>> A;
}

long long ask(int x, int y) {
	if (x < 0 || x > n + 1 || y < 0 || y > n + 1) {
		cout << "-1\n";
		exit(0);
	}
	return A[x][y];
}
int main() {
	freopen("ex_matrix1.in","r",stdin);
	freopen("matrix.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	for (cin >> T >> id; T; T--) {
		cin >> n >> k;
		A = vector<vector<long long>>(n + 2, vector<long long>(n + 2, 0));
		for (int i = 0; i < k; i++) {
			int x, y;
			cin >> x >> y;
			for (int p = 0; p <= n + 1; p++)
				for (int q = 0; q <= n + 1; q++) {
					A[p][q] += max(abs(p - x), abs(q - y));
				}
		}
		auto pos = solve(n, id);
		cout << pos.size() << "\n";
		for (int i = 0; i < (int)pos.size(); i++) {
			cout << pos[i].first << " " << pos[i].second << "\n";
		}
	}
}