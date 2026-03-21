#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
int T;
int n,k;
ll a[N],s[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            s[i]=s[i-1]+a[i];
        }
        vector<int> id;
        for(int i=1;i<=n;++i){
            if(a[i]>s[i-1])id.push_back(i);
        }
        for(int i=1;i<=n;++i){
            vector<int> nd;
            for(int x:id){
                if(a[x]>s[x-1]+(x<=i)*a[i]){
                    nd.push_back(x);
                }
            }
            if(nd.size()<k){
                cout<<n<<' ';
                continue;
            }
            int as=0;
            if(k>0){
                int las=nd[nd.size()-k];
                as+=n-las+1;
                if(las<i)--as;
            }
            if(nd.size()==k){
                if(s[i-1]>=a[i]){
                    as+=lower_bound(s+1,s+n+1,a[i])-s;
                }
                else{
                    as+=lower_bound(s+1,s+n+1,a[i]*2)-s-1;
                }
            }
            cout<<as<<' ';
        }
        cout<<'\n';
    }
    return 0;
}