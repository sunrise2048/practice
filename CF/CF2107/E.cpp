#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int T;
int n;
ll k;
ll a[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        a[1]=n;
        int id=2;
        while(id<n){
            if(k<=1)break;
            ll s=a[id-1]-1;
            while(s*(s-1)/2>k+1)--s;
            a[id]=s;
            k-=s*(s-1)/2;
            ++id;
        }
        a[id]=0;
        if(k>1){
            cout<<"No\n";
            continue;
        }
        cout<<"Yes\n";
        int no=id;
        for(int i=id-1;i;--i){
            if(i+1!=id)cout<<i<<' '<<i+1<<'\n';
            int cn=a[i]-a[i+1]-1;
            while(cn--){
                cout<<i<<' '<<no<<'\n';
                ++no;
            }
        }
    }
    return 0;
}