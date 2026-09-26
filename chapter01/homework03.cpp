#include<iostream>
using namespace std;

int f(int n){
    int i, j, k, sum= 0;
        for(i=1; i<n+1;i++){
            for(j=n; j>i-1; j--){
                for(k=1; k<j+1; k++) 
                    sum++;
                printf("sum=%d\n",sum);
            }
        }
    return (sum);
}
// 时间复杂度为 o(n*n*n)
// i    1        2     ...     n
// j    n       n-1    ...     1
// k==j n       n-1    ...     1
//sum==n*n + (n-1)*(n-1) + ... + 1*15
// sum即循环次数 1 + 2*2 + ... + n*n

int main(){
    int n=5;
    cout << f(n) << endl;//结果应是1到5的平方和，即1+4+9+16+25=55，不过要分别打印出每次循环的sum值

    return 0;
}