#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int T;
int n;
mt19937 mt(time(0));
int qu(int x,int y,int z){
    cout<<"? "<<x<<' '<<y<<' '<<z<<endl;
    int s;
    cin>>s;
    return s;
}
int mx[N];
int a[N];
int main(){
    ios::sync_with_stdio(0);
    cin>>T;
    while(T--){
        cin>>n;
        int len=(n-4)/6;
        int px=-1,py=-1;
        while(px==-1){
            int x=mt()%n+1,y=mt()%n+1,z=mt()%n+1;
            while(x==y)y=mt()%n+1;
            while(x==z||y==z)z=mt()%n+1;
            if(qu(x,y,z)<=len){
                px=x,py=y;
                break;
            }
        }
        int p1=0;
        int z1=-1;
        for(int i=1;i<=n;++i){
            if(i==px||i==py)continue;
            mx[i]=qu(px,py,i);
            if(mx[i]>z1){
                z1=mx[i];
                p1=i;
            }
        }
        a[p1]=1;
        int p21=0,p22=0;
        int p2=0;
        for(int i=1;i<=n;++i){
            if(i==px||i==py)continue;
            if(mx[i]==z1-1){
                if(!p21)p21=i;
                else p22=i;
            }
        }
        if(p22){
            int l1=qu(p1,p21,px),l2=qu(p1,p22,px);
            if(l2<l1)p21=p22;
        }
        p2=p21;
        a[p2]=2;
        for(int i=1;i<=n;++i){
            if(i==p1||i==p2)continue;
            a[i]=2+qu(p1,p2,i);
        }
        if(a[1]>a[2]){
            for(int i=1;i<=n;++i)a[i]=n-a[i]+1;
        }
        cout<<"! ";
        for(int i=1;i<=n;++i)cout<<a[i]<<' ';
        cout<<endl;
        cin>>n;
    }
    return 0;
}