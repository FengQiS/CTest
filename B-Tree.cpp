#include "pch.h"
#include <iostream>
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
	BTreeNode() 
	{ 
		num = 0; 
		isLeaf = true;
		parent = NULL;
		for (int i=0; i < 2*m; i++)
			child[i] = NULL; 
		for (int x = 0; x < max; x++)
			key[x] = 0;
	}
};

BTreeNode* SearchBTree(BTreeNode* root, int k)
{
	BTreeNode* p = root;
	while (true)
	{
		int i = 0;
		while (i < p->num && p->key[i] < k)
			i++;
		if (i < p->num && k == p->key[i])
			return p;
		else if (p->isLeaf == true)
			return NULL;
		else
			p = p->child[i];
	}
}

void InsertBTree(BTreeNode* root, int k)//判断是不是叶子？是否已满？是不是根节点？
{
	if (root == NULL)
	{
		root = new BTreeNode();
		root->key[0] = k;
		root->num++;
		return;
	}
	BTreeNode* p = root;
	while (true)
	{
		int i = 0;
		while (i < p->num && p->key[i] < k) i++;
		if (p->isLeaf)
		{
			if (p->num < max)
			{
				if (i == p->num)
				{
					p->key[i] = k;
					p->num++;
					break;
				}
				else
				{
					for (int j = p->num; j > i; j--) p->key[j] = p->key[j - 1];
					p->key[i] = k;
					p->num++;
					break;
				}
			}
			else
			{
				//分裂结点
				int o = p->key[m - 1];
				//当前结点为根节点
				if (p->parent == NULL)
				{
					BTreeNode* l = new BTreeNode();
					BTreeNode* r = new BTreeNode();
					l->key[0] = p->key[0];
					l->num++;
					l->key[1] = p->key[1];
					l->num++;
					r->key[0] = p->key[3]; 
					r->num++;
					r->key[1] = p->key[4];
					r->num++;

					p->isLeaf = false;
					for (int x = 0; x < p->num; x++) p->key[x] = 0;
					p->num = 0;
					p->key[0] = o;
					p->num++;
					p->child[0] = l;
					p->child[1] = r;
					l->parent = p;
					r->parent = p;

					if (k < o)
					{
						for (int j = l->num; j > i; j--) l->key[j] = l->key[j - 1];
						l->key[i] = k;
						l->num++;
					}
					else
					{
						i = i - m;
						for (int j = r->num; j > i; j--) r->key[j] = r->key[j - 1];
						r->key[i] = k;
						r->num++;
					}
					break;
				}
				else//当前结点不是根节点
				{
					BTreeNode* f = p->parent;
					int t = 0;
					while (t < f->num && f->key[t] < o) t++;
					for (int x = f->num; x > t; x--)
					{
						f->key[x] = f->key[x - 1];
						if (x == f->num) f->child[x+1] = f->child[x];
						f->child[x] = f->child[x-1];
					}
					f->key[t] = o;
					f->num++;
					BTreeNode* l = new BTreeNode();
					BTreeNode* r = new BTreeNode();
					l->key[0] = p->key[0];
					l->num++;
					l->key[1] = p->key[1];
					l->num++;
					r->key[0] = p->key[3];
					r->num++;
					r->key[1] = p->key[4];
					r->num++;
					f->child[t] = l;
					f->child[t + 1] = r;
					l->parent = f;
					r->parent = f;
					if (k < o)
					{
						for (int j = l->num; j > i; j--) l->key[j] = l->key[j - 1];
						l->key[i] = k;
						l->num++;
					}
					else
					{
						i = i - m;
						for (int j = r->num; j > i; j--) r->key[j] = r->key[j - 1];
						r->key[i] = k;
						r->num++;
					}
					delete p;
					break;
				}
			}
		}
		else if (p->num < max)//内部结点没满，继续往下遍历
		{
			p = p->child[i];
		}
		else //内部节点满了，先拆分再往下遍历
		{
			int o = p->key[m - 1];
			if (p->parent == NULL)//内部节点为根节点
			{
				BTreeNode* l = new BTreeNode();
				BTreeNode* r = new BTreeNode();
				l->key[0] = p->key[0]; 
				l->num++;
				l->key[1] = p->key[1];
				l->num++;
				l->child[0] = p->child[0];
				p->child[0]->parent = l;
				l->child[1] = p->child[1];
				p->child[1]->parent = l;
				l->child[2] = p->child[2];
				p->child[2]->parent = l;
				l->isLeaf = false;

				r->key[0] = p->key[3];
				r->num++;
				r->key[1] = p->key[4];
				r->num++;
				r->child[0] = p->child[3];
				p->child[3]->parent = r;
				r->child[1] = p->child[4]; 
				p->child[4]->parent = r;
				r->child[2] = p->child[5];
				p->child[5]->parent = r;
				r->isLeaf = false;

				for (int x = 0; x < p->num; x++)
				{
					p->key[x] = 0;
					p->child[x] = NULL;
				}
				p->child[p->num] = NULL;
				p->num = 0;
				p->key[0] = o;
				p->num++;
				p->child[0] = l;
				p->child[1] = r;
				l->parent = p;
				r->parent = p;

				if (i < m)
					p = l->child[i];
				else
					p = r->child[i-m];
			}
	        else
	        {
		        BTreeNode* f = p->parent;
		        int t = 0;
		        while (t < f->num && f->key[t] < o) t++;
		        for (int x = f->num; x > t;  x--)
		        {
			        f->key[x] = f->key[x - 1];
					if (x == f->num) f->child[x + 1] = f->child[x];
			        f->child[x] = f->child[x - 1];
		        }
		        f->key[t] = o;
		        f->num++;
		        BTreeNode* l = new BTreeNode();
		        BTreeNode* r = new BTreeNode();

		        l->key[0] = p->key[0]; 
			   l->num++;
			   l->key[1] = p->key[1];
			   l->num++;
			   l->child[0] = p->child[0];
			   p->child[0]->parent = l;
			   l->child[1] = p->child[1];
			   p->child[1]->parent = l;
			   l->child[2] = p->child[2];
			   p->child[2]->parent = l;
			   l->isLeaf = false;

		        r->key[0] = p->key[3];
			   r->num++;
			   r->key[1] = p->key[4];
			   r->num++;
			   r->child[0] = p->child[3];
			   p->child[3]->parent = r;
			   r->child[1] = p->child[4];
			   p->child[4]->parent = r;
			   r->child[2] = p->child[5];
			   p->child[5]->parent = r;
			   r->isLeaf = false;

		        f->child[t] = l;
		        f->child[t + 1] = r;
		        l->parent = f;
		        r->parent = f;

		        delete p;
		        if (i < m)
			        p = l->child[i];
		        else
			        p = r->child[i - m];
	        }
		}
	}
}

void DeleteBTree(BTreeNode* root, int key)
{
	BTreeNode* x = SearchBTree(root, key);
}

void PrintBTree(BTreeNode* root)
{
	if (root == NULL)
	{
		return;
	}
	BTreeNode* p = root;
	for (int i = 0; i < p->num; i++)
	{
		PrintBTree(p->child[i]);
		cout << p->key[i] << " ";
		if(i == p->num-1) PrintBTree(p->child[p->num]);
	}
	//cout << endl;
}

int main()
{
	//the test data: 10 9 8 11 13 6 7 4 3 18 20 1 5 19 25 22 23 24 2 12 14 15 26 27 16 28 19 30 31 32
	BTreeNode* root = NULL;
	PrintBTree(root);
	root = new BTreeNode();
	root->key[0] = 10;
	root->num++;
	PrintBTree(root);
	cout << endl;

	InsertBTree(root,9);
	InsertBTree(root, 8);
	InsertBTree(root, 11);
	InsertBTree(root, 13);
	PrintBTree(root);
	cout << endl;

	cout << "insert 6 7 4:" << endl;
	InsertBTree(root, 6);
	InsertBTree(root, 7);
	InsertBTree(root, 4);
	PrintBTree(root);
	cout << endl;

	cout << "insert 3:" << endl;
	InsertBTree(root, 3);
	PrintBTree(root);
	cout << endl;

	cout << "insert 18 20:" << endl;
	InsertBTree(root, 18);
	InsertBTree(root, 20);
	PrintBTree(root);
	cout << endl;

	cout << "insert 1 5 19:" << endl;
	InsertBTree(root, 1);
	InsertBTree(root, 5);
	InsertBTree(root, 19);
	PrintBTree(root);
	cout << endl;

	cout << "insert 25:" << endl;
	InsertBTree(root, 25);
	PrintBTree(root);
	cout << endl;

	cout << "insert 22 23 24:" << endl;
	InsertBTree(root, 22);
	InsertBTree(root, 23);
	InsertBTree(root, 24);
	PrintBTree(root);
	cout << endl;

	cout << "insert 2:" << endl;
	InsertBTree(root, 2);
	PrintBTree(root);
	cout << endl;

	cout << "insert 12:" << endl;
	InsertBTree(root, 12);
	PrintBTree(root);
	cout << endl;

	cout << "insert 14 15 26 27:" << endl;
	InsertBTree(root, 14);
	InsertBTree(root, 15);
	InsertBTree(root, 26);
	InsertBTree(root, 27);
	PrintBTree(root);
	cout << endl;

	cout << "insert 16 28:" << endl;
	InsertBTree(root, 16);
	InsertBTree(root, 28);
	PrintBTree(root);
	cout << endl;

	cout << "insert 29 30:" << endl;
	InsertBTree(root, 29);
	InsertBTree(root, 30);
	PrintBTree(root);
	cout << endl;

	cout << "insert 31:" << endl;
	InsertBTree(root, 31);
	PrintBTree(root);
	cout << endl;

	cout << "insert 32 21:" << endl;
	InsertBTree(root, 32);
	InsertBTree(root, 21);
	PrintBTree(root);
	cout << endl;

	return 0;
}
