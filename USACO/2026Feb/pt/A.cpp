#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int mod=1e9+7;
int n,q;
vector<int> e[N];
int fa[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
/*
kx+b
*/
struct fc1{
    ll k,b;
    fc1()=default;
    fc1(ll v):k(v),b(0){}
    fc1(ll k,ll b):k(k),b(b){}
    fc1 operator+(const fc1& y)const{
        return fc1(k*y.k%mod,(k*y.b+b)%mod);
    }
};
/*
?!?!?!?????
*/
struct fc2{
    ll a,b,c,d,e,f;
    fc2()=default;
    fc2(ll v):a(v),b(0),c(0),d(v),e(0),f(0){}
    fc2(ll a,ll b,ll c,ll d,ll e,ll f):a(a),b(b),c(c),d(d),e(e),f(f){}
    fc2 operator+(const fc2& y)const{
        return fc2((a*y.a+b*y.c)%mod,(a*y.b+b*y.d)%mod,(c*y.a+d*y.c)%mod,(c*y.b+d*y.d)%mod,(y.e+e*y.a+f*y.c)%mod,(y.f+e*y.b+f*y.d)%mod);
    }
};
template<typename Info>
class SGT{
public:
    int n;
    vector<Info> t;
    #define mid (l+r>>1)
    #define rs (k<<1|1)
    #define ls (k<<1)
    void build(int l,int r,int k,const vector<Info>& a){
        if(l==r){
            t[k]=a[l-1];
            return;
        }
        build(l,mid,ls,a);build(mid+1,r,rs,a);
        t[k]=t[ls]+t[rs];
    }
    void build(const vector<Info>& a){
        n=a.size();
        t.resize(n<<2);
        build(1,n,1,a);
    }
    Info query(int l,int r,int k,int x,int y){
        if(x<=l&&r<=y)return t[k];
        if(y<=mid)return query(l,mid,ls,x,y);
        if(x>mid)return query(mid+1,r,rs,x,y);
        return query(l,mid,ls,x,y)+query(mid+1,r,rs,x,y);
    }
    Info query(int l,int r){
        if(l>r)return Info(1);
        return query(1,n,1,l,r);
    }
    #undef mid
    #undef rs
    #undef ls
};
SGT<fc1> sgt_fc1;
SGT<fc2> sgt_fc2;
int d[N],si[N];
int zs[N],top[N];
int dfn[N],cn_dfn;
int nfd[N];
void dfs_dfn(int no,int tp){
    top[no]=tp;
    dfn[no]=++cn_dfn;
    nfd[cn_dfn]=no;
    if(!zs[no])return;
    dfs_dfn(zs[no],tp);
    for(int to:e[no]){
        if(to==zs[no]||to==fa[no])continue;
        dfs_dfn(to,to);
    }
}
void init_hav(){
    for(int no=n;no;--no){
        si[no]=1;
        for(int to:e[no]){
            si[no]+=si[to];
            if(si[zs[no]]<si[to])zs[no]=to;
        }
    }
    dfs_dfn(1,1);
}
int lca(int x,int y){
    while(top[x]!=top[y]){
        if(d[top[x]]>d[top[y]])x=fa[top[x]];
        else y=fa[top[y]];
    }
    return d[x]<d[y]?x:y;
}
int kth(int x,int y){
    while(top[x]!=top[y]){
        if(d[top[x]]==d[y]+1)return top[x];
        x=fa[top[x]];
    }
    return nfd[dfn[y]+1];
}
fc1 query_path_fc1(int lc,int x,bool fl=0){
    fc1 as(1);
    while(top[x]!=top[lc]){
        as=sgt_fc1.query(dfn[top[x]],dfn[x])+as;
        x=fa[top[x]];
    }
    int l=dfn[lc]+fl;
    if(l<=dfn[x])as=sgt_fc1.query(l,dfn[x])+as;
    return as;
}
fc2 query_path_fc2(int lc,int x,bool fl=0){
    fc2 as(1);
    while(top[x]!=top[lc]){
        // cout<<dfn[top[x]]<<' '<<dfn[x]<<'\n';
        as=sgt_fc2.query(dfn[top[x]],dfn[x])+as;
        x=fa[top[x]];
    }
    int l=dfn[lc]+fl;
    // cout<<dfn[lc]<<' '<<dfn[x]<<'\n';
    if(l<=dfn[x])as=sgt_fc2.query(l,dfn[x])+as;
    return as;
}
pair<ll,ll> get_nfc2(int lc,int y){
    if(lc==y)return {0,0};
    int ch=kth(y,lc);
    fc2 qu=query_path_fc2(ch,y);
    ll k=(qu.c+qu.d)%mod;
    k=ksm(k);
    ll a=k*(qu.a+qu.b)%mod;
    ll b=k*(qu.e+qu.f)%mod;
    // cout<<k<<' '<<a<<' '<<b<<'\n';
    return {(a-1+mod)%mod,b};
}
ll ny[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i=2;i<=n;++i){
        cin>>fa[i];
        e[fa[i]].push_back(i);
        d[i]=d[fa[i]]+1;
    }
    ny[0]=1;
    for(int i=1;i<=n;++i){
        ny[i]=ny[i-1]*i%mod;
    }
    ny[n]=ksm(ny[n]);
    for(int i=n;i;--i){
        ll la=ny[i-1];
        ny[i-1]=ny[i]*i%mod;
        ny[i]=ny[i]*la%mod;
    }
    vector<ll> A(n+1),B(n+1),suma(n+1),sumb(n+1);
    for(int no=n;no;--no){
        if(e[no].empty()){
            A[no]=ny[d[no]];
            B[no]=1;
        }
        else{
            ll sa=0,sb=0;
            for(int to:e[no]){
                sa=(sa+A[to])%mod;sb=(sb+B[to])%mod;
            }
            suma[no]=sa,sumb[no]=sb;
            int de=e[no].size();
            ll fA=sa*ny[de]%mod,fB=sb*ny[de]%mod;
            ll k=(1-fA+mod)%mod;
            k=ksm(k);
            A[no]=fA*k%mod;
            B[no]=(1+fB)*k%mod;
        }
    }
    vector<ll> FA(n+1),FB(n+1);
    for(int no=1;no<=n;++no){
        if(e[no].empty())continue;
        int de=e[no].size();
        ll ny_de=ny[de];
        for(int to:e[no]){
            ll SA=(suma[no]-A[to]+mod)%mod;
            ll SB=(sumb[no]-B[to]+mod)%mod;
            ll k=SA*ny_de%mod;
            ll fm=ksm((1-k+mod)%mod);
            ll a=k*fm%mod,b=ny_de*fm%mod;
            ll c=fm*(1+SB*ny_de%mod)%mod;
            ll fm2=ksm((1-a*FA[no]%mod+mod)%mod);
            ll A=b*fm2%mod;
            ll B=(a*FB[no]+c)%mod*fm2%mod;
            FA[to]=(FA[no]+1)*A%mod;
            FB[to]=((FA[no]+1)*B+FB[no])%mod;
        }
    }
    // for(int i=1;i<=n;++i){
    //     cout<<A[i]<<' '<<B[i]<<' '<<FA[i]<<' '<<FB[i]<<'\n';
    // }
    init_hav();
    vector<fc1> a_fc1(n);
    vector<fc2> a_fc2(n);
    for(int i=1;i<=n;++i){
        a_fc1[dfn[i]-1]=fc1((A[i]+1)%mod,B[i]);
        if(i==1)a_fc2[dfn[i]-1]=fc2(1);
        else{
            int nf=fa[i],de=e[nf].size();
            ll SA=(suma[nf]-A[i]+mod)%mod;
            ll SB=(sumb[nf]-B[i]+mod)%mod;
            ll K=(de+1-SA+mod)%mod;
            a_fc2[dfn[i]-1]=fc2(0,de,mod-1,K,0,(de+SB)%mod);
        }
    }
    // for(auto [a,b,c,d,e,f]:a_fc2){
    //     cout<<a<<' '<<b<<' '<<c<<' '<<d<<' '<<e<<' '<<f<<'\n';
    // }
    sgt_fc1.build(a_fc1);sgt_fc2.build(a_fc2);
    while(q--){
        int x,y;
        cin>>x>>y;
        if(x==y){
            cout<<"0\n";
            continue;
        }
        int lc=lca(x,y);
        auto [kL,bL]=get_nfc2(lc,y);
        ll k=(1-kL*FA[lc]%mod+mod)%mod;
        ll sA=(FB[lc]*kL+bL)%mod;
        ll sB=sA*ksm(k)%mod;
        ll S1=(FA[lc]*sB+FB[lc])%mod;
        ll S2=(S1+sB)%mod;
        // cout<<kL<<' '<<bL<<'\n';
        // cout<<k<<' '<<sA<<' '<<sB<<' '<<S1<<' '<<S2<<'\n';
        if(lc==x){
            cout<<sB<<'\n';
            continue;
        }
        int fx=fa[x];
        ll Sx;
        if(fx==lc)Sx=S2;
        else{
            int ch=kth(x,lc);
            fc1 ls=query_path_fc1(ch,fx);
            Sx=(ls.k*S2+ls.b)%mod;
        }
        ll ans=(A[x]*Sx+B[x])%mod;
        cout<<ans<<'\n';
    }
    return 0;
}