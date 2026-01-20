#include"Catherine.h"
#include<bits/stdc++.h>
using namespace std;
int A;
bool fl_be;
bool fl_idt;
int la_w;
int z;// 01->0 00->1 11->2
int zt;
void Init(int a,int b) {
    ::A=a;
    zt=-1;
}
bool fl_z;
int Move(vector<int> y){
    if(A>2){
        if(y[0]&&y[1])return 0;
        if(y[1]&&y[2])return 1;
        if(y[0]&&y[2])return 2;
        if(y[0])return 0;
        if(y[1])return 1;
        if(y[2])return 2;
        return -1;
    }
    if(!fl_be){
        fl_be=1;
        if(y[0]+y[1]>1){
            if(y[0]+y[1]>2){
                if(y[0]>1){
                    fl_idt=1;
                    return la_w=1;
                }
                fl_idt=1;
                return la_w=0;
            }
            if(y[0]==0){
                z=2;
                return la_w=1;
            }
            if(y[1]==0){
                z=1;
                return la_w=0;
            }
            z=0;
            return la_w=1;
        }
        if(y[0]){
            fl_idt=1;
            return la_w=0;
        }
        fl_idt=1;
        return la_w=1;
    }
    if(fl_idt){
        if(y[0]+y[1]==1){
            return la_w=y[1];
        }
        y[la_w]++;
        if(y[0]==1)return la_w=0;
        return la_w=1;
    }
    if(y[0]+y[1]==0){
        fl_idt=1;
        return -1;
    }
    if(y[0]+y[1]!=1){
        if(y[la_w]==0){
            fl_idt=1;
            return -1;
        }
        fl_idt=1;
        la_w^=1;
        return la_w;
    }
    if(zt==-1){
        zt=y[1];
        if(z==0){
            if(zt){
                fl_z=1;
                return la_w=1;
            }
            return la_w=0;
        }
        else if(z==1){
            return la_w=1;
        }
        return la_w=0;
    }
    if(fl_z){
        fl_z=0;
        return la_w=0;
    }
    if(z==0){
        if(zt==0){
            if(y[0]){
                fl_idt=1;
                return la_w=0;
            }
            fl_idt=1;
            return -1;
        }
        if(y[1]){
            fl_idt=1;
            return la_w=1;
        }
        fl_idt=1;
        return -1;
    }
    if(z==1){
        if(y[0]){
            fl_idt=1;
            return -1;
        }
        fl_idt=1;
        return la_w=1;
    }
    if(y[0]){
        fl_idt=1;
        return -1;
    }
    fl_idt=1;
    return la_w=1;
}
