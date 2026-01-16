#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace __gnu_pbds;
using namespace std;
using ll=long long;
using ull=unsigned long long;
const int N=1e6+5;
const ull bsp=(ull)(2e9)+11;
int T;
int n;
int a[N];
ull vl[N];
ull rd1,rd2;
ull splitmix64(ull x) {
    x += 0x9e3779b97f4a7c15ull;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ull;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebull;
    return x ^ (x >> 31);
}
ull hash_pr(ull x,ull y){
    x=splitmix64(x),y=splitmix64(y);
    return x*y+x+(x^y);
}
mt19937_64 mt(time(0));
ll ans;
const int limbl=100;
int t[N],mx,cnc;
int mi[N];
vector<ull> qs[N];
gp_hash_table<ull,int> mp;
ull sm[N];
void solve(int l,int r){
    if(r-l+1<=limbl){
        for(int i=l;i<=r;++i){
            for(int j=i;j<=r;++j){
                t[a[j]]++;
                if(t[a[j]]==1)++cnc;
                mx=max(mx,t[a[j]]);
                if(cnc*mx==j-i+1){
                    ++ans;
                }
            }
            cnc=mx=0;
            for(int j=i;j<=r;++j){
                t[a[j]]=0;
            }
        }
        return;
    }
    const int mid=(l+r>>1);
    ull sum_c=0,sumv=0;
    for(int i=mid+1;i<=r;++i){
        sumv+=vl[a[i]];
        if(!t[a[i]])sum_c+=vl[a[i]];
        t[a[i]]=1;
        mp[hash_pr(sum_c,(sum_c-sumv%sum_c)%sum_c)]++;
    }
    for(int i=mid+1;i<=r;++i){
        t[a[i]]=0;
    }
    sum_c=sumv=0;
    for(int i=mid;i>=l;--i){
        sumv+=vl[a[i]];
        if(!t[a[i]])sum_c+=vl[a[i]];
        t[a[i]]=1;
        ans+=mp[hash_pr(sum_c,sumv%sum_c)];
    }
    for(int i=l;i<=mid;++i)t[a[i]]=0;
    sum_c=sumv=0;
    mp.clear();
    ull smx_c=0,smxv=0;
    {
        int nid=mid+1;
        int cnc=0;
        for(int i=mid+1;i<=r;++i)sm[i]=sm[i-1]+vl[a[i]];
        for(int i=mid;i>=l;--i){
            sumv+=vl[a[i]];
            if(!t[a[i]]){
                sum_c+=vl[a[i]];
                ++cnc;
            }
            t[a[i]]++;
            if(mx<t[a[i]]){
                mx=t[a[i]];
            }
            while(nid<=r&&t[a[nid]]){
                ++nid;
            }
            ll tcn=cnc*mx;
            if(i+tcn-1<nid&&i+tcn-1>mid&&sm[i+tcn-1]+sumv==mx*sum_c)++ans;
        }
        for(int i=mid+1;i<=r;++i)sm[i]=0;
        sumv=sum_c=0;
        mx=0;cnc=0;
        for(int i=l;i<=mid;++i){
            t[a[i]]=0;
        }
        for(int i=mid;i>=l;--i)sm[i]=sm[i+1]+vl[a[i]];
        nid=mid;
        for(int i=mid+1;i<=r;++i){
            sumv+=vl[a[i]];
            if(!t[a[i]]){
                sum_c+=vl[a[i]];
                ++cnc;
            }
            t[a[i]]++;
            if(mx<t[a[i]]){
                mx=t[a[i]];
            }
            while(nid>=l&&t[a[nid]]){
                --nid;
            }
            ll tcn=cnc*mx;
            if(i-tcn+1>nid&&i-tcn+1<=mid&&sm[i-tcn+1]+sumv==mx*sum_c)++ans;
        }
        for(int i=l;i<=mid;++i)sm[i]=0;
        sumv=sum_c=0;
        mx=0;cnc=0;
        for(int i=mid+1;i<=r;++i){
            t[a[i]]=0;
        }
    }
    for(int i=r;i>mid;--i){
        mi[a[i]]=i;
    }
    sumv=sum_c=0;
    int nr=r;
    for(int i=mid;i>=l;--i){
        sumv+=vl[a[i]];
        if(!t[a[i]])sum_c+=vl[a[i]];
        t[a[i]]++;
        if(mx<t[a[i]]){
            mx=t[a[i]];
            smx_c=smxv=0;
            nr=r;
        }
        if(t[a[i]]==mx){
            smx_c+=vl[a[i]];
            smxv+=vl[a[i]]*t[a[i]];
            if(mi[a[i]])nr=min(nr,mi[a[i]]-1);
        }
        ull nc=sum_c-smx_c,nv=sumv-smxv;
        if(nr>mid){
            if(nc)qs[nr].push_back(hash_pr(mx,hash_pr(nc,mx*nc-nv)));
            else qs[nr].push_back(hash_pr(mx,0));
        }
    }
    for(int i=l;i<=mid;++i)t[a[i]]=0;
    for(int i=mid+1;i<=r;++i)mi[a[i]]=0;
    mx=0;
    sumv=sum_c=smx_c=smxv=0;
    for(int i=mid+1;i<=r;++i){
        sumv+=vl[a[i]];
        if(!t[a[i]])sum_c+=vl[a[i]];
        t[a[i]]++;
        if(mx<t[a[i]]){
            mx=t[a[i]];
            smx_c=smxv=0;
            nr=r;
        }
        if(t[a[i]]==mx){
            smx_c+=vl[a[i]];
            smxv+=vl[a[i]]*t[a[i]];
        }
        ull nc=sum_c-smx_c,nv=sumv-smxv;
        if(nc)mp[hash_pr(mx,hash_pr(nc,nv))]++;
        else mp[hash_pr(mx,0)]++;
        for(ull no:qs[i]){
            ans+=mp[no];
        }
        qs[i].clear();
    }
    mp.clear();
    for(int i=mid+1;i<=r;++i){
        t[a[i]]=0;
    }
    mx=0;
    //cout<<l<<' '<<mid<<' '<<r<<' '<<ans<<'\n';
    solve(l,mid);solve(mid+1,r);
}
const ull lim_mt=1e11,lim_mi=1e9;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    rd1=mt(),rd2=mt();
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        for(int i=1;i<=n;++i){
            vl[i]=mt()%lim_mt+lim_mi;
        }
        ans=0;
        solve(1,n);
        cout<<ans<<'\n';
    }
    return 0;
}