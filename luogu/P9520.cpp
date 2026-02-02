#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1.2e5+5;
const int M=5e6+5;
int T;
int n,q;
vector<int> e[N];
int si[N],d[N];
int fa[N];
int zs[N],top[N];
int dfn[N],cn_dfn;
int lg[N];
struct ques{
    int x,y;
}qs[N];
int tx[N],ty[N];
int cn_nd;
int st_in[18][N],st_out[18][N];
int in[M];
vector<int> et[M];
void dfs1(int no,int fa){
    d[no]=d[fa]+1;
    si[no]=1;
    ::fa[no]=fa;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs1(to,no);
        si[no]+=si[to];
        if(si[to]>si[zs[no]])zs[no]=to;
    }
}
void dfs2(int no,int tp){
    top[no]=tp;
    dfn[no]=++cn_dfn;
    if(!zs[no])return;
    dfs2(zs[no],tp);
    for(int to:e[no]){
        if(to==fa[no]||to==zs[no])continue;
        dfs2(to,to);
    }
}
void adde(int x,int y){
    et[x].push_back(y);
    in[y]++;
}
void add_in(int x,int y,int id){
    x=ty[x-1]+1,y=ty[y];
    if(x>y)return;
    int k=lg[y-x+1];
    adde(id,st_in[k][x]);
    adde(id,st_in[k][y-(1<<k)+1]);
}
void add_out(int x,int y,int id){
    x=tx[x-1]+1,y=tx[y];
    if(x>y)return;
    int k=lg[y-x+1];
    adde(st_out[k][x],id);
    adde(st_out[k][y-(1<<k)+1],id);
}
void sol(int x,int y,int id){
    int flx=1,fly=1;
    while(top[x]!=top[y]){
        if(d[top[x]]>d[top[y]]){
            int dl=dfn[top[x]],dr=dfn[x];
            add_in(dl,dr,id);add_out(dl,dr-flx,id);
            flx=0;
            x=fa[top[x]];
        }
        else{
            int dl=dfn[top[y]],dr=dfn[y];
            add_in(dl,dr-fly,id);add_out(dl,dr,id);
            fly=0;
            y=fa[top[y]];
        }
    }
    int dl=dfn[x],dr=dfn[y];
    if(dl>dr)swap(dl,dr);
    if(d[x]>d[y]){
        add_in(dl+fly,dr,id);
        add_out(dl,dr-flx,id);
    }
    else{
        add_in(dl,dr-fly,id);
        add_out(dl+flx,dr,id);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=cn_nd;++i){
            et[i].clear();
            in[i]=0;
        }
        for(int i=1;i<=n+1;++i){
            e[i].clear();
            si[i]=d[i]=0;
            zs[i]=top[i]=0;
            tx[i]=ty[i]=0;
        }
        cn_dfn=0;
        for(int i=1;i<n;++i){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        dfs1(1,0);
        dfs2(1,1);
        cin>>q;
        for(int i=2;i<=q;++i)lg[i]=lg[i>>1]+1;
        for(int i=1;i<=q;++i){
            cin>>qs[i].x>>qs[i].y;
            tx[dfn[qs[i].x]]++;
            ty[dfn[qs[i].y]]++;
        }
        for(int i=1;i<=n;++i){
            tx[i]+=tx[i-1];
            ty[i]+=ty[i-1];
        }
        cn_nd=q;
        for(int i=1;i<=q;++i){
            auto [x,y]=qs[i];
            st_out[0][tx[dfn[x]]]=i;
            st_in[0][ty[dfn[y]]]=i;
        }
        for(int j=1;j<18;++j){
            for(int i=1;i+(1<<j)-1<=q;++i){
                st_out[j][i]=++cn_nd;
                adde(st_out[j-1][i],st_out[j][i]);
                adde(st_out[j-1][i+(1<<j-1)],st_out[j][i]);
                st_in[j][i]=++cn_nd;
                adde(st_in[j][i],st_in[j-1][i]);
                adde(st_in[j][i],st_in[j-1][i+(1<<j-1)]);
            }
        }
        for(int i=1;i<=q;++i){
            sol(qs[i].x,qs[i].y,i);
        }
        queue<int> q;
        for(int i=1;i<=cn_nd;++i){
            if(!in[i])q.push(i);
        }
        while(!q.empty()){
            int no=q.front();
            q.pop();
            for(int to:et[no]){
                in[to]--;
                if(!in[to])q.push(to);
            }
        }
        bool fl=1;
        for(int i=1;i<=cn_nd;++i){
            if(in[i]){
                fl=0;
                break;
            }
        }
        if(fl)cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}