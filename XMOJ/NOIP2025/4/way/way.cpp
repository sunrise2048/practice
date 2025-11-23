#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int T;
int n,q;
int a[N];
int p[N],tim[N];
int main(){
    freopen("way.in","r",stdin);
    freopen("way.out","w",stdout);
    scanf("%d",&T);
    while (T--) {
        scanf("%d%d",&n,&q);
        for (int i=0;i<n;++i) {
            scanf("%d",&a[i]);
            a[i]-=n-1;
            tim[i]=0;
            p[i]=-1;
        }
        stack<int> st;
        for (int i=0;i<n;++i) {
            if (a[i]==1) continue;
            if (a[i]==2) {
                st.push(i);
            }
            else if(!st.empty()) {
                int tp=st.top();
                st.pop();
                p[tp]=i;
                tim[i]=i-tp+1;
            }
        }
        for (int i=0;i<n;++i) {
            if (st.empty()) break;
            if (a[i]==0&&tim[i]==0) {
                int tp=st.top();
                st.pop();
                p[tp]=i;
                tim[i]=(n-tp+1)+i+1;
            }
        }
        while (q--) {
            ll id;
            scanf("%lld",&id);
            ll nt=id/n+1;
            int id0=id%n;
            if (a[id0]==0&&(tim[id0]==0||tim[id0]>nt)) {
                printf("%d ",n-1);
            }
            else {
                int ls=(nt-1)%(n+1);
                if (id0-ls==-1) {
                    printf("%d ",n);
                }
                else {
                    ll z=(id0-ls);
                    if (z<0) z+=n+1;
                    bool fl=0;
                    if (a[z]==2) {
                        if (p[z]==-1||tim[p[z]]>nt) fl=1;
                        if (id0-ls>=0&&tim[p[z]]==nt&&p[z]>id0) fl=1;
                    }
                    if (fl) printf("%d ",n+1);
                    else printf("%d ",n);
                }
            }
        }
        printf("\n");
    }
    return 0;
}