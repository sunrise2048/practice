#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=55;
int n;
ll a,b;
ll d[N];
bool ch(){
    ll s=0;
    for(int i=0;i<n;++i){
        s+=d[i];
    }
    if(s&1)return 0;
    for(int i=0;i<n;++i){
        if(d[i]>s-d[i])return 0;
    }
    return 1;
}
ll x[N],y[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    cin>>a>>b;
    d[0]=a+b;
    for(int i=1;i<n;++i)cin>>d[i];
    if(!ch()){
        cout<<"NO\n";
        return 0;
    }
    x[n]=a,y[n]=b;
    int m=n;
    while(n>2){
        ll s=0;
        for(int i=1;i<n-1;++i){
            s+=d[i];
        }
        ll nd=min(d[0]+d[n-1],s);
        ll td=(nd+d[n-1]-d[0])/2;
        ll nd1=nd-td;
        int opa=a/abs(a),opb=b/abs(b);
        if(nd1<=abs(a)){
            x[n-1]=opa*nd1,y[n-1]=-opb*td;
        }
        else{
            x[n-1]=a+opa*td,y[n-1]=opb*(nd1-abs(a));
        }
        d[0]=nd;
        a=x[n-1],b=y[n-1];
        --n;
    }
    cout<<"YES\n";
    for(int i=1;i<=m;++i){
        cout<<x[i]<<' '<<y[i]<<'\n';
    }
    return 0;
}