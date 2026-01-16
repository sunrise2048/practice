#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e3+5;
const int mod=998244353;
int T;
int n,m;
int a[N];
int f[N][N];
bool fl[N][N];
int gc[N][N];
vector<int> e[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    for(int i=1;i<=3000;++i){
        gc[0][i]=i;
        for(int j=1;j<i;++j){
            gc[j][i]=gc[i%j][j];
        }
    }
    for(int i=1;i<=3000;++i){
        for(int j=i+1;j<=3000;++j){
            int k=i*j/gc[i][j];
            if(k/i-k/j!=1)continue;
            fl[i][j]=1;
            e[i].push_back(j);
        }
    }
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        if(a[1]&&a[1]!=1){
            cout<<"0\n";
            continue;
        }
        f[1][1]=1;
        for(int i=2;i<=n;++i){
            memset(f[i],0,sizeof(int)*(m+1));
            for(int j=i-1;j<=m;++j){
                if(!f[i-1][j])continue;
                if(a[i]){
                    if(fl[j][a[i]]){
                        f[i][a[i]]=(f[i][a[i]]+f[i-1][j])%mod;
                    }
                    continue;
                }
                for(int k:e[j]){
                    if(k>m)break;
                    f[i][k]=(f[i][k]+f[i-1][j])%mod;
                }
            }
        }
        int ans=0;
        for(int i=n;i<=m;++i)ans=(ans+f[n][i])%mod;
        cout<<ans<<'\n';
    }
    return 0;
}