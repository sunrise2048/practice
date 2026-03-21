#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int M=N*20;
const int lm=1e6;
const ll inf=1e18;
int n;
int a[N];
vector<int> e[N];
class LCT{
public:
    struct node{
        ll k,b=inf;
        ll lz;
        int lson,rson;
    }t[M];
    int cn;
    #define mid (l+r>>1)
    #define rs(k) t[k].rson
    #define ls(k) t[k].lson
    void upd(int k,ll d){
        t[k].b+=d;
        t[k].lz+=d;
    }
    void pushdown(int k){
        if(!t[k].lz)return;
        if(ls(k))upd(ls(k),t[k].lz);
        if(rs(k))upd(rs(k),t[k].lz);
        t[k].lz=0;
    }
    ll get(ll k,ll b,int x){return k*x+b;}
    void ins(int l,int r,int& k,ll tk,ll tb){
        if(!k){
            k=++cn;
            t[k].k=tk;t[k].b=tb;
            return;
        }
        pushdown(k);
        if(get(tk,tb,l)<=get(t[k].k,t[k].b,l)){
            if(get(tk,tb,r)<=get(t[k].k,t[k].b,r)){
                swap(t[k].k,tk);
                swap(t[k].b,tb);
                return;
            }
            if(get(tk,tb,mid)<=get(t[k].k,t[k].b,mid)){
                swap(tk,t[k].k);swap(tb,t[k].b);
                ins(mid+1,r,rs(k),tk,tb);
            }
            else ins(l,mid,ls(k),tk,tb);
        }
        else if(get(tk,tb,r)<=get(t[k].k,t[k].b,r)){
            if(get(tk,tb,mid+1)<=get(t[k].k,t[k].b,mid+1)){
                swap(tk,t[k].k);swap(tb,t[k].b);
                ins(l,mid,ls(k),tk,tb);
            }
            else ins(mid+1,r,rs(k),tk,tb);
        }
    }
    int merge(int l,int r,int x,int y){
        if(!x||!y)return x|y;
        pushdown(x);pushdown(y);
        if(l!=r){
            ls(x)=merge(l,mid,ls(x),ls(y));
            rs(x)=merge(mid+1,r,rs(x),rs(y));
        }
        ins(l,r,x,t[y].k,t[y].b);
        return x;
    }
    ll query(int l,int r,int k,int x){
        if(!x)return inf;
        ll as=get(t[k].k,t[k].b,x);
        if(l==r)return as;
        pushdown(k);
        if(x<=mid)return min(as,query(l,mid,ls(k),x));
        return min(as,query(mid+1,r,rs(k),x));
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
int rt[N];
ll gx[N];
void dfs(int no){
    if(e[no].empty()){
        sgt.ins(1,lm,rt[no],a[no],0);
        return;
    }
    for(int to:e[no]){
        dfs(to);
    }
    ll s=0;
    for(int to:e[no]){
        gx[to]=sgt.query(1,lm,rt[to],a[no]);
        s+=gx[to];
    }
    for(int to:e[no]){
        sgt.upd(rt[to],s-gx[to]);
        rt[no]=sgt.merge(1,lm,rt[no],rt[to]);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    if(n==1){cout<<"0\n";return 0;}
    for(int i=2;i<=n;++i){
        int fa;
        cin>>fa;
        e[fa].push_back(i);
    }
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    dfs(1);
    cout<<sgt.query(1,lm,rt[1],a[1])<<'\n';
    return 0;
}