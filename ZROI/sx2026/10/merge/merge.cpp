#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int n,q;
int a[N];
mt19937 mt(time(0));
class Treap{
public:
    struct node{
        int mx;
        int si;
        int s[2];
        int key;
    }t[N];
    void init(int id){
        t[id].key=mt();
        t[id].si=1;
        t[id].mx=id;
    }
    void pushup(int k){
        t[k].si=t[t[k].s[0]].si+t[t[k].s[1]].si+1;
        t[k].mx=max({k,t[t[k].s[0]].mx,t[t[k].s[1]].mx});
    }
    void split_by_si(int k,int si,int& idx,int& idy){
        if(!k){
            idx=idy=0;
            return;
        }
        if(si<=t[t[k].s[0]].si){
            idy=k;
            split_by_si(t[k].s[0],si,idx,t[idy].s[0]);
            pushup(idy);
        }
        else{
            idx=k;
            si-=t[t[k].s[0]].si+1;
            split_by_si(t[k].s[1],si,t[idx].s[1],idy);
            pushup(idx);
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
    int query_mx(int k){
        if(!k)return 0;
        if(t[k].mx==k)return t[t[k].s[0]].si;
        if(t[k].mx==t[t[k].s[0]].mx)return query_mx(t[k].s[0]);
        return t[t[k].s[0]].si+1+query_mx(t[k].s[1]);
    }
    int query(int k,int si){
        while(k){
            if(t[t[k].s[0]].si>=si)k=t[k].s[0];
            else if(t[t[k].s[0]].si+1==si){
                return k;
            }
            else{
                si-=t[t[k].s[0]].si+1;
                k=t[k].s[1];
            }
        }
        return -1;
    }
}treap;
int siz(int x){return treap.t[x].si;}
int rt[N];
class SGT{
public:
    int t[N<<2];
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    void pushup(int k){t[k]=t[ls]+t[rs];}
    void update(int l,int r,int k,int x,int d){
        if(l==r){
            t[k]+=d;
            return;
        }
        if(x<=mid)update(l,mid,ls,x,d);
        else update(mid+1,r,rs,x,d);
        pushup(k);
    }
    pair<int,int> query(int l,int r,int k,int si){
        if(l==r)return {l,0};
        if(t[ls]>=si)return query(l,mid,ls,si);
        auto as=query(mid+1,r,rs,si-t[ls]);as.second+=t[ls];
        return as;
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
int main(){
    freopen("merge.in","r",stdin);
    freopen("merge.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        treap.init(i);
    }
    for(int i=1;i<=n;++i){
        int j=i+1;
        int nrt=a[i];
        while(j<=n&&a[j]<a[i]){
            nrt=treap.merge(nrt,a[j]);
            ++j;
        }
        rt[a[i]]=nrt;
        sgt.update(1,n,1,a[i],j-i);
        i=j-1;
    }
    while(q--){
        int op,x;
        cin>>op>>x;
        if(op==1){
            auto [val,si]=sgt.query(1,n,1,x);
            cout<<treap.query(rt[val],x-si)<<'\n';
        }
        else{
            auto [rtv,siv]=sgt.query(1,n,1,x);
            if(siz(rt[rtv])+siv==x)continue;
            sgt.update(1,n,1,rtv,-(siv+siz(rt[rtv])-x));
            int nrt;
            treap.split_by_si(rt[rtv],x-siv,rt[rtv],nrt);
            int tsi=treap.query_mx(nrt);
            while(tsi){
                int trt;
                treap.split_by_si(nrt,tsi,nrt,trt);
                int nv=treap.t[trt].mx;
                rt[nv]=trt;
                sgt.update(1,n,1,nv,treap.t[trt].si);
                tsi=treap.query_mx(nrt);
            }
            int nv=treap.t[nrt].mx;
            rt[nv]=nrt;
            sgt.update(1,n,1,nv,treap.t[nrt].si);
        }
    }
    return 0;
}