#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=15;
const int a[11]={0,1,2,4,7,12,20,29,38,52,73};
int n;
ll w[N][N];
int p[N];
ll mx;
void get_mx(int n){
    mx=0;
    iota(p+1,p+n+1,1);
    do{
        ll s=0;
        for(int i=2;i<=n;++i){
            s+=w[p[i-1]][p[i]];
        }
        mx=max(mx,s);
    }while(next_permutation(p+1,p+n+1));
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    w[1][2]=w[2][1]=1;
    for(int i=3;i<=n;++i){
        get_mx(i-1);
        for(int j=1;j<i;++j){
            w[i][j]=w[j][i]=a[j]*(mx+1);
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            cout<<w[i][j]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}