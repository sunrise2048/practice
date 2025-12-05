#include<bits/stdc++.h>
using namespace std;
using ll=long long;
template<typename Derived, typename UpdateType>
class Node {
public:
    Node() = default;

    Node(int l, int r): l(l), r(r) {
    }

    void Update(const UpdateType &update) {
        static_cast<Derived *>(this)->Update(update);
    }

    void PushUp(const Derived &lson, const Derived &rson) {
        static_cast<Derived *>(this)->PushUp(lson, rson);
    }

    void PushDown(Derived &lson, Derived &rson) {
        static_cast<Derived *>(this)->PushDown(lson, rson);
    }

    template<typename ValueType>
    ValueType Value() const {
        return static_cast<Derived *>(this)->Value();
    }

    int l, r;
};

template<typename Node, typename UpdateType>
class SegmentTree {
public:
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

    explicit SegmentTree(int n): n(n) {
        assert(n > 0);
        nodes.resize((n << 2) + 1);
        Build(1, n, 1);
    }

    void ModifySingle(int l, int r, int rt, int pos, const UpdateType &value) {
        assert(l <= pos);
        assert(pos <= r);
        if (l == r) {
            nodes[rt].Update(value);
            return;
        }
        nodes[rt].PushDown(nodes[rt << 1], nodes[rt << 1 | 1]);
        int m = (l + r) >> 1;
        if (pos <= m) {
            ModifySingle(lson, pos, value);
        } else {
            ModifySingle(rson, pos, value);
        }
        nodes[rt].PushUp(nodes[rt << 1], nodes[rt << 1 | 1]);
    }

    void ModifyRange(int l, int r, int rt, int nowl, int nowr, const UpdateType &value) {
        assert(l <= r);
        assert(nowl <= nowr);
        assert(!(nowl > r || l > nowr));
        if (nowl <= l && r <= nowr) {
            nodes[rt].Update(value);
            return;
        }
        nodes[rt].PushDown(nodes[rt << 1], nodes[rt << 1 | 1]);
        int m = (l + r) >> 1;
        if (nowl <= m) {
            ModifyRange(lson, nowl, nowr, value);
        }
        if (nowr > m) {
            ModifyRange(rson, nowl, nowr, value);
        }
        nodes[rt].PushUp(nodes[rt << 1], nodes[rt << 1 | 1]);
    }

    const Node &QuerySingle(int l, int r, int rt, int pos) {
        assert(l <= pos);
        assert(pos <= r);
        if (l == r) {
            return nodes[rt];
        }
        nodes[rt].PushDown(nodes[rt << 1].nodes[rt << 1 | 1]);
        int m = (l + r) >> 1;
        if (pos <= m) return QuerySingle(lson, pos);
        return QuerySingle(rson, pos);
    }

    template<typename QueryType>
    QueryType QueryRange(int l, int r, int rt, int nowl, int nowr,
                         function<QueryType(const QueryType &, const QueryType &)> f) {
        assert(l <= r);
        assert(nowl <= nowr);
        assert(!(nowl > r || l > nowr));
        if (nowl <= l && r <= nowr) {
            return nodes[rt].Value();
        }
        nodes[rt].PushDown(nodes[rt << 1], nodes[rt << 1 | 1]);
        int m = (l + r) >> 1;
        if (nowr <= m) return QueryRange(lson, nowl, nowr, f);
        if (nowl > m) return QueryRange(rson, nowl, nowr, f);
        return f(QueryRange(lson, nowl, nowr, f), QueryRange(rson, nowl, nowr, f));
    }

    vector<Node> nodes;
    int n;

private:
    void Build(int l, int r, int rt) {
        nodes[rt].l = l;
        nodes[rt].r = r;
        if (l == r) return;
        int m = (l + r) >> 1;
        Build(lson);
        Build(rson);
        nodes[rt].PushUp(nodes[rt << 1], nodes[rt << 1 | 1]);
    }
#undef lson
#undef rson
};


class SumNode : public Node<SumNode, long long> {
public:
    SumNode(): Node(), sum(0), col(0) {
    }

    void Update(long long x) {
        sum += x * (r - l + 1);
        col += x;
    }

    void PushUp(const SumNode &l, const SumNode &r) {
        sum = l.sum + r.sum;
    }

    void PushDown(SumNode &l, SumNode &r) {
        l.col += col;
        l.sum += col * (l.r - l.l + 1);
        r.col += col;
        r.sum += col * (r.r - r.l + 1);
        col = 0;
    }

    long long Value() const {
        return sum;
    }

    long long sum, col;
};
int main(){
    int n,m;
    cin>>n>>m;
    SegmentTree<SumNode,long long> sgt(n);
    for(int i=1;i<=n;++i){
        int a;
        cin>>a;
        sgt.ModifySingle(1,n,1,i,a);
    }
    while(m--){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            int val;
            cin>>val;
            sgt.ModifyRange(1,n,1,x,y,val);
        }
        else{
            cout<<sgt.QueryRange<long long>(1,n,1,x,y,[](const long long& x,const long long& y){
                return x+y;
            })<<'\n';
        }
    }
    return 0;
}