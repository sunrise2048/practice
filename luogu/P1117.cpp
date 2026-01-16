#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=6e4+5;
int T;
int n;
string s;
char c[N];
int sa[N],rk[N],lrk[N<<1];
int t[N];
int id[N];
int h[N];
int lg[N];
int st[18][N];
void SA(){
    memset(t,0,sizeof(t));
    memset(sa,0,sizeof(sa));
    memset(rk,0,sizeof(rk));
    memset(lrk,0,sizeof(lrk));
    const int n=::n<<1;
    int m=210;
    for(int i=1;i<=n;++i){
        rk[i]=c[i];
        t[rk[i]]++;
    }
    for(int i=1;i<=m;++i)t[i]+=t[i-1];
    for(int i=n;i;--i){
        sa[t[rk[i]]--]=i;
    }
    for(int k=1;k<n;k<<=1){
        int tn=0;
        for(int i=n-k+1;i<=n;++i)id[++tn]=i;
        for(int i=1;i<=n;++i){
            if(sa[i]>k){
                id[++tn]=sa[i]-k;
            }
        }
        memset(t,0,sizeof(int)*(m+1));
        for(int i=1;i<=n;++i)++t[rk[i]];
        for(int i=1;i<=m;++i)t[i]+=t[i-1];
        for(int i=n;i;--i)sa[t[rk[id[i]]]--]=id[i];
        memcpy(lrk,rk,sizeof(int)*(n+1));
        m=0;
        for(int i=1;i<=n;++i){
            if(lrk[sa[i]]==lrk[sa[i-1]]&&lrk[sa[i]+k]==lrk[sa[i-1]+k])rk[sa[i]]=m;
            else rk[sa[i]]=++m;
        }
        if(n==m)break;
    }
    int j=0;
    for(int i=1;i<=n;++i){
        if(j)--j;
        while(c[i+j]==c[sa[rk[i]-1]+j])++j;
        h[rk[i]]=j;
    }
    for(int i=2;i<=n;++i)lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;++i){
        st[0][i]=h[i];
    }
    for(int j=1;j<18;++j){
        for(int i=1;i+(1<<j)-1<=n;++i){
            st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)]);
        }
    }
}
int get_mi(int l,int r){
    int k=lg[r-l+1];
    return min(st[k][l],st[k][r-(1<<k)+1]);
}
int get_lcp(int x,int y){
    return min(n-y+1,get_mi(min(rk[x],rk[y])+1,max(rk[x],rk[y])));
}
int get_lcs(int x,int y){
    return get_mi(min(rk[2*n-x+1],rk[2*n-y+1])+1,max(rk[2*n-x+1],rk[2*n-y+1]));
}
ll f[N],g[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>s;
        n=s.size();
        s="0"+s;
        memset(f,0,sizeof(f));memset(g,0,sizeof(g));
        for(int i=1;i<=n;++i){
            c[i]=s[i];
            c[n+i]=s[n-i+1];
        }
        c[2*n+1]=0;
        SA();
        for(int k=1;k*2<=n;++k){
            for(int i=1;i+k<=n;i+=k){
                int lcp=min(get_lcp(i,i+k),k);
                int lcs=min(get_lcs(i,i+k),k);
                if(lcp+lcs-1<k)continue;
                int l=i-lcs+1;
                int r=i+lcp-k;
                g[r]++;g[l-1]--;
                l+=2*k-1,r+=2*k-1;
                f[l]++;f[r+1]--;
            }
        }
        for(int i=1;i<=n;++i)f[i]+=f[i-1];
        ll ans=0;
        for(int i=n;i;--i){
            g[i]+=g[i+1];
            ans+=f[i-1]*g[i];
        }
        cout<<ans<<'\n';
    }
    return 0;
}