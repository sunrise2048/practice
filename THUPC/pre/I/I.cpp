#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=205;
const int mod=1e9+7;
int n,m;
string s[N];
int f[N][N][N];
int cn[N][N][2];
bool fl[N][N][N];
bool tf[N];
bool nf[N];
int c[N];
void find_ans(){
    for(int i=1;i<=m;++i){
        bool fl0=0;
        for(int la=1;la<=n;++la){
            if(!tf[la])continue;
            if(cn[n][i][1]-cn[la-1][i][1]==0&&fl[i+1][la][n]){
                fl0=1;
                break;
            }
        }
        if(fl0)cout<<"0";
        else cout<<"1";
        int op=fl0^1;
        c[i]=op;
        memset(nf,0,sizeof(nf));
        for(int la=1;la<=n;++la){
            if(!tf[la])continue;
            if(op){
                for(int j=la-1;j<=n;++j){
                    if(cn[n][i][0]-cn[j][i][0]==0&&cn[j][i][1]-cn[la-1][i][1]==0&&fl[i+1][la][j]&&fl[i+1][j+1][n]){
                        nf[j+1]=1;
                    }
                }
            }
            else{
                if(cn[n][i][1]-cn[la-1][i][1]==0&&fl[i+1][la][n])nf[la]=1;
            }
        }
        memcpy(tf,nf,sizeof(nf));
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>s[i];
        s[i]="0"+s[i];
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cn[i][j][0]=cn[i-1][j][0];
            cn[i][j][1]=cn[i-1][j][1];
            if(s[i][j]!='.'){
                cn[i][j][s[i][j]-'0']++;
            }
        }
    }
    for(int i=1;i<=n+1;++i){
        for(int j=i-1;j<=n;++j){
            fl[m+1][i][j]=1;
        }
    }
    for(int k=m;k;--k){
        for(int i=1;i<=n+1;++i){
            fl[k][i][i-1]=1;
            for(int j=i;j<=n;++j){
                for(int t=i-1;t<=j;++t){
                    if(!fl[k+1][i][t])break;
                    if(cn[t][k][1]-cn[i-1][k][1])break;
                    if(!fl[k+1][t+1][j])continue;
                    if(cn[j][k][0]-cn[t][k][0])continue;
                    fl[k][i][j]=1;
                }
            }
        }
    }
    if(!fl[1][1][n]){
        cout<<"-1\n";
        return 0;
    }
    tf[1]=1;
    find_ans();
    for(int i=1;i<=n+1;++i){
        for(int j=i-1;j<=n;++j){
            f[m+1][i][j]=1;
        }
    }
    for(int k=m;k;--k){
        for(int i=1;i<=n+1;++i){
            f[k][i][i-1]=1;
            for(int j=i;j<=n;++j){
                if(j==n){
                    if(c[k]==0){
                        if(cn[n][k][1]-cn[i-1][k][1])continue;
                        f[k][i][j]=f[k+1][i][j];
                    }
                    else{
                        for(int t=i-1;t<j;++t){
                            if(!fl[k+1][i][t])break;
                            if(cn[t][k][1]-cn[i-1][k][1])break;
                            if(!fl[k+1][t+1][j])continue;
                            if(cn[j][k][0]-cn[t][k][0])continue;
                            f[k][i][j]=(f[k][i][j]+1ll*f[k+1][i][t]*f[k+1][t+1][j])%mod;
                        }
                    }
                }
                else{
                    for(int t=i-1;t<=j;++t){
                        if(!fl[k+1][i][t])break;
                        if(cn[t][k][1]-cn[i-1][k][1])break;
                        if(!fl[k+1][t+1][j])continue;
                        if(cn[j][k][0]-cn[t][k][0])continue;
                        f[k][i][j]=(f[k][i][j]+1ll*f[k+1][i][t]*f[k+1][t+1][j])%mod;
                    }
                }
            }
        }
    }
    cout<<' ';
    cout<<f[1][1][n]<<'\n';
    return 0;
}