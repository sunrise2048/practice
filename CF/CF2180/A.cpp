#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int main(){
    int T;
    cin>>T;
    while(T--){
        int l,a,b;
        cin>>l>>a>>b;
        int gc=__gcd(l,b);
        a%=gc;
        cout<<a+(l/gc-1)*gc<<'\n';
    }
    return 0;
}