#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
const int N=1005;
const ull bas=19260817;
int T;
int n,m;
ull bs[N];
unordered_set<ull> st;
int a[N][N];
int b[N];
int d;
void solve(int l,int r,int d,int op=0){
    if(l>r)return;
    if(d==::d+1)return;
    const int mid=l+r>>1;
    for(int i=l;i<=mid;++i)a[d][i]=op;
    for(int i=mid+1;i<=r;++i)a[d][i]=op^1;
    solve(l,mid,d+1,op);solve(mid+1,r,d+1,op^(d==1));
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    bs[0]=1;
    for(int i=1;i<=1000;++i)bs[i]=bs[i-1]*bas;
    while(T--){
        cin>>n>>m;
        if((n*m)&1){
            cout<<"NO\n";
            continue;
        }
        if((n<10&&m>(1<<n))||(m<10&&n>(1<<m))){
            cout<<"NO\n";
            continue;
        }
        cout<<"YES\n";
        bool fl=0;
        if(m&1){
            swap(n,m);fl=1;
        }
        for(int i=1;i<=n;++i)memset(a[i],0,sizeof(int)*(m+1));
        st.clear();
        d=0;
        while((1<<d)<m)++d;
        solve(1,m,1);
        for(int i=1;i<=d;++i){
            ull ha=0;
            for(int j=1;j<=m;++j)ha+=bs[j]*a[i][j];
            st.insert(ha);
        }
        memset(b,0,sizeof(int)*(m+2));
        while(!b[m+1]&&d+2<=n){
            ull h1=0,h2=0;
            for(int i=1;i<=m;++i){
                h1+=b[i]*bs[i];
                h2+=(1-b[i])*bs[i];
            }
            if(st.count(h1)==0&&st.count(h2)==0){
                ++d;
                for(int i=1;i<=m;++i)a[d][i]=b[i],a[d+1][i]=1-b[i];
                ++d;
                st.insert(h1);st.insert(h2);
            }
            {
                int ed=1;
                while(b[ed])++ed;
                for(int i=1;i<ed;++i)b[i]=0;
                b[ed]=1;
            }
        }
        for(int dd=1;dd+d<=n;++dd){
            for(int i=1;i<=m;++i)a[dd+d][i]=1-a[dd][i];
        }
        if(fl){
            for(int i=1;i<=m;++i){
                for(int j=1;j<=n;++j){
                    cout<<a[j][i];
                }cout<<'\n';
            }
        }
        else{
            for(int i=1;i<=n;++i){
                for(int j=1;j<=m;++j){
                    cout<<a[i][j];
                }cout<<'\n';
            }
        }
    }
    return 0;
}