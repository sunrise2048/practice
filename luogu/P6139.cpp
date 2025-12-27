#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int n;
string s;
struct node{
    int s[26];
    int len;
    int link;
}t[N<<1];
int cnt=1;
int cn0;
int ins(int p,int c){
    if(t[p].s[c]&&t[t[p].s[c]].len==t[p].len+1)return t[p].s[c];
    int no=++cnt;
    bool chk=t[p].s[c];
    t[no].len=t[p].len+1;
    while(!t[p].s[c]){
        t[p].s[c]=no;
        p=t[p].link;
    }
    if(!p){
        t[no].link=1;
        return no;
    }
    int q=t[p].s[c];
    if(t[p].len+1==t[q].len){
        t[no].link=q;
        return no;
    }
    int cl=++cnt;
    t[cl]=t[q];
    t[cl].len=t[p].len+1;
    t[q].link=t[no].link=cl;
    while(t[p].s[c]==q){
        t[p].s[c]=cl;
        p=t[p].link;
    }
    if(chk){
        ++cn0;
    }
    return chk?cl:no;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>s;
        int p=1;
        for(char c:s){
            p=ins(p,c-'a');
        }
    }
    ll ans=0;
    for(int i=1;i<=cnt;++i)ans+=t[i].len-t[t[i].link].len;
    cout<<ans<<'\n'<<cnt-cn0<<'\n';
    return 0;
}