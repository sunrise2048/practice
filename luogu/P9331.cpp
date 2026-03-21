#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n,q;
int L[N],R[N];
int d[N<<1];
int dl[N],dr[N];
vector<pair<int,int>> e[N<<1];
void adde(int u,int v,int w){
    e[v].emplace_back(u,w);
}
#define mid (l+r>>1)
int build_te(int l,int r){
    if(l==r)return l;
    adde(mid+n,build_te(l,mid),0);
    adde(mid+n,build_te(mid+1,r),0);
    return n+mid;
}
void build(int l,int r,int x,int y,int u){
    int k=(l==r?l:mid+n);
    if(x<=l&&r<=y){
        adde(u,k,1);
        return;
    }
    if(x<=mid)build(l,mid,x,y,u);
    if(y>mid)build(mid+1,r,x,y,u);
}
#undef mid
void build_e(){
    build_te(1,n);
    for(int i=1;i<=n;++i){
        build(1,n,L[i],R[i],i);
    }
}
bool fl[N<<1];
void dij(){
    memset(fl,0,sizeof(fl));
    priority_queue<pair<int,int>> pq;
    for(int i=1;i<(n<<1);++i){
        pq.emplace(-d[i],i);
    }
    while(!pq.empty()){
        auto [dn,no]=pq.top();
        pq.pop();
        if(fl[no])continue;
        fl[no]=1;
        dn=-dn;
        for(auto [to,tw]:e[no]){
            if(d[to]<=dn+tw)continue;
            d[to]=dn+tw;
            pq.emplace(-d[to],to);
        }
    }
}
const int inf=1e7;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>L[i]>>R[i];
    }
    build_e();
    memset(d,0x3f,sizeof(d));
    for(int i=1;i<=n;++i){
        if(L[i]==1)d[i]=1;
    }
    dij();
    for(int i=1;i<=n;++i)dl[i]=d[i];
    memset(d,0x3f,sizeof(d));
    for(int i=1;i<=n;++i){
        if(R[i]==n)d[i]=1;
    }
    dij();
    for(int i=1;i<=n;++i)dr[i]=d[i];
    memset(d,0x3f,sizeof(d));
    for(int i=1;i<=n;++i){
        d[i]=min(inf,dl[i]+dr[i]-1);
    }
    dij();
    cin>>q;
    while(q--){
        int x;
        cin>>x;
        cout<<(d[x]>=inf?-1:d[x])<<'\n';
    }
    return 0;
}