#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n,b;
string ans;
int qu(int x,string s){
    while(ans.size()+s.size()<b)s+="1";
    cout<<x<<' '<<ans<<s<<endl;
    string op;
    cin>>op;
    return op=="yes";
}
void solve(vector<int> id){
    if(ans.size()==b)return;
    if(!id.size()){
        while(ans.size()<b)ans+="0";
        return;
    }
    vector<int> st;
    string cm;
    int op=qu(id[0],"0");
    cm.push_back('0'+op);
    st.push_back(id[0]);
    for(int i=1;i<id.size();++i){
        int no=id[i];
        op=qu(no,cm);
        int lop=op;
        while(!st.empty()&&lop){
            st.pop_back();
            cm.pop_back();
            lop=qu(no,cm);
        }
        if(ans.size()+cm.size()==b)continue;
        if(op||qu(no,cm+"0"))cm+="1";
        else cm+="0";
        st.push_back(no);
    }
    for(int i=st.size()-1;i>=0;--i){
        if(qu(st[i],cm)){
            while(st.size()>i+1){
                st.pop_back();
                cm.pop_back();
            }
        }
    }
    ans+=cm;
    solve(st);
}
int main(){
    ios::sync_with_stdio(0);
    cin>>n>>b;
    vector<int> id(n);
    iota(id.begin(),id.end(),1);
    solve(id);
    cout<<0<<' '<<ans<<endl;
    return 0;
}