#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <queue>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>

class Random {
public:
    explicit Random(std::uint64_t seed) : rng(seed) {}

    int nextInt(int l, int r) {
        std::uniform_int_distribution<int> dist(l, r);
        return dist(rng);
    }

    bool nextBool() {
        return nextInt(0, 1) == 1;
    }

    template <class T>
    void shuffle(std::vector<T>& v) {
        std::shuffle(v.begin(), v.end(), rng);
    }

private:
    std::mt19937_64 rng;
};

struct Edge {
    int u;
    int v;
};

struct TestCase {
    int n;
    int m;
    int k;
    std::vector<int> color;
    std::vector<Edge> edges;
};

static std::uint64_t encodeEdge(int u, int v) {
    if (u > v) std::swap(u, v);
    return (static_cast<std::uint64_t>(u) << 32) ^ static_cast<std::uint64_t>(v);
}

static std::vector<int> partitionSum(Random& rnd, int total, int parts, int minValue) {
    std::vector<int> result(parts, minValue);
    int remaining = total - parts * minValue;
    for (int i = 0; i < parts; ++i) {
        int left = parts - i - 1;
        if (remaining == 0) break;
        int avg = remaining / (left + 1);
        int hi = std::min(remaining, std::max(0, avg * 3 + 5));
        int add = (i + 1 == parts ? remaining : rnd.nextInt(0, hi));
        result[i] += add;
        remaining -= add;
    }
    if (remaining > 0) result.back() += remaining;
    rnd.shuffle(result);
    return result;
}

static int chooseK(Random& rnd, int n) {
    int mode = rnd.nextInt(1, 100);
    if (mode <= 60) {
        return rnd.nextInt(1, std::min(n, 8));
    }
    if (mode <= 90) {
        return rnd.nextInt(1, std::min(n, 50));
    }
    return rnd.nextInt(1, std::min(n, 200));
}

static int chooseWalkLength(Random& rnd, int n, int k) {
    int base = std::max(1, std::min(250, 4 * n / std::max(1, k)));
    int mode = rnd.nextInt(1, 100);
    if (mode <= 70) {
        return rnd.nextInt(0, base);
    }
    if (mode <= 95) {
        return rnd.nextInt(0, std::min(1000, base * 3));
    }
    return rnd.nextInt(0, std::min(4000, base * 8));
}

static TestCase buildCase(Random& rnd, int n, int extraEdge) {
    TestCase tc;
    tc.n = n;
    tc.m = n - 1 + extraEdge;
    tc.k = chooseK(rnd, n);
    tc.color.assign(n + 1, 0);
    tc.edges.reserve(tc.m);

    std::vector<std::vector<int>> graph(n + 1);
    std::unordered_set<std::uint64_t> used;
    used.reserve(static_cast<std::size_t>(tc.m) * 2 + 10);

    for (int v = 2; v <= n; ++v) {
        int u = rnd.nextInt(1, v - 1);
        tc.edges.push_back({u, v});
        graph[u].push_back(v);
        graph[v].push_back(u);
        used.insert(encodeEdge(u, v));
    }

    while ((int)tc.edges.size() < tc.m) {
        int u = rnd.nextInt(1, n);
        int v = rnd.nextInt(1, n);
        if (u == v) continue;
        std::uint64_t code = encodeEdge(u, v);
        if (used.count(code)) continue;
        used.insert(code);
        tc.edges.push_back({u, v});
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int op = rnd.nextBool() ? 1 : 0;

    std::vector<int> parties(tc.k);
    std::iota(parties.begin(), parties.end(), 1);
    rnd.shuffle(parties);

    for (int id : parties) {
        int cur = rnd.nextInt(1, n);
        tc.color[cur] = id;
        int len = chooseWalkLength(rnd, n, tc.k);
        for (int step = 0; step < len; ++step) {
            const auto& adj = graph[cur];
            int to = adj[rnd.nextInt(0, static_cast<int>(adj.size()) - 1)];
            cur = to;
            tc.color[cur] = id;
        }
    }

    std::vector<int> seeds;
    seeds.reserve(n);
    for (int v = 1; v <= n; ++v) {
        if (tc.color[v] != 0) seeds.push_back(v);
    }
    rnd.shuffle(seeds);

    std::queue<int> q;
    for (int v : seeds) q.push(v);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graph[u]) {
            if (tc.color[v] == 0) {
                tc.color[v] = tc.color[u];
                q.push(v);
            }
        }
    }

    if (op == 1) {
        int maxChanges = std::max(1, std::min(n, n / 30 + 3));
        int changes = rnd.nextInt(1, maxChanges);
        std::vector<int> vertices(n);
        std::iota(vertices.begin(), vertices.end(), 1);
        rnd.shuffle(vertices);
        for (int i = 0; i < changes; ++i) {
            int v = vertices[i];
            int newColor = rnd.nextInt(1, tc.k);
            if (tc.k > 1) {
                while (newColor == tc.color[v]) {
                    newColor = rnd.nextInt(1, tc.k);
                }
            }
            tc.color[v] = newColor;
        }
    }

    return tc;
}

int main(int argc, char* argv[]) {
    freopen("1-1.in","w",stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::uint64_t seed;
    if (argc >= 2) {
        seed = std::stoull(argv[1]);
    } else {
        seed = static_cast<std::uint64_t>(
            std::chrono::steady_clock::now().time_since_epoch().count());
    }
    Random rnd(seed);

    const int totalN = rnd.nextInt(97000, 100000);
    const int T = rnd.nextInt(8, 25);

    std::vector<int> ns = partitionSum(rnd, totalN, T, 2);

    int extraBudget = 100000 - (totalN - T);
    std::vector<int> extra(T, 0);
    std::vector<int> candidates;
    candidates.reserve(T);
    for (int i = 0; i < T; ++i) {
        if (ns[i] >= 3) candidates.push_back(i);
    }
    rnd.shuffle(candidates);
    int totalExtraEdges = rnd.nextInt(0, std::min(static_cast<int>(candidates.size()), extraBudget));
    for (int i = 0; i < totalExtraEdges; ++i) {
        extra[candidates[i]] = 1;
    }

    std::vector<TestCase> tests;
    tests.reserve(T);

    int sumN = 0;
    int sumM = 0;
    int sumK = 0;
    for (int i = 0; i < T; ++i) {
        TestCase tc = buildCase(rnd, ns[i], extra[i]);
        sumN += tc.n;
        sumM += tc.m;
        sumK += tc.k;
        tests.push_back(std::move(tc));
    }

    std::cout << T << '\n';
    for (const auto& tc : tests) {
        std::cout << tc.n << ' ' << tc.m << ' ' << tc.k << '\n';
        for (int i = 1; i <= tc.n; ++i) {
            std::cout << tc.color[i] << (i == tc.n ? '\n' : ' ');
        }
        for (const auto& e : tc.edges) {
            std::cout << e.u << ' ' << e.v << '\n';
        }
    }

    std::cerr << "seed=" << seed
              << " T=" << T
              << " sumN=" << sumN
              << " sumM=" << sumM
              << " sumK=" << sumK
              << '\n';

    return 0;
}
