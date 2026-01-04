#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int T;
int n;
int a[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        if(n==2){
            cout<<"1\n2 1\n1\n1 2\n";
            continue;
        }
        if(n==3){
            cout<<"5\n2 3 1\n2\n1 3\n2 3\n";
            continue;
        }
        ll sum=0;
        for(int i=1;i<n;++i){
            sum+=max(1ll*(i-1)*(i-1),1ll*(n-i)*(n-i));
        }
        cout<<sum<<'\n';
        const int mid=n/2;
        cout<<mid+1<<' ';
        for(int i=2;i<mid;++i)cout<<i+1<<' ';
        cout<<1<<' ';
        for(int i=mid+1;i<n;++i){
            cout<<i+1<<' ';
        }
        cout<<2<<'\n';
        cout<<n-1<<'\n';
        for(int i=2;i<=mid;++i){
            cout<<i<<' '<<n<<'\n';
        }
        for(int i=mid+1;i<n;++i){
            cout<<i<<' '<<1<<'\n';
        }
        cout<<1<<' '<<n<<'\n';
    }
    return 0;
}