#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=6005;
int T;
int n,k;
int ne[N];
vector<int> zy[N];
ll s[N];
ll f[N][N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;++i){
            cin>>s[i];
            s[i]+=s[i-1];
        }
        for(int i=0;i<=n;++i)zy[i].clear();
        {
            stack<int> st;
            for(int i=n;i>=0;--i){
                while(!st.empty()&&s[st.top()]<s[i]){
                    zy[i].push_back(st.top());
                    st.pop();
                }
                if(!st.empty())ne[i]=st.top();
                else ne[i]=n+1;
                st.push(i);
            }
        }
        for(int i=1;i<=n;++i){
            memset(f[i],0x3f,sizeof(ll)*(n+1));
        }
        for(int i=1;i<=n;++i){
            if(i<=k)f[i][i]=0;
            for(int j=0;j<=k;++j){
                for(int t:zy[i-1]){
                    if(j+t-i>k)break;
                    f[t][j+t-i]=min(f[t][j+t-i],f[i-1][j]);
                }
            }
            if(ne[i-1]>n)continue;
            int t=ne[i-1],ts=t-i;
            for(int j=0;j+ts<=k;++j){
                f[t][j+ts]=min(f[t][j+ts],f[i-1][j]+s[t]-s[i-1]);
            }
        }
        ll ans=f[n][0];
        for(int i=1;i<=k;++i)ans=min(ans,f[n][i]);
        cout<<ans<<'\n';
    }
    return 0;
}