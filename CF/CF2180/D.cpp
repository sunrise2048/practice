#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e6+5;
int T;
int n;
int x[N];
int r[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            cin>>x[i];
        }
        if(n==1){
            cout<<"0\n";
            continue;
        }
        for(int i=1;i<=n;++i){
            r[i]=1e9+5;
            if(i!=1)r[i]=min(r[i],x[i]-x[i-1]);
            if(i!=n)r[i]=min(r[i],x[i+1]-x[i]);
        }
        int cn=0;
        pair<int,int> lst{0,r[1]};
        for(int i=2;i<=n;++i){
            int d=x[i]-x[i-1];
            if(lst.second+r[i]<=d){
                lst={0,r[i]};
            }
            else{
                ++cn;
                lst={d-lst.second,d-lst.first};
                lst.second=min(lst.second,r[i]);
            }
        }
        cout<<cn<<'\n';
    }
    return 0;
}