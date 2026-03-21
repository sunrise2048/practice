#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const string st[3]={"green","red","blue"};
int T,tp;
int gid(string s){
    for(int i=0;i<3;++i){
        if(st[i]==s)return i;
    }
    return 0;
}
string ch1(int x,int y){
    return st[(6-x-y)%3];
}
string ch2(int x,int y){
    return st[(x+y)%3];
}
string ch3(int x,int y){
    return st[(y-x+3)%3];
}
string ch4(int x,int y){
    return st[(y-x+3)%3];
}
int main(){
    cin>>T>>tp;
    while(T--){
        if(tp==1){
            string a[4];
            for(int i=0;i<4;++i)cin>>a[i];
            if(ch1(gid(a[3]),gid(a[1]))==a[0]){
                cout<<1<<endl;
            }
            else if(ch2(gid(a[0]),gid(a[2]))==a[1]){
                cout<<2<<endl;
            }
            else if(ch3(gid(a[1]),gid(a[3]))==a[2]){
                cout<<3<<endl;
            }
            else cout<<4<<endl;
        }
        else{
            int id;
            string l,r;
            cin>>id>>l>>r;
            if(id==1)cout<<ch1(gid(l),gid(r))<<endl;
            else if(id==2)cout<<ch2(gid(l),gid(r))<<endl;
            else if(id==3)cout<<ch3(gid(l),gid(r))<<endl;
            else cout<<ch4(gid(l),gid(r))<<endl;
        }
    }
    return 0;
}