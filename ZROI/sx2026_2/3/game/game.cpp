#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int kc=500;
const int K=505;
int n,m;
int a[N];
vector<ll> t[N<<2];
#define mid (l+r>>1)
#define rs (k<<1|1)
#define ls (k<<1)
vector<ll> pushup(const vector<ll>& x,const vector<ll>& y){
    vector<ll> ve=x;
    for(ll val:y){
        while(ve.size()>1&&ve.back()>=val&&ve.back()>=ve[ve.size()-2]){
            val=val-ve.back()+ve[ve.size()-2];
            ve.pop_back();ve.pop_back();
        }
        ve.push_back(val);
    }
    return ve;
}
void build(int l,int r,int k){
    if(l==r){
        t[k].push_back(a[l]);
        return;
    }
    build(l,mid,ls);build(mid+1,r,rs);
    t[k]=pushup(t[ls],t[rs]);
}
void update(int l,int r,int k,int x){
    if(l==r){
        t[k][0]=a[x];
        return;
    }
    if(x<=mid)update(l,mid,ls,x);
    else update(mid+1,r,rs,x);
    t[k]=pushup(t[ls],t[rs]);
}
vector<ll> query(int l,int r,int k,int x,int y){
    if(x<=l&&r<=y)return t[k];
    if(y<=mid)return query(l,mid,ls,x,y);
    if(x>mid)return query(mid+1,r,rs,x,y);
    return pushup(query(l,mid,ls,x,y),query(mid+1,r,rs,x,y));
}
#undef mid
#undef rs
#undef ls
int main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    build(1,n,1);
    while(m--){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            a[x]=y;
            update(1,n,1,x);
        }
        else{
            vector<ll> as=query(1,n,1,x,y);
            sort(as.begin(),as.end());
            ll ans=0;
            int op=1;
            while(!as.empty()){
                ans+=op*as.back();
                op=-op;
                as.pop_back();
            }
            cout<<ans<<'\n';
        }
    }
    return 0;
}