#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n,m;
set<pair<int,int>> st;
int gt(int x,int y){
    int cn=0;
    while(x%y==0){
        ++cn;
        x/=y;
    }
    return cn;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        st.clear();
        st.emplace(0,0);
        for(int i=2;i<=n;++i){
            for(int j=m/i;j;--j){
                int no=i*j;
                if(no-i+n>m)continue;
                auto it=st.lower_bound({no-i+1,0});
                int cn=gt(no,i)+(prev(it)->second);
                it=st.lower_bound({no-i,0});
                while(it!=st.end()&&(it->second)<=cn){
                    st.erase(it);
                    it=st.lower_bound({no-i,0});
                }
                st.emplace(no-i,cn);
            }
        }
        cout<<st.rbegin()->second<<'\n';
    }
    return 0;
}