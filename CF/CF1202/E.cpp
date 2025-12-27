#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n;
string s;
ll f[N],g[N];
int m;
struct node{
    int s[26];
    int fail;
    int cnt;
}t[N];
int cn;
string ls[N];
void ins(int id){
    int no=0;
    for(char c:ls[id]){
        if(!t[no].s[c-'a'])t[no].s[c-'a']=++cn;
        no=t[no].s[c-'a'];
    }
    t[no].cnt++;
}
void build(){
    queue<int> q;
    for(int i=0;i<26;++i){
        if(t[0].s[i])q.push(t[0].s[i]);
    }
    while(!q.empty()){
        int no=q.front();
        q.pop();
        t[no].cnt+=t[t[no].fail].cnt;
        for(int i=0;i<26;++i){
            if(t[no].s[i]){
                t[t[no].s[i]].fail=t[t[no].fail].s[i];
                q.push(t[no].s[i]);
            }
            else t[no].s[i]=t[t[no].fail].s[i];
        }
    }
}
void cl(){
    for(int i=0;i<=cn;++i){
        memset(t[i].s,0,sizeof(t[i].s));
        t[i].fail=t[i].cnt=0;
    }
    cn=0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>s;
    n=s.size();
    s="0"+s;
    cin>>m;
    for(int i=1;i<=m;++i){
        cin>>ls[i];
        ins(i);
    }
    build();
    int no=0;
    for(int i=1;i<=n;++i){
        no=t[no].s[s[i]-'a'];
        f[i]=t[no].cnt;
    }
    cl();
    for(int i=1;i<=m;++i){
        reverse(ls[i].begin(),ls[i].end());
        ins(i);
    }
    build();
    no=0;
    for(int i=n;i;--i){
        no=t[no].s[s[i]-'a'];
        g[i]=t[no].cnt;
    }
    ll ans=0;
    for(int i=1;i<n;++i){
        ans+=f[i]*g[i+1];
    }
    cout<<ans<<'\n';
    return 0;
}