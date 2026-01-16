#include<bits/stdc++.h>
using namespace std;
using ull=unsigned long long;
const ull bas=19260817;
const int N=2e5+5;
int n,q;
char c[N];
ull bs[N];
ull ha[N];
ull geth(int l,int r){
    return ha[r]-ha[l-1]*bs[r-l+1];
}
int get_lcp(int x,int y){
    int l=0,r=n-max(x,y)+2;
    while(l<r-1){
        int mid=l+r>>1;
        if(geth(x,x+mid-1)==geth(y,y+mid-1))l=mid;
        else r=mid;
    }
    return l;
}
int get_lcs(int x,int y){
    int l=0,r=min(x,y)+1;
    while(l<r-1){
        int mid=l+r>>1;
        if(geth(x-mid+1,x)==geth(y-mid+1,y))l=mid;
        else r=mid;
    }
    return l;
}
bool cmp(int x,int y){
    int lcp=get_lcp(x,y);
    if(lcp>=n-y+1)return 0;
    return c[x+lcp]<c[y+lcp];
}
struct Runs{
    int l,r,p;
    Runs()=default;
    Runs(int l,int r,int p):l(l),r(r),p(p){}
};
vector<Runs> runs;
int st[N],str;
void get_runs(int x,int y){
    if(y>n||c[x]!=c[y])--x,--y;
    if(x<1||c[x]!=c[y])return;
    int l=x-get_lcs(x,y)+1,r=y+get_lcp(x,y)-1;
    if(r-l+1>=(y-x)*2){
        runs.emplace_back(l,r,y-x);
    }
}
void lyndon(int op){
    st[str=1]=n+1;
    for(int i=n;i;--i){
        while(str>1&&cmp(i,st[str])==op)--str;
        get_runs(i,st[str]);
        st[++str]=i;
    }
}
class BIT{
public:
    int t[N];
    void upd(int x,int y){
        while(x){
            t[x]+=y;
            x-=(x&-x);
        }
    }
    int qu(int x){
        int s=0;
        while(x<=n){
            s+=t[x];
            x+=(x&-x);
        }
        return s;
    }
}bit;
vector<pair<int,int>> qu[N];
vector<Runs> rr[N],by[N];
map<ull,int> mp;
ull ans[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>q;
    bs[0]=1;
    for(int i=1;i<=n;++i){
        cin>>c[i];
        bs[i]=bs[i-1]*bas;
        ha[i]=ha[i-1]*bas+c[i];
    }
    lyndon(0);lyndon(1);
    sort(runs.begin(),runs.end(),[](const Runs& x,const Runs& y){
        return x.l!=y.l?x.l<y.l:(x.r!=y.r?x.r<y.r:x.p<y.p);
    });
    vector<Runs> nR;
    for(Runs no:runs){
        if(nR.empty()||nR.back().l!=no.l||nR.back().r!=no.r){
            nR.push_back(no);
        }
    }
    swap(nR,runs);
    for(int i=1;i<=q;++i){
        int l,r;
        cin>>l>>r;
        qu[r].emplace_back(l,i);
    }
    for(Runs no:runs){
        rr[no.r].push_back(no);
        for(int j=no.l;j+no.p*2-1<=no.r;++j){
            by[j+no.p*2-1].push_back(no);
        }
    }
    for(int i=1;i<=n;++i){
        for(Runs no:by[i]){
            auto [l,r,p]=no;
            int t=(i-l+1)/(2*p),tl=i-t*2*p+1;
            ull ph=geth(tl,i);
            if(mp[ph])bit.upd(mp[ph],-1);
            mp[ph]=0;
        }
        for(auto [l,id]:qu[i]){
            ans[id]=bit.qu(l);
            for(Runs no:by[i]){
                int rlen=i-max(no.l,l)+1,p=no.p;
                ull ys=rlen%(2*p),cs=rlen/(2*p);
                if(cs==0)continue;
                if(ys>=p-1)ans[id]+=cs*p;
                else ans[id]+=cs*(ys+1)+(cs-1)*(p-ys-1);
            }
        }
        for(Runs no:rr[i]){
            auto [l,r,p]=no;
            for(int j=l;j+2*p-1<=r;++j){
                int t=(r-j+1)/(2*p);
                int tr=j+t*(2*p)-1;
                if(r-tr>=p)continue;
                ull ha=geth(j,tr);
                mp[ha]=j;
                bit.upd(j,1);
            }
        }
    }
    for(int i=1;i<=q;++i){
        cout<<ans[i]<<'\n';
    }
    return 0;
}