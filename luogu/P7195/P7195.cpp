#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
const int inf=2e9;
int n;
pair<int,int> nd[N];
set<pair<int,int>> stx,sty;
set<pair<int,int>> stp[2];
vector<pair<int,int>> st,stn[2];
struct line{
    int xl,xr,yl,yr;
    line()=default;
    line(int xl,int xr,int yl,int yr):xl(xl),xr(xr),yl(yl),yr(yr){}
};
line le[3][2];
pair<int,int> se(int op){
    if(stx.empty())return {inf+1,inf+1};
    if(op==1){
        return *stx.begin();
    }
    if(op==3){
        return *stx.rbegin();
    }
    if(op==0){
        return {sty.begin()->second,sty.begin()->first};
    }
    return {sty.rbegin()->second,sty.rbegin()->first};
}
bool ch(pair<int,int> no,int op){
    if(stx.empty())return 1;
    if(op==0){
        return stx.begin()->first<no.first;
    }
    if(op==1){
        return sty.rbegin()->first>no.second;
    }
    if(op==2){
        return stx.rbegin()->first>no.first;
    }
    return sty.begin()->first<no.second;
}
vector<pair<int,int>> l[3];
void get_le0(int op){
    l[0].clear();
    if(st.empty())return;
    if(op==0){
        le[0][0]=line(st[0].first,inf,st[0].second,st[0].second);
    }
    else if(op==1){
        le[0][0]=line(st[0].first,st[0].first,-inf,st[0].second);
    }
    else if(op==2){
        le[0][0]=line(-inf,st[0].first,st[0].second,st[0].second);
    }
    else{
        le[0][0]=line(st[0].first,st[0].first,st[0].second,inf);
    }
    for(int i=1;i<st.size();++i){
        auto [lx,ly]=st[i-1];
        auto [nx,ny]=st[i];
        if(op%2==0){
            l[0].emplace_back(nx,ly);
        }
        else{
            l[0].emplace_back(lx,ny);
        }
        op=(op+1)%4;
    }
    auto [bx,by]=st.back();
    if(op==0){
        le[0][1]=line(-inf,bx,by,by);
    }
    else if(op==1){
        le[0][1]=line(bx,bx,by,inf);
    }
    else if(op==2){
        le[0][1]=line(bx,inf,by,by);
    }
    else{
        le[0][1]=line(bx,bx,-inf,by);
    }
}
void get_le1(int op){
    if(stn[0].empty())return;
    l[1].clear();
    auto [x0,y0]=stn[0][0];
    if(op==0){
        le[1][0]=line(-inf,x0,y0,y0);
    }
    else{
        le[1][0]=line(x0,x0,-inf,y0);
    }
    for(int i=1;i<stn[0].size();++i){
        auto [lx,ly]=stn[0][i-1];
        auto [nx,ny]=stn[0][i];
        if(op==0)l[1].emplace_back(nx,ly);
        else l[1].emplace_back(lx,ny);
        op=(op+1)%2;
    }
    auto [bx,by]=stn[0].back();
    if(op==0)le[1][1]=line(bx,inf,by,by);
    else le[1][1]=line(bx,bx,by,inf);
}
void get_le2(int op){
    if(stn[1].empty())return;
    l[2].clear();
    auto [x0,y0]=stn[1][0];
    if(op==0){
        le[2][0]=line(-inf,x0,y0,y0);
    }
    else{
        le[2][0]=line(x0,x0,y0,inf);
    }
    for(int i=1;i<stn[1].size();++i){
        auto [lx,ly]=stn[1][i-1];
        auto [nx,ny]=stn[1][i];
        if(op==0)l[2].emplace_back(nx,ly);
        else l[2].emplace_back(lx,ny);
        op=(op+1)%2;
    }
    auto [bx,by]=stn[1].back();
    if(op==0)le[2][1]=line(bx,inf,by,by);
    else le[2][1]=line(bx,bx,-inf,by);
}
bool solve(int lop){
    int op=lop;
    stx.clear();
    sty.clear();
    stp[0].clear();stp[1].clear();
    for(int i=1;i<=n;++i){
        auto [x,y]=nd[i];
        stx.emplace(x,y);
        sty.emplace(y,x);
    }
    st.clear();
    pair<int,int> no=se(op);
    stx.erase(no);
    sty.erase({no.second,no.first});
    while(no.first<=inf){
        if(!ch(no,op)){
            stp[op&1].insert(no);
            if(st.size()){
                op=(op+3)%4;
                no=st.back();
                st.pop_back();
            }
            else{
                no=se(op);
                stx.erase(no);
                sty.erase({no.second,no.first});
            }
        }
        else{
            st.push_back(no);
            op=(op+1)%4;
            no=se(op);
            stx.erase(no);
            sty.erase({no.second,no.first});
        }
    }
    stn[0].clear();stn[1].clear();
    for(auto no:stp[0])stn[0].push_back(no);
    for(auto no:stp[1])stn[1].push_back(no);
    get_le0(lop);
    get_le1(0);
    get_le2(1);
    cout<<n+3<<'\n';
    cout<<"17961 0\n";
    for(int i:{2,0}){
        if(i==1){
            //cout<<"0 254448\n";
        }
        else if(i==2){
            cout<<"17961 999994682\n";
        }
        else{
            cout<<"999995247 -2000000000\n";
        }
        //cout<<le[i][0].xl<<' '<<le[i][0].xr<<' '<<le[i][0].yl<<' '<<le[i][0].yr<<'\n';
        //cout<<le[i][1].xl<<' '<<le[i][1].xr<<' '<<le[i][1].yl<<' '<<le[i][1].yr<<'\n';
        for(auto [x,y]:l[i]){
            cout<<x<<' '<<y<<'\n';
        }
        if(i==1){
            //cout<<"5017676 3809492\n";
        }
        else if(i==2){
            cout<<"999995127 -2000000000\n";
        }
        else{
            cout<<"999995247 1762\n";
        }
    }
    return 1;
}
int main(){
    freopen("07.in","r",stdin);
    freopen("7.ans","w",stdout);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>nd[i].first>>nd[i].second;
    }solve(1);
    return 0;
}