#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int T;
int n;
ll a[N];
ll f[N][2][4];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        memset(f,0,sizeof(f));
        for(int i=1;i<=n;++i){
            for(int s:{0,1}){
                for(int sz:{0,1,2,3}){
                    for(int op:{-1,0,1}){
                        if(s+op==2)continue;
                        if((sz&(1<<(i&1)))&&op==1)continue;
                        int ts=max(0,s+op);
                        int tsz=sz;
                        if(op==-1){
                            if(sz&(1<<(i&1)))tsz-=(1<<(i&1));
                        }
                        else if(op==1){
                            tsz+=(1<<(i&1));
                        }
                        f[i][ts][tsz]=max(f[i][ts][tsz],f[i-1][s][sz]+op*a[i]);
                    }
                }
            }
        }
        ll ans=0;
        for(int s:{0,1}){
            for(int sz:{0,1,2,3}){
                ans=max(ans,f[n][s][sz]);
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}