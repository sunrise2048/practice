#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n,m;
string s,t;
bitset<N> flc[26],ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>s;
    n=s.size();
    s="0"+s;
    for(int i=1;i<=n;++i){
        flc[s[i]-'a'][i]=1;
    }
    cin>>m;
    while(m--){
        int op;
        cin>>op;
        if(op==1){
            int x;
            char c;
            cin>>x>>c;
            flc[s[x]-'a'][x]=0;
            flc[c-'a'][x]=1;
            s[x]=c;
        }
        else{
            int l,r;
            cin>>l>>r;
            cin>>t;
            if(t.size()>r-l+1){
                cout<<"0\n";
                continue;
            }
            ans.set();
            int id=0;
            for(char c:t){
                ans&=flc[c-'a']>>id;
                ++id;
            }
            r=r-t.size()+1;
            cout<<(ans>>l).count()-(ans>>(r+1)).count()<<'\n';
        }
    }
    return 0;
}