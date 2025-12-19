#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int M=2e5;
const int B=450;
const int K=455;
int n;
int val[N];
vector<int> e[N];
int cn_dfn;
int dfn[N],nfd[N];
int d[N];
int zs[N];
int si[N];
int ff[N];
class T{
public:
    int cn[N];
    int tcn[K][N<<1];
    int mx[K];
    int L[K],R[K];
    int kid[N];
    int kc;
    void init(){
        for(int i=1;i<=n;++i){
            cn[val[i]]+=2;
        }
        kc=(M+B-1)/B;
        for(int i=1;i<=kc;++i){
            L[i]=R[i-1]+1;
            R[i]=min(i*B,M);
            for(int j=L[i];j<=R[i];++j){
                kid[j]=i;
            }
            for(int j=L[i];j<=R[i];++j){
                mx[i]=max(mx[i],cn[j]);
                tcn[i][cn[j]]++;
            }
        }
    }
    void upd(int x,int d){
        tcn[kid[x]][cn[x]]--;
        cn[x]+=d;
        tcn[kid[x]][cn[x]]++;
        if(cn[x]>mx[kid[x]])mx[kid[x]]++;
        if(tcn[kid[x]][mx[kid[x]]]==0)--mx[kid[x]];
    }
    int query(){
        int mxk=1;
        for(int i=2;i<=kc;++i){
            if(mx[i]>mx[mxk])mxk=i;
        }
        for(int i=L[mxk];i<=R[mxk];++i){
            if(cn[i]==mx[mxk])return i;
        }
        return -1;
    }
}tt;
void dfs(int no,int fa){
    si[no]=1;
    ff[no]=fa;
    for(int to:e[no]){
        if(to==fa)continue;
        dfs(to,no);
        si[no]+=si[to];
        if(si[zs[no]]<si[to])zs[no]=to;
    }
}
void dfs1(int no,int fa){
    dfn[no]=++cn_dfn;
    nfd[cn_dfn]=no;
    if(!zs[no])return;
    dfs1(zs[no],no);
    for(int to:e[no]){
        if(to==fa)continue;
        if(to==zs[no])continue;
        dfs1(to,no);
    }
}
int kc;
int q;
struct ques{
    int x,y;
    int xc;
    int id;
}qs[N];
void upd(int l,int r,int d){
    for(int i=l;i<=r;++i){
        tt.upd(val[nfd[i]],d);
    }
}
void mov(int x,int y){
    x=nfd[x],y=nfd[y];
    const int xl=dfn[x],xr=dfn[x]+si[x]-1;
    const int yl=dfn[y],yr=dfn[y]+si[y]-1;
    if(xr<yl||yr<xl){
        upd(xl,xr,-1);upd(yl,yr,1);
    }
    else{
        if(yl<xl)upd(yl,xl-1,1);
        if(yr>xr)upd(xr+1,yr,1);
        if(yl>xl)upd(xl,yl-1,-1);
        if(yr<xr)upd(yr+1,xr,-1);
    }
}
int ans[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>val[i];
    }
    tt.init();
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    dfs1(1,0);
    for(int i=2;i<=n;++i){
        int x=nfd[i-1],y=nfd[i];
        d[i]=d[i-1];
        const int xl=dfn[x],xr=dfn[x]+si[x]-1;
        const int yl=dfn[y],yr=dfn[y]+si[y]-1;
        if(xr<yl||yr<xl)d[i]+=si[x]+si[y];
        else d[i]+=max(xl,yl)-min(xl,yl)+max(xr,yr)-min(xr,yr);
    }
    kc=sqrt(d[n])+1;
    cin>>q;
    for(int i=1;i<=q;++i){
        cin>>qs[i].x>>qs[i].y;
        qs[i].id=i;
        qs[i].x=dfn[qs[i].x];
        qs[i].y=dfn[qs[i].y];
        if(qs[i].x>qs[i].y)swap(qs[i].x,qs[i].y);
        qs[i].xc=d[qs[i].x]/kc+1;
    }
    sort(qs+1,qs+q+1,[](const ques& x,const ques& y){
        return x.xc!=y.xc?x.xc<y.xc:((x.xc&1)?x.y<y.y:x.y>y.y);
    });
    qs[0].x=qs[0].y=1;
    for(int i=1;i<=q;++i){
        mov(qs[i-1].x,qs[i].x);mov(qs[i-1].y,qs[i].y);
        ans[qs[i].id]=tt.query();
    }
    for(int i=1;i<=q;++i){
        cout<<ans[i]<<'\n';
    }
    return 0;
}