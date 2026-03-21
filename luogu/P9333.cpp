#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5,M=20;
int n,m;
int a[N][M];
int s[M];
struct node{
    int mx=-M,qmx=-M;
    int z;
    void add(const int& val,const int& nz){
        if(z==nz)return;
        if(val>mx){
            qmx=mx;
            mx=val;z=nz;
        }
        else if(val>qmx)qmx=val;
    }
};
node f[1<<M];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=0;j<m;++j){
            cin>>a[i][j];
            if(a[i][j]==0)a[i][j]=-1;
            s[j]+=a[i][j];
        }
        int nz=0;
        for(int j=0;j<m;++j){
            if(a[i][j]<0)nz|=(1<<j);
        }
        f[nz].add(__builtin_popcount(nz),i);
    }
    for(int k=1;k<(1<<m);k<<=1){
        for(int i=0;i<(1<<m);i+=(k<<1)){
            for(int j=0;j<k;++j){
                f[i+j+k].add(f[i+j].mx,f[i+j].z);
                f[i+j+k].add(f[i+j].qmx,0);
                f[i+j].add(f[i+j+k].mx-1,f[i+j+k].z);
                f[i+j].add(f[i+j+k].qmx-1,0);
            }
        }
    }
    for(int i=1;i<=n;++i){
        int cn=0,tz=0;
        for(int j=0;j<m;++j){
            if(s[j]-a[i][j]-1>0)++cn;
            else if(s[j]-a[i][j]-1>-2)tz|=(1<<j);
        }
        cout<<cn+(i==f[tz].z?f[tz].qmx:f[tz].mx)<<'\n';
    }
    return 0;
}