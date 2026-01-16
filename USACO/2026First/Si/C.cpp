#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n,k;
int c[N];
int cn[N][2];
int op[N];
int mx[2],mi[2];
int lmx[2],lmi[2];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=0;i<k;++i){
            cn[i][0]=cn[i][1]=0;
        }
        for(int i=0;i<=n-k;++i){
            char op;
            cin>>op;
            c[i]=op-'0';
        }
        for(int i=0;i<k;++i){
            op[i]=0;
            cn[i][op[i]]++;
        }
        for(int i=k;i<n;++i){
            if(c[i-k]^c[i-k+1]){
                op[i]=op[i-k]^1;
                cn[i%k][op[i]]++;
            }
            else{
                op[i]=op[i-k];
                cn[i%k][op[i]]++;
            }
        }
        mx[0]=0;mx[1]=-n-1;
        mi[0]=0;mi[1]=n+1;
        for(int i=0;i<k;++i){
            for(int op:{0,1}){
                lmi[op]=mi[op];
                lmx[op]=mx[op];
            }
            mx[0]=mx[1]=-n-1;
            mi[0]=mi[1]=n+1;
            for(int lop:{0,1}){
                for(int nop:{0,1}){
                    mx[lop^nop]=max(mx[lop^nop],lmx[lop]+cn[i][nop^1]);
                    mi[lop^nop]=min(mi[lop^nop],lmi[lop]+cn[i][nop^1]);
                }
            }
        }
        cout<<mi[c[0]]<<' '<<mx[c[0]]<<'\n';
    }
    return 0;
}