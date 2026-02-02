#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
const int f[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int n,m,q;
vector<vector<char>> op;
vector<vector<int>> id,d,fl;
vector<pair<int,int>> nd;
pair<int,int> fd;
int ff[N<<1];
int find(int x){return ff[x]==x?x:ff[x]=find(ff[x]);}
class LCA{
public:
    vector<int> e[N<<1];
    int rt;
    int de[N<<1],zs[N<<1];
    int fa[N<<1];
    int top[N<<1];
    int si[N<<1];
    int fr[N<<1];
    void add(int x,int y){
        e[x].push_back(y);
        fa[y]=x;
        fr[y]=1;
    }
    void dfs1(int no){
        si[no]=1;
        zs[no]=-1;
        for(int to:e[no]){
            de[to]=de[no]+1;
            dfs1(to);
            si[no]+=si[to];
            if(zs[no]==-1||si[zs[no]]<si[to])zs[no]=to;
        }
    }
    void dfs2(int no,int tp){
        top[no]=tp;
        if(zs[no]==-1)return;
        dfs2(zs[no],tp);
        for(int to:e[no]){
            if(to==zs[no])continue;
            dfs2(to,to);
        }
    }
    void init(){
        for(int i=0;i<2*n*m;++i){
            if(!fr[i]){
                add(2*n*m,i);
            }
        }
        rt=2*n*m;
        dfs1(rt);dfs2(rt,rt);
    }
    int lca(int x,int y){
        while(top[x]!=top[y]){
            if(de[top[x]]>de[top[y]])x=fa[top[x]];
            else y=fa[top[y]];
        }
        return de[x]<de[y]?x:y;
    }
    int query(int x,int y){
        int lc=lca(x,y);
        if(lc>=n*m)lc-=n*m;
        return d[lc/m][lc%m];
    }
}hld;
void adde(int x,int y){
    x=find(x);y=find(y);
    if(x==y)return;
    hld.add(x,y);
    ff[y]=x;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>q;
    op.resize(n,vector<char>(m));
    d.resize(n,vector<int>(m,-1));
    id.resize(n,vector<int>(m));
    fl.resize(n,vector<int>(m));
    iota(ff,ff+2*n*m+1,0);
    queue<pair<int,int>> qd;
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            cin>>op[i][j];
            if(op[i][j]=='#'){
                fl[i][j]=1;
                fd=max(fd,{i,j});
            }
            else if(op[i][j]=='v'){
                d[i][j]=0;
                qd.emplace(i,j);
            }
        }
    }
    while(!qd.empty()){
        auto [x,y]=qd.front();
        qd.pop();
        for(auto [dx,dy]:f){
            int tx=x+dx,ty=y+dy;
            if(tx<0||tx>=n||ty<0||ty>=m)continue;
            if(d[tx][ty]!=-1)continue;
            d[tx][ty]=d[x][y]+1;
            qd.emplace(tx,ty);
        }
    }
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            if(fl[i][j])continue;
            fl[i][j]=1;
            nd.emplace_back(-d[i][j],i*m+j);
        }
    }
    sort(nd.begin(),nd.end());
    for(auto [ds,id]:nd){
        int x=id/m,y=id%m;
        fl[x][y]=0;
        for(auto [dx,dy]:f){
            int tx=x+dx,ty=y+dy;
            if(tx<0||tx>=n||ty<0||ty>=m)continue;
            if(fl[tx][ty])continue;
            int td=tx*m+ty;
            if(x!=tx&&min(x,tx)==fd.first&&y>=fd.second){
                adde(id+n*m,td);
                adde(id,td+n*m);
            }
            else{
                adde(id,td);
                adde(id+n*m,td+n*m);
            }
        }
    }
    hld.init();
    while(q--){
        int x,y;
        cin>>x>>y;
        --x;--y;
        cout<<hld.query(x*m+y,x*m+y+n*m)<<'\n';
    }
    return 0;
}