#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int mod=998244353;
int T;
int n,m;
vector<int> e[N];
int fa[N],si[N];
bool fl[N];
int ts[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
ll ksm(ll x,int y=mod-2){
    y=(y+mod-1)%(mod-1);
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
bool dfs(int no,int fa){
    if(no==n-1)return 1;
    for(int to:e[no]){
        if(to==fa)continue;
        bool nf=dfs(to,no);
        if(nf){
            if(no==n)fl[to]=1;
            return 1;
        }
    }
    return 0;
}
void dfs1(int no,int fa){
    ts[no]=1;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs1(to,no);
        ts[no]+=ts[to];
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;++i){
            fa[i]=i;
            si[i]=1;
            fl[i]=0;
            e[i].clear();
        }
        for(int i=1;i<=m;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
            if(u>v)swap(u,v);
            if(v==n)fl[u]=1;
            u=find(u),v=find(v);
            fa[v]=u;
            si[u]+=si[v];
        }
        int cn=0;
        ll s=1;
        for(int i=1;i<=n;++i){
            if(fa[i]==i){
                ++cn;
                s=s*si[i]%mod;
            }
        }
        if(find(n-1)==find(n)){
            for(int i=1;i<=n;++i)fl[i]=0;
            dfs(n,0);
            for(int i=1;i<n;++i){
                if(fl[i])cout<<s*ksm(n,cn-2)%mod<<' ';
                else cout<<"0 ";
            }
            cout<<'\n';
            continue;
        }
        dfs1(n,0);
        for(int i=1;i<n;++i){
            if(find(i)==find(n)&&!fl[i]){
                cout<<"0 ";
                continue;
            }
            if(find(i)==find(n)){
                cout<<ts[i]*ksm(si[find(n)])%mod*s%mod*ksm(n,cn-2)%mod<<' ';
                continue;
            }
            if(find(i)==find(n-1)){
                cout<<s*ksm(si[find(i)])%mod*ksm(si[find(n)])%mod*(si[find(i)]+si[find(n)])%mod*ksm(n,cn-3)%mod<<' ';
                continue;
            }
            cout<<si[find(i)]*ksm(si[find(i)]+si[find(n)])%mod*s%mod*ksm(si[find(i)])%mod*ksm(si[find(n)])%mod*(si[find(i)]+si[find(n)])%mod*ksm(n,cn-3)%mod<<' ';
        }
        cout<<'\n';
    }
    return 0;
}