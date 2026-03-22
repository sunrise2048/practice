#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
int T;
int n,q;
vector<pair<int,int>> ve;
int qu(pair<int,int> x){
    if(x.second<x.first)return n+1;
    if(x.first==1&&x.second==n)return n;
    cout<<"? "<<x.first<<' '<<x.second<<endl;
    int ans;
    cin>>ans;
    return ans;
}
int main(){
    cin>>T;
    while(T--){
        cin>>n>>q;
        ve.clear();
        for(int i=1;i<=q;++i){
            int l,r;
            cin>>l>>r;
            ve.emplace_back(l,r);
        }
        sort(ve.begin(),ve.end(),[](const pair<int,int>& x,const pair<int,int>& y){
            return x.first!=y.first?x.first<y.first:x.second>y.second;
        });
        vector<pair<int,int>> st;
        for(auto [l,r]:ve){
            if(!st.empty()&&st.back().second>=r)continue;
            st.emplace_back(l,r);
        }
        swap(ve,st);
        if(st[0]==make_pair(1,n)){
            cout<<"! "<<n<<endl;
            continue;
        }
        int ans=max(qu(ve[0]),qu(ve.back()));
        int l=0,r=ve.size()-1;
        while(l<r-1){
            int mid=(l+r>>1);
            auto [tl,tr]=ve[mid];
            int al=qu({tl,n}),ar=qu({1,tr});
            ans=max(ans,min(al,ar));
            if(al<=ar)r=mid;
            else l=mid;
        }
        cout<<"! "<<ans<<endl;
    }
    return 0;
}