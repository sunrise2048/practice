#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=4405;
const int inf=1e9;
int n;
ll a[N],b[N];
int id0[N],id[N];
int p[N];
int cn[N];
bool ch(ll t){
    auto cmp=[&](const int& x,const int& y){
        ll tx=t*a[x]+b[x],ty=t*a[y]+b[y];
        return tx!=ty?tx<ty:x>y;
    };
    sort(id+1,id+(n<<1)+1,cmp);
    int mx=0;
    for(int i=1;i<=(n<<1);++i){
        cn[id0[i]]=0;
        if(cmp(mx,id0[i]))mx=id0[i];
        if(id0[i]<=n)++cn[mx];
    }
    int si=0;
    for(int i=(n<<1);i;--i){
        si+=cn[id[i]];
        if(id[i]>n)--si;
        if(si<0)return 0;
    }
    return 1;
}
const int M=N*3;
const int E=N*30;
class FLOW{
public:
    int s=1,t=2;
    struct edge{
        int v,w,c;
        int ne;
    }e[E];
    int cne=1,cnn=2;
    int head[M];
    ll d[M];
    int la[M];
    bool inq[M];
    void add(int u,int v,int w,int c){
        e[++cne].v=v;
        e[cne].w=w;
        e[cne].c=c;
        e[cne].ne=head[u];
        head[u]=cne;
    }
    void adde(int u,int v,int w,int c){
        add(u,v,w,c);add(v,u,0,-c);
    }
    int nw_node(){return ++cnn;}
    int sum;
    bool spfa(){
        memset(d,0x3f,sizeof(d));
        queue<int> q;
        d[s]=0;
        q.push(s);
        while(!q.empty()){
            int no=q.front();
            q.pop();
            inq[no]=0;
            for(int i=head[no];i;i=e[i].ne){
                if(!e[i].w)continue;
                int to=e[i].v;
                int tw=e[i].c;
                if(d[to]<=d[no]+tw)continue;
                d[to]=d[no]+tw;
                la[to]=i;
                if(!inq[to]){
                    inq[to]=1;
                    q.push(to);
                }
            }
        }
        if(d[t]>inf)return 0;
        int no=t;
        while(no!=s){
            int le=la[no];
            sum+=e[le].c;
            e[le].w--;
            e[le^1].w++;
            no=e[le^1].v;
        }
        return 1;
    }
    int dinic(){
        while(spfa());
        return sum;
    }
}flow;
int nd[N],l1[N],l2[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=(n<<1);++i){
        cin>>a[i]>>b[i];
    }
    iota(id0+1,id0+(n<<1)+1,1);iota(id+1,id+(n<<1)+1,1);
    sort(id0+1,id0+(n<<1)+1,[](const int& x,const int& y){
        return (b[x]!=b[y]?b[x]<b[y]:x>y);
    });
    ll l=-1,r=1e9+7;
    while(l<r-1){
        ll mid=(l+r>>1);
        if(ch(mid))r=mid;
        else l=mid;
    }
    if(r>1e9){
        cout<<"-1\n";
        return 0;
    }
    cout<<r<<' ';
    ch(r);
    for(int i=1;i<=(n<<1);++i){
        p[id0[i]]=i;
        nd[i]=flow.nw_node();
        l1[i]=flow.nw_node();
        l2[i]=flow.nw_node();
    }
    for(int i=1;i<=(n<<1);++i){
        if(i>1){
            flow.adde(l1[i],l1[i-1],n,0);
            flow.adde(l2[i],l2[i-1],n,0);
        }
        if(id0[i]<=n){
            flow.adde(nd[id0[i]],l1[i],1,1);
        }
        else{
            flow.adde(l1[i],nd[id0[i]],1,0);
        }
        flow.adde(l1[p[id[i]]],l2[i],n,0);
        if(id[i]<=n){
            flow.adde(nd[id[i]],l2[i],1,0);
        }
        else{
            flow.adde(l2[i],nd[id[i]],1,1);
        }
    }
    for(int i=1;i<=n;++i){
        flow.adde(1,nd[i],1,0);
        flow.adde(nd[i+n],2,1,0);
    }
    cout<<flow.dinic()<<'\n';
    return 0;
}