#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int M=650;
const int mod=998244353;
int T;
int n,x;
int f[M][N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>x;
        if((ll)n*(n+1)/2-1>x){
            cout<<"0\n";
            continue;
        }
        if(n==1){
            cout<<x<<'\n';
            continue;
        }
        ++x;
        for(int i=1;i<=n;++i)memset(f[i],0,sizeof(int)*(x+1));
        f[1][1]=1;
        for(int i=1;i<=n;++i){
            for(int j=1;j<=x;++j){
                if(i!=n&&i+j<=x)f[i][i+j]=(f[i][i+j]+f[i][j])%mod;
                if(i+j+1<=x)f[i+1][i+j+1]=(f[i+1][i+j+1]+f[i][j])%mod;
            }
        }
        int ans=0;
        for(int i=1;i<=x;++i)ans=(ans+(ll)f[n][i]*(x-i+1))%mod;
        cout<<ans<<'\n';
    }
    return 0;
}