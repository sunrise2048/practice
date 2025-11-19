#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n,q;
int c[N];
vector<int> e[N];
vector<int> t[N];
int d[N];
int bf[N][18];
int dfn[N],cn_dfn;
void dfs_init (int no,int fa) {
    d[no]=d[fa]+1;
    dfn[no]=++cn_dfn;
    bf[no][0]=fa;
    for (int i=1;i<18;++i) bf[no][i]=bf[bf[no][i-1]][i-1];
    for (int to:e[no]) {
        if (to==fa) continue;
        dfs_init(to,no);
    }
}
int lca (int x,int y) {
    if (d[x]<d[y]) swap(x,y);
    for (int i=17;i>=0;--i) {
        if (d[bf[x][i]]>=d[y]) x=bf[x][i];
    }
    if (x==y) return x;
    for (int i=17;i>=0;--i) {
        if (bf[x][i]!=bf[y][i]) x=bf[x][i],y=bf[y][i];
    }
    return bf[x][0];
}
int kth (int x,int k) {
    for (int i=17;i>=0;--i) {
        if (k&(1<<i)) x=bf[x][i];
    }
    return x;
}
class DFZ{
public:
    int de[N],nf[N];
    int dis[19][N];
    bool vis[N];
    int nn;
    int si[N],mxs[N];
    int rt;
    void find(int no,int fa){
        si[no]=1,mxs[no]=0;
        for(int to:e[no]){
            if(vis[to]||to==fa)continue;
            find(to,no);
            si[no]+=si[to];
            mxs[no]=max(mxs[no],si[to]);
        }
        mxs[no]=max(mxs[no],nn-si[no]);
        if(mxs[no]<=nn/2)rt=no;
    }
    void sol(int nrt,int fa){
        de[nrt]=de[fa]+1;
        vis[nrt]=1;
        nf[nrt]=fa;
        auto dfs=[&](auto self,int no,int fa)->void{
            si[no]=1;
            for(int to:e[no]){
                if(vis[to]||to==fa)continue;
                dis[de[nrt]][to]=dis[de[nrt]][no]+1;
                self(self,to,no);
                si[no]+=si[to];
            }
        };
        dfs(dfs,nrt,0);
        for(int to:e[nrt]){
            if(vis[to])continue;
            nn=si[to];
            rt=0;
            find(to,0);
            sol(rt,nrt);
        }
    }
    vector<pair<int,int>> v1[N],v2[N];
    void init(){
        memset(de,0,sizeof(de));
        memset(nf,0,sizeof(nf));
        memset(dis,0,sizeof(dis));
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;++i){
            v1[i].clear();v2[i].clear();
        }
        nn=n;
        mxs[0]=n+1;
        rt=0;
        find(1,0);
        sol(rt,0);
        /*for(int i=1;i<=n;++i){
            cout<<nf[i]<<' ';
        }cout<<'\n';*/
    }
    int qu(vector<pair<int,int>>& v,int d){
        int id=lower_bound(v.begin(),v.end(),make_pair(d+1,-1))-v.begin()-1;
        return (id==-1?0:v[id].second);
    }
    int query(int x,int d){
        int ans=qu(v1[x],d);
        for(int no=x,i=de[x]-1;i;no=nf[no],--i){
            ans+=qu(v1[nf[no]],d-dis[i][x]);
            ans+=qu(v2[no],d-dis[i][x]);
        }
        return ans;
    }
    void up(int x,int d,int op){
        //cout<<x<<' '<<d<<' '<<op<<'\n';
        v1[x].emplace_back(d,op);
        for(int no=x,i=de[x]-1;i;no=nf[no],--i){
            v1[nf[no]].emplace_back(dis[i][x]+d,op);
            v2[no].emplace_back(dis[i][x]+d,-op);
        }
    }
    void sort_v(){
        for(int i=1;i<=n;++i){
            sort(v1[i].begin(),v1[i].end());
            sort(v2[i].begin(),v2[i].end());
            for(int j=1;j<v1[i].size();++j)v1[i][j].second+=v1[i][j-1].second;
            for(int j=1;j<v2[i].size();++j)v2[i][j].second+=v2[i][j-1].second;
        }
    }
}dfz;
vector<int> e1[N];
int st[N],tr;
int nc;
int md[N];
int nf[N];
void dfs_c(int no){
    md[no]=(c[no]==nc?0:n+1);
    for(int to:e1[no]){
        nf[to]=no;
        dfs_c(to);
        md[no]=min(md[no],md[to]+d[to]-d[no]);
    }
}
void dfs_up(int no){
    dfz.up(no,md[no],1);
    for(int to:e1[no]){
        md[to]=min(md[to],md[no]+d[to]-d[no]);
        int ds=(md[no]+md[to]+d[to]-d[no])>>1;
        if(ds<md[to])dfz.up(to,md[to],-1);
        else if(ds>md[to]+d[to]-d[no])dfz.up(no,md[no],-1);
        else dfz.up(kth(to,ds-md[to]),ds,-1);
        dfs_up(to);
    }
    e1[no].clear();
}
void sol_col(int c){
    if(t[c].empty())return;
    sort(t[c].begin(),t[c].end(),[](const int& x,const int& y){
        return dfn[x]<dfn[y];
    });
    st[tr=1]=1;
    for(int no:t[c]){
        if(no==1)continue;
        int lc=lca(st[tr],no);
        while(dfn[st[tr-1]]>=dfn[lc]){
            e1[st[tr-1]].push_back(st[tr]);
            --tr;
        }
        if(st[tr]!=lc){
            e1[lc].push_back(st[tr]);
            st[tr]=lc;
        }
        st[++tr]=no;
    }
    while(tr>1){
        e1[st[tr-1]].push_back(st[tr]);
        --tr;
    }nc=c;
    dfs_c(1);
    dfs_up(1);
}
void solve(){
    memset(d,0,sizeof(d));
    memset(dfn,0,sizeof(dfn));
    memset(c,0,sizeof(c));
    scanf("%d",&n);
    for (int i=1;i<=n;++i) t[i].clear();
    for (int i=1;i<=(n<<1);++i) e[i].clear();
    for (int i=1;i<=n;++i) {
        scanf("%d",&c[i]);
        t[c[i]].push_back(i);
    }
    for (int i=1;i<n;++i) {
        int u,v;
        scanf("%d%d",&u,&v);
        e[u].push_back(n+i);
        e[n+i].push_back(u);
        e[v].push_back(n+i);
        e[n+i].push_back(v);
    }
    dfs_init(1,0);
    n=(n<<1)-1;
    dfz.init();
    for(int i=1;i<=n;++i)sol_col(i);
    dfz.sort_v();
    scanf("%d",&q);
    while(q--){
        int x,d;
        scanf("%d%d",&x,&d);
        d<<=1;
        printf("%d\n",dfz.query(x,d));
    }
}
int main(){
    freopen("sl.in","r",stdin);
    freopen("sl.out","w",stdout);
    scanf("%d",&T);
    scanf("%d",&T);
    while(T--){
        solve();
    }
    return 0;
}