#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=405;
const int M=N*N*4;
const ll inf=1e16;
int n,m;
int op[N][N];
int vx[N][N],vy[N][N];
vector<pair<int,int>> e[M];
ll d[M];
bool vis[M];
struct node{
    ll d;
    int no;
    node(ll d,int no):d(d),no(no){}
    bool operator<(const node& ls)const{
        return d>ls.d;
    }
};
void dij(int s){
    memset(d,0x3f,sizeof(d));
    memset(vis,0,sizeof(vis));
    d[s]=0;
    priority_queue<node> q;
    q.emplace(0,s);
    while(!q.empty()){
        int no=q.top().no;
        q.pop();
        if(vis[no])continue;
        vis[no]=1;
        for(auto [to,tw]:e[no]){
            if(d[to]>d[no]+tw){
                d[to]=d[no]+tw;
                q.emplace(d[to],to);
            }
        }
    }
}
int id[N][N];
bool flx[N][N],fly[N][N];
void dfs(int no){
    vis[no]=1;
    for(auto [to,tw]:e[no]){
        if(d[no]!=d[to]+tw)continue;
        if(abs(to-no)==1){
            int x=no/(m+1),y=max(no,to)%(m+1);
            fly[x][y]=1;
            if(!vis[to])dfs(to);
        }
        else{
            int x=max(no,to)/(m+1),y=no%(m+1);
            flx[x][y]=1;
            if(!vis[to])dfs(to);
        }
    }
}
bool ch(int x,int y){
    if(x<0||y<0)return 1;
    return op[x][y]==0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            cin>>op[i][j];
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=0;j<=m;++j){
            cin>>vx[i][j];
        }
    }
    for(int i=0;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>vy[i][j];
        }
    }
    for(int i=0;i<=n;++i){
        for(int j=0;j<=m;++j){
            id[i][j]=i*(m+1)+j;
        }
    }
    for(int i=0;i<=n;++i){
        for(int j=0;j<=m;++j){
            if(i){
                e[id[i][j]].emplace_back(id[i-1][j],vx[i][j]);
                e[id[i-1][j]].emplace_back(id[i][j],vx[i][j]);
            }
            if(j){
                e[id[i][j]].emplace_back(id[i][j-1],vy[i][j]);
                e[id[i][j-1]].emplace_back(id[i][j],vy[i][j]);
            }
        }
    }
    dij(0);
    memset(vis,0,sizeof(vis));
    for(int i=0;i<=n;++i){
        for(int j=0;j<=m;++j){
            if(vis[id[i][j]])continue;
            if(!op[i][j])continue;
            dfs(id[i][j]);
        }
    }
    for(int i=0;i<=(n+1)*(m+1);++i)e[i].clear();
    for(int i=0;i<=n;++i){
        for(int j=0;j<=m;++j){
            int id0=id[i][j]*4;
            int id1=id[i][j]*4+1;
            int id2=id[i][j]*4+2;
            int id3=id[i][j]*4+3;
            if(ch(i-1,j-1)&&ch(i-1,j)&&!flx[i][j]){
                e[id0].emplace_back(id1,0);
            }
            if(ch(i-1,j)&&ch(i,j)&&!fly[i][j+1]){
                e[id1].emplace_back(id2,0);
            }
            if(ch(i,j)&&ch(i,j-1)&&!flx[i+1][j]){
                e[id2].emplace_back(id3,0);
            }
            if(ch(i,j-1)&&ch(i-1,j-1)&&!fly[i][j]){
                e[id3].emplace_back(id0,0);
            }
            if(ch(i-1,j-1)&&i){
                e[id0].emplace_back(id[i-1][j]*4+3,vx[i][j]);
            }
            if(ch(i-1,j)&&j!=m){
                e[id1].emplace_back(id[i][j+1]*4,vy[i][j+1]);
            }
            if(ch(i,j)&&i!=n){
                e[id2].emplace_back(id[i+1][j]*4+1,vx[i+1][j]);
            }
            if(ch(i,j-1)&&j){
                e[id3].emplace_back(id[i][j-1]*4+2,vy[i][j]);
            }
        }
    }
    dij(0);
    cout<<d[3]<<'\n';
    return 0;
}