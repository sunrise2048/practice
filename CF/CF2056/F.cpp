#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=(1<<18)+5;
int T;
int n,m;
int f[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        int ck;
        cin>>ck>>m;
        n=0;
        while(ck--){
            char c;
            cin>>c;
            n+=c-'0';
        }
        int ans=0;
        int lm=0;
        while((1<<lm)<=min(n,m))++lm;
        for(int i=0;i<(1<<lm);++i){
            f[i]=(i<n&&i<m&&(((n-i-1)&(i/2))==0));
        }
        for(int k=1;k<(1<<lm);k<<=1){
            for(int i=0;i<(1<<lm);i+=(k<<1)){
                for(int j=0;j<k;++j){
                    f[i+j+k]^=f[i+j];
                }
            }
        }
        int ls=0,cn=0;
        for(int i=0;i<(1<<lm);++i){
            if(f[i]){
                ls^=i;
                ++cn;
            }
        }
        if((m>>lm)&1)ans=ls;
        if(cn&1){
            int hb=(m>>lm)-1;
            if(hb%4==0){
                ans^=hb<<lm;
            }
            else if(hb%4==1){
                ans^=1<<lm;
            }
            else if(hb%4==2){
                ans^=(hb+1)<<lm;
            }
        }
        for(int i=((m>>lm)<<lm);i<m;++i)ans^=i*f[i%(1<<lm)];
        cout<<ans<<'\n';
    }
    return 0;
}