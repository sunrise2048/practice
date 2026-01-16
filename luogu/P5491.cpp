#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int T;
ll n,p;
ll a;
mt19937 mt(time(0));
ll ksm(ll x,int y){
    ll an=1;
    while(y){
        if(y&1)an=an*x%p;
        x=x*x%p;
        y>>=1;
    }
    return an;
}
bool ch(int x){
    return ksm(x,(p-1)/2)==1;
}
ll bs;
struct exCom{
    ll x,y;
    exCom()=default;
    exCom(ll x,ll y):x(x),y(y){}
    exCom operator*(const exCom& ls)const{
        return exCom((x*ls.x+y*ls.y%p*bs)%p,(x*ls.y+y*ls.x)%p);
    }
};
exCom ksm(exCom x,int y){
    exCom an(1,0);
    while(y){
        if(y&1)an=an*x;
        x=x*x;
        y>>=1;
    }
    return an;
}
int main(){
    cin>>T;
    while(T--){
        cin>>n>>p;
        n%=p;
        if(n==0){
            cout<<"0\n";
            continue;
        }
        if(!ch(n)){
            cout<<"Hola!\n";
            continue;
        }
        a=0;
        while(!a||ch((a*a+p-n)%p))a=mt()%p;
        bs=(a*a+p-n)%p;
        ll an1=ksm(exCom(a,1),(p+1)/2).x;
        ll an2=p-an1;
        if(an1>an2)swap(an1,an2);
        cout<<an1<<' '<<an2<<'\n'; 
    }
    return 0;
}