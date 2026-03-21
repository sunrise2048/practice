#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int n=2e5;
int main(){
    freopen("bus.in","w",stdout);
    cout<<n<<'\n';
    for(int i=1;i<n;++i){
        cout<<i<<' '<<i+1<<'\n';
    }
    cout<<n<<'\n';
    for(int i=1;i<=n/2;++i){
        cout<<i<<' '<<i+n/2<<'\n';
    }
    mt19937 mt(time(0));
    for(int i=1;i<=n/2;++i){
        int a=mt()%n+1,b=mt()%n+1;
        while(a==b)b=mt()%n+1;
        cout<<a<<' '<<b<<'\n';
    }
    return 0;
}