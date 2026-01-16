#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n;
char c[N];
struct node{
    int s[26];
    int link;
    int len;
    int ed;
}t[N<<1];
int cn;
vector<int> e[N<<1];
int las;
class SGT{
public:
    struct node{
        int lson,rson;
    }t[N*40];
    int cn;
    #define ls(k) t[k].lson
    #define rs(k) t[k].rson
    #define mid (l+r>>1)
    void update(int l,int r,int& k,int x){
        k=++cn;
        if(l==r)return;
        if(x<=mid)update(l,mid,ls(k),x);
        else update(mid+1,r,rs(k),x);
    }
    bool query(int l,int r,int k,int x,int y){
        if(!k)return 0;
        if(x<=l&&r<=y)return 1;
        if(y<=mid)return query(l,mid,ls(k),x,y);
        if(x>mid)return query(mid+1,r,rs(k),x,y);
        return query(l,mid,ls(k),x,y)||query(mid+1,r,rs(k),x,y);
    }
    int merge(int x,int y){
        if(!x||!y)return x|y;
        int no=++cn;
        ls(no)=merge(ls(x),ls(y));
        rs(no)=merge(rs(x),rs(y));
        return no;
    }
    #undef mid
    #undef ls
    #undef rs
}sgt;
int rt[N<<1];
void ins(int c){
    int no=++cn;
    t[no].len=t[las].len+1;
    int la=las;
    while(la!=-1&&!t[la].s[c]){
        t[la].s[c]=no;
        la=t[la].link;
    }
    if(la==-1){
        las=no;
        return;
    }
    int q=t[la].s[c];
    if(t[q].len==t[la].len+1){
        t[no].link=q;
        las=no;
        return;
    }
    int cl=++cn;
    t[cl]=t[q];
    t[cl].len=t[la].len+1;
    t[no].link=cl;
    t[q].link=cl;
    while(la!=-1&&t[la].s[c]==q){
        t[la].s[c]=cl;
        la=t[la].link;
    }
    las=no;
}
int f[N<<1],g[N<<1];
void dfs1(int no){
    for(int to:e[no]){
        dfs1(to);
        t[no].ed=t[to].ed;
        rt[no]=sgt.merge(rt[no],rt[to]);
    }
}
int ans;
void dfs2(int no){
    if(!t[no].link){
        f[no]=1;
        g[no]=no;
        for(int to:e[no])dfs2(to);
        return;
    }
    int fa=g[t[no].link];
    if(sgt.query(1,n,rt[fa],t[no].ed-t[no].len+t[fa].len,t[no].ed-1)){
        f[no]=f[fa]+1;
        g[no]=no;
    }
    else{
        f[no]=f[fa];
        g[no]=fa;
    }
    ans=max(ans,f[no]);
    for(int to:e[no])dfs2(to);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    t[0].link=-1;
    for(int i=1;i<=n;++i){
        cin>>c[i];
        ins(c[i]-'a');
        sgt.update(1,n,rt[las],i);
        t[las].ed=i;
    }
    for(int i=cn;i>=0;--i){
        if(i)e[t[i].link].push_back(i);
    }
    dfs1(0);
    ans=1;
    dfs2(0);
    cout<<ans<<'\n';
    return 0;
}