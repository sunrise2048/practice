#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int mod=998244353;
int n;
int a[N],b[N];
ll mi[N];
ll sum;
ll ksm(ll x,int y=mod-2){
    ll an=1;
    while(y){
        if(y&1)an=an*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return an;
}
ll ans;
int l[N],r[N];
ll get_g(int l,int x,int r){
    if(l>x||x>r)return 0;
    return (mi[x-1]-(l==1?0:mi[l-2])+mod)*(mi[n-x]-(r==n?0:mi[n-r-1])+mod)%mod;
}
void calc1(){
    stack<int> st;
    for(int i=1;i<=n;++i){
        while(!st.empty()&&a[st.top()]<a[i])st.pop();
        l[i]=(st.empty()?1:st.top()+1);
        st.push(i);
    }
    while(!st.empty())st.pop();
    for(int i=n;i;--i){
        while(!st.empty()&&a[st.top()]<=a[i])st.pop();
        r[i]=(st.empty()?n:st.top()-1);
        st.push(i);
        ans=(ans+get_g(l[i],i,r[i])*a[i])%mod;
    }
}
void calc2(){
    stack<int> st;
    for(int i=1;i<=n;++i){
        while(!st.empty()&&(a[st.top()]<a[i]||a[st.top()]<b[i])){
            r[st.top()]=i-1;
            st.pop();
        }
        if(a[i]>=b[i])st.push(i);
        else r[i]=i-1;
    }
    while(!st.empty()){
        r[st.top()]=n;
        st.pop();
    }
    for(int i=n;i;--i){
        while(!st.empty()&&(a[st.top()]<=a[i]||a[st.top()]<b[i])){
            l[st.top()]=i+1;
            st.pop();
        }
        if(a[i]>=b[i])st.push(i);
        else l[i]=i+1;
    }
    while(!st.empty()){
        l[st.top()]=1;
        st.pop();
    }
    for(int i=1;i<=n;++i)ans=(ans-get_g(l[i],i,r[i])*a[i]%mod+mod)%mod;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=1;i<=n;++i)cin>>b[i];
    mi[0]=1;
    for(int i=1;i<=n;++i)mi[i]=mi[i-1]*2%mod;
    calc1();calc2();
    for(int i=1;i<=n;++i){
        swap(a[i],b[i]);
    }
    calc1();calc2();
    cout<<ans*ksm((mod+1)/2,n)%mod<<'\n';
    return 0;
}