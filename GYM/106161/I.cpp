#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10;
typedef long long ll;

int T;
int n,m;
pair<int,int> to[N<<1];

struct Point{
    int x,y;

    void read() {
        scanf("%d%d",&x,&y);
    }
}a[N<<1],b[N];

Point operator-(Point x,Point y) {
    x.x-=y.x;
    x.y-=y.y;
    return x;
}

ll cross(Point x,Point y) {
    return 1ll*x.x*y.y-1ll*x.y*y.x;
}

struct Seg{
    struct Node{
        ll sum;
        ll tag;
        #define lid(x) (x<<1)
        #define rid(x) (x<<1|1)
        #define sum(x) t[x].sum
        #define tag(x) t[x].tag
    }t[N<<3];

    void pushup(int id) {
        sum(id)=sum(lid(id))+sum(rid(id));
    }

    void pushdown(int id,int L,int R) {
        if(tag(id)) {
            int mid=L+R>>1;
            sum(lid(id))+=1ll*tag(id)*(mid-L+1),tag(lid(id))+=tag(id);
            sum(rid(id))+=1ll*tag(id)*(R-mid),tag(rid(id))+=tag(id);
            tag(id)=0;
        }
    }

    void build(int id,int L,int R) {
        sum(id)=tag(id)=0;
        if(L==R) return ;
        int mid=L+R>>1;
        build(lid(id),L,mid),build(rid(id),mid+1,R);
    }

    void modify(int id,int L,int R,int l,int r,ll val) {
        if(L>=l && R<=r) {
            sum(id)+=1ll*val*(R-L+1);
            tag(id)+=val;
            return ;
        }
        pushdown(id,L,R);
        int mid=L+R>>1;
        if(mid>=l) modify(lid(id),L,mid,l,r,val);
        if(mid+1<=r) modify(rid(id),mid+1,R,l,r,val);
        pushup(id);
    }

    ll query(int id,int L,int R,int l,int r) {
        if(L>=l && R<=r) return sum(id);
        pushdown(id,L,R);
        int mid=L+R>>1;
        ll res=0;
        if(mid>=l) res+=query(lid(id),L,mid,l,r);
        if(mid+1<=r) res+=query(rid(id),mid+1,R,l,r);
        return res;
    }

    #undef lid
    #undef rid
    #undef sum
    #undef tag
}seg[2];

void build() {
    seg[0].build(1,1,n<<1);
    seg[1].build(1,1,n<<1);
}

void modify(int t,int l,int r,int val) {
    seg[0].modify(1,1,n<<1,l,r,val);
    seg[1].modify(1,1,n<<1,l,r,1ll*t*val);
}

ll query(int t,int l,int r) {
    return seg[1].query(1,1,n<<1,l,r)-(t-1)*seg[0].query(1,1,n<<1,l,r);
}

int main() {
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) a[i].read(),a[i+n]=a[i];
        scanf("%d",&m);
        for(int i=1;i<=m;i++) b[i].read();
        ll ans=1ll*n*(n-1)*(n-2)/3;
        int pl=1,pr=1;
        for(int i=1;i<=m;i++) if(cross(b[i]-a[1],b[pl]-a[1])>0) pl=i;
        for(int i=1;i<=m;i++) if(cross(b[pr]-a[1],b[i]-a[1])>0) pr=i;
        for(int i=1;i<=n;i++) {
            while(cross(b[pl%m+1]-a[i],b[pl]-a[i])>0) pl=pl%m+1;
            while(cross(b[pr]-a[i],b[pr%m+1]-a[i])>0) pr=pr%m+1;
            int L=i+1,R=i+n-1,mid,res=i;
            while(L<=R) {
                mid=L+R>>1;
                if(cross(a[mid]-a[i],b[pl]-a[i])>=0) res=mid,L=mid+1;
                else R=mid-1;
            }
            to[i].first=res;
            L=i+1,R=i+n-1,mid,res=i+n;
            while(L<=R) {
                mid=L+R>>1;
                if(cross(b[pr]-a[i],a[mid]-a[i])>=0) res=mid,R=mid-1;
                else L=mid+1;
            }
            to[i].second=res;
            to[i+n].first=min(n*2+1,to[i].first+n);
            to[i+n].second=min(n*2,to[i].second+n);
            ans-=1ll*(to[i].first-i)*(to[i].first-i-1)/2;
            ans-=1ll*(i+n-to[i].second)*(i+n-to[i].second-1)/2;
            ans-=1ll*(to[i].second-to[i].first-1)*(to[i].first-i+i+n-to[i].second);
            // ans+=2ll*(to[i].second-to[i].first-1)*(to[i].second-to[i].first-2)/2;
        }
        assert(ans%2==0);
        ans>>=1;
        ans*=3;
        build();
        static vector<int> ins[N<<1];
        for(int i=1;i<=n<<1;i++) ins[i].clear();
        for(int i=1;i<=n;i++) ins[to[i].first+1].push_back(i);
        for(int i=n<<1;i>=1;i--) {
            if(to[i].first<to[i].second) modify(i,to[i].first+1,to[i].second-1,1);
            for(int j:ins[i]) {
                int l=to[j].first+1,r=to[j].second-1;
                if(l<=r) ans-=3*query(i,l,r);
            }
        }
        // for(int i=1;i<=n;i++) {
        //     for(int j=to[i].first+1;j<to[i].second;j++) {
        //         for(int k=to[j].first+1;k<to[j].second && k<to[i].second;k++) ans--;
        //     }
        // }
        assert(ans%3==0);
        ans/=3;
        printf("%lld\n",ans);
    }
    return 0;
}
