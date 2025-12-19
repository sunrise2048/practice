#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=35;
const int M=105;
int n,k;
__float128 pp[M];
__float128 mp[M][N],mfp[M][N];
__float128 f[N][N];
__float128 get_val(int x,int y){
    __float128 sum=0;
    __float128 sp=0;
    for(int i=0;i<=100;++i){
        __float128 np=pp[i]*mp[i][y]*mfp[i][x-y]*1000;
        sp+=pp[i]*mp[i][y]*mfp[i][x-y];
        for(int j=1;j<=k-x;++j){
            np=np*2*i/100;
        }
        sum+=np;
    }
    if(sp==0)return -1;
    return sum/sp;
}
__float128 get_p(int x,int y){
    __float128 sum=0;
    __float128 sp=0;
    for(int i=0;i<=100;++i){
        sum+=pp[i]*mp[i][y]*mfp[i][x-y]*i/100;
        sp+=pp[i]*mp[i][y]*mfp[i][x-y];
    }
    if(sp==0)return -1;
    return sum/sp;
}
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;++i){
        int a;
        scanf("%d",&a);
        pp[a]++;
    }
    for(int i=0;i<=100;++i){
        pp[i]/=n;
        mp[i][0]=1;
        for(int j=1;j<=k;++j){
            mp[i][j]=mp[i][j-1]*i/100;
        }
        mfp[i][0]=1;
        for(int j=1;j<=k;++j){
            mfp[i][j]=mfp[i][j-1]*(100-i)/100;
        }
    }
    for(int i=0;i<=k;++i){
        f[k][i]=1000;
    }
    for(int i=k-1;i>=0;--i){
        for(int j=0;j<=i;++j){
            __float128 tp=get_p(i,j);
            if(tp<0){
                f[i][j]=1000;
                continue;
            }
            f[i][j]=max(get_val(i,j),(1-tp)*f[i+1][j]+tp*f[i+1][j+1]);
        }
    }
    printf("%.20Lf\n",(long double)(f[0][0]-1000));
    return 0;
}