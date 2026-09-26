#include<iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int m = 0;
    for(int i=1;i<=n;i++)
    {
        for(int j=2*i;j<=n;j++)
        {
            m++;
        }
    }

    cout<<"m="<<m<<endl;// m==n*n/4;
    return 0;
}

// 时间复杂度为 o(n*n)