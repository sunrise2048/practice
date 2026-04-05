#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2005;
int T;
int n,d;
int a[N];
bitset<N> f[N],g[2][N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>d;
        for(int i=1;i<=n;++i)cin>>a[i];
        sort(a+1,a+n+1);
        if(a[n]+a[n-1]>d){
            cout<<"No\n";
            continue;
        }
        f[0].reset();
        f[0][0]=1;
        for(int i=1;i<=n-1;++i){
            f[i]=f[i-1]|(f[i-1]<<a[i]);
        }
        if(f[n-1][d-a[n]]){
            cout<<"Yes\n";
            continue;
        }
        for(int j=0;j<=d;++j){
            g[0][j].reset();
            g[1][j].reset();
        }
        g[0][0][0]=1;
        for(int i=0;i<n;++i){
            for(int j=0;j<=d-a[n];++j)g[(i+1)&1][j].reset();
            for(int j=0;j<=d-a[n];++j){
                g[(i+1)&1][j]|=g[i&1][j];
                g[(i+1)&1][j]|=g[i&1][j]<<a[i+1];
                g[(i+1)&1][j+a[i+1]]|=g[i&1][j];
            }
        }
        bool fl=0;
        for(int i=a[n];d-i>=a[n];++i){
            if(g[n&1][i][d-i]){
                fl=1;
                break;
            }
        }
        if(fl)cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}