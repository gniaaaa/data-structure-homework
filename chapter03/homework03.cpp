/*
第三题

(1) 合法性判断（栈初态、终态均为空）：
    合法的充要条件有两个：
      ① 任意前缀中，入栈次数 I 不少于出栈次数 O（否则出现空栈出栈）；
      ② 整个序列中 I 与 O 的总次数相等（否则终态栈不空）。

    A. IOIIOIOO   I:4 O:4，每个前缀都有 I>=O          -> 合法
    B. IOOIOIIO   I:4 O:4，但前缀 IOO 中 O=2>I=1       -> 非法（空栈出栈）
    C. IIIOIOIO   I:5 O:3，终态栈内还剩 2 个元素       -> 非法（终态非空）
    D. IIIOOIOO   I:4 O:4，每个前缀都有 I>=O          -> 合法

    故合法序列为 A、D。

(2) 判定算法见下面的 Judge 函数，时间复杂度 O(n)，空间复杂度 O(1)。
*/

#include<iostream>
using namespace std;

bool Judge(char A[]){
    int count=0;                        //count 为当前栈内元素个数，代替真实建栈
    for(int i=0;A[i]!='\0';i++){
        if(A[i]=='I'){
            count++;                    //入栈
        }
        else if(A[i]=='O'){
            count--;                    //出栈
            if(count<0){                //空栈还要出栈，提前判定为非法
                return false;
            }
        }
        else{
            return false;               //出现 I、O 以外的非法字符
        }
    }
    return count==0;                    //终态栈必须为空
}

int main(){
    char seq[4][9]={"IOIIOIOO","IOOIOIIO","IIIOIOIO","IIIOOIOO"};
    char name[4]={'A','B','C','D'};
    for(int i=0;i<4;i++){
        cout<<name[i]<<" "<<seq[i]<<" -> "
            <<(Judge(seq[i])?"合法":"非法")<<endl;
    }
    return 0;
}
