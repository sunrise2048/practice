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
int ins(int p,int c){
    int no=++cnt;
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
    return no;
}
int cn_trie;
struct tnode{
    int s[26];
}tn[N];
int pos[N];
void ins(){
    int no=0;
    for(char c:s){
        if(!tn[no].s[c-'a']){
            tn[no].s[c-'a']=++cn_trie;
        }
        no=tn[no].s[c-'a'];
    }
}
void build(){
    queue<int> q;
    q.push(0);
    pos[0]=1;
    while(!q.empty()){
        int no=q.front();
        q.pop();
        for(int i=0;i<26;++i){
            int ns=tn[no].s[i];
            if(!ns)continue;
            pos[ns]=ins(pos[no],i);
            q.push(ns);
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>s;
        ins();
    }
    build();
    ll ans=0;
    for(int i=1;i<=cnt;++i)ans+=t[i].len-t[t[i].link].len;
    cout<<ans<<'\n'<<cnt<<'\n';
    return 0;
}