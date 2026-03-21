#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
int a[N];
int c[N];
int p[N];
ll sum;
int vl[N];
set<int> st;
multiset<int> mst;
int id[N];
void gt(int x){
    auto it=st.lower_bound(x);
    while(it!=st.end()&&a[*it]<=a[x]){
        sum+=c[x]-vl[*it];
        mst.erase(mst.find(vl[*it]));
        mst.insert(c[x]);
        vl[*it]=c[x];
        st.erase(it);
        it=st.lower_bound(x);
    }
    while(it!=st.begin()&&a[*prev(it)]<=a[x]){
        sum+=c[x]-vl[*prev(it)];
        mst.erase(mst.find(vl[*prev(it)]));
        mst.insert(c[x]);
        vl[*prev(it)]=c[x];
        st.erase(prev(it));
        it=st.lower_bound(x);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i)cin>>a[i];
        for(int i=1;i<=n;++i)cin>>c[i];
        for(int i=1;i<=n;++i)cin>>p[i];
        sum=0;
        st.clear();
        for(int i=1;i<=n;++i){
            st.insert(i);
            id[i]=i;
            vl[i]=0;
        }
        sort(id+1,id+n+1,[](const int& x,const int& y){
            return c[x]<c[y];
        });
        mst.clear();
        for(int i=1;i<=n;++i){
            mst.insert(0);
        }
        for(int i=1;i<=n;++i){
            int no=id[i];
            gt(no);
        }
        st.clear();
        for(int i=1;i<=n;++i){
            st.insert(i);
        }
        cout<<sum-(*mst.rbegin())<<' ';
        for(int i=1;i<=n;++i){
            int no=p[i];
            c[no]=0;
            gt(no);
            cout<<sum-(*mst.rbegin())<<' ';
        }cout<<'\n';
    }
    return 0;
}