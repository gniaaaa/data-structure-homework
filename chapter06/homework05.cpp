/*
第五题

对一棵以孩子-兄弟链表表示的树统计叶子结点的个数。
    int Count(CSTree root);      // root 为根

在孩子-兄弟链表中，"叶子"就是没有孩子的结点，即 firstchild == NULL。
注意不能把 nextsibling == NULL 当作叶子条件——nextsibling 描述的是兄弟关系，
与是否为叶子无关（尾兄弟完全可能还有孩子）。

递归式：

    Count(NULL) = 0
    Count(T)    = 1                        若 T->firstchild == NULL
                + Σ Count(c)               c 遍历 T 的每个孩子

遍历所有孩子时沿 c = c->nextsibling 前进；对每个孩子递归统计它的子树。

复杂度：
    时间 O(n)，每个结点恰好访问一次；
    空间 O(h)，h 为树的高度（递归栈）。

若传入森林的根，本函数只统计以 root 为根的这一棵树；
要统计整片森林，可对根链上的每棵树分别调用后求和。
*/

#include <iostream>
using namespace std;

typedef char elemtype;

struct TreeNode {
    elemtype data;
    struct TreeNode *firstchild;
    struct TreeNode *nextsibling;
};
typedef struct TreeNode * CSTree;

int Count(CSTree root)
{
    if (root == NULL) {
        return 0;
    }

    int cnt = (root->firstchild == NULL) ? 1 : 0;   // root 自己是叶子？
    for (CSTree c = root->firstchild; c != NULL; c = c->nextsibling) {
        cnt += Count(c);                            // 统计每棵子树
    }
    return cnt;
}

/* ---------- 以下为测试辅助，不属于答案主体 ---------- */

static CSTree NewNode(elemtype d)
{
    CSTree t = new TreeNode;
    t->data = d;
    t->firstchild = t->nextsibling = NULL;
    return t;
}

static void AddLastChild(CSTree parent, CSTree child)
{
    if (parent->firstchild == NULL) {
        parent->firstchild = child;
    } else {
        CSTree p = parent->firstchild;
        while (p->nextsibling != NULL) p = p->nextsibling;
        p->nextsibling = child;
    }
}

static void Release(CSTree t)
{
    if (t == NULL) return;
    Release(t->firstchild);
    Release(t->nextsibling);
    delete t;
}

static void Test(const char *name, CSTree root, int expect)
{
    int got = Count(root);
    cout << name << " -> 叶子数 = " << got
         << (got == expect ? "   [OK]" : "   [FAIL]") << endl;
    Release(root);
}

int main()
{
    Test("空树", NULL, 0);
    Test("单结点", NewNode('A'), 1);

    // A(B(D,E,F), C(G))  -> 叶子 D,E,F,G 共 4 个
    CSTree a = NewNode('A'), b = NewNode('B'), c = NewNode('C');
    CSTree d = NewNode('D'), e = NewNode('E'), f = NewNode('F'), g = NewNode('G');
    AddLastChild(a, b);
    AddLastChild(a, c);
    AddLastChild(b, d);
    AddLastChild(b, e);
    AddLastChild(b, f);
    AddLastChild(c, g);
    Test("A(B(D,E,F),C(G))", a, 4);

    // 关键反例：尾兄弟 P 没有 nextsibling，但有一个孩子 Q
    // A(B, P(Q)) -> 叶子为 B、Q，共 2 个
    CSTree a2 = NewNode('A'), b2 = NewNode('B'), p2 = NewNode('P'), q2 = NewNode('Q');
    AddLastChild(a2, b2);
    AddLastChild(a2, p2);
    AddLastChild(p2, q2);
    Test("A(B,P(Q))，尾兄弟有孩子", a2, 2);

    // 单链 X(Y(Z)) -> 只有 Z 一个叶子
    CSTree x = NewNode('X'), y = NewNode('Y'), z = NewNode('Z');
    AddLastChild(x, y);
    AddLastChild(y, z);
    Test("单链 X(Y(Z))", x, 1);

    return 0;
}
