#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
int n;
int a[N];
int b[N];
int c[N];
int mi;
bool ch(){
    if(a[2]+b[2]==2)return 1;
    for(int i=2;i<=n;++i){
        if(a[i]<a[i-1]||a[i]>a[i-1]+1)return 1;
        if(b[i]<b[i-1]||b[i]>b[i-1]+1)return 1;
        if(a[i]!=a[i-1]&&b[i]!=b[i-1])return 1;
        if((ll)a[i]*b[i]<i)return 1;
    }
    return 0;
}
set<pair<int,int>> st;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    for(int i=1;i<=n;++i){
        cin>>b[i];
    }
    if(a[1]+b[1]!=2){
        cout<<"-1\n";
        return 0;
    }
    if(ch()){
        cout<<"-1\n";
        return 0;
    }
    c[1]=0;
    for(int i=2;i<=n;++i){
        if(a[i]!=a[i-1]){
            c[i]=a[i]-1;
        }
        else if(b[i]!=b[i-1]){
            st.emplace(1,i);
            mi-=a[n];
            c[i]=mi;
        }
        else{
            auto [len,id]=*st.begin();
            st.erase(st.begin());
            c[i]=c[id]+1;
            ++len;
            st.emplace(len,i);
        }
    }
    st.clear();
    for(int i=1;i<=n;++i){
        st.emplace(c[i],i);
    }
    int cn=0;
    while(!st.empty()){
        auto [vl,id]=*st.begin();
        st.erase(st.begin());
        c[id]=++cn;
    }
    for(int i=1;i<=n;++i){
        cout<<c[i]<<' ';
    }
    return 0;
}