/*
第二题

试编写算法，判断两棵以二叉链表表示的二叉树 p 和 q 是否相似。
    bool Similar(BiTree p, BiTree q);   // 相似返回 true，否则返回 false

思路：
"相似"只比较形状，不比较结点中的数据。两种情形必须同时满足：

    (1) p 与 q 同为空树  -> 相似；
    (2) p 与 q 均非空，且 p->lc 与 q->lc 相似、p->rc 与 q->rc 相似。

只要出现"一边空、一边非空"，立即返回 false。
递归终止于空树；很小，用一层递归即可处理。

复杂度：
    时间 O(min(n, m))，n、m 为两棵树的结点数（一旦形状不同就提前返回）；
    空间 O(h1 + h2)，为递归栈深度，最坏 O(n + m)。
*/

#include <iostream>
using namespace std;

typedef char elemtype;                       // 课件中的 elemtype，此处取 char

struct btnode {
    struct btnode *lc;
    struct btnode *rc;
    elemtype data;
};
typedef struct btnode *PtrToNode;
typedef PtrToNode BiTree;

bool Similar(BiTree p, BiTree q)
{
    if (p == NULL && q == NULL) {
        return true;                         // 两棵空树相似
    }
    if (p == NULL || q == NULL) {
        return false;                        // 只有一边为空，形状不同
    }
    return Similar(p->lc, q->lc) && Similar(p->rc, q->rc);
}

/* ---------- 以下为测试辅助，不属于答案主体 ---------- */

static BiTree NewNode(elemtype d, BiTree lc = NULL, BiTree rc = NULL)
{
    BiTree t = new btnode;
    t->data = d;
    t->lc = lc;
    t->rc = rc;
    return t;
}

static void Release(BiTree t)
{
    if (t == NULL) return;
    Release(t->lc);
    Release(t->rc);
    delete t;
}

static void Test(const char *name, BiTree p, BiTree q, bool expect)
{
    bool got = Similar(p, q);
    cout << name << " -> " << (got ? "相似" : "不相似")
         << (got == expect ? "   [OK]" : "   [FAIL]") << endl;
    Release(p);
    Release(q);
}

int main()
{
    // 1) 两棵空树
    Test("空树 vs 空树", NULL, NULL, true);

    // 2) 形状相同，数据不同：仍应相似
    BiTree p1 = NewNode('A', NewNode('B'), NewNode('C', NewNode('D'), NULL));
    BiTree q1 = NewNode('X', NewNode('Y'), NewNode('Z', NewNode('W'), NULL));
    Test("同形异值（A(B,C(D))）", p1, q1, true);

    // 3) 左右孩子位置不同
    BiTree p2 = NewNode('A', NewNode('B'), NULL);
    BiTree q2 = NewNode('A', NULL, NewNode('B'));
    Test("左单枝 vs 右单枝", p2, q2, false);

    // 4) 一边多一个结点
    BiTree p3 = NewNode('A', NewNode('B'), NewNode('C'));
    BiTree q3 = NewNode('A', NewNode('B'), NULL);
    Test("满二层 vs 只有左孩子", p3, q3, false);

    // 5) 完全相同的两个非空树
    BiTree p4 = NewNode('A', NewNode('B'), NewNode('C'));
    BiTree q4 = NewNode('1', NewNode('2'), NewNode('3'));
    Test("同形同构", p4, q4, true);

    return 0;
}
