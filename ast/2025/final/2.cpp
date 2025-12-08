#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=505;
const int M=1e5+5;
class Flow{
public:
    int s,t;
    struct edge{
        int v;
        int w;
        int c;
        int ne;
    }e[M];
    bool inq[N];
    int head[N];
    int cn;
    Flow(int s,int t):s(s),t(t),cn(1){}
    void add(int u,int v,int w,int c){
        e[++cn].v=v;
        e[cn].w=w;
        e[cn].c=c;
        e[cn].ne=head[u];
        head[u]=cn;
    }
    void adde(int u,int v,int w,int c){
        add(u,v,w,c);add(v,u,0,-c);
    }
    int cur[N];
    int d[N];
    bool bfs(){
        memset(d,0x3f,sizeof(d));
        memcpy(cur,head,sizeof(cur));
        queue<int> q;
        d[s]=0;
        q.push(s);
        while(!q.empty()){
            int no=q.front();
            q.pop();
            inq[no]=0;
            for(int i=head[no];i;i=e[i].ne){
                if(!e[i].w)continue;
                int to=e[i].v,tw=e[i].c;
                if(d[to]<=d[no]+tw)continue;
                d[to]=d[no]+tw;
                if(!inq[to]){
                    q.push(to);
                    inq[to]=1;
                }
            }
        }
        return d[t]!=0x3f3f3f3f;
    }
    ll cost;
    int dfs(int no,int mif){
        if(no==t)return mif;
        inq[no]=1;
        int s=0;
        for(int& i=cur[no];i;i=e[i].ne){
            if(!e[i].w)continue;
            int to=e[i].v,tc=e[i].c;
            if(d[to]!=d[no]+tc)continue;
            if(inq[to])continue;
            int nf=dfs(to,min(e[i].w,mif));
            if(nf){
                cost+=tc*nf;
                s+=nf;
                mif-=nf;
                e[i].w-=nf;
                e[i^1].w+=nf;
            }
            if(!mif)break;
        }
        if(s==0)d[no]=-1;
        inq[no]=0;
        return s;
    }
    int dinic(){
        int cn=0;
        while(bfs()){
            cn+=dfs(s,1e9);
        }
        return cn;
    }
}flow(1,2);
int n,m,k,l;
int id_in[N];
int id_zin[N],id_zout[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>k>>l;
    int cn=2;
    for(int i=1;i<=n;++i){
        id_in[i]=++cn;
    }
    for(int i=1;i<=m;++i){
        id_zin[i]=++cn;
        id_zout[i]=++cn;
    }
    for(int i=1;i<=k;++i){
        int x;
        cin>>x;
        flow.adde(1,id_in[x],1,0);
    }
    for(int i=1;i<=l;++i){
        int x;
        cin>>x;
        flow.adde(id_in[x],2,1,0);
    }
    for(int i=1;i<=m;++i){
        int cn;
        cin>>cn;
        flow.adde(id_zin[i],id_zout[i],cn,1);
        int p,q;
        cin>>p>>q;
        while(p--){
            int x;
            cin>>x;
            flow.adde(id_in[x],id_zin[i],cn,0);
        }
        while(q--){
            int x;
            cin>>x;
            flow.adde(id_zout[i],id_in[x],cn,0);
        }
    }
    int tcn=flow.dinic();
    if(tcn!=k){
        cout<<"-1\n";
        return 0;
    }
    cout<<flow.cost<<'\n';
    return 0;
}
