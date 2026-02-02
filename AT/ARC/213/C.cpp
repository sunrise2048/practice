#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const ll inf=1e16;
int T;
int n;
ll a[N];
vector<int> et[N],eu[N];
class FLOW{
public:
    int s,t;
    int cn_node;
    struct edge{
        int v,w,c;
        int ne;
    }e[N*20];
    int cn_edge;
    int head[N*2];
    ll d[N*2];
    bool inq[N*2];
    int lae[N*2];
    ll sum;
    void init(){
        s=1,t=2;
        sum=0;
        for(int i=1;i<=cn_node;++i){
            head[i]=0;
        }
        cn_node=2;
        cn_edge=1;
    }
    int add_node(){
        return ++cn_node;
    }
    void add(int u,int v,int w,int c){
        e[++cn_edge].v=v;
        e[cn_edge].w=w;
        e[cn_edge].c=c;
        e[cn_edge].ne=head[u];
        head[u]=cn_edge;
    }
    void adde(int u,int v,int w,int c){
        add(u,v,w,c);add(v,u,0,-c);
    }
    bool spfa(){
        memset(d,0x3f,sizeof(ll)*(cn_node+1));
        d[s]=0;
        queue<int> q;
        q.push(s);
        while(!q.empty()){
            int no=q.front();
            q.pop();
            inq[no]=0;
            for(int i=head[no];i;i=e[i].ne){
                if(e[i].w==0)continue;
                int to=e[i].v,tc=e[i].c;
                if(d[to]<=d[no]+tc)continue;
                d[to]=d[no]+tc;
                lae[to]=i;
                if(!inq[to]){
                    q.push(to);
                    inq[to]=1;
                }
            }
        }
        if(d[t]>=inf)return 0;
        int no=t;
        while(no!=s){
            int ne=lae[no];
            sum+=e[ne].c;
            e[ne].w--;
            e[ne^1].w++;
            no=e[ne^1].v;
        }
        return 1;
    }
    ll dinic(){
        int T=4;
        while(T--){
            if(!spfa())return -1;
        }
        return sum;
    }
}flow;
int cn_dfn;
int fat[N];
int sit[N];
int dfn[N];
int nfd[N];
int siu[N],zsu[N];
int col[N];
class SGT{
public:
    vector<pair<int,int>> t[N<<2];
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    vector<pair<int,int>> pushup(const vector<pair<int,int>>& x,const vector<pair<int,int>>& y){
        vector<pair<int,int>> ve;
        int idx=0,idy=0,ns=0;
        while(ns<4&&(idx!=x.size()||idy!=y.size())){
            if(idx==x.size()||(idy!=y.size()&&x[idx].first>y[idy].first)){
                bool fl=1;
                for(int i=0;i<ns;++i){
                    if(ve[i].second==y[idy].second){
                        fl=0;
                        break;
                    }
                }
                if(fl){
                    ve.push_back(y[idy]);
                    ns++;
                }
                ++idy;
            }
            else{
                bool fl=1;
                for(int i=0;i<ns;++i){
                    if(ve[i].second==x[idx].second){
                        fl=0;
                        break;
                    }
                }
                if(fl){
                    ve.push_back(x[idx]);
                    ns++;
                }
                ++idx;
            }
        }
        return ve;
    }
    void build(int l,int r,int k){
        if(l==r){
            t[k].clear();
            t[k].emplace_back(a[nfd[l]],0);
            return;
        }
        build(l,mid,ls);build(mid+1,r,rs);
        t[k]=pushup(t[ls],t[rs]);
    }
    void update(int l,int r,int k,int x,int d){
        if(l==r){
            t[k][0]={a[nfd[l]],d};
            return;
        }
        if(x<=mid)update(l,mid,ls,x,d);
        else update(mid+1,r,rs,x,d);
        t[k]=pushup(t[ls],t[rs]);
    }
    vector<pair<int,int>> query(int l,int r,int k,int x,int y){
        if(x<=l&&r<=y)return t[k];
        if(y<=mid)return query(l,mid,ls,x,y);
        if(x>mid)return query(mid+1,r,rs,x,y);
        return pushup(query(l,mid,ls,x,y),query(mid+1,r,rs,x,y));
    }
    void adde(int u,int l1,int r1,int l2=1,int r2=0){
        vector<pair<int,int>> ve;
        if(l1<=r1)ve=query(1,n,1,l1,r1);
        if(l2<=r2)ve=pushup(ve,query(1,n,1,l2,r2));
        for(auto [v,c]:ve){
            flow.adde(u,col[c],1,v);
        }
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
void dfs1(int no,int fa){
    sit[no]=1;
    fat[no]=fa;
    dfn[no]=++cn_dfn;
    nfd[cn_dfn]=no;
    for(int to:et[no]){
        if(to==fa)continue;
        dfs1(to,no);
        sit[no]+=sit[to];
    }
}
void dfs2(int no,int fa){
    siu[no]=1;
    zsu[no]=0;
    for(int to:eu[no]){
        if(to==fa)continue;
        dfs2(to,no);
        siu[no]+=siu[to];
        if(siu[zsu[no]]<siu[to])zsu[no]=to;
    }
}
void dfs_c(int no,int fa,int c){
    sgt.update(1,n,1,dfn[no],c);
    for(int to:eu[no]){
        if(to==fa)continue;
        dfs_c(to,no,c);
    }
}
ll ans[N];
void dfs3(int no,int fa){
    for(int to:eu[no]){
        if(to==fa||to==zsu[no])continue;
        dfs3(to,no);
        dfs_c(to,no,0);
    }
    if(zsu[no]){
        dfs3(zsu[no],no);
    }
    flow.init();
    if(fa){
        col[0]=flow.add_node();
        flow.adde(col[0],2,1,0);
    }
    if(zsu[no]){
        col[1]=flow.add_node();
        flow.adde(col[1],2,1,0);
    }
    int nc=1;
    for(int to:eu[no]){
        if(to==fa||to==zsu[no])continue;
        ++nc;
        col[nc]=flow.add_node();
        flow.adde(col[nc],2,1,0);
        dfs_c(to,no,nc);
    }
    for(int to:et[no]){
        int nd=flow.add_node();
        flow.adde(1,nd,1,0);
        if(to==fat[no]){
            sgt.adde(nd,1,dfn[no]-1,dfn[no]+sit[no],n);
        }
        else{
            sgt.adde(nd,dfn[to],dfn[to]+sit[to]-1);
        }
    }
    ans[no]=flow.dinic();
    for(int to:eu[no]){
        if(to==fa||to==zsu[no])continue;
        dfs_c(to,no,1);
    }
    sgt.update(1,n,1,dfn[no],1);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        cn_dfn=0;
        for(int i=1;i<=n;++i){
            et[i].clear();
            eu[i].clear();
        }
        for(int i=1;i<=n;++i)cin>>a[i];
        for(int i=1;i<n;++i){
            int u,v;
            cin>>u>>v;
            et[u].push_back(v);
            et[v].push_back(u);
        }
        for(int i=1;i<n;++i){
            int u,v;
            cin>>u>>v;
            eu[u].push_back(v);
            eu[v].push_back(u);
        }
        dfs1(1,0);
        sgt.build(1,n,1);
        dfs2(1,0);
        dfs3(1,0);
        for(int i=1;i<=n;++i){
            cout<<ans[i]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}