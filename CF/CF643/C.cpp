#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
const int K=55;
const double inf=1e18;
int n,k;
double t[N],s[N];
double ss[N];
double ds[N];
int fj[K];
double f[N][K];
double calc(int l,int r){
    return ss[r]-ss[l-1]-s[l-1]*(ds[r]-ds[l-1]);
}
double get_k(int id){
    return -s[id];
}
double get_b(int k,int id){
    return f[id][k-1]-ss[id]+s[id]*ds[id];
}
int id[K][N];
int sr[K],sl[K];
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;++i){
        cin>>t[i];
        s[i]=s[i-1]+t[i];
        ss[i]=ss[i-1]+s[i]/t[i];
        ds[i]=ds[i-1]+1/t[i];
    }
    for(int i=1;i<=k;++i){
        sl[i]=sr[i]=1;
    }
    for(int i=1;i<=n;++i){
        f[i][0]=inf;
        for(int j=1;j<=k;++j){
            while(sl[j]!=sr[j]&&get_b(j,id[j][sl[j]])+get_k(id[j][sl[j]])*ds[i]>=get_b(j,id[j][sl[j]+1])+get_k(id[j][sl[j]+1])*ds[i])++sl[j];
            f[i][j]=ss[i]+get_b(j,id[j][sl[j]])+get_k(id[j][sl[j]])*ds[i];
            double nk=-s[i],nb=f[i][j-1]-ss[i]+s[i]*ds[i];
            while(sl[j]!=sr[j]&&(get_b(j,id[j][sr[j]])-get_b(j,id[j][sr[j]-1]))/(get_k(id[j][sr[j]-1])-get_k(id[j][sr[j]]))>=(nb-get_b(j,id[j][sr[j]]))/(get_k(id[j][sr[j]])-nk))--sr[j];
            id[j][++sr[j]]=i;
        }
    }
    printf("%.12f\n",f[n][k]);
    return 0;
}