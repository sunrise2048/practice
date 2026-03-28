#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int n;
int a[N],b[N];
int l[N],r[N];
int solve(int no,int x,int y){
    if(x>y)return 0;
    int ans=n+1;
    int len1=n-(no-x),len2=n-(y-no);
    if(b[len1]<=a[no]){
        ans=min(ans,solve(l[no],x,no-1)+(b[len1]==a[no]));
    }
    if(b[len2]<=a[no]){
        ans=min(ans,solve(r[no],no+1,y)+(b[len2]==a[no]));
    }
    return ans;
}
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
    sort(b+1,b+n+1);
    stack<int> st;
    for(int i=1;i<=n;++i){
        int ls=0;
        while(!st.empty()&&a[st.top()]>a[i]){
            ls=st.top();
            st.pop();
        }
        if(!st.empty())r[st.top()]=i;
        l[i]=ls;
        st.push(i);
    }
    int be=st.top();
    while(!st.empty()){
        be=st.top();
        st.pop();
    }
    int as=solve(be,1,n);
    if(as>n)as=-1;
    cout<<as<<'\n';
    return 0;
}