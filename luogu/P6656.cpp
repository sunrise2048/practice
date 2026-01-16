#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e6+5;
int n;
string s;
char c[N];
int sa[N],rk[N];
int id[N];
int lrk[N];
int t[N];
int h[N];
int lg[N];
int st[21][N];
void SA(){
    int m=210;
    for(int i=1;i<=(n<<1);++i){
        rk[i]=c[i];t[rk[i]]++;
    }
    for(int i=1;i<=m;++i)t[i]+=t[i-1];
    for(int i=(n<<1);i;--i){
        sa[t[rk[i]]--]=i;
    }
    for(int k=1;k<(n<<1);k<<=1){
        int tn=0;
        for(int i=(n<<1)-k+1;i<=(n<<1);++i)id[++tn]=i;
        for(int i=1;i<=(n<<1);++i){
            if(sa[i]>k)id[++tn]=sa[i]-k;
        }
        memset(t,0,sizeof(int)*(m+1));
        for(int i=1;i<=(n<<1);++i)t[rk[i]]++;
        for(int i=1;i<=m;++i)t[i]+=t[i-1];
        for(int i=(n<<1);i;--i)sa[t[rk[id[i]]]--]=id[i];
        m=0;
        memcpy(lrk,rk,sizeof(int)*((n<<1)+1));
        for(int i=1;i<=(n<<1);++i){
            if(lrk[sa[i-1]]==lrk[sa[i]]&&lrk[sa[i-1]+k]==lrk[sa[i]+k])rk[sa[i]]=m;
            else rk[sa[i]]=++m;
        }
        if((n<<1)==m)break;
    }
    for(int i=2;i<=(n<<1);++i)lg[i]=lg[i>>1]+1;
    int j=0;
    for(int i=1;i<=(n<<1);++i){
        if(j)--j;
        while(c[i+j]==c[sa[rk[i]-1]+j])++j;
        h[rk[i]]=j;
    }
    for(int i=1;i<=(n<<1);++i){
        st[0][i]=h[i];
    }
    for(int j=1;j<21;++j){
        for(int i=1;i+(1<<j)-1<=(n<<1);++i){
            st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)]);
        }
    }
}
struct node{
    int l,r,k;
    node()=default;
    node(int l,int r,int k):l(l),r(r),k(k){}
};
vector<node> ve;
int get_mi(int l,int r){
    int k=lg[r-l+1];
    return min(st[k][l],st[k][r-(1<<k)+1]);
}
int get_lcp(int x,int y){
    return get_mi(min(rk[x],rk[y])+1,max(rk[x],rk[y]));
}
int get_lcs(int x,int y){
    return get_mi(min(rk[2*n-x+1],rk[2*n-y+1])+1,max(rk[2*n-x+1],rk[2*n-y+1]));
}
bool cmp(int x,int y){
    int lc=get_lcp(x,y);
    lc=min(lc,n-y+1);
    if(y+lc==n+1)return 0;
    return c[x+lc]<c[y+lc];
}
void solve(int x,int y){
    if(y==n+1||c[x]!=c[y]){
        --x;--y;
        if(x==0)return;
    }
    if(c[x]!=c[y])return;
    int lcp=get_lcp(x,y);
    int lcs=get_lcs(x,y);
    lcp=min(lcp,n-y+1);
    if(lcp+lcs-1<y-x)return;
    int len=y-x+lcs+lcp-1;
    if(len>=(y-x)*2){
        ve.emplace_back(x-lcs+1,y+lcp-1,y-x);
    }
}
int st_id[N],str;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>s;
    n=s.size();
    s="0"+s;
    for(int i=1;i<=n;++i){
        c[i]=s[i];
        c[i+n]=s[n-i+1];
    }
    SA();
    st_id[str=1]=n+1;
    for(int i=n;i;--i){
        while(str>1&&cmp(i,st_id[str])==0)--str;
        st_id[++str]=i;
        solve(i,st_id[str-1]);
    }
    st_id[str=1]=n+1;
    for(int i=n;i;--i){
        while(str>1&&cmp(i,st_id[str])==1)--str;
        st_id[++str]=i;
        solve(i,st_id[str-1]);
    }
    sort(ve.begin(),ve.end(),[](const node& x,const node& y){
        return x.l!=y.l?x.l<y.l:(x.r!=y.r?x.r<y.r:x.k<y.k);
    });
    pair<int,int> ls(0,0);
    vector<node> tv;
    for(node no:ve){
        if(ls==make_pair(no.l,no.r))continue;
        ls={no.l,no.r};
        tv.push_back(no);
    }
    cout<<tv.size()<<'\n';
    for(node no:tv){
        cout<<no.l<<' '<<no.r<<' '<<no.k<<'\n';
    }
    return 0;
}