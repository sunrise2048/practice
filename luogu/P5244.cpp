#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int M=1e6+5;
int n,m;
pair<int,int> a[N];
int cn[N];
class BIT{
public:
    int t[M];
    void up(int x,int d){
        ++x;
        while(x<=m+1){
            t[x]=max(t[x],d);
            x+=(x&-x);
        }
    }
    int qu(int x){
        ++x;
        int s=0;
        while(x){
            s=max(t[x],s);
            x-=(x&-x);
        }
        return s;
    }
}bit;
vector<int> id[N];
ll f[N];
int lm;
vector<int> t[N<<2];
#define mid (l+r>>1)
#define rs (k<<1|1)
#define ls (k<<1)
void update(int l,int r,int k,int x,int y,int d){
    if(x<=l&&r<=y){
        t[k].push_back(d);
        return;
    }
    if(x<=mid)update(l,mid,ls,x,y,d);
    if(y>mid)update(mid+1,r,rs,x,y,d);
}
int ncn;
vector<int> qid,lid;
void dfs(int l,int r,int k){
    if(!t[k].empty()){
        swap(t[k],qid);
        solve(0,qid.size()-1,);
    }
    if(l==r)return;
    dfs(l,mid,ls);dfs(mid+1,r,rs);
}
#undef mid
#undef rs
#undef ls
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>a[i].first>>a[i].second;
    }
    sort(a+1,a+n+1);
    a[n+1]={m,m};
    ++n;
    for(int i=1;i<=n;++i){
        cn[i]=bit.qu(a[i].second)+1;
        bit.up(a[i].second,cn[i]);
    }
    for(int i=0;i<=n;++i){
        id[cn[i]].push_back(i);
    }
    for(int i=1;i<=cn[n];++i){
        lm=id[i-1].size();
        swap(lid,id[i-1]);
        for(int j=0;j<id[i].size();++j){
            int no=id[i][j];
            ;
        }
    }
    return 0;
}