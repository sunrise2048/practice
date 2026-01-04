#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
int n,m,k;
int c[N];
bool flc[N];
int sus[N];
class BCJ{
public:
    int fa[N<<1];
    int si[N<<1];
    void init(){
        fill(si+1,si+2*n+1,1);
        iota(fa+1,fa+2*n+1,1);
    }
    vector<pair<int,int>> ve;
    int find(int x){return fa[x]==x?x:find(fa[x]);}
    void merge(int x,int y,bool fl=0){
        x=find(x),y=find(y);
        if(x==y)return;
        if(si[x]<si[y])swap(x,y);
        fa[y]=x;
        si[x]+=si[y];
        if(fl)ve.emplace_back(x,y);
    }
    void cx(){
        while(!ve.empty()){
            auto [x,y]=ve.back();
            ve.pop_back();
            fa[y]=y;
            si[x]-=si[y];
        }
    }
    bool ch(int no){
        return find(no)!=find(no+n);
    }
}bcj;
map<int,vector<pair<int,int>>> mp[N];
bool ch(vector<pair<int,int>>& ve){
    for(auto [x,y]:ve){
        bcj.merge(x,y+n,1);bcj.merge(x+n,y,1);
        if(!bcj.ch(x))return 0;
    }
    return 1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=n;++i){
        cin>>c[i];
    }
    bcj.init();
    for(int i=1;i<=k;++i){
        flc[i]=1;
    }
    for(int i=1;i<=m;++i){
        int u,v;
        cin>>u>>v;
        if(c[u]==c[v]){
            bcj.merge(u,v+n);
            bcj.merge(u+n,v);
        }
        else{
            if(c[u]>c[v])swap(u,v);
            mp[c[u]][c[v]].emplace_back(u,v);
        }
    }
    for(int i=1;i<=n;++i){
        if(!bcj.ch(i)){
            flc[c[i]]=0;
        }
    }
    for(int i=k;i;--i){
        sus[i]=sus[i+1]+flc[i];
    }
    ll ans=0;
    for(int c1=1;c1<=k;++c1){
        if(!flc[c1])continue;
        ans+=sus[c1+1];
        for(auto [c2,tv]:mp[c1]){
            if(!flc[c2])continue;
            if(!ch(tv))--ans;
            bcj.cx();
        }
    }
    cout<<ans<<'\n';
    return 0;
}