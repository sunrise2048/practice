#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1005;
int n;
struct edge{
    int u,v;
    edge()=default;
    edge(int u,int v):u(u),v(v){}
}e[2][N<<1];
int cnt[2];
bool fl[N];
vector<vector<int>> ve;
vector<int> d[2][N];
int cn;
int fa[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int getv(edge& e,int u){return e.u+e.v-u;}
void solve(){
    if(cn<=1)return;
    for(int i=1;i<=n;++i){
        d[0][i].clear();
        d[1][i].clear();
    }
    for(int op:{0,1}){
        for(int i=1;i<=cnt[op];++i){
            auto [u,v]=e[op][i];
            if(fl[u]||fl[v])continue;
            d[op][u].push_back(i);
            d[op][v].push_back(i);
        }
    }
    int no=0;
    for(int i=1;i<=n;++i){
        if(fl[i])continue;
        if(d[0][i].size()+d[1][i].size()<=3){
            no=i;
            break;
        }
    }
    if(d[0][no].size()+d[1][no].size()==2){
        fl[no]=1;
        --cn;
        solve();
        ve.push_back({d[0][no][0],d[1][no][0]});
        return;
    }
    int np=0;
    fl[no]=1;
    --cn;
    if(d[0][no].size()==2)np=1;
    int bc=++cnt[np^1];
    int ua=d[np][no][0],ub=d[np^1][no][0],uc=d[np^1][no][1];
    e[np^1][bc]=edge(getv(e[np^1][ub],no),getv(e[np^1][uc],no));
    solve();
    int id=0;
    for(int i=0;i<ve.size();++i){
        if(ve[i][np^1]==bc){id=i;break;}
    }
    iota(fa+1,fa+n+1,1);
    for(int i=0;i<ve.size();++i){
        if(id==i)continue;
        auto [u,v]=(i<id?e[np][ve[i][np]]:e[np^1][ve[i][np^1]]);
        fa[find(u)]=find(v);
    }
    if(find(getv(e[np][ua],no))!=find(getv(e[np^1][ub],no)))swap(ub,uc);
    ve[id][np^1]=uc;ve.insert(ve.begin()+id,{ua,ub});
    if(np)swap(ve[id][0],ve[id][1]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int op:{0,1}){
        cnt[op]=n-1;
        for(int i=1;i<n;++i)cin>>e[op][i].u>>e[op][i].v;
    }cn=n;
    solve();
    for(int op:{0,1}){
        for(auto x:ve)cout<<x[op]<<' ';
        cout<<'\n';
    }
    return 0;
}