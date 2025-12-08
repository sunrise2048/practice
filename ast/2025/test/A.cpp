#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=21;
const ll finf=-1e16;
int n;
ll a[N];
ll b[N][N];
ll f[1<<N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=0;i<n;++i){
        cin>>a[i];
    }
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            cin>>b[i][j];
        }
    }
    memset(f,~0x3f,sizeof(f));
    f[0]=0;
    for(int i=0;i<(1<<n)-1;++i){
        if(f[i]<finf)continue;
        int x;
        for(int j=0;j<n;++j){
            if(i&(1<<j))continue;
            x=j;
            break;
        }
        for(int y=x+1;y<n;++y){
            if(i&(1<<y))continue;
            for(int z=y+1;z<n;++z){
                if(i&(1<<z))continue;
                int tz=i|(1<<x)|(1<<y)|(1<<z);
                f[tz]=max(f[tz],f[i]+max({a[x],a[y],a[z],b[x][y],b[y][z],b[x][z],b[x][y]*b[y][z]*b[x][z]}));
            }
        }
    }
    cout<<f[(1<<n)-1];
    return 0;
}