#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int T;
int n,k;
int a[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        if(k&1){
            for(int i=1;i<=k;++i)cout<<n<<' ';
        }
        else{
            memset(a,0,sizeof(int)*(k+1));
            for(int bs=29;bs>=0;--bs){
                int cn=0;
                for(int i=1;i<=k;++i){
                    if((a[i]+(1<<bs))<=n){
                        ++cn;
                    }
                }
                if(n&(1<<bs)){
                    if(cn%2==0)--cn;
                }
                else{
                    if(cn%2==1)--cn;
                }
                for(int i=1;i<=k;++i){
                    if((a[i]+(1<<bs))>n)continue;
                    if(!cn)break;
                    if((a[i]&((1<<30)-(1<<bs+1)))!=(n&((1<<30)-(1<<bs+1)))){
                        a[i]+=(1<<bs);
                        --cn;
                    }
                }
                for(int i=1;i<=k;++i){
                    if((a[i]+(1<<bs))>n)continue;
                    if(!cn)break;
                    if((a[i]&((1<<30)-(1<<bs+1)))==(n&((1<<30)-(1<<bs+1)))){
                        a[i]+=(1<<bs);
                        --cn;
                    }
                }
            }
            for(int i=1;i<=k;++i)cout<<a[i]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}