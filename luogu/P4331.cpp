#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5;
int n;
int a[N];
int b[N];
ll ans;
struct node{
    int s[2];
    int val;
    int d;
    int si;
}t[N];
int rt[N];
int st[N];
int tr;
int merge(int x,int y){
    if(!x||!y)return x|y;
    if(t[x].val<t[y].val)swap(x,y);
    t[x].s[1]=merge(t[x].s[1],y);
    if(t[t[x].s[1]].d>t[t[x].s[0]].d){
        swap(t[x].s[1],t[x].s[0]);
        t[x].d=t[t[x].s[0]].d+1;
    }
    t[x].si=t[t[x].s[0]].si+t[t[x].s[1]].si+1;
    return x;
}
int del(int x){return merge(t[x].s[0],t[x].s[1]);}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    t[0].val=-1e9;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        a[i]-=i;
        t[i].val=a[i];
        t[i].si=1;
        t[i].d=1;
        rt[i]=i;
        while(t[rt[st[tr]]].val>t[rt[i]].val){
            rt[i]=merge(rt[i],rt[st[tr]]);
            --tr;
            int nl=i-st[tr];
            while(2*t[rt[i]].si>nl+1){
                rt[i]=del(rt[i]);
            }
        }
        st[++tr]=i;
    }
    for(int i=1;i<=tr;++i){
        for(int l=st[i-1]+1;l<=st[i];++l){
            b[l]=t[rt[st[i]]].val;
            ans+=abs(a[l]-b[l]);
            b[l]+=l;
        }
    }
    cout<<ans<<'\n';
    for(int i=1;i<=n;++i){
        cout<<b[i]<<'\n';
    }
    return 0;
}