#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int mod=1e4+7;
int n,m,q;
ll en,em;
map<int,int> mh[2],ml[2];
map<pair<int,int>,int> xz;
int fl;
set<int> sth[2],stl[2];
ll s0[4],s1[4];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
ll calc(){
    if(fl)return 0;
    s0[0]=sth[0].empty()+sth[1].empty();
    s1[0]=stl[0].empty()+stl[1].empty();
    s0[1]=max(0,(sth[0].empty()?n:*sth[0].begin())-(sth[1].empty()?1:*sth[1].rbegin()))%mod;
    s1[1]=max(0,(stl[0].empty()?m:*stl[0].begin())-(stl[1].empty()?1:*stl[1].rbegin()))%mod;
    s0[2]=max(0,(sth[1].empty()?n:*sth[1].begin())-(sth[0].empty()?1:*sth[0].rbegin()))%mod;
    s1[2]=max(0,(stl[1].empty()?m:*stl[1].begin())-(stl[0].empty()?1:*stl[0].rbegin()))%mod;
    en=ksm(2,n-sth[0].size()-sth[1].size()),em=ksm(2,m-stl[0].size()-stl[1].size());
    s0[3]=(en-s0[0]-s0[1]-s0[2]+3*mod)%mod;
    s1[3]=(em-s1[0]-s1[1]-s1[2]+3*mod)%mod;
    ll ans=0;
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            if(i&j)continue;
            ans=(ans+s0[i]*s1[j])%mod;
        }
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>q;
    cout<<calc()<<'\n';
    for(int i=1;i<=q;++i){
        char op;
        int x,y;
        cin>>op>>x>>y;
        if(op=='+'){
            int z;
            cin>>z;--z;
            if(z>1)z^=1;
            xz[{x,y}]=z;
            int d=z&1;
            d^=(x&1)^(y&1);
            if(!mh[d][x]){
                sth[d].insert(x);
                if(mh[d^1][x])++fl;
            }
            mh[d][x]++;
            d=z/2;
            d^=(x&1)^(y&1);
            if(!ml[d][y]){
                stl[d].insert(y);
                if(ml[d^1][y])++fl;
            }
            ml[d][y]++;
        }
        else{
            int z=xz[{x,y}];
            int d=z&1;
            d^=(x&1)^(y&1);
            --mh[d][x];
            if(!mh[d][x]){
                sth[d].erase(x);
                if(mh[d^1][x])--fl;
            }
            d=z/2;
            d^=(x&1)^(y&1);
            --ml[d][y];
            if(!ml[d][y]){
                stl[d].erase(y);
                if(ml[d^1][y])--fl;
            }
        }
        cout<<calc()<<'\n';
    }
    return 0;
}