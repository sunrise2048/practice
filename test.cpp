#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int T;
int n;
pair<int,ll> a[N];
int lb[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            cin>>a[i].first;
            a[i].second=1;
        }
        sort(a+1,a+n+1);
        int m=1;
        for(int i=2;i<=n;++i){
            if(a[i].first==a[m].first){
                a[m].second++;
                continue;
            }
            ++m;
            a[m]=a[i];
        }
        n=m;
        for(int i=1;i<n;++i){
            int xs=a[i].first^a[i+1].first;
            for(int j=29;j>=0;--j){
                if(xs&(1<<j)){
                    lb[i]=j;
                    break;
                }
            }
        }
        ll ans=0;
        for(int i=1;i<n;++i){
            bool fl=1;
            if(i!=1&&lb[i-1]<lb[i])fl=0;
            if(i!=n-1&&lb[i+1]<lb[i])fl=0;
            if(fl){
                ans+=a[i].second*a[i+1].second;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
/*
1 2 4 5 6
 2 4 1 2
*/