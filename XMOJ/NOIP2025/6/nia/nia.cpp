#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=805;
const int mod=1e9+7;
int n;
struct edge{
    int u,v,w;
}e[N];
vector<int> id[N];
vector<pair<int,int>> ed;
int te[N][N];
int fa[N];
ll jc[N*N],ny[N*N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
void init(int lim){
    jc[0]=1;
    for(int i=1;i<=lim;++i)jc[i]=jc[i-1]*i%mod;
    ny[lim]=ksm(jc[lim]);
    for(int i=lim;i;--i)ny[i-1]=ny[i]*i%mod;
}
ll A(int x,int y){
    return jc[x]*ny[x-y]%mod;
}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
ll an=1;
int main(){
    freopen("nia.in","r",stdin);
    freopen("nia.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<n;++i){
        scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    }
    sort(e+1,e+n,[](const edge& x,const edge& y){
        return x.w<y.w;
    });
    init(n*(n-1)/2);
    iota(fa+1,fa+n+1,1);
    for(int i=1;i<=n;++i)id[i].push_back(i);
    int nw=0;
    for(int i=1;i<n;++i){
        te[e[i].u][e[i].v]=te[e[i].v][e[i].u]=e[i].w;
        int u=find(e[i].u),v=find(e[i].v);
        if(e[i].w-nw-1>ed.size()){
            printf("0\n");
            exit(0);
        }
        an=an*A(ed.size(),e[i].w-nw-1)%mod;
        int cn=e[i].w-nw-1;
        while(cn--){
            ++nw;
            auto [tu,tv]=ed.back();
            ed.pop_back();
            te[tu][tv]=te[tv][tu]=nw;
        }
        ++nw;
        for(auto tu:id[u]){
            for(auto tv:id[v]){
                if(tu==e[i].u&&tv==e[i].v)continue;
                ed.emplace_back(tu,tv);
            }
        }
        while(!id[v].empty()){
            id[u].push_back(id[v].back());
            id[v].pop_back();
        }
        fa[v]=u;
    }
    an=an*A(ed.size(),ed.size())%mod;
    while(!ed.empty()){
        auto [tu,tv]=ed.back();
        ed.pop_back();
        ++nw;
        te[tu][tv]=te[tv][tu]=nw;
    }
    printf("%lld\n",an);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            printf("%d ",te[i][j]);
        }
        printf("\n");
    }
    return 0;
}