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
          while (i < p->num && p[i] < k)
               i++;
          if (i < p->num && k == p[i])
               return p;
          else if (p->isLeaf == TRUE)
               return null;
          else
               p = p->child[i];
     }
}

void InsertBTree(BTreeNode root, int k)
{
     //BTreeNode x = SearchBTree(root, key);
     if (root == null)
     {
          root = new BTreeNode();
          root->key[0] = k;
          num++;
          return;
     }
     BTreeNode p = root;
     while (TRUE)
     {
          int i = 0;
          while (i < p->num && p->key[i] < k) i++;
          if (p-> isLeaf)
          {
               if (p->num < 2*m-1)
               {
                    if (i == p->num) 
                    {
                         p->key[i] = k; 
                         p->num++;
                         break;
                    }
                    else
                    {
                         for (int j = p->num; j--; j>i) p->key[j] = p->key[j-1];
                         p->key[i] = k;
                         p->num++;
                         break;
                    }
               }
               else
               {
                    int m = p->key[m-1];
                    BTreeNode f = p->parent;
                    int t = 0;
                    while (t < f->num && f->key[t] < m) t++;
                    for (int x = f->num; x--; x>t) 
                    {
                         f->key[x] = f->key[x-1];
                         f->child[x] = f->child[x-1];
                    }
                    f->key[t] = m;
                    f->num++;
                    BTreeNode l = new BtreeNode();
                    BTreeNode r = new BtreeNode();
                    l->key[0] = p->key[0]; l->key[1] = p->key[1];
                    r->key[0] = p->key[3]; r->key[1] = p->key[4];
                    f->c[t] = l;
                    f->c[t+1] = r;
                    l->parent = f;
                    r->parent = f;
                    if (k < p->key[m-1])
                         l->key[m-1] = k; l->num++;
                    else
                         r->key[m-1] = k; r->num++;
                    delete p;
               }
          }
          else
          {
               p = p->child[i];
          }
     }
}

void DeleteBTree(int key)
{
     BTreeNode x = SearchBTree(root, key);
}

int main()
{
     //the test data: 10 9 8 11 13 6 7 4 3 18 20 1 5 19 25 22 23 24
     BTreeNode root;
     return 0;
}
