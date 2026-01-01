#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2005;
const int mod=998244353;
int n,m;
char c[N][N];
ll er[N*N];
int fa[N<<1];
int si[N<<1],cn[N<<1],s[N<<1];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>c[i][j];
        }
    }
    er[0]=1;
    for(int i=1;i<=n*m;++i){
        er[i]=er[i-1]*2%mod;
    }
    iota(fa+1,fa+n+m+1,1);
    fill(si+1,si+n+m+1,1);
    if(n%2==0&&m%2==0){
        int cn=0;
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                if(c[i][j]=='?')++cn;
            }
        }
        cout<<er[cn]<<'\n';
        return 0;
    }
    if(n%2==0){
        ll s1=1,s2=1;
        for(int i=1;i<=n;++i){
            int sm=0;
            int cn=0;
            for(int j=1;j<=m;++j){
                if(c[i][j]=='?')++cn;
                else sm^=c[i][j]-'0';
            }
            if(!cn){
                if(sm)s1=0;
                else s2=0;
            }
            else{
                s1=s1*er[cn-1]%mod;
                s2=s2*er[cn-1]%mod;
            }
        }
        cout<<(s1+s2)%mod<<'\n';
        return 0;
    }
    if(m%2==0){
        ll s1=1,s2=1;
        for(int j=1;j<=m;++j){
            int sm=0;
            int cn=0;
            for(int i=1;i<=n;++i){
                if(c[i][j]=='?')++cn;
                else sm^=c[i][j]-'0';
            }
            if(!cn){
                if(sm)s1=0;
                else s2=0;
            }
            else{
                s1=s1*er[cn-1]%mod;
                s2=s2*er[cn-1]%mod;
            }
        }
        cout<<(s1+s2)%mod<<'\n';
        return 0;
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(c[i][j]!='?'){
                if(c[i][j]=='0')continue;
                s[find(i)]^=1;
                s[find(n+j)]^=1;
                continue;
            }
            int x=find(i),y=find(j+n);
            if(x==y){
                cn[x]++;
                continue;
            }
            cn[x]+=cn[y]+1;
            si[x]+=si[y];
            s[x]^=s[y];
            fa[y]=x;
        }
    }
    ll an1=1,an2=1;
    for(int i=1;i<=n+m;++i){
        if(fa[i]!=i)continue;
        if(s[i]!=0){
            an1=0;
        }
        else an1=an1*er[cn[i]-si[i]+1]%mod;
        if((s[i]+si[i])%2!=0){
            an2=0;
        }
        else{
            an2=an2*er[cn[i]-si[i]+1]%mod;
        }
    }
    cout<<(an1+an2)%mod<<'\n';
    return 0;
}