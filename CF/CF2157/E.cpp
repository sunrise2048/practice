#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=6e5+5;
int T;
int n,k;
int t[N];
int b[N];
bool ch(int x){
    memset(b,0,sizeof(int)*(3*n+1));
    stack<int> st;
    for(int i=3*n;i>2*n;--i)st.push(i);
    for(int i=2*n;i;--i){
        if(t[i]==0){
            st.push(i);
            continue;
        }
        b[i]=1;
        int ls=t[i]-1;
        while(ls&&st.top()<=i+x){
            b[st.top()]=1;
            st.pop();
            --ls;
        }
        if(b[i+x]+ls>k)return 0;
    }
    return 1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        memset(t,0,sizeof(int)*(n*2+1));
        bool nf=1;
        for(int i=1;i<=n;++i){
            int a;
            cin>>a;
            t[a]++;
            if(t[a]>k)nf=0;
        }
        if(nf){
            cout<<"0\n";
            continue;
        }
        int l=0,r=n;
        while(l<r-1){
            int mid=l+r>>1;
            if(ch(mid))r=mid;
            else l=mid;
        }
        cout<<r<<'\n';
    }
    return 0;
}