#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int T;
int n;
int a[N];
class BIT{
public:
    int t[N];
    void cl(){memset(t,0,sizeof(int)*(n+1));}
    void upd(int x,int d){
        while(x<=n){
            t[x]+=d;
            x+=(x&-x);
        }
    }
    int qu(int x){
        int s=0;
        while(x){
            s+=t[x];
            x-=(x&-x);
        }
        return s;
    }
}bit1,bit2;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;++i)cin>>a[i];
        vector<int> lis,lds;
        bit1.cl();bit2.cl();
        ll sum=0;
        for(int i=1;i<=n;++i){
            int iti=lower_bound(lis.begin(),lis.end(),a[i])-lis.begin();
            int itd=lower_bound(lds.begin(),lds.end(),a[i],greater<int>())-lds.begin();
            if(iti<lis.size()){
                sum-=bit2.qu(lis[iti]-1);
                bit1.upd(lis[iti],-1);
            }
            if(itd<lds.size()){
                sum-=bit1.qu(n)-bit1.qu(lds[itd]);
                bit2.upd(lds[itd],-1);
            }
            if(iti<lis.size())lis[iti]=a[i];
            else lis.push_back(a[i]);
            bit1.upd(a[i],1);
            sum+=bit2.qu(a[i]-1);
            if(itd<lds.size())lds[itd]=a[i];
            else lds.push_back(a[i]);
            sum+=bit1.qu(n)-bit1.qu(a[i]);
            bit2.upd(a[i],1);
            cout<<sum<<' ';
        }cout<<'\n';
    }
    return 0;
}