#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int mod=1e9+7;
int T;
int n;
ll b[N];
ll jc[N],ny[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
void init(){
    const int n=1e5;
    jc[0]=1;
    for(int i=1;i<=n;++i)jc[i]=jc[i-1]*i%mod;
    ny[n]=ksm(jc[n]);
    for(int i=n;i;--i)ny[i-1]=ny[i]*i%mod;
}
ll C(int x,int y){
    return jc[x]*ny[y]%mod*ny[x-y]%mod;
}
int a[N];
vector<int> id;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    init();
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            a[i]=0;
            cin>>b[i];
        }
        id.clear();
        for(int i=n;i;--i){
            if(!b[i])continue;
            id.push_back(i);
            for(int j=i-1;j;--j){
                b[j]=(b[j]-b[i]*C(i,j)%mod+mod)%mod;
            }
        }
        int z=0;
        const int U=(1<<29);
        for(int no:id){
            int vl=b[no];
            while(vl<U&&(vl&z))vl+=mod;
            for(int i=1;i<=no;++i)a[i]|=vl;
        }
        for(int i=1;i<=n;++i){
            cout<<a[i]<<' ';
        }cout<<'\n';
    }
    return 0;
}