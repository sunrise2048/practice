#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int mod=1e9+7;
int T;
ll n,m;
ll xl,xr,yl,yr;
const int sH[6]={0,1,3,4,6,9};
const int sG[6]={0,1,5,8,16,31};
const int sS[6]={0,1,3,6,10,15};
ll pre_g0(ll x){
    if(x<0)return 0;
    ll cyc=x/6,ys=x%6;
    ll mc=cyc%mod;
    ll s=0;
    s=(6*mc%mod*mc%mod+5*mc)%mod;
    s=(s+2*mc*ys)%mod;
    s=(s+sH[ys])%mod;
    return s;
}
ll pre_g1(ll x){
    if(x<0)return 0;
    ll cyc=x/6,ys=x%6;
    ll mc=cyc%mod;
    ll m2=mc*mc%mod,m3=m2*mc%mod;
    ll s=0;
    s=(s+24*m3+6*m2+mc)%mod;
    s=(s+12*m2%mod*(ys+1))%mod;
    s=(s+2*mc*sS[ys])%mod;
    s=(s+6*mc*sH[ys])%mod;
    s=(s+sG[ys])%mod;
    return s;
}
ll calc_g0(ll l,ll r){
    if(l>r)return 0;
    return (pre_g0(r)-pre_g0(l-1)+mod)%mod;
}
ll calc_g1(ll l,ll r){
    if(l>r)return 0;
    return (pre_g1(r)-pre_g1(l-1)+mod)%mod;
}
ll calc(ll x,ll y){
    if(x>y)swap(x,y);
    ll sum=0;
    sum=(sum+calc_g1(4,x+2)-3*calc_g0(4,x+2)%mod+mod)%mod;
    sum=(sum+(x-1)%mod*calc_g0(x+3,y+2))%mod;
    sum=(sum+(x+y+1)%mod*calc_g0(y+3,x+y)-calc_g1(y+3,x+y)+mod)%mod;
    return sum;
}
const int xs0[2]={4,8},xs1[2]={16,26};
const int xf0[2][6]={{0,0,0,2,2,4},{0,2,2,4,6,8}};
const int xf1[2][6]={{0,0,0,6,6,16},{0,2,2,8,16,26}};
ll calc_hf0(ll x,int op){
    if(x<0)return 0;
    ll cyc=x/6,ys=x%6;
    ll mc=cyc%mod;
    ll s=0;
    s=(s+6*mc%mod*(mc-1+mod))%mod;
    s=(s+xs0[op]*mc)%mod;
    s=(s+2*mc%mod*(ys+1))%mod;
    s=(s+xf0[op][ys])%mod;
    return s;
}
ll calc_hf1(ll x,int op){
    if(x<0)return 0;
    ll cyc=x/6,ys=x%6;
    ll mc=cyc%mod;
    ll m2=mc*mc%mod;
    ll s=0;
    s=(s+12*mc%mod*(mc-1+mod)%mod*(2*mc-1+mod))%mod;
    s=(s+(15+3*xs0[op])*mc%mod*(mc-1+mod))%mod;
    s=(s+xs1[op]*mc)%mod;
    s=(s+12*m2%mod*(ys+1))%mod;
    s=(s+2*mc*sS[ys])%mod;
    s=(s+6*mc*xf0[op][ys])%mod;
    s=(s+xf1[op][ys])%mod;
    return s;
}
ll ppre_s(ll x,int op){
    if(x<op)return 0;
    ll len=(x-op)/2;
    return calc_hf0(len,op);
}
ll ppre_st(ll x,int op){
    if(x<op)return 0;
    ll len=(x-op)/2;
    ll a=op?calc_hf0(len,op):0,b=calc_hf1(len,op);
    return (2*b+a)%mod;
}
ll pre_s(ll x){
    if(x<0)return 0;
    return (ppre_s(x,0)+ppre_s(x,1))%mod;
}
ll calc1(ll x,ll y){
    if(x<4||y<2)return 0;
    ll s=0;
    ll A=x-2*y,L=0;
    if(A>=0){
        s=(s+(y-1)%mod*pre_s(A))%mod;
        L=A+1;
    }
    ll R=x-4;
    if(L>R)return s;
    int op=(x&1);
    ll ss=(ppre_s(R,op)-ppre_s(L-1,op)+mod)%mod;
    ll st=(ppre_st(R,op)-ppre_st(L-1,op)+mod)%mod;
    ll ds=(ppre_s(R,op^1)-ppre_s(L-1,op^1)+mod)%mod;
    ll dt=(ppre_st(R,op^1)-ppre_st(L-1,op^1)+mod)%mod;
    ll bs=((x-2)%mod*ss-st+mod)%mod;
    bs=(bs+(x-3)%mod*ds-dt+mod)%mod;
    bs=(mod+1)/2*bs%mod;
    return (s+bs)%mod;
}
ll solve(ll x,ll y){
    if(x<2||y<2)return 0;
    ll ans=(calc(x,y)+calc1(x,y)+calc1(y,x)+2)%mod;
    return ans;
}
int main(){
    freopen("matrix.in","r",stdin);
    freopen("matrix.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T>>n>>m;
    while(T--){
        cin>>xl>>xr>>yl>>yr;
        --xl,--xr,--yl,--yr;
        ll ans=solve(xr,yr)-solve(xl-1,yr)-solve(xr,yl-1)+solve(xl-1,yl-1)+2*mod;
        ans%=mod;
        cout<<ans<<'\n';
    }
    return 0;
}