#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
const ll mod=1e9+7;
const ll bas=19260817;
int T;
int n,m;
int a[N],b[N];
ll bs[N];
ll ha[N],hb[N];
void init(){
    const int n=3e5;
    bs[0]=1;
    for(int i=1;i<=n;++i)bs[i]=bs[i-1]*bas%mod;
}
bool ch(int x,int y,int len){
    return (ha[x+len-1]-ha[x-1]*bs[len]%mod+mod)%mod==(hb[y+len-1]-hb[y-1]*bs[len]%mod+mod)%mod;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    init();
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n*m;++i)cin>>a[i];
        for(int i=1;i<=n*m;++i)cin>>b[i];
        for(int i=1;i<=n*m;++i){
            ha[i]=(ha[i-1]*bas+a[i])%mod;
            hb[i]=(hb[i-1]*bas+b[i])%mod;
        }
        int cn=0;
        int x=1;
        for(int i=1;i<=n;++i){
            int y=(i-1)*m+1;
            while(y<=i*m&&x<=(i-1)*m){
                if(a[x]==b[y])++x;
                else ++cn;
                ++y;
            }
            while(y<=i*m){
                int len=i*m-y+1;
                if(ch((i-1)*m+1,y,len)){
                    x+=len;
                    break;
                }
                ++y;++cn;
            }
        }
        cout<<cn<<'\n';
    }
    return 0;
}