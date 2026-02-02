#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int lm=1e9;
int n;
int fa[N];
ll h[N],c[N];
ll d[N];
vector<int> e[N];
int in[N];
class SGT{
public:
    struct node{
        ll val;
        int lson,rson;
    }t[N*32];
    int cn;
    #define mid (l+r>>1)
    #define ls(k) t[k].lson
    #define rs(k) t[k].rson
    void pushup(int k){
        t[k].val=t[ls(k)].val+t[rs(k)].val;
    }
    void update(int l,int r,int& k,int x,int d){
        if(!k)k=++cn;
        if(l==r){
            t[k].val+=d;
            return;
        }
        if(x<=mid)update(l,mid,ls(k),x,d);
        else update(mid+1,r,rs(k),x,d);
        pushup(k);
    }
    int upd(int l,int r,int& k,int x,ll d){
        if(!d)return 0;
        if(!k)return 0;
        if(l==r){
            ll nd=min(d,t[k].val);
            t[k].val-=nd;
            if(!t[k].val)k=0;
            return nd;
        }
        ll s=0;
        if(x>mid)s+=upd(mid+1,r,rs(k),x,d);
        s+=upd(l,mid,ls(k),x,d-s);
        pushup(k);
        if(!t[k].val)k=0;
        return s;
    }
    ll query(int l,int r,int k,int x){
        if(r<=x)return t[k].val;
        if(x<=mid)return query(l,mid,ls(k),x);
        return query(l,mid,ls(k),x)+query(mid+1,r,rs(k),x);
    }
    int merge(int l,int r,int x,int y){
        if(!x||!y)return x|y;
        t[x].val+=t[y].val;
        if(l==r)return x;
        ls(x)=merge(l,mid,ls(x),ls(y));
        rs(x)=merge(mid+1,r,rs(x),rs(y));
        return x;
    }
    #undef mid
    #undef ls
    #undef rs
}sgt;
int rt[N];
ll ans;
int nrt;
ll nd;
ll sc;
vector<pair<int,int>> val;
void dfs(int no){
    if(!in[no])return;
    val.emplace_back(h[no],c[no]);
    sc+=c[no];
    in[no]=0;
    for(int to:e[no]){
        nrt=sgt.merge(1,lm,nrt,rt[to]);
        nd+=d[to];
    }
    dfs(fa[no]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>fa[i]>>h[i]>>c[i];
        e[fa[i]].push_back(i);
        in[fa[i]]++;
    }
    queue<int> q;
    for(int i=1;i<=n;++i){
        if(!in[i])q.push(i);
    }
    while(!q.empty()){
        int no=q.front();
        q.pop();
        for(int to:e[no]){
            d[no]+=d[to];
            rt[no]=sgt.merge(1,lm,rt[no],rt[to]);
        }
        d[no]+=sgt.upd(1,lm,rt[no],h[no],c[no]);
        if(h[no]!=lm)sgt.update(1,lm,rt[no],h[no]+1,c[no]);
        in[fa[no]]--;
        if(!in[fa[no]])q.push(fa[no]);
    }
    for(int i=1;i<=n;++i){
        if(!in[i])continue;
        val.clear();
        sc=0;
        nrt=nd=0;
        dfs(i);
        sort(val.begin(),val.end());
        ll mi=sc+nd+sgt.query(1,lm,nrt,1);
        int lf=0;
        ll nc=0;
        for(auto [f,c]:val){
            if(lf!=f){
                if(lf)mi=min(mi,sc-nc+nd+sgt.query(1,lm,nrt,lf));
                lf=f;
                nc=0;
            }
            nc+=c;
        }
        mi=min(mi,sc-nc+nd+sgt.query(1,lm,nrt,lf));
        ans+=mi;
    }
    cout<<ans<<'\n';
    return 0;
}