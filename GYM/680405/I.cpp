#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1005;
int T;
int n,m;
int a[N][N];
int main(){
    ios::sync_with_stdio(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                cin>>a[i][j];
            }
            sort(a[i]+1,a[i]+m+1);
        }
        ll s=0;
        for(int j=1;j<=m;++j){
            int mi=1e9+7;
            for(int i=1;i<=n;++i)mi=min(mi,a[i][j]);
            s+=mi;
        }
        cout<<s<<'\n';
    }
    return 0;
}