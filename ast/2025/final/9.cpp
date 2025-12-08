#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
const int mod=1e9+7;
int n,m;
struct edge{
    int u,v,w;
}e[N];
int fa[N];
ll er[N];
ll ans;
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
    iota(fa+1,fa+n+1,1);
    er[0]=1;
    for(int i=1;i<=m;++i){
        er[i]=er[i-1]*((mod+1)/2)%mod;
    }
    ans=1;
    for(int i=1;i<=m;++i){
        map<pair<int,int>,int> mp;
        int j=i;
        while(j!=m+1&&e[j].w==e[i].w){
            auto [tu,tv,asdad]=e[j];
            tu=find(tu),tv=find(tv);
            if(tu!=tv){
                mp[{min(tu,tv),max(tu,tv)}]++;
            }
            ++j;
        }
        for(auto [nv,cn]:mp){
            fa[nv.first]=nv.second;
            ans=ans*(1-er[cn]+mod)%mod;
        }
        i=j-1;
    }
    cout<<ans<<'\n';
    return 0;
}