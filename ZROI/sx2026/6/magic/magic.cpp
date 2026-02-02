#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int n;
int a[N];
int ne[N];
int h[N];
void solve(int l,int r,int d){
    if(l>r)return;
    if(a[l]-d==r-l+1){
        h[l]=r-l+1;
        solve(l+1,r,d+1);
        return;
    }
    vector<vector<int>> prex;
    vector<int> nid;
    int c=ne[l]-l+1,s=a[l]-d-c;
    int no=ne[l];
    solve(l+1,no-1,s+d+2);
    prex.push_back({l});
    nid.push_back(no);
    while(no<=r){
        int tr=a[no]-d-s-c;
        int to=no+tr;
        if(to!=no&&a[to]-d>tr+s+1){
            solve(no+1,to-1,d+s+2);
            c=to-no+1;
            nid.push_back(to);
            no=to;
        }
        else{
            solve(no+1,to,d+s+1);
            prex.push_back(nid);
            nid.clear();
            if(to<r)nid.push_back(to+1);
            c=to+1-l+1;
            --s;
            no=to+1;
        }
    }
    if(!nid.empty())prex.push_back(nid);
    int nv=r-l+1;
    reverse(prex.begin(),prex.end());
    for(auto ve:prex){
        for(int no:ve){
            h[no]=nv;
        }
        --nv;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        a[i]++;
    }
    {
        stack<int> st;
        for(int i=1;i<=n;++i){
            ne[i]=n+1;
            while(!st.empty()&&a[st.top()]<a[i]){
                ne[st.top()]=i;
                st.pop();
            }
            st.push(i);
        }
    }
    solve(1,n,0);
    for(int i=1;i<=n;++i){
        cout<<h[i]<<' ';
    }
    return 0;
}