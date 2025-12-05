#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using ull=unsigned long long;
const int N=2e5+5;
int n,m,q;
pair<int,int> a[N];
#define mid (l+r>>1)
int rt[N];
struct node{
    ull val:18;
    ull ls:23,rs:23;
}t[N*40];
int cn;
int update(int l,int r,int k,int x,int y){
    if(l==r)return k+1;
    t[++cn]=t[k];
    if(x<=l&&r<=y){
        t[cn].val++;
        return cn;
    }
    int no=cn;
    int lz=t[no].val-min((l==mid?t[no].ls:t[t[no].ls].val),(mid+1==r?t[no].rs:t[t[no].rs].val));
    if(x<=mid)t[no].ls=update(l,mid,t[no].ls,x,y);
    if(y>mid)t[no].rs=update(mid+1,r,t[no].rs,x,y);
    t[no].val=min((l==mid?t[no].ls:t[t[no].ls].val),(mid+1==r?t[no].rs:t[t[no].rs].val))+lz;
    return no;
}
int query(int l,int r,int k,int x,int y){
    if(l==r)return k;
    if(x<=l&&r<=y)return t[k].val;
    if(y<=mid)return query(l,mid,t[k].ls,x,y)+t[k].val-min((l==mid?t[k].ls:t[t[k].ls].val),(mid+1==r?t[k].rs:t[t[k].rs].val));
    if(x>mid)return query(mid+1,r,t[k].rs,x,y)+t[k].val-min((l==mid?t[k].ls:t[t[k].ls].val),(mid+1==r?t[k].rs:t[t[k].rs].val));
    return min(query(l,mid,t[k].ls,x,y),query(mid+1,r,t[k].rs,x,y))+t[k].val-min((l==mid?t[k].ls:t[t[k].ls].val),(mid+1==r?t[k].rs:t[t[k].rs].val));
}
#undef mid
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>a[i].first;
        a[i].second=i;
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i){
        rt[i]=update(1,n-m+1,rt[i-1],max(1,a[i].second-m+1),min(n-m+1,a[i].second));
    }
    cin>>q;
    int las=0;
    while(q--){
        int l,r,x;
        cin>>l>>r>>x;
        x^=las;
        int nk=lower_bound(a+1,a+n+1,make_pair(x,0))-a;
        cout<<(las=query(1,n-m+1,rt[nk-1],l,r))<<'\n';
    }
    return 0;
}