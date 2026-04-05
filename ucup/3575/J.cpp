#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e4+5;
int n,mod;
ll inv[N];
int cn[N];
int main(){
    cin>>n>>mod;
    int m=n*n;
    inv[1]=1;
    for(int i=2;i<=n;++i)inv[i]=(ll)(mod-mod/i)*inv[mod%i]%mod;
    ll jc=1;
    for(int i=1;i<=n;++i)jc=jc*i%mod;
    int cn0=n;
    ll s=1;
    ll las=0;
    ll ans=0;
    const int B=1e6;
    for(int L=n;L<=m;L+=B){
        int R=min(m,L+B-1);
        int len=R-L+1;
        vector<int> pr(len,-1),ne,ve;
        ne.reserve(len/2+5);ve.reserve(len/2+5);
        for(int i=1;i<=n;++i){
            int jl=max(n-i+1,(L+i-1)/i);
            int jr=min(n,R/i);
            for(int j=jl;j<=jr;++j){
                int id=i*j-L;
                ve.push_back(i);
                ne.push_back(pr[id]);
                pr[id]=ve.size()-1;
            }
        }
        for(int id=0;id<len;++id){
            if(pr[id]==-1)continue;
            int x=L+id;
            if(x>las){
                ans=(ans+(cn0?0:s)*(x-las))%mod;
                las=x;
            }
            for(int no=pr[id];no!=-1;no=ne[no]){
                int i=ve[no];
                int ls=cn[i];cn[i]++;
                if(ls==0)--cn0;
                else{
                    s=s*inv[ls]%mod*(ls+1)%mod;
                }
            }
        }
    }
    if(las<m){
        ans=(ans+(cn0?0:s)*(m-las))%mod;
    }
    cout<<(jc*m-ans+mod)%mod<<'\n';
    return 0;
}