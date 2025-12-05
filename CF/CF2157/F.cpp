#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2.5e5+5;
const int K=63;
int n;
vector<pair<int,int>> opt;
vector<int> id;
set<int> st;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    if(n==4){
        cout<<"4\n1 4\n3 1\n2 1\n3 1\n";
        return 0;
    }
    id.resize(n);
    iota(id.begin(),id.end(),1);
    for(int no:id)st.insert(no);
    int bs=1;
    while(id.size()>1){
        bs*=K;
        sort(id.begin(),id.end(),[&](const int& x,const int& y){
            return x%bs!=y%bs?x%bs<y%bs:x>y;
        });
        vector<int> tid;
        for(int no:id){
            if(no%bs==0||no==n){
                tid.push_back(no);
                continue;
            }
            opt.emplace_back(no,(*st.upper_bound(no))-no);
            st.erase(no);
        }
        swap(tid,id);
    }
    cout<<opt.size()<<'\n';
    for(auto [x,l]:opt)cout<<x<<' '<<l<<'\n';
    return 0;
}