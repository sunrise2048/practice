#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=505;
const int M=1e5+5;
const int inf=1e9+7;
int n,m,q;
struct edge{
    int u,v,w;
}e[M];
int l[M],r[M];
int fa[N];
map<int,ll> mk,mb;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        cin>>e[i].u>>e[i].v>>e[i].w;
    }
    sort(e+1,e+m+1,[](const edge& x,const edge& y){
        return x.w<y.w;
    });
    for(int i=1;i<=m;++i){
        l[i]=0;
        r[i]=inf;
    }
    for(int i=1;i<=m;++i){
        auto [u,v,w]=e[i];
        iota(fa+1,fa+n+1,1);
        for(int j=i-1;j;--j){
            auto [tu,tv,tw]=e[j];
            if(find(tu)==find(tv))continue;
            fa[find(tu)]=find(tv);
            if(find(u)==find(v)){
                l[i]=(w+tw+1)/2;
                r[j]=(w+tw+1)/2;
                break;
            }
        }
    }
    for(int i=1;i<=m;++i){
        mk[l[i]]--;
        mb[l[i]]+=e[i].w;
        mk[e[i].w]+=2;
        mb[e[i].w]-=2*e[i].w;
        mk[r[i]]--;
        mb[r[i]]+=e[i].w;
    }
    cin>>q;
    auto itk=mk.begin(),itb=mb.begin();
    ll sk=0,sb=0;
    while(q--){
        int x;
        cin>>x;
        while(itk!=mk.end()&&itk->first<=x){
            sk+=itk->second;
            ++itk;
        }
        while(itb!=mb.end()&&itb->first<=x){
            sb+=itb->second;
            ++itb;
        }
        cout<<sk*x+sb<<'\n';
    }
    return 0;
}