#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
ll k;
ll a[N],b[N];
struct oper{
    int val;
    int x,y;
    oper(int val,int x,int y):val(val),x(x),y(y){}
    bool operator<(const oper& ls)const{
        return val>ls.val;
    }
};
set<int> id;
priority_queue<oper> pq;
void ins(int no){
    if(!a[no])return;
    auto it=id.lower_bound(no);
    if (it==id.end()) it=id.begin();
    pq.emplace((n+*it-no)%n,no,*it);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while (T--) {
        cin>>n>>k;
        ll sum=0;
        for (int i=1;i<=n;++i) {
            cin>>a[i];
            sum+=a[i];
        }
        id.clear();
        for (int i=1;i<=n;++i) {
            cin>>b[i];
            if (b[i]) id.insert(i);
        }
        while (!pq.empty()) pq.pop();
        for (int i=1;i<=n;++i) {
            ins(i);
        }
        int nv=0;
        while (sum>k) {
            auto [tv,x,y]=pq.top();
            pq.pop();
            if (!a[x]) continue;
            if (!b[y]) {
                ins(x);
                continue;
            }
            nv=tv+1;
            int mi=min(a[x],b[y]);
            a[x]-=mi,b[y]-=mi;
            sum-=mi;
            if (!b[y]) id.erase(y);
            if (a[x]) ins(x);
        }
        cout<<nv<<'\n';
    }
    return 0;
}