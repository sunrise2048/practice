#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
int a[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        ll sum = 0;
        int mx = 0;
        for(int i=0;i<n;++i){
            cin>>a[i];
        }
        for (int i = 0; i < n; ++i) {
            sum += max(a[i], a[(i+1)%n]);
            mx = max(mx, a[i]);
        }
        cout<<sum-mx<<'\n';
    }
    return 0;
}