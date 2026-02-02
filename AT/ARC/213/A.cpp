#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e4+5;
const int L=9;
int n,l;
int a[N][L];
int c[N];
int f[N];
int qmx;
int p[N];
int get(int x,int y){
    for(int i=0;i<l;++i){
        p[a[y][i]]=i;
    }
    int cn=0;
    for(int i=0;i<l;++i){
        for(int j=i+1;j<l;++j){
            if(p[a[x][i]]>p[a[x][j]])++cn;
        }
    }
    return cn;
}
const int lm=9*8/2;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>l;
    for(int i=1;i<=n;++i){
        cin>>c[i];
        for(int j=0;j<l;++j){
            cin>>a[i][j];
        }
    }
    for(int i=0;i<l;++i)a[0][i]=i+1;
    qmx=-1e9;
    for(int i=1;i<=n;++i){
        if(i>=lm)qmx=max(qmx,f[i-lm]);
        f[i]=qmx;
        for(int j=i-1;j>i-lm&&j>=0;--j){
            if(get(i,j)<=i-j)f[i]=max(f[i],f[j]);
        }
        f[i]+=c[i];
    }
    int ans=0;
    for(int i=1;i<=n;++i)ans=max(ans,f[i]);
    cout<<ans<<'\n';
    return 0;
}