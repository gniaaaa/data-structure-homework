/*
第五题 (1)

推荐权重矩阵的计算本质上是稀疏矩阵乘法 C = A × B：
  A：用户-物品交互矩阵，m 行 × n 列，A[i][k] 为用户 i 对物品 k 的交互分值；
  B：物品相似度矩阵，  n 行 × n 列，B[k][j] 为物品 k 与物品 j 的相似度；
  C：推荐权重矩阵，    m 行 × n 列，C[i][j] = Σ_k A[i][k] * B[k][j]，
     表示「用户 i 通过他交互过的物品 k，把兴趣传播到物品 j」的累计权重。

矩阵仍用三元组顺序表 TSMatrix 表示（与课件第 17 页一致，下标从 1 开始，
data[1..t] 按行序、同行按列序排列），结果 C 只保留权重 != 0 的元素。

算法（按行累加法）：
  依次处理 A 的每一行 i：
    1. 清空长度为 C.n 的累加数组 acc[] 和标记数组 has[]；
    2. 对 A 中所有行号为 i 的非零元 A(i,k,v)，遍历 B 中行号为 k 的所有非零元
       B(k,j,w)，做 acc[j] += v * w，并置 has[j] = true；
    3. 本行处理完后，按列序把 has[j] 为真且 acc[j] != 0 的分量压入 C。
  这样 C 天然按行序、同行按列序排列，不需要再排序，也不需要反复查找插入位置。

复杂度：设 A、B 的非零元个数为 tA、tB，C 的列数为 p，
  时间 O(m*tA + tA*tB + m*p)，空间 O(p + tC)。
  只对非零元做乘法，这正是稀疏矩阵必须用三元组/链表而不能用二维数组的原因：
  99% 为 0 时，稠密乘法要做 m*n*p 次乘加，其中绝大多数是在乘 0。

说明：这里为了对应题目规模使用定长数组；工程上 acc 应按 B.n 动态分配。
*/

#include<iostream>
#include<iomanip>
using namespace std;

#define MAXSIZE 100                 //三元组表容量 u
typedef double elemtype;            //权重是小数，用 double

typedef struct tuple{
    int i,j;
    elemtype v;
} TupleNode;

typedef struct sparmattp{
    int m,n,t;                      //m:行数; n:列数; t:非零元素数目
    TupleNode data[MAXSIZE+1];      //data[1..t]
} TSMatrix;

//建立三元组表：按行序、同行按列序给出 (i,j,v)
TSMatrix CreateTSMatrix(int m,int n,int t,const int rows[],const int cols[],const double vals[]){
    TSMatrix M;
    M.m=m;
    M.n=n;
    M.t=t;
    for(int p=1;p<=t;p++){
        M.data[p].i=rows[p-1];
        M.data[p].j=cols[p-1];
        M.data[p].v=vals[p-1];
    }
    return M;
}

void PrintTSMatrix(const char *name,TSMatrix M){
    cout<<name<<"（"<<M.m<<" 行 × "<<M.n<<" 列，"<<M.t<<" 个非零元）"<<endl;
    if(M.t==0){
        cout<<"  （空矩阵）"<<endl<<endl;
        return;
    }
    cout<<"     i   j        v"<<endl;
    for(int p=1;p<=M.t;p++){
        cout<<"  "<<setw(4)<<M.data[p].i
            <<setw(4)<<M.data[p].j
            <<setw(9)<<fixed<<setprecision(2)<<M.data[p].v<<endl;
    }
    cout<<endl;
}

//稀疏矩阵相乘，返回推荐权重矩阵 C（只保留非零元）
TSMatrix MultiplySparse(TSMatrix A,TSMatrix B){
    TSMatrix C;
    C.t=0;
    if(A.n!=B.m){                   //维度不匹配，返回空矩阵
        C.m=0;
        C.n=0;
        return C;
    }
    C.m=A.m;
    C.n=B.n;
    if(A.t==0||B.t==0){
        return C;
    }

    double acc[MAXSIZE+1];          //acc[j]：本行第 j 列的累加权重
    bool has[MAXSIZE+1];            //has[j]：本行第 j 列是否被累加过

    for(int i=1;i<=A.m;i++){
        for(int j=1;j<=C.n;j++){
            acc[j]=0.0;
            has[j]=false;
        }

        //把 A 第 i 行的每个非零元与 B 的对应行相乘，累加到 acc
        for(int p=1;p<=A.t;p++){
            if(A.data[p].i!=i){
                continue;           //只处理第 i 行的元素
            }
            int k=A.data[p].j;
            elemtype av=A.data[p].v;
            for(int q=1;q<=B.t;q++){
                if(B.data[q].i!=k){
                    continue;       //只处理 B 第 k 行的元素
                }
                int j=B.data[q].j;
                acc[j]+=av*B.data[q].v;
                has[j]=true;
            }
        }

        //把本行非零的权重按列序压入 C
        for(int j=1;j<=C.n;j++){
            if(has[j]&&acc[j]!=0.0){
                C.t++;
                C.data[C.t].i=i;
                C.data[C.t].j=j;
                C.data[C.t].v=acc[j];
            }
        }
    }
    return C;
}

//把三元组表还原成二维数组打印，方便和手算结果对照
void PrintDense(const char *name,TSMatrix M){
    cout<<name<<"（按二维矩阵形式）"<<endl;
    double a[20][20];
    for(int i=1;i<=M.m;i++){
        for(int j=1;j<=M.n;j++){
            a[i][j]=0.0;
        }
    }
    for(int p=1;p<=M.t;p++){
        a[M.data[p].i][M.data[p].j]=M.data[p].v;
    }
    for(int i=1;i<=M.m;i++){
        cout<<"   ";
        for(int j=1;j<=M.n;j++){
            cout<<setw(7)<<fixed<<setprecision(2)<<a[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}

int main(){
    //---- 用课件第 41 页的例子验证 ----
    //A：3 用户 × 4 物品，5 个非零元
    int ar[]={1,1,2,2,3};
    int ac[]={1,3,2,4,1};
    double av[]={1.0,0.8,0.5,0.7,0.9};
    //B：4 物品 × 4 物品，7 个非零元
    //注：课件第 41 页的 B 表只列了 6 个元素（漏了 B[4][4] = 1.0），
    //但课件自己给出的 C(2,4) = 0.7 × 1.0 = 0.7 恰恰需要 B[4][4] = 1.0；
    //而相似度矩阵的对角元都应为 1.0，故这里按 7 个非零元补齐。
    int br[]={1,1,2,3,3,4,4};
    int bc[]={1,3,2,1,3,2,4};
    double bv[]={1.0,0.6,1.0,0.6,1.0,0.8,1.0};

    TSMatrix A=CreateTSMatrix(3,4,5,ar,ac,av);
    TSMatrix B=CreateTSMatrix(4,4,7,br,bc,bv);

    PrintTSMatrix("A 用户-物品交互矩阵",A);
    PrintTSMatrix("B 物品相似度矩阵",B);

    TSMatrix C=MultiplySparse(A,B);
    PrintTSMatrix("C 推荐权重矩阵",C);
    PrintDense("C",C);

    cout<<"与课件第 41 页对照："<<endl;
    cout<<"  C(1,1)=1.0*1.0+0.8*0.6=1.48   C(1,3)=1.0*0.6+0.8*1.0=1.40"<<endl;
    cout<<"  C(2,2)=0.5*1.0+0.7*0.8=1.06   C(2,4)=0.7*1.0=0.70"<<endl;
    cout<<"  C(3,1)=0.9*1.0=0.90           C(3,3)=0.9*0.6=0.54"<<endl;
    cout<<"其余元素为 0，未存入三元组表，与程序输出一致。"<<endl<<endl;

    //---- 再做一个可手算的小例子，检查一般性 ----
    //A2：2×3，B2：3×2  ->  C2：2×2
    int ar2[]={1,1,2};
    int ac2[]={1,3,2};
    double av2[]={1.0,2.0,3.0};
    int br2[]={1,2,3};
    int bc2[]={1,2,1};
    double bv2[]={4.0,5.0,6.0};

    TSMatrix A2=CreateTSMatrix(2,3,3,ar2,ac2,av2);
    TSMatrix B2=CreateTSMatrix(3,2,3,br2,bc2,bv2);
    TSMatrix C2=MultiplySparse(A2,B2);

    PrintTSMatrix("A2（2×3）",A2);
    PrintTSMatrix("B2（3×2）",B2);
    PrintTSMatrix("C2 = A2 × B2",C2);
    PrintDense("C2",C2);
    cout<<"手算：C2(1,1)=1*4+2*6=16，C2(2,2)=3*5=15，其余为 0，程序输出一致。"<<endl;

    return 0;
}
