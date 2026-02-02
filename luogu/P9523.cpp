#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2505;
int n;
char s[N];
ll A,B,C;
ll f[N][N];
int lcp[N][N];
int nxt[N][N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i)cin>>s[i];
    cin>>A>>B>>C;
    for(int i=n;i;--i){
        for(int j=n;j;--j){
            if(s[i]==s[j])lcp[i][j]=lcp[i+1][j+1]+1;
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<i;++j){
            int lc=min(lcp[i][j],i-j);
            nxt[i][lc]=max(nxt[i][lc],j);
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=n;j;--j){
            nxt[i][j]=max(nxt[i][j],nxt[i][j+1]);
        }
    }
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n+1;++i)f[i][i-1]=0;
    for(int len=1;len<=n;++len){
        for(int i=1;i+len-1<=n;++i){
            int j=i+len-1;
            f[i][j]=min(f[i][j],min(f[i+1][j],f[i][j-1])+A);
            int k=i;
            int cn=1;
            while(k){
                f[k][j]=min(f[k][j],f[i][j]+B+cn*C+(j-k+1-len*cn)*A);
                ++cn;
                k=nxt[k][len];
            }
        }
    }
    cout<<f[1][n]<<'\n';
    return 0;
}