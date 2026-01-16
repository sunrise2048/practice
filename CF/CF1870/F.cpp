#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using I128=__int128;
const int N=65;
int T;
ll n,m;
ll mi[N];
int lm;
ll get_rk(ll val,int k){
    ll s=0;
    ll x=val;
    for(int i=k;i>=0;--i){
        s+=x-mi[i]+1;
        x/=m;
    }
    if(k==lm)return s;
    for(int i=k+1;i<lm;++i){
        s+=(val-mi[k])*mi[i-k];
    }
    s+=min((I128)n+1,(I128)val*mi[lm-k])-mi[lm];
    return s;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        mi[0]=1;
        for(int i=1;i<=60;++i){
            if((I128)mi[i-1]*m>n){
                lm=i-1;
                break;
            }
            mi[i]=mi[i-1]*m;
        }
        ll ans=0;
        for(int i=0;i<=lm;++i){
            ll L=mi[i],R=mi[i+1]-1;
            if(i==lm)R=n;
            ll l=L-1,r=R+1;
            while(l<r-1){
                ll mid=(l+r>>1);
                if(get_rk(mid,i)<=mid)l=mid;
                else r=mid;
            }
            ans+=l;
            l=L-1,r=R+1;
            while(l<r-1){
                ll mid=(l+r>>1);
                if(get_rk(mid,i)<=mid-1)l=mid;
                else r=mid;
            }
            ans-=l;
        }
        cout<<ans<<'\n';
    }
    return 0;
}