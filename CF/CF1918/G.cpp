#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int n;
int a[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    int be;
    if(n&1){
        if(n<=5){
            cout<<"NO\n";
            return 0;
        }
        be=7;
        a[1]=-3,a[2]=1,a[3]=2,a[4]=1,a[5]=-1,a[6]=-3,a[7]=-2;
    }
    else{
        be=2;
        a[1]=1,a[2]=2;
    }
    for(int i=be;i<n;i+=2){
        a[i+1]=-a[i];
        a[i+2]=a[i-1]-a[i];
    }
    cout<<"YES\n";
    for(int i=1;i<=n;++i){
        cout<<a[i]<<' ';
    }
    cout<<'\n';
    return 0;
}