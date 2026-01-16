#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int inf=1e9+7;
int n,q;
int a[N];
struct line{
    int sum,cnt,lm;
    line()=default;
    line(int sum,int cnt,int lm):sum(sum),cnt(cnt),lm(lm){}
};
struct node{
    int vl,vr;
    int sum,cnt;
    vector<line> el,er;
}t[N<<2];
#define mid (l+r>>1)
#define rs (k<<1|1)
#define ls (k<<1)
node pushup(node x,node y){
    node ans;
    ans.vl=x.vl;
    ans.vr=y.vr;
    ans.sum=min(x.sum+y.sum,inf);
    ans.cnt=0;
    ans.el=x.el;ans.er=y.er;
    vector<line> ml=x.er,mr=y.el;
    ml.emplace_back(x.sum,x.cnt,0);
    mr.emplace_back(y.sum,y.cnt,0);
    vector<line> ner,nel;
    int ns=0,lm=0;
    int nl=0,nr=-1,cnt=ml[0].cnt;
    while(true){
        ns=min(inf,ml[nl].sum+(nr==-1?0:mr[nr].sum));
        lm=(nr==-1?y.vl:mr[nr].lm);
        if(ns>=lm&&nr+1<mr.size()){
            ++nr;
        }
        else if(nl+1==ml.size())break;
        else{
            if(ns<ml[nl].lm){
                if(nr+1==mr.size()){
                    ner.emplace_back(ns,cnt,ml[nl].lm);
                }
                cnt=0;
            }
            cnt+=ml[++nl].cnt;
        }
    }
    if(nr+1==mr.size())ans.cnt+=cnt;
    else ans.el.emplace_back(ns,cnt,lm);
    swap(ml,mr);
    nl=0,nr=-1,cnt=ml[0].cnt;
    while(true){
        ns=min(inf,ml[nl].sum+(nr==-1?0:mr[nr].sum));
        lm=(nr==-1?x.vr:mr[nr].lm);
        if(ns>=lm&&nr+1<mr.size()){
            ++nr;
        }
        else if(nl+1==ml.size())break;
        else{
            if(ns<ml[nl].lm){
                if(nr+1==mr.size()){
                    nel.emplace_back(ns,cnt,ml[nl].lm);
                }
                cnt=0;
            }
            cnt+=ml[++nl].cnt;
        }
    }
    if(nr+1==mr.size())ans.cnt+=cnt;
    else ans.er.emplace_back(ns,cnt,lm);
    for(line no:nel)ans.el.push_back(no);
    for(line no:ner)ans.er.push_back(no);
    return ans;
}
void build(int l,int r,int k){
    if(l==r){
        t[k].sum=t[k].vl=t[k].vr=a[l];
        t[k].cnt=1;
        return;
    }
    build(l,mid,ls);build(mid+1,r,rs);
    t[k]=pushup(t[ls],t[rs]);
}
void update(int l,int r,int k,int x){
    if(l==r){
        t[k].sum=t[k].vl=t[k].vr=a[l];
        t[k].cnt=1;
        return;
    }
    if(x<=mid)update(l,mid,ls,x);
    else update(mid+1,r,rs,x);
    t[k]=pushup(t[ls],t[rs]);
}
node query(int l,int r,int k,int x,int y){
    if(x<=l&&r<=y)return t[k];
    if(y<=mid)return query(l,mid,ls,x,y);
    if(x>mid)return query(mid+1,r,rs,x,y);
    return pushup(query(l,mid,ls,x,y),query(mid+1,r,rs,x,y));
}
#undef mid
#undef rs
#undef ls
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    build(1,n,1);
    cin>>q;
    while(q--){
        int op;
        cin>>op;
        if(op==1){
            int x,y;
            cin>>x>>y;a[x]=y;
            update(1,n,1,x);
        }
        else{
            int x,y;
            cin>>x>>y;
            cout<<query(1,n,1,x,y).cnt<<'\n';
        }
    }
    return 0;
}