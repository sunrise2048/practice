#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n,m;
int a[N];
int b[N];
class Trie{
public:
    struct node{
        int s[2];
        int cn;
    }t[N*30];
    int cn;
    void cl(){
        for(int i=1;i<=cn;++i){
            t[i].s[0]=t[i].s[1]=t[i].cn=0;
        }
        cn=1;
    }
    int qu(int no,int k,int vl){
        if(k==-1)return 0;
        int op=((vl&(1<<k))!=0);
        if(t[no].s[op])return qu(t[no].s[op],k-1,vl);
        return qu(t[no].s[op^1],k-1,vl)|(1<<k);
    }
    int qu_mix(int vl){
        return qu(1,29,vl);
    }
    void ins(int vl){
        int no=1;
        for(int i=29;i>=0;--i){
            if(vl&(1<<i)){
                if(!t[no].s[1])t[no].s[1]=++cn;
                no=t[no].s[1];
            }
            else{
                if(!t[no].s[0])t[no].s[0]=++cn;
                no=t[no].s[0];
            }
            t[no].cn++;
        }
    }
    int qu_cn(int no,int k,int vl,int x){
        if(k==-1)return t[no].cn;
        int opv=((vl&(1<<k))!=0),opx=((x&(1<<k))!=0);
        if(!opx)return qu_cn(t[no].s[opv],k-1,vl,x);
        return t[t[no].s[opv]].cn+qu_cn(t[no].s[opv^1],k-1,vl,x);
    }
    int calc(int vl,int x){
        return qu_cn(1,29,vl,x);
    }
}trie;
int mi;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    mi=(1<<30);
    trie.cl();
    for(int i=1;i<=n;++i){
        cin>>a[i];
        mi=min(mi,trie.qu_mix(a[i]));
        trie.ins(a[i]);
    }
    trie.cl();
    ll ans=0;
    for(int i=1;i<=m;++i){
        int a;
        cin>>a;
        ans+=trie.calc(a,mi);
        trie.ins(a);
    }
    cout<<ans<<'\n';
    return 0;
}