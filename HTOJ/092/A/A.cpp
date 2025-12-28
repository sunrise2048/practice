#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int T;
int n,m,q;
vector<int> E[N],e[N];
int cn_dfn;
int dfn[N],nfd[N],fa[N];
int a[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void dfs(int no,int fa){
    ::fa[no]=fa;
    dfn[no]=++cn_dfn;
    nfd[cn_dfn]=no;
    for(int to:e[no])dfs(to,no);
}
int lg[N];
int st_lc[20][N],st_a[20][N];
int get_mx(int x,int y){
    if(x==y)return x;
    x=dfn[x],y=dfn[y];
    if(x>y)swap(x,y);
    ++x;
    int k=lg[y-x+1];
    return max(st_lc[k][x],st_lc[k][y-(1<<k)+1]);
}
int get_mxa(int l,int r){
    if(l>=r)return 0;
    --r;
    int k=lg[r-l+1];
    return max(st_a[k][l],st_a[k][r-(1<<k)+1]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m>>q;
        for(int i=1;i<=n;++i){
            e[i].clear();E[i].clear();
        }
        for(int i=1;i<n;++i){
            int u,v;
            cin>>u>>v;
            E[u].push_back(v);
            E[v].push_back(u);
        }
        iota(fa+1,fa+n+1,1);
        for(int i=1;i<=n;++i){
            for(int to:E[i]){
                if(to>i)continue;
                to=find(to);
                e[i].push_back(to);
                fa[to]=i;
            }
        }
        cn_dfn=0;
        dfs(n,0);
        for(int i=2;i<=max(n,m);++i)lg[i]=lg[i>>1]+1;
        for(int i=1;i<=n;++i){
            st_lc[0][dfn[i]]=fa[i];
        }
        for(int j=1;j<20;++j){
            for(int i=1;i+(1<<j)-1<=n;++i){
                st_lc[j][i]=max(st_lc[j-1][i],st_lc[j-1][i+(1<<j-1)]);
            }
        }
        for(int i=1;i<=m;++i){
            cin>>a[i];
        }
        for(int i=1;i<m;++i){
            st_a[0][i]=get_mx(a[i],a[i+1]);
        }
        for(int j=1;j<20;++j){
            for(int i=1;i+(1<<j)-1<m;++i){
                st_a[j][i]=max(st_a[j-1][i],st_a[j-1][i+(1<<j-1)]);
            }
        }
        for(int i=1;i<=q;++i){
            int l,r,u;
            cin>>l>>r>>u;
            cout<<max(get_mxa(l,r),get_mx(a[l],u))<<'\n';
        }
    }
    return 0;
}