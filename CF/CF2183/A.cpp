#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=105;
int T;
int n;
int a[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        int cn=0;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            cn+=a[i];
        }
        if(cn==n){
            cout<<"Alice\n";
            continue;
        }
        if(a[1]||a[n]){
            cout<<"Alice\n";
            continue;
        }
        cout<<"Bob\n";
    }
    return 0;
}