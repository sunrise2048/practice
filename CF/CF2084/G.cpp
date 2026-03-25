#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5005;
int T;
int n;
int op[N];
ll f[N][N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        memset(op,-1,sizeof(int)*(n+1));
        for(int i=1;i<=n;++i){
            int a;
            cin>>a;
            if(a)op[a]=i&1;
        }
        for(int i=0;i<=(n+1)/2;++i)memset(f[i],~0x3f,sizeof(ll)*(n/2+1));
        f[0][0]=0;
        for(int i=1;i<=n;++i){
            for(int j=0;j<i;++j){
                int k=i-1-j;
                if(j>(n+1)/2||k>n/2)continue;
                if(op[i]!=0)f[j+1][k]=max(f[j+1][k],f[j][k]+(j+1)*i+(n/2-k)*i);
                if(op[i]!=1)f[j][k+1]=max(f[j][k+1],f[j][k]+(k+1)*i+((n+1)/2-j)*i);
            }
        }
        cout<<f[(n+1)/2][n/2]<<'\n';
    }
    return 0;
}