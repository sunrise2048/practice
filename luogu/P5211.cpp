#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int mod=2000000033;
const int bas=2000000011;
const int K=455;
const int kc=450;
int n,q;
int c[N];
class HASH{
public:
    int ks;
    ll bs[N];
    ll bps[N];
    int L[K],R[K];
    int kid[N];
    ll sm[K];
    ll ps[N];
    ll lz[K];
    void init(){
        bs[0]=bps[0]=1;
        for(int i=1;i<=n;++i){
            bs[i]=bs[i-1]*bas%mod;
            bps[i]=(bps[i-1]+bs[i])%mod;
        }
        ks=(n+kc-1)/kc;
        for(int i=1;i<=ks;++i){
            L[i]=R[i-1]+1;
            R[i]=i*kc;
        }
        R[ks]=n;
        for(int i=1;i<=ks;++i){
            sm[i]=sm[i-1];
            for(int j=L[i];j<=R[i];++j){
                kid[j]=i;
                sm[i]=(sm[i]+bs[j]*c[j]%mod+mod)%mod;
                ps[j]=((j==L[i]?0:ps[j-1])+bs[j]*c[j]%mod+mod)%mod;
            }
        }
    }
    void upd(int l,int r,ll d){
        if(kid[l]==kid[r]){
            const int kd=kid[l];
            for(int i=kd;i<=ks;++i)sm[i]=(sm[i]+(bps[r]-bps[l-1]+mod)%mod*d%mod+mod)%mod;
            for(int i=l;i<=r;++i){
                c[i]+=d;
                ps[i]=(ps[i]+(bps[i]-bps[l-1]+mod)%mod*d%mod+mod)%mod;
            }
            for(int i=r+1;i<=R[kd];++i){
                ps[i]=(ps[i]+(bps[r]-bps[l-1]+mod)%mod*d%mod+mod)%mod;
            }
            return;
        }
        const int kdx=kid[l],kdy=kid[r];
        sm[kdx]=(sm[kdx]+(bps[R[kdx]]-bps[l-1]+mod)%mod*d%mod+mod)%mod;
        for(int i=l;i<=R[kdx];++i){
            ps[i]=(ps[i]+(bps[i]-bps[l-1]+mod)%mod*d%mod+mod)%mod;
            c[i]+=d;
        }
        for(int i=kdx+1;i<kdy;++i){
            sm[i]=(sm[i]+(bps[R[i]]-bps[l-1]+mod)%mod*d%mod+mod)%mod;
            lz[i]+=d;
        }
        for(int i=kdy;i<=ks;++i){
            sm[i]=(sm[i]+(bps[r]-bps[l-1]+mod)%mod*d%mod+mod)%mod;
        }
        for(int i=L[kdy];i<=r;++i){
            ps[i]=(ps[i]+(bps[i]-bps[L[kdy]-1]+mod)%mod*d%mod+mod)%mod;
            c[i]+=d;
        }
        for(int i=r+1;i<=R[kdy];++i)ps[i]=(ps[i]+(bps[r]-bps[L[kdy]-1]+mod)%mod*d%mod+mod)%mod;
    }
    ll query(int l,int r){
        if(kid[l]==kid[r])return ((ps[r]-(l==L[kid[l]]?0:ps[l-1])+mod)%mod+(lz[kid[l]]%mod+mod)%mod*((bps[r]-bps[l-1]+mod)%mod)%mod)%mod;
        const int kdx=kid[l],kdy=kid[r];
        return ((ps[r]+sm[kdy-1]-sm[kdx-1]+mod-(l==L[kdx]?0:ps[l-1])+mod)%mod-(lz[kdx]%mod+mod)%mod*((bps[l-1]-bps[L[kdx]-1]+mod)%mod)%mod+mod+(lz[kdy]%mod+mod)%mod*((bps[r]-bps[L[kdy]-1]+mod)%mod)%mod)%mod;
    }
    ll yw(int id){return bs[id];}
    int getc(int id){
        return c[id]+lz[kid[id]];
    }
}geth;
struct node{
    vector<int> id;
}t[N<<2];
#define mid (l+r+1>>1)
#define rs (k<<1|1)
#define ls (k<<1)
bool cmp(int x,int y,int R,bool fl=1){
    int l=0,r=R-y+2;
    ll bs=geth.yw(y-x);
    while(l<r-1){
        int md=(l+r>>1);
        if(geth.query(x,x+md-1)*bs%mod==geth.query(y,y+md-1))l=md;
        else r=md;
    }
    return (l==R-y+1?fl:geth.getc(x+l)<geth.getc(y+l));
}
void pushup(int l,int r,int k){
    t[k]=t[rs];
    int bst=-1;
    for(int x:t[ls].id){
        if(bst==-1||cmp(x,bst,r))bst=x;
    }
    t[k].id.push_back(bst);
}
void build(int l,int r,int k){
    if(l==r){
        t[k].id.push_back(l);
        return;
    }
    build(l,mid-1,ls);build(mid,r,rs);
    pushup(l,r,k);
}
void update(int l,int r,int k,int x,int y){
    if(x<=l&&r<=y)return;
    if(x<mid)update(l,mid-1,ls,x,y);
    if(y>=mid)update(mid,r,rs,x,y);
    pushup(l,r,k);
}
int bst;
void query(int l,int r,int k,int x,int y){
    if(x<=l&&r<=y){
        for(int nx:t[k].id){
            if(bst==-1||cmp(nx,bst,y,0))bst=nx;
        }
        return;
    }
    if(y>=mid)query(mid,r,rs,x,y);
    if(x<mid)query(l,mid-1,ls,x,y);
}
#undef mid
#undef rs
#undef ls
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        cin>>c[i];
    }
    geth.init();
    build(1,n,1);
    while(q--){
        int op,l,r;
        cin>>op>>l>>r;
        if(op==2){
            bst=-1;
            query(1,n,1,l,r);
            cout<<bst<<'\n';
        }
        else{
            int d;
            cin>>d;
            geth.upd(l,r,d);
            update(1,n,1,l,r);
        }
    }
    return 0;
}