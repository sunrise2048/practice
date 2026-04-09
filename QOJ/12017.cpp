#include<bits/stdc++.h>
using namespace std;
using ull=unsigned long long;
const int N=1e5+5;
int n,m;
vector<pair<int,int>> e[N];
ull vl[N];
vector<int> ec[N];
mt19937_64 mt(time(0));
int fa[N],d[N],si[N];
ull dv[N];
int zs[N],top[N];
void dfs1(int no,int fa){
    ::fa[no]=fa;
    d[no]=d[fa]+1;
    si[no]=1;
    for(auto [to,tc]:e[no]){
        if(to==fa)continue;
        dv[to]=dv[no]^vl[tc];
        dfs1(to,no);
        si[no]+=si[to];
        if(si[to]>si[zs[no]])zs[no]=to;
    }
}
void dfs2(int no,int tp){
    top[no]=tp;
    if(!zs[no])return;
    dfs2(zs[no],tp);
    for(auto [to,tc]:e[no]){
        if(to==fa[no]||to==zs[no])continue;
        dfs2(to,to);
    }
}
int lca(int x,int y){
    while(top[x]!=top[y]){
        if(d[top[x]]>d[top[y]])x=fa[top[x]];
        else y=fa[top[y]];
    }
    return d[x]<d[y]?x:y;
}
int get_dis(int x,int y){
    return d[x]+d[y]-2*d[lca(x,y)];
}
class Clen{
public:
    struct node{
        int x,y,len;
    };
    unordered_map<ull,node> mp;
    int mx=0;
    void cl(){
        mp.clear();
        mx=0;
    }
    void ins(int x){
        if(!mp.count(dv[x])){
            mp[dv[x]]={x,x,0};
            return;
        }
        node as=mp[dv[x]];
        int lx=get_dis(x,as.x),ly=get_dis(x,as.y);
        mx=max({mx,lx,ly});
        if(lx>ly){
            if(lx>as.len){
                as.len=lx;
                as.y=x;
            }
        }
        else{
            if(ly>as.len){
                as.len=ly;
                as.x=x;
            }
        }
        mp[dv[x]]=as;
    }
    void ins(node nd){
        ins(nd.x);ins(nd.y);
    }
    pair<int,int> qu(){
        for(auto [vl,nd]:mp){
            if(nd.len==mx)return {nd.x,nd.y};
        }
        return {0,0};
    }
};
int ans[N];
bool vis[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<n;++i){
        int u,v,c;;
        cin>>u>>v>>c;
        e[u].emplace_back(v,i);
        e[v].emplace_back(u,i);
        ec[c].push_back(i);
    }
    for(int i=1;i<=n;++i){
        if(ec[i].empty())continue;
        ull nv=0;
        while(ec[i].size()>1){
            int no=ec[i].back();ec[i].pop_back();
            vl[no]=mt();
            nv^=vl[no];
        }
        vl[ec[i][0]]=nv;
    }
    dfs1(1,0);dfs2(1,1);
    Clen mx;
    for(int i=1;i<=n;++i){
        mx.ins(i);
    }
    auto [x,y]=mx.qu();
    vector<int> ve;
    {
        vector<int> ev;
        int lc=lca(x,y);
        int no=x;
        while(no!=lc){
            vis[no]=1;
            ve.push_back(no);
            no=fa[no];
        }
        vis[lc]=1;
        ve.push_back(lc);
        no=y;
        while(no!=lc){
            vis[no]=1;
            ev.push_back(no);
            no=fa[no];
        }
        reverse(ev.begin(),ev.end());
        for(int no:ev)ve.push_back(no);
    }
    for(int i=1;i<=n;++i){
        if(!vis[i])ans[i]=mx.mx;
    }
    mx.cl();
    int nmx=0;
    for(int no:ve){
        for(auto [to,tc]:e[no]){
            if(vis[to])continue;
            Clen cmx;
            auto dfs=[&](int no,int fa,auto&& dfs)->void {
                cmx.ins(no);
                mx.ins(no);
                for(auto [to,tc]:e[no]){
                    if(to==fa)continue;
                    dfs(to,no,dfs);
                }
            };
            dfs(to,no,dfs);
            nmx=max(nmx,cmx.mx);
        }
        ans[no]=max(ans[no],nmx);
        mx.ins(no);
        nmx=max(nmx,mx.mx);
    }
    mx.cl();
    nmx=0;
    reverse(ve.begin(),ve.end());
    for(int no:ve){
        for(auto [to,tc]:e[no]){
            if(vis[to])continue;
            Clen cmx;
            auto dfs=[&](int no,int fa,auto&& dfs)->void {
                cmx.ins(no);
                mx.ins(no);
                for(auto [to,tc]:e[no]){
                    if(to==fa)continue;
                    dfs(to,no,dfs);
                }
            };
            dfs(to,no,dfs);
            nmx=max(nmx,cmx.mx);
        }
        ans[no]=max(ans[no],nmx);
        mx.ins(no);
        nmx=max(nmx,mx.mx);
    }
    while(m--){
        int x;
        cin>>x;
        cout<<ans[x]<<'\n';
    }
    return 0;
}