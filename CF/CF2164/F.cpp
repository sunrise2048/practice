#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
const int mod=998244353;
int T;
int n;
vector<int> e[N];
int fa[N];
int a[N];
ll jc[N],ny[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
void init(){
    const int n=5e5;
    jc[0]=1;
    for(int i=1;i<=n;++i)jc[i]=jc[i-1]*i%mod;
    ny[n]=ksm(jc[n]);
    for(int i=n;i;--i)ny[i-1]=ny[i]*i%mod;
}
mt19937 mt(time(0));
class Treap{
public:
    struct node{
        int key;
        int s[2];
        int si;
    }t[N];
    int rt;
    void init(){
        rt=1;
        for(int i=1;i<=n;++i){
            t[i].key=mt();
            t[i].si=1;
            t[i].s[0]=t[i].s[1]=0;
        }
    }
    void pushup(int x){
        t[x].si=t[t[x].s[0]].si+t[t[x].s[1]].si+1;
    }
    void split(int no,int k,int& x,int& y){
        if(!no){x=y=0;return;}
        if(k<=t[t[no].s[0]].si){
            y=no;
            split(t[no].s[0],k,x,t[y].s[0]);
            pushup(y);
        }
        else{
            x=no;k-=t[t[no].s[0]].si+1;
            split(t[no].s[1],k,t[x].s[1],y);
            pushup(x);
        }
    }
    int merge(int x,int y){
        if(!x||!y)return x|y;
        if(t[x].key<t[y].key){
            t[x].s[1]=merge(t[x].s[1],y);
            pushup(x);
            return x;
        }
        t[y].s[0]=merge(x,t[y].s[0]);
        pushup(y);
        return y;
    }
    void erase(int rk){
        int x,y,z;
        split(rt,rk-1,x,y);
        split(y,1,y,z);
        rt=merge(x,z);
    }
    void ins(int no,int rk){
        int x,y;
        split(rt,rk-1,x,y);
        rt=merge(merge(x,no),y);
    }
    int query_id(int no,int rk){
        if(rk==t[t[no].s[0]].si+1)return no;
        if(rk<=t[t[no].s[0]].si)return query_id(t[no].s[0],rk);
        return query_id(t[no].s[1],rk-t[t[no].s[0]].si-1);
    }
    int query(int rk){
        return query_id(rt,rk);
    }
}treap;
vector<int> ls[N],rs[N];
int si[N];
ll f[N];
void dfs1(int no,int d){
    if(no!=1){
        if(a[no]==0){
            ls[treap.query(1)].push_back(no);
        }
        else if(a[no]==d){
            rs[treap.query(d)].push_back(no);
        }
        else{
            int lf=treap.query(a[no]),rf=treap.query(a[no]+1);
            if(lf>rf)rs[lf].push_back(no);
            else ls[rf].push_back(no);
        }
        treap.ins(no,a[no]+1);
    }
    for(int to:e[no]){
        dfs1(to,d+1);
    }
    if(no!=1)treap.erase(a[no]+1);
}  
void dfs2(int no){
    si[no]=f[no]=1;
    int s0=0,s1=0;
    for(int to:ls[no]){
        dfs2(to);
        s0+=si[to];
        si[no]+=si[to];
    }
    for(int to:rs[no]){
        dfs2(to);
        s1+=si[to];
        si[no]+=si[to];
    }
    f[no]=jc[s0]*jc[s1]%mod;
    for(int to:ls[no])f[no]=f[no]*ny[si[to]]%mod*f[to]%mod;
    for(int to:rs[no])f[no]=f[no]*ny[si[to]]%mod*f[to]%mod;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin>>T;
    while(T--){
        cin>>n;
        treap.init();
        for(int i=1;i<=n;++i){
            ls[i].clear();rs[i].clear();
            f[i]=1;
            e[i].clear();
        }
        for(int i=2;i<=n;++i){
            cin>>fa[i];
            e[fa[i]].push_back(i);
        }
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        dfs1(1,0);
        dfs2(1);
        cout<<f[1]<<'\n';
    }
    return 0;
}