#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int T;
ll x,y;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>x>>y;
        ll ans=0;
        for(int hb=50;hb>=0;--hb){
            ll bs=(1ll<<hb);
            if(x%(2*bs)==0&&(y+1)%(2*bs)==0){
                ans+=bs;
                continue;
            }
            ll jz=(y/(2*bs))*(2*bs)+bs;
            if(x+y+1==2*jz){
                ll d=jz-x;
                ans+=(d&-d);
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}