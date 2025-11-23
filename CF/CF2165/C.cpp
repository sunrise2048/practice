#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=5e5+5;
int T;
int n,q;
int a[N];
priority_queue<int> pq,er;
vector<int> ne,na;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>q;
        while(!pq.empty())pq.pop();
        while(!er.empty())er.pop();
        for(int i=1;i<=n;++i){
            cin>>a[i];
            pq.push(a[i]);
        }
        while(q--){
            ne.clear();na.clear();
            int x;
            cin>>x;
            int hb=29;
            int ans=0;
            while(x){
                while((x&(1<<hb))==0)--hb;
                while(er.size()&&er.top()==pq.top()){
                    er.pop();pq.pop();
                }
                if(pq.top()>=x)break;
                if(pq.top()>=(1<<hb)){
                    int no=pq.top();
                    ne.push_back(no);
                    pq.pop();
                    na.push_back(no-(1<<hb));
                    pq.push(no-(1<<hb));
                    x-=(1<<hb);
                    continue;
                }
                int no=pq.top();
                ans+=(1<<hb)-no;
                ne.push_back(no);
                pq.pop();
                na.push_back(0);
                pq.push(0);
                x-=(1<<hb);
            }
            cout<<ans<<'\n';
            for(int val:na)er.push(val);
            for(int val:ne)pq.push(val);
        }
    }
    return 0;
}