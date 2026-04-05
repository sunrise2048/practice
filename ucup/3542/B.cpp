#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int g[3][3]={{9,18,27},{21,42,51},{37,58,67}};
int T;
ll w,s;
ll f[5][13];
ll calc1(ll w,ll s){
    ll kw=w/3;
    ll ans=0;
    ll bs=4*4*4;
    for(int i=3;i;--i){
        ans+=min(s,kw)*(bs-27);
        s-=min(s,kw);
        bs=bs/4*3;
    }
    return ans;
}
ll calc2(ll w,ll s){
    ll ks=s/3;
    ll ls=0;
    ll ans=0;
    for(int i=0;i<3;++i){
        ans+=min(w,ks)*(g[i][2]-ls);
        ls=g[i][2];
        w-=min(w,ks);
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    for(int i=0;i<5;++i){
        for(int j=0;j<=i*3;++j){
            for(int w=1;w<=3;++w){
                if(i+w>4)continue;
                for(int k=1;k<=3;++k){
                    f[i+w][j+k]=max(f[i+w][j+k],f[i][j]+g[w-1][k-1]);
                }
            }
        }
    }
    cin>>T;
    while(T--){
        cin>>w>>s;
        ll ns=min(s,3*w);
        ll ans=0;
        for(int cw=0;cw<5;++cw){
            for(int cs=0;cs<13;++cs){
                if(cw>w||cs>ns)continue;
                ll tw=w-cw,ts=s-cs;
                if(ts<=tw&&tw%3==0){
                    ll sm=f[cw][cs]+calc1(tw,ts);
                    ans=max(ans,sm);
                }
                if(tw<=ts&&ts%3==0){
                    ll sm=f[cw][cs]+calc2(tw,ts);
                    ans=max(ans,sm);
                }
            }
        }
        ans+=27*s;
        cout<<ans<<'\n';
    }
    return 0;
}