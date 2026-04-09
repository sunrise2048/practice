#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
int T;
int n,m;
int s[N];
ll c[N];
ll f[N];
vector<ll> er[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;++i){
            cin>>s[i];
            s[i]=(s[i-1]+s[i])%m;
        }
        s[n+1]=s[n];c[n+1]=0;
        for(int i=1;i<=n;++i)cin>>c[i];
        memset(f,0x3f,sizeof(ll)*(n+2));
        ++n;
        for(int i=1;i<=n;++i)er[i].clear();
        for(int i=1;i<=n;++i){
            f[i]=c[i];
            if(s[i]==0)break;
        }
        multiset<ll> st;
        unordered_map<ll,int> ma;
        int cn=0;
        int r=0;
        for(int i=1;i<=n;++i){
            if(i>1){
                ma[s[i-1]]--;
                if(!ma[s[i-1]])--cn;
            }
            for(ll ns:er[i])st.erase(st.find(ns));
            if(!st.empty()){
                f[i]=min(f[i],(*st.begin())+c[i]);
            }
            while(r<n&&cn<m){
                ++r;
                ma[s[r]]++;
                if(ma[s[r]]==1)++cn;
            }
            st.insert(f[i]);
            er[r+1].push_back(f[i]);
        }
        cout<<f[n]<<'\n';
    }
    return 0;
}