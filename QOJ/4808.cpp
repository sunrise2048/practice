#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n,q;
int a[N];
struct ques{
    int l,r;
    int id;
    int lc;
}qs[N];
ll ans[N];
int tl[2][1<<20],tr[2][1<<20];
ll cnt;
int cnl[2],cnr[2];
void upd_l(const int& op,int x,int d){
    cnt+=cnr[op^1]*d;
    cnt+=(cnr[op]-tr[op][x])*d;
    tl[op][x]+=d;
    cnl[op]+=d;
}
void upd_r(const int& op,int x,int d){
    cnt+=cnl[op^1]*d;
    cnt+=(cnl[op]-tl[op][x])*d;
    tr[op][x]+=d;
    cnr[op]+=d;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        --a[i];a[i]^=a[i-1];
    }
    const int kc=sqrt(n)+1;
    for(int i=1;i<=q;++i){
        cin>>qs[i].l>>qs[i].r;
        qs[i].id=i;
        qs[i].lc=qs[i].l/kc;
    }
    sort(qs+1,qs+q+1,[](const ques& x,const ques& y){
        return x.lc!=y.lc?x.lc<y.lc:(x.lc&1?x.r>y.r:x.r<y.r);
    });
    int l=1,r=0;
    for(int i=1;i<=q;++i){
        while(l>qs[i].l){
            --l;
            cnr[l&1]++;tr[l&1][a[l]]++;
            upd_l((l-1)&1,a[l-1],1);
        }
        while(r<qs[i].r){
            ++r;
            cnl[(r-1)&1]++;tl[(r-1)&1][a[r-1]]++;
            upd_r(r&1,a[r],1);
        }
        while(l<qs[i].l){
            upd_l((l-1)&1,a[l-1],-1);
            cnr[l&1]--;tr[l&1][a[l]]--;
            ++l;
        }
        while(r>qs[i].r){
            upd_r(r&1,a[r],-1);
            cnl[(r-1)&1]--;tl[(r-1)&1][a[r-1]]--;
            --r;
        }
        ans[qs[i].id]=cnt;
    }
    for(int i=1;i<=q;++i){
        cout<<ans[i]<<'\n';
    }
    return 0;
}