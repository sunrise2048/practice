#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=10;
const int L=6e4;
const int mod=998244353;
int T;
int n;
int a[L],b[L],c[L];
int mi[N+1];
int sa[N][3],sb[N][3],sc[N][3];
int op[3][3];
int dfs(int x,int y){
    if(y==3){
        y-=3;
        ++x;
    }
    if(x==3){
        vector<int> s(3);
        for(int i=0;i<n;++i){
            s[0]=s[1]=s[2]=0;
            for(int a=0;a<3;++a){
                for(int b=0;b<3;++b){
                    s[op[a][b]]=(s[op[a][b]]+(ll)sa[i][a]*sb[i][b])%mod;
                }
            }
            if(s[0]!=sc[i][0]||s[1]!=sc[i][1]||s[2]!=sc[i][2])return 0;
        }
        return 1;
    }
    for(int i=0;i<3;++i){
        op[x][y]=i;
        if(dfs(x,y+1))return 1;
    }
    return 0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    mi[0]=1;
    for(int i=1;i<=10;++i)mi[i]=mi[i-1]*3;
    cin>>T;
    while(T--){
        cin>>n;
        memset(sa,0,sizeof(sa));
        memset(sb,0,sizeof(sb));
        memset(sc,0,sizeof(sc));
        for(int i=0;i<mi[n];++i){
            cin>>a[i];
            for(int j=0;j<n;++j){
                int op=i/mi[j]%3;
                sa[j][op]=(sa[j][op]+a[i])%mod;
            }
        }
        for(int i=0;i<mi[n];++i){
            cin>>b[i];
            for(int j=0;j<n;++j){
                int op=i/mi[j]%3;
                sb[j][op]=(sb[j][op]+b[i])%mod;
            }
        }
        for(int i=0;i<mi[n];++i){
            cin>>c[i];
            for(int j=0;j<n;++j){
                int op=i/mi[j]%3;
                sc[j][op]=(sc[j][op]+c[i])%mod;
            }
        }
        dfs(0,0);
        for(int i=0;i<3;++i){
            for(int j=0;j<3;++j){
                cout<<op[i][j]<<' ';
            }
        }
        cout<<'\n';
    }
    return 0;
}