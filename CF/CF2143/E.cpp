#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
char c[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        vector<char> ve;
        for(int i=1;i<=n;++i){
            cin>>c[i];
        }
        if(n&1){
            cout<<"-1\n";
            continue;
        }
        {
            char lc=c[1];
            int op=0;
            for(int i=1;i<=n;++i){
                if(c[i]==lc){
                    op^=1;
                }
                else{
                    if(op){
                        ve.push_back(lc);
                        lc=c[i];
                        continue;
                    }
                    if(ve.empty())op=1;
                    else ve.pop_back();
                    lc=c[i];
                }
            }
            if(op)ve.push_back(lc);
        }
        if(((n-ve.size())/2)&1){
            cout<<"-1\n";
            continue;
        }
        if(n==ve.size()&&ve[0]==')'){
            cout<<"-1\n";
            continue;
        }
        int ls=(n-ve.size())/2;
        for(int i=0;i<ls;++i)cout<<"(";
        for(auto c:ve)cout<<c;
        for(int i=0;i<ls;++i)cout<<")";
        cout<<'\n';
    }
    return 0;
}