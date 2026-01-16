#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=205;
int n,m;
char c[N][N];
class Flow{
public:
    static constexpr int N=205*205*2;
    static constexpr int M=N*8;
    static constexpr int inf=0x3f3f3f3f;
    struct edge{
        int v,w;
        int ne;
    }e[M];
    int s=1,t=2;
    int cn_node=2,cne=1;
    int head[N],cur[N];
    int d[N];
    int add_node(){
        ++cn_node;
        return cn_node;
    }
    void add(int u,int v,int w){
        e[++cne].v=v;
        e[cne].w=w;
        e[cne].ne=head[u];
        head[u]=cne;
    }
    void adde(int u,int v,int w){
        add(u,v,w);add(v,u,0);
    }
    bool bfs(){
        memset(d,0x3f,sizeof(int)*(cn_node+1));
        memcpy(cur,head,sizeof(int)*(cn_node+1));
        queue<int> q;
        d[s]=0;
        q.push(s);
        while(!q.empty()){
            int no=q.front();
            q.pop();
            for(int i=head[no];i;i=e[i].ne){
                if(!e[i].w)continue;
                int to=e[i].v;
                if(d[to]!=inf)continue;
                d[to]=d[no]+1;
                if(to==t)return 1;
                q.push(to);
            }
        }
        return 0;
    }
    int dfs(int no,int lm){
        if(no==t)return lm;
        int s=0;
        for(int& i=cur[no];i;i=e[i].ne){
            if(!e[i].w)continue;
            int to=e[i].v;
            if(d[to]!=d[no]+1)continue;
            int tl=dfs(to,min(lm,e[i].w));
            if(tl){
                e[i].w-=tl;
                e[i^1].w+=tl;
                s+=tl;
                lm-=tl;
                if(!lm)break;
            }
        }
        if(!s)d[no]=inf;
        return s;
    }
    int dinic(){
        int sum=0;
        while(bfs())sum+=dfs(s,N);
        return sum;
    }
}flow;
int id1[N][N],id2[N][N];
int cn,cne;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>c[i][j];
            if(c[i][j]=='#')++cn;
        }
    }
    for(int i=1;i<n;++i){
        for(int j=1;j<=m;++j){
            if(c[i][j]=='.'||c[i+1][j]=='.')continue;
            id1[i][j]=flow.add_node();
            flow.adde(1,id1[i][j],1);
            ++cne;
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<m;++j){
            if(c[i][j]=='.'||c[i][j+1]=='.')continue;
            id2[i][j]=flow.add_node();
            flow.adde(id2[i][j],2,1);
            ++cne;
        }
    }
    for(int i=1;i<n;++i){
        for(int j=1;j<=m;++j){
            if(id1[i][j]&&id2[i][j]){
                flow.adde(id1[i][j],id2[i][j],1);
            }
            if(id1[i][j]&&id2[i+1][j]){
                flow.adde(id1[i][j],id2[i+1][j],1);
            }
            if(id1[i][j]&&id2[i][j-1]){
                flow.adde(id1[i][j],id2[i][j-1],1);
            }
            if(id1[i][j]&&id2[i+1][j-1]){
                flow.adde(id1[i][j],id2[i+1][j-1],1);
            }
        }
    }
    cout<<cn-(cne-flow.dinic());
    return 0;
}