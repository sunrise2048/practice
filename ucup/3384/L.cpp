#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e5+5;
int n;
struct node{
    int x,y;
    int id;
    bool mix,max,miy,may;
}a[N];
vector<int> usls;
vector<int> dx[2],dy[2];
vector<int> bj[2][2];
ll sum;
vector<vector<int>> ve;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i].x>>a[i].y;
        a[i].id=i;
    }
    sort(a+1,a+n+1,[](const node& x,const node& y){
        return x.x<y.x;
    });
    int cn=n/3;
    for(int i=1;i<=cn;++i){
        a[i].mix=1;
        a[n-i+1].max=1;
        sum+=a[n-i+1].x-a[i].x;
    }
    sort(a+1,a+n+1,[](const node& x,const node& y){
        return x.y<y.y;
    });
    for(int i=1;i<=cn;++i){
        a[i].miy=1;
        a[n-i+1].may=1;
        sum+=a[n-i+1].y-a[i].y;
    }
    for(int i=1;i<=n;++i){
        if((a[i].mix||a[i].max)&&(a[i].miy||a[i].may)){
            bj[a[i].max][a[i].may].push_back(a[i].id);
        }
        else if(a[i].mix){
            dx[0].push_back(a[i].id);
        }
        else if(a[i].max){
            dx[1].push_back(a[i].id);
        }
        else if(a[i].miy){
            dy[0].push_back(a[i].id);
        }
        else if(a[i].may){
            dy[1].push_back(a[i].id);
        }
        else usls.push_back(a[i].id);
    }
    for(int tc0=0;tc0<=bj[0][0].size();++tc0){
        if(tc0>max(dx[1].size(),dy[1].size()))continue;
        int tc1=dx[1].size()-tc0;
        if(tc1>max(bj[0][1].size(),dy[0].size()))continue;
        int tc2=dy[0].size()-tc1;
        if(tc2>max(bj[1][1].size(),dx[0].size()))continue;
        int tc3=dx[0].size()-tc2;
        if(tc3>bj[1][0].size())continue;
        if(tc0+tc3!=dy[1].size())continue;
        if(bj[0][0].size()-tc0!=bj[1][1].size()-tc2)continue;
        if(bj[0][1].size()-tc1!=bj[1][0].size()-tc3)continue;
        while(tc0--){
            ve.push_back({bj[0][0].back(),dx[1].back(),dy[1].back()});
            bj[0][0].pop_back();dx[1].pop_back();dy[1].pop_back();
        }
        while(tc1--){
            ve.push_back({bj[0][1].back(),dx[1].back(),dy[0].back()});
            bj[0][1].pop_back(),dx[1].pop_back();dy[0].pop_back();
        }
        while(tc2--){
            ve.push_back({bj[1][1].back(),dx[0].back(),dy[0].back()});
            bj[1][1].pop_back();dx[0].pop_back();dy[0].pop_back();
        }
        while(tc3--){
            ve.push_back({bj[1][0].back(),dx[0].back(),dy[1].back()});
            bj[1][0].pop_back();dx[0].pop_back();dy[1].pop_back();
        }
        while(bj[0][0].size()){
            ve.push_back({bj[0][0].back(),bj[1][1].back(),usls.back()});
            bj[0][0].pop_back();bj[1][1].pop_back();usls.pop_back();
        }
        while(bj[1][0].size()){
            ve.push_back({bj[1][0].back(),bj[0][1].back(),usls.back()});
            bj[1][0].pop_back();bj[0][1].pop_back();usls.pop_back();
        }
        break;
    }
    cout<<sum*2<<'\n';
    for(auto nv:ve){
        cout<<nv[0]<<' '<<nv[1]<<' '<<nv[2]<<'\n';
    }
    return 0;
}