#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
const int mod=1e9+7;
int n,q;
ll a[N],b[N];
ll sa[N];
ll lk[N],lb[N];
int ne[N],na[N];
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        cin>>a[i]>>b[i];
    }
    lk[0]=1;
    for(int i=1;i<=n;++i){
        if(b[i]>1){
            lk[i]=lk[i-1]*b[i]%mod;
            lb[i]=lb[i-1]*b[i]%mod;
        }
        else{
            lk[i]=lk[i-1];
            lb[i]=(lb[i-1]+a[i])%mod;
        }
        sa[i]=sa[i-1]+a[i];
    }
    ne[n+1]=n+1;
    na[n+1]=n+1;
    for(int i=n;i;--i){
        if(b[i]>1)ne[i]=i;
        else ne[i]=ne[i+1];
        if(a[i]>0)na[i]=i;
        else na[i]=na[i+1];
    }
    while(q--){
        ll x;
        int l,r;
        cin>>x>>l>>r;
        ++l;
        if(x==0){
            int tn=na[l];
            if(tn>r){
                cout<<"0\n";
                continue;
            }
            x=a[tn];
            l=tn+1;
        }
        bool fl=0;
        while(!fl&&l<=r){
            int tn=ne[l];
            if(tn>r){
                x+=sa[r]-sa[l-1];x%=mod;
                break;
            }
            x+=sa[tn-1]-sa[l-1];
            if(x>=mod){
                x%=mod;
                fl=1;
                l=tn;
                break;
            }
            x=max(x*b[tn],x+a[tn]);
            if(x>=mod){
                x%=mod;
                fl=1;
            }
            l=tn+1;
        }
        if(fl&&l<=r){
            x=(x-lb[l-1]+mod)%mod*ksm(lk[l-1])%mod;
            x=(x*lk[r]+lb[r])%mod;
        }
        cout<<x<<'\n';
    }
    return 0;
}