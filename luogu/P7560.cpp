#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2.5e5+5;
int n,m,q;
struct ope{
    int op,l,r;
    ll x,y;
}qs[N];
class SGT{
public:
    ll t_mi[N<<2],t_add[N<<2];
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    void upd(int k,ll d){
        if(d==0)return;
        t_add[k]+=d;
        if(t_add[k]<0){
            t_mi[k]+=t_add[k];
            t_add[k]=0;
        }
    }
    void pushdown(int k){
        upd(ls,t_mi[k]);
        upd(ls,t_add[k]);
        upd(rs,t_mi[k]);
        upd(rs,t_add[k]);
        t_mi[k]=t_add[k]=0;
    }
    void update(int l,int r,int k,int x,int y,ll d){
        if(x<=l&&r<=y){
            upd(k,d);
            return;
        }
        pushdown(k);
        if(x<=mid)update(l,mid,ls,x,y,d);
        if(y>mid)update(mid+1,r,rs,x,y,d);
    }
    ll query(int l,int r,int k,int x){
        if(l==r)return t_add[k];
        pushdown(k);
        if(x<=mid)return query(l,mid,ls,x);
        return query(mid+1,r,rs,x);
    }
    #undef mid
    #undef rs
    #undef ls
}sgt;
int lm;
class BIT{
public:
    ll t[N];
    void cl(){memset(t,0,sizeof(t));}
    void up(int x,ll d){
        while(x<=lm){
            t[x]+=d;
            x+=(x&-x);
        }
    }
    ll qu_val(int x){
        ll s=0;
        while(x){
            s+=t[x];
            x-=(x&-x);
        }
        return s;
    }
    int qu(ll k){
        int no=0;
        for(int i=17;i>=0;--i){
            if(no+(1<<i)<=lm&&t[no+(1<<i)]<k){
                k-=t[no+(1<<i)];
                no+=(1<<i);
            }
        }
        return no+1;
    }
}bit;
int ans[N];
vector<int> qu[N],up[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>q;lm=n;
    for(int i=1;i<=q;++i){
        cin>>qs[i].op;
        if(qs[i].op==1){
            cin>>qs[i].l>>qs[i].r>>qs[i].x>>qs[i].y;
            sgt.update(1,n,1,qs[i].l,qs[i].r,qs[i].y);
            bit.up(qs[i].l,qs[i].y);
            bit.up(qs[i].r+1,-qs[i].y);
            up[qs[i].l].push_back(i);
            up[qs[i].r+1].push_back(-i);
        }
        else if(qs[i].op==2){
            cin>>qs[i].l>>qs[i].r>>qs[i].x;
            sgt.update(1,n,1,qs[i].l,qs[i].r,-qs[i].x);
        }
        else{
            cin>>qs[i].x>>qs[i].y;
            ll si=sgt.query(1,n,1,qs[i].x),s=bit.qu_val(qs[i].x);
            if(qs[i].y>si){
                continue;
            }
            qs[i].y+=s-si;
            qu[qs[i].x].push_back(i);
        }
    }
    bit.cl();lm=q;
    for(int i=1;i<=n;++i){
        for(int no:up[i]){
            if(no>0)bit.up(no,qs[no].y);
            else bit.up(-no,-qs[-no].y);
        }
        for(int no:qu[i]){
            ans[no]=qs[bit.qu(qs[no].y)].x;
        }
    }
    for(int i=1;i<=q;++i){
        if(qs[i].op==3)cout<<ans[i]<<'\n';
    }
    return 0;
}