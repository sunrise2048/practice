#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n,k;
int a[N];
int lmi[N],rmi[N];
int lma[N],rma[N];
vector<pair<int,int>> ve[N];
class BIT{
public:
    ll t[N];
    void upd(int x,ll d){
        while(x<=n){
            t[x]+=d;
            x+=x&-x;
        }
    }
    ll qu(int x){
        ll s=0;
        while(x){
            s+=t[x];
            x-=x&-x;
        }
        return s;
    }
}bit;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;++i){
            ve[i].clear();
            cin>>a[i];
        }
        stack<int> st;
        for(int i=1;i<=n;++i){
            while(!st.empty()&&a[st.top()]>a[i])st.pop();
            lmi[i]=st.empty()?1:st.top()+1;
            st.push(i);
        }
        while(!st.empty())st.pop();
        for(int i=n;i;--i){
            while(!st.empty()&&a[st.top()]>=a[i])st.pop();
            rmi[i]=st.empty()?n:st.top()-1;
            st.push(i);
        }
        while(!st.empty())st.pop();
        for(int i=1;i<=n;++i){
            while(!st.empty()&&a[st.top()]<=a[i])st.pop();
            lma[i]=st.empty()?1:st.top()+1;
            st.push(i);
        }
        while(!st.empty())st.pop();
        for(int i=n;i;--i){
            while(!st.empty()&&a[st.top()]<a[i])st.pop();
            rma[i]=st.empty()?n:st.top()-1;
            st.push(i);
        }
        for(int i=1;i<=n;++i){
            if(k-a[i]<=n)ve[k-a[i]].emplace_back(i,1);
            ve[a[i]].emplace_back(i,0);
        }
        ll ans=0;
        for(int i=1;i<=n;++i){
            reverse(ve[i].begin(),ve[i].end());
            for(auto [id,op]:ve[i]){
                if(op){
                    bit.upd(lma[id],rma[id]-id+1);
                }
                else{
                    ans+=bit.qu(min(rmi[id]+1,n))*(id-lmi[id]+1);
                }
            }
            for(auto [id,op]:ve[i]){
                if(op)bit.upd(lma[id],-(rma[id]-id+1));
            }
            ve[i].clear();
        }
        cout<<ans<<'\n';
    }
    return 0;
}