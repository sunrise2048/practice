#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=105;
int T;
int n;
int p[N];
int main(){
    ios::sync_with_stdio(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            cin>>p[i];
            cout<<min(2,n)<<' ';
        }
        cout<<'\n';
    }
    return 0;
}