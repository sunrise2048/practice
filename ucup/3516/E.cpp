#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5005;
int T;
int n;
char a[N];
bool f[N][N];
int g[N][N];
char an[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i)cin>>a[i];
        for(int i=0;i<=n;++i){
            memset(f[i],0,sizeof(bool)*(n+1));
            memset(g[i],0,sizeof(int)*(n+1));
        }
        f[0][0]=1;
        cout<<a[1];
        an[1]=a[1];
        for(int len=1;len<=n;++len){
            bool ff=0;
            an[len+1]='z';
            for(int x=0;x<=len;++x){
                if(f[x][len-1]&&a[x+len]<=an[len]){
                    f[x][len]=1;
                }
                if(x&&f[x-1][len]&&a[x+len]<=an[x]){
                    f[x][len]=1;
                }
                if(f[len-1][x]&&a[x+len]<=an[len]){
                    f[len][x]=1;
                }
                if(x&&f[len][x-1]&&a[x+len]<=an[x]){
                    f[len][x]=1;
                }
                if(f[len][x]&&len+x==n){
                    ff=1;
                    break;
                }
                if(f[len][x])an[len+1]=min(an[len+1],a[len+x+1]);
            }
            if(ff){
                cout<<'\n';
                break;
            }
            cout<<an[len+1];
        }
    }
    return 0;
}