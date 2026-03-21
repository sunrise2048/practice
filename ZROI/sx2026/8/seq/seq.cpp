#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const ll inf=1e18;
int n,q;
ll a[N];
ll f[N][2];
ll s[N];
int get_id(ll k){
    int l=0,r=n+1;
    while(l<r-1){
        int mid=l+r>>1;
        if(f[mid][0]>=k)r=mid;
        else l=mid;
    }
    return r;
}
ll ans[N];
struct ques{
    int id;
    ll x,b;
    ques()=default;
    ques(int id,ll x,ll b):id(id),x(x),b(b){}
};
vector<ques> qs[N];
const ll M=5+(ll)2e12;
class LCT{
public:
    struct node{
        ll k,b;
        int lson,rson;
    }t[N];
    int cn;
    #define mid (l+r>>1)
    #define rs(k) t[k].rson
    #define ls(k) t[k].lson
    ll get(ll k,ll b,ll x){
        return k*x+b;
    }
    void update(ll l,ll r,int& k,ll tk,ll tb){
        if(!k){
            k=++cn;
            t[k].k=tk,t[k].b=tb;
            return;
        }
        if(get(t[k].k,t[k].b,l)<=get(tk,tb,l)){
            if(get(t[k].k,t[k].b,r)<=get(tk,tb,r)){
                t[k].k=tk,t[k].b=tb;
                return;
            }
            if(get(t[k].k,t[k].b,mid)<=get(tk,tb,mid)){
                swap(t[k].k,tk);swap(t[k].b,tb);
                update(mid+1,r,rs(k),tk,tb);
            }
            else update(l,mid,ls(k),tk,tb);
        }
        else if(get(t[k].k,t[k].b,r)<=get(tk,tb,r)){
            if(get(t[k].k,t[k].b,mid+1)<=get(tk,tb,mid+1)){
                swap(t[k].k,tk);swap(t[k].b,tb);
                update(l,mid,ls(k),tk,tb);
            }
            else update(mid+1,r,rs(k),tk,tb);
        }
    }
    ll query(ll l,ll r,int k,ll x){
        if(!k)return -inf;
        if(x<=mid)return max(get(t[k].k,t[k].b,x),query(l,mid,ls(k),x));
        return max(get(t[k].k,t[k].b,x),query(mid+1,r,rs(k),x));
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        f[i][0]=max(f[i-1][1],f[i-1][0]);
        f[i][1]=a[i]+f[i-1][0];
    }
    for(int i=n;i;--i)s[i]=s[i+1]+a[i];
    f[n+1][0]=inf;
    for(int i=1;i<=q;++i){
        ll k;
        cin>>k;
        int id=min(n+1,get_id(k)+3);
        ll nk;
        int cn=10;
        while(id>1&&(cn--)){
            --id;
            nk=k-f[id-1][0];
            if(nk<=a[id]&&nk>=0)qs[id].emplace_back(i,nk,(id-1)*nk);
        }
    }
    int rt=0;
    sgt.update(0,M,rt,-n,0);
    for(int i=n;i;--i){
        for(auto [id,k,b]:qs[i]){
            ans[id]=max(ans[id],s[i]+b+sgt.query(0,M,rt,k));
        }
        sgt.update(0,M,rt,-(i-1),-a[i]);
    }
    for(int i=1;i<=q;++i){
        cout<<ans[i]<<'\n';
    }
    return 0;
}