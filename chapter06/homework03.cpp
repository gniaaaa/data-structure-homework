/*
第三题

编写算法判断一棵以二叉链表表示的二叉树是否为完全二叉树。
    bool JudgeComplete(BiTree root);

思路：
把二叉树按层序（含空指针）排成一列。完全二叉树的定义等价于：
"按层序编号后，所有非空结点占据编号 1..n，中间不允许出现空洞"。
因此只要用队列做层序遍历，并把空孩子也入队：

    seenNull = false
    while 队列非空:
        取出队首结点 t
        if t == NULL: seenNull = true; continue
        if seenNull: return false        // 空结点之后又出现非空结点，有空洞
        把 t->lc、t->rc 入队（空指针也入队）
    return true

关键点：空指针必须入队，否则无法察觉"左孩子空、右孩子非空"这种空洞；
结点为空时不能访问 t->lc / t->rc。

复杂度：
    时间 O(n)，每个结点(含其空孩子)进队出队各一次；
    空间 O(n)，队中最多存放一层的空/非空指针。
*/

#include <iostream>
#include <queue>
using namespace std;

typedef char elemtype;

struct btnode {
    struct btnode *lc;
    struct btnode *rc;
    elemtype data;
};
typedef struct btnode *PtrToNode;
typedef PtrToNode BiTree;

bool JudgeComplete(BiTree root)
{
    queue<BiTree> Q;
    Q.push(root);
    bool seenNull = false;

    while (!Q.empty()) {
        BiTree t = Q.front();
        Q.pop();

        if (t == NULL) {
            seenNull = true;                 // 遇到第一个"空洞"
            continue;
        }
        if (seenNull) {
            return false;                    // 空洞之后还有非空结点 -> 非完全二叉树
        }

        Q.push(t->lc);                       // 空指针也要入队
        Q.push(t->rc);
    }
    return true;
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

static void Test(const char *name, BiTree root, bool expect)
{
    bool got = JudgeComplete(root);
    cout << name << " -> " << (got ? "完全二叉树" : "不是完全二叉树")
         << (got == expect ? "   [OK]" : "   [FAIL]") << endl;
    Release(root);
}

int main()
{
    Test("空树", NULL, true);
    Test("单结点", NewNode('A'), true);

    //       A
    //      / |
    //     B   C
    //    / |
    //   D   E           -> 完全
    Test("5 结点完全二叉树",
         NewNode('A', NewNode('B', NewNode('D'), NewNode('E')), NewNode('C')), true);

    //       A
    //      / |
    //     B   C
    //      |       B 只有右孩子 -> 有空洞
    Test("B 只有右孩子",
         NewNode('A', NewNode('B', NULL, NewNode('D')), NewNode('C')), false);

    //       A
    //      /
    //     B
    //      |
    //       D            -> 非完全
    Test("左下右空但下层有结点",
         NewNode('A', NewNode('B', NULL, NewNode('D')), NULL), false);

    //       A
    //      / |
    //     B   C
    //      |  |
    //       D   E        -> 非完全（C 的左孩子空、右孩子非空）
    Test("C 只有右孩子",
         NewNode('A', NewNode('B', NULL, NewNode('D')), NewNode('C', NULL, NewNode('E'))), false);

    //       A
    //      / |
    //     B   C           -> 满二叉树，也是完全二叉树
    Test("满二叉树", NewNode('A', NewNode('B'), NewNode('C')), true);

    return 0;
}
