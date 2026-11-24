/*
第二题

重复子串：由一个或多个连续相等的字符组成的子串（不重叠）。
即求串 s 中「最长连续相同字符段」的长度。

思路：一次线性扫描，cur 记当前这段连续相同字符的长度，
遇到字符变化就用它更新 best 并把 cur 重置为 1；扫描结束后再更新一次
（防止最长的一段正好落在串尾）。

时间复杂度 O(n)，空间复杂度 O(1)。
*/

#include<iostream>
using namespace std;

int LongestString(char s[],int n){
    if(n<=0){
        return 0;                       //空串
    }
    int best=1;
    int cur=1;
    for(int i=1;i<n;i++){
        if(s[i]==s[i-1]){
            cur++;                      //仍是同一段
        }
        else{
            if(cur>best){
                best=cur;               //一段结束，更新最大值
            }
            cur=1;                      //重新开始计数
        }
    }
    if(cur>best){
        best=cur;                       //处理最长段在串尾的情况
    }
    return best;
}

int main(){
    char s1[]="aaabbccccd";
    char s2[]="abcd";
    char s3[]="abbbbb";
    char s4[]="";
    cout<<"aaabbccccd -> "<<LongestString(s1,10)<<endl;
    cout<<"abcd       -> "<<LongestString(s2,4)<<endl;
    cout<<"abbbbb     -> "<<LongestString(s3,6)<<endl;
    cout<<"空串        -> "<<LongestString(s4,0)<<endl;
    return 0;
}
