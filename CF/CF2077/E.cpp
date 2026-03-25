#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int mod=998244353;
int T;
int n;
ll a[N];
ll s[N];
ll ans;
int pr[N],ne[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        ans=0;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            s[i]=s[i-1]+(2*(i&1)-1)*a[i];
        }
        stack<int> st;
        for(int i=0;i<=n;++i){
            while(!st.empty()&&s[st.top()]<=s[i])st.pop();
            pr[i]=(st.empty()?0:st.top()+1);
            st.push(i);
        }
        while(!st.empty())st.pop();
        for(int i=n;i>=0;--i){
            while(!st.empty()&&s[st.top()]<s[i])st.pop();
            ne[i]=(st.empty()?n:st.top()-1);
            st.push(i);
        }
        while(!st.empty())st.pop();
        for(int i=0;i<=n;++i){
            ans=(ans+(s[i]%mod+mod)%mod*(i-pr[i]+1)%mod*(ne[i]-i+1))%mod;
        }
        for(int i=0;i<=n;++i){
            while(!st.empty()&&s[st.top()]>=s[i])st.pop();
            pr[i]=(st.empty()?0:st.top()+1);
            st.push(i);
        }
        while(!st.empty())st.pop();
        for(int i=n;i>=0;--i){
            while(!st.empty()&&s[st.top()]>s[i])st.pop();
            ne[i]=(st.empty()?n:st.top()-1);
            st.push(i);
        }
        while(!st.empty())st.pop();
        for(int i=0;i<=n;++i){
            ans=(ans-(s[i]%mod+mod)%mod*(i-pr[i]+1)%mod*(ne[i]-i+1)%mod+mod)%mod;
        }
        cout<<ans<<'\n';
    }
    return 0;
}