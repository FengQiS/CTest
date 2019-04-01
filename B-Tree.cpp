#include <iostream>
#include <vector>
using namespace std;

const int m = 3;
const int max = 2 * m - 1;
const int min = m - 1;

struct BTreeNode {
     int num;
     bool isLeaf;
     int key[max];
     BTreeNode* parent;
     BTreeNode* child[2*m];
     ListNode() : {num = 0; isleaf = TRUE; for (int i = 0; i++; i < 2*m) c[i] = null;}
};

BTreeNode SearchBTree(BTreeNode root, int key)
{
     BTreeNode p = root;
     while (TRUE)
     {
          int i = 0;
          while (i < p->num && k < p[i])
               i++;
          if (i < p->num && k == p[i])
               return p;
          else if (p->isLeaf == TRUE)
               return null;
          else
               p = p->child[i];
     }
}

void InsertBTree(BTreeNode root, int key)
{
     BTreeNode x = SearchBTree(root, key);
}

void DeleteBTree(int key)
{
     BTreeNode x = SearchBTree(root, key);
}

int main()
{
     BTreeNode root;
     return 0;
}
