#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e3+5;
const ll inf=1e16;
int T;
int n;
pair<ll,ll> a[N];
ll f[2][N][5];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            int x,y;
            cin>>x>>y;
            a[i].first=x+y;
            a[i].second=x-y;
        }
        sort(a+1,a+n+1,[](const pair<int,int>& x,const pair<int,int>& y){
            return x.second<y.second;
        });
        memset(f,0x3f,sizeof(f));
        f[0][0][0]=0;
        for(int i=1;i<=n;++i){
            const int op=i&1;
            for(int j=0;j<=i;++j){
                f[op][j][0]=f[op][j][1]=f[op][j][2]=f[op][j][3]=f[op][j][4]=inf;
            }
            f[op][0][0]=f[op^1][0][0];
            for(int j=1;j<=i;++j){
                f[op][j][1]=min({f[op^1][j][1],f[op^1][j-1][1]+2*a[i].first,f[op^1][j-1][0]+2*a[i].first-2*a[i].second});
                f[op][j][2]=min({f[op^1][j][2],f[op^1][j-1][2]+2*a[i].first,f[op^1][j-1][1]+a[i].first+a[i].second,f[op^1][j-1][0]+a[i].first-a[i].second});
                f[op][j][3]=min({f[op^1][j][3],f[op^1][j-1][3]+2*a[i].first,f[op^1][j-1][2]+a[i].first-a[i].second});
                f[op][j][4]=min({f[op^1][j][4],f[op^1][j-1][3]+2*a[i].first+2*a[i].second,f[op^1][j-1][2]+a[i].first+a[i].second});
            }
        }
        for(int i=2;i<=n;++i){
            cout<<f[n&1][i][4]/2<<' ';
        }cout<<'\n';
    }
    return 0;
}