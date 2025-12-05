#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e4+5;
const ll lim=1e16;
int n,m,q;
char a[N],b[N];
ll len[N];
char get_A(int k,ll id);
char get_B(int k,ll id);
char get_A(int k,ll id){
    if(k==0)return a[id];
    if(k==1){
        if(id<=n)return get_A(k-1,id);
        return get_B(k-1,id-n);
    }
    if(id<=len[k-1])return get_A(k-1,id);
    return get_B(k-1,id-len[k-1]);
}
char get_B(int k,ll id){
    if(k==0)return b[id];
    if(k==1){
        if(id<=m)return get_B(k-1,id);
        return get_A(k-1,id-m);
    }
    if(id<=len[k-1])return get_B(k-1,id);
    return get_A(k-1,id-len[k-1]);
}
int main(){
    freopen("origami.in","r",stdin);
    freopen("origami.out","w",stdout);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;++i){
        char c=getchar();
        while((c<'a'||'z'<c)&&(c<'A'||'Z'<c))c=getchar();
        a[i]=c;
    }
    for(int i=1;i<=m;++i){
        char c=getchar();
        while((c<'a'||'z'<c)&&(c<'A'||'Z'<c))c=getchar();
        b[i]=c;
    }
    len[1]=n+m;
    for(int i=2;i<=10000;++i){
        len[i]=len[i-1]*2;
        if(len[i]>=lim){
            break;
        }
    }
    while(q--){
        ll id;
        scanf("%lld",&id);
        int k=0;
        for(int i=1;i<=1000;++i){
            if(len[i]>=id){
                k=i;
                break;
            }
        }
        printf("%c\n",get_A(k,id));
    }
    return 0;
}