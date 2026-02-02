#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e4+5;
int T;
int n;
int a[N];
const int M=2e5+5;
const int E=5e6+5;
const int inf=1e8;
class FLOW{
public:
    int s,t;
    struct edge{
        int v,w;
        int ne;
    }e[E];
    int cne;
    int head[M];
    int d[M];
    int cur[M];
    void init(){
        for(int i=1;i<=4*n+3;++i){
            head[i]=0;
        }
        s=4*n+1,t=4*n+2;
        cne=1;
    }
    void add(int u,int v,int w){
        ++cne;
        e[cne].v=v;
        e[cne].w=w;
        e[cne].ne=head[u];
        head[u]=cne;
    }
    void adde(int u,int v,int w){
        add(u,v,w);add(v,u,0);
    }
    bool bfs(){
        memset(d,0x3f,sizeof(int)*(4*n+3));
        memcpy(cur,head,sizeof(int)*(4*n+3));
        queue<int> q;
        d[s]=0;
        q.push(s);
        while(!q.empty()){
            int no=q.front();
            q.pop();
            for(int i=head[no];i;i=e[i].ne){
                if(!e[i].w)continue;
                int to=e[i].v;
                if(d[to]<inf)continue;
                d[to]=d[no]+1;
                q.push(to);
            }
        }
        return d[t]<inf;
    }
    int dfs(int no,int lm){
        if(no==t)return lm;
        int s=0;
        for(int& i=cur[no];i;i=e[i].ne){
            if(!e[i].w)continue;
            int to=e[i].v;
            if(d[to]!=d[no]+1)continue;
            int ts=dfs(to,min(lm,e[i].w));
            if(ts){
                s+=ts;
                lm-=ts;
                e[i].w-=ts;
                e[i^1].w+=ts;
                if(!lm)break;
            }
        }
        if(!s)d[no]=-1;
        return s;
    }
    int dinic(){
        int sm=0;
        while(bfs())sm+=dfs(s,inf);
        return sm;
    }
}flow;
int t[N];
void add(int x,int y){
    int x0=x,x1=x+n,y0=y,y1=y+n;
    flow.adde(x0,y0+2*n,1);
    flow.adde(x0,y1+2*n,1);
    flow.adde(x1,y1+2*n,1);
}
const int lm=5e4;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        flow.init();
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        sort(a+1,a+n+1);
        for(int i=1;i<=2*n;++i){
            flow.adde(4*n+1,i,1);
            flow.adde(i+2*n,4*n+2,1);
        }
        for(int i=1;i<=n;++i){
            flow.adde(i,i+3*n,1);
        }
        if(n<=250){
            for(int i=1;i<=n;++i){
                for(int j=i+1;j<=n;++j){
                    if(a[j]%a[i]==0){
                        add(j,i);
                    }
                }
            }
        }
        else{
            memset(t,0,sizeof(t));
            for(int i=1;i<=n;++i)t[a[i]]=i;
            for(int i=1;i<=lm;++i){
                if(!t[i])continue;
                for(int j=2*i;j<=lm;j+=i){
                    if(!t[j])continue;
                    add(t[j],t[i]);
                }
            }
        }
        cout<<flow.dinic()-n<<'\n';
    }
    return 0;
}