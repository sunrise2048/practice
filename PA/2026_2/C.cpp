#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e3+5;
int n,k;
int a[N];
set<pair<int,int>> st;
ll d;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        st.emplace(a[i],i);
    }
    while(!st.empty()){
        auto [val,id]=*st.rbegin();
        st.erase({val,id});
        if(id>1&&a[id-1]<val-k){
            d+=val-k-a[id-1];
            st.erase({a[id-1],id-1});
            st.emplace(val-k,id-1);
            a[id-1]=val-k;
        }
        if(id<n&&a[id+1]<val-k){
            d+=val-k-a[id+1];
            st.erase({a[id+1],id+1});
            st.emplace(val-k,id+1);
            a[id+1]=val-k;
        }
    }
    cout<<d<<'\n';
    return 0;
}