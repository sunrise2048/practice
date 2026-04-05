#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
ll a[N];
int f[N],s[N];
vector<pair<ll,int>> ve[N];
void ins(int no,ll vl,int ts){
    for(int i=0;i<ve[no].size();++i){
        auto& [tv,ns]=ve[no][i];
        ll d=__gcd(tv,vl);
        if(d==1)continue;
        if(d==tv){
            ns=max(ns,ts);
            vl/=d;
            continue;
        }
        tv/=d;
        vl/=d;
        ve[no].emplace_back(d,max(ns,ts));
    }
    if(vl!=1)ve[no].emplace_back(vl,ts);
}
int main(){
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            f[i]=s[i]=0;
            ve[i].clear();
        }
        for(int i=n;i;--i){
            cin>>a[i];
            int si;
            cin>>si;
            while(si--){
                int to;
                cin>>to;
                s[i]+=f[to];
                for(auto [vl,ts]:ve[to]){
                    vl=__gcd(vl,a[i]);
                    if(vl==1)continue;
                    ins(i,vl,ts);
                }
            }
            f[i]=s[i]+1;
            for(auto [vl,ts]:ve[i]){
                f[i]=min(f[i],s[i]+1-ts);
            }
            ins(i,a[i],0);
            for(auto& [vl,ts]:ve[i])ts+=f[i]-s[i];
            cout<<f[i]<<endl;
        }
    }
    return 0;
}