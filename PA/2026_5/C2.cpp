#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int T;
int n,k;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        if(n>2*k){
            cout<<"NIE\n";
            continue;
        }
        for(int i=1;i<=k;++i)cout<<"A";
        for(int i=1;i<=n-k;++i)cout<<"P";
        cout<<'\n';
    }
    return 0;
}