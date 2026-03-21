#include<bits/stdc++.h>
using namespace std;
using ll=unsigned long long;
const int N=1e5+5;
const int mod=998244353;
int n;
int a[6][N];
int p[6][N];
int b[N];
ll f[N],s[N];
ll sf[4][1<<16],ss[4][1<<16];
ll bs[N];
inline bool ch(const int& x,const int& y){
    for(int i=0;i<6;++i){
        if(a[i][x]<a[i][y])return 0;
    }
    return 1;
}
inline void calc_bl(int l,int r){
    for(int i=l;i<r;++i){
        for(int j=l;j<i;++j){
            if(ch(i,j)){
                f[i]+=f[j];s[i]+=s[j];
            }
        }
        f[i]%=mod;
        s[i]=(s[i]+f[i]*b[i])%mod;
    }
}
int bid[1<<16];
inline void calc_bs(int l,int r){
    memset(sf,0,sizeof(sf));memset(ss,0,sizeof(ss));
    memset(bs+r,-1,sizeof(ll)*(n-r));
    for(int be=l;be<r;be+=16){
        const int op=(be-l)/16;
        for(int z=1;z<(1<<16);++z){
            int lb=z&-z;
            const int bd=bid[lb]+be;
            sf[op][z]=sf[op][z^lb]+f[bd];
            ss[op][z]=ss[op][z^lb]+s[bd];
        }
    }
    for(int op=0;op<6;++op){
        ll nz=0;
        for(int i=0;i<n;++i){
            const int no=p[op][i];
            if(no>=l&&no<r)nz|=(1ull<<(no-l));
            bs[no]&=nz;
        }
    }
    for(int i=r;i<n;++i){
        int bs1=bs[i]&((1<<16)-1);
        f[i]+=sf[0][bs1];s[i]+=ss[0][bs1];
    }
    for(int i=r;i<n;++i){
        int bs1;
        bs1=(bs[i]>>16)&((1<<16)-1);
        f[i]+=sf[1][bs1];s[i]+=ss[1][bs1];
    }
    
    for(int i=r;i<n;++i){
        int bs1;
        bs1=(bs[i]>>32)&((1<<16)-1);
        f[i]+=sf[2][bs1];s[i]+=ss[2][bs1];
    }
    
    for(int i=r;i<n;++i){
        int bs1;
        bs1=(bs[i]>>48)&((1<<16)-1);
        f[i]+=sf[3][bs1];s[i]+=ss[3][bs1];
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=0;i<n;++i){
        for(int j=0;j<6;++j){
            cin>>a[j][i];a[j][i]--;
            p[j][a[j][i]]=i;
        }
    }
    for(int i=0;i<n;++i)cin>>b[i];
    for(int i=0;i<n;++i)f[i]=1;
    for(int i=0;i<16;++i)bid[1<<i]=i;
    for(int be=0;be<n;be+=64){
        int ed=min(n,be+64);
        calc_bl(be,ed);
        if(ed!=n){
            calc_bs(be,ed);
        }
    }
    ll ans=0;
    for(int i=0;i<n;++i)ans=(ans+s[i])%mod;
    cout<<ans<<'\n';
    return 0;
}