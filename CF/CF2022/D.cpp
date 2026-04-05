#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int T;
int n;
int get_op(int x,int y){
    cout<<"? "<<x<<' '<<y<<endl;
    int o;
    cin>>o;o^=1;
    return o;
}
bool ch_h(vector<int> id){
    int op=0;
    for(int i=0;i<id.size();++i){
        op^=get_op(id[i],id[(i+1)%id.size()]);
    }
    return op;
}
int get_i(int x,int y,int z){
    int op=get_op(x,z)^get_op(z,x);
    if(op)return x;
    return y;
}
int solve(int n){
    if(n==5){
        int opx=get_op(3,4),opy=get_op(4,5),opz=get_op(5,3);
        if(opx^opy^opz){
            int fx=get_op(4,3),fy=get_op(5,4);
            if(opx!=fx&&opy!=fy)return 4;
            if(opx!=fx)return 3;
            return 5;
        }
        if(get_op(1,3)^get_op(3,1))return 1;
        return 2;
    }
    if(n==4){
        if(get_op(3,4)^get_op(4,3)){
            return get_i(3,4,1);
        }
        return get_i(1,2,3);
    }
    if(get_op(n-1,n)^get_op(n,n-1)){
        return get_i(n-1,n,1);
    }
    return solve(n-2);
}
int main(){
    cin>>T;
    while(T--){
        cin>>n;
        int ans;
        if(n==3){
            if(ch_h({1,2})){
                ans=get_i(1,2,3);
                cout<<"! "<<ans<<endl;
            }
            else{
                cout<<"! 3"<<endl;
            }
            continue;
        }
        ans=solve(n);
        cout<<"! "<<ans<<endl;
    }
    return 0;
}