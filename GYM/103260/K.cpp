#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int n=2e5;
int m;
set<pair<int,int>> st[N];
set<int> ts[N<<2];
int lz[N<<2],t[N<<2];
void init(){
    for(int i=1;i<=(n<<2);++i){
        lz[i]=t[i]=n+1;
    }
    lz[1]=t[1]=0;
    for(int i=0;i<=n;++i){
        ts[1].insert(i);
        st[i].emplace(0,n);
    }
}
#define mid (l+r>>1)
#define rs (k<<1|1)
#define ls (k<<1)
void pushup(int k){
    t[k]=min(lz[k],max(t[ls],t[rs]));
}
void upd(int l,int r,int k){
    if(ts[k].empty()){
        lz[k]=n+1;
    }
    else lz[k]=*ts[k].begin();
    if(l==r)t[k]=lz[k];
    else pushup(k); 
}
void update(int l,int r,int k,int x,int y,int d){
    if(x<=l&&r<=y){
        ts[k].erase(d);
        upd(l,r,k);
        return;
    }
    if(ts[k].count(d)){
        ts[k].erase(d);
        ts[ls].insert(d);
        upd(l,mid,ls);
        ts[rs].insert(d);
        upd(mid+1,r,rs);
    }
    if(x<=mid)update(l,mid,ls,x,y,d);
    if(y>mid)update(mid+1,r,rs,x,y,d);
    upd(l,r,k);
}
int query(int l,int r,int k,int x,int y){
    if(x<=l&&r<=y)return t[k];
    if(y<=mid)return min(lz[k],query(l,mid,ls,x,y));
    if(x>mid)return min(lz[k],query(mid+1,r,rs,x,y));
    return min(lz[k],max(query(l,mid,ls,x,y),query(mid+1,r,rs,x,y)));
}
#undef mid
#undef rs
#undef ls
ll lans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin>>m;
    while(m--){
        int op;
        cin>>op;
        if(op==1){
            ll x,l,r;
            cin>>x>>l>>r;
            x^=lans,l^=lans,r^=lans;
            auto it=st[x].lower_bound({l,0});
            while(it!=st[x].end()&&it->first<=r){
                auto [tl,tr]=*it;
                st[x].erase(it);
                update(0,n,1,tl,min((ll)tr,r),x);
                if(tr>r)st[x].emplace(r+1,tr);
                it=st[x].lower_bound({l,0});
            }
            if(it!=st[x].begin()&&prev(it)->second>=l){
                --it;
                auto [tl,tr]=*it;
                st[x].erase(it);
                update(0,n,1,l,min(r,(ll)tr),x);
                st[x].emplace(tl,l-1);
                if(tr>r)st[x].emplace(r+1,tr);
            }
        }
        else{
            ll l,r;
            cin>>l>>r;
            l^=lans,r^=lans;
            int ans=query(0,n,1,l,r);
            lans+=ans;
            cout<<ans<<'\n';
        }
    }
    return 0;
}