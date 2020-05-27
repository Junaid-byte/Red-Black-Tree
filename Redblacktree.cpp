#include<iostream>	
#include<conio.h>
#include<string>

using namespace std;

struct RBT
{
	int info;
	int color;
	RBT *left, *right, *parent;
}; 
typedef RBT *Rbtptr;
class Redblacktree
{
	public:
	Rbtptr root;
	Rbtptr TNULL;
  
	void initializeNullNode(Rbtptr node, Rbtptr parent)
	{
		node->info = 0;
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->color = 0;
	}

	void Preorder(Rbtptr node)
	{
		if (node != TNULL)
		{
			cout << node->info << " ";
			Preorder(node->left);
			Preorder(node->right);
		}
	}

	void Inorder(Rbtptr node)
	{
		if (node != TNULL)
		{
			Inorder(node->left);
			cout << node->info << " ";
			Inorder(node->right);
		}
	}

	void Postorder(Rbtptr node)
	{
		if (node != TNULL)
		{
			Postorder(node->left);
			Postorder(node->right);
			cout << node->info;
		}
	}

	Rbtptr SearchRbtptr(Rbtptr node, int key)
	{
		if (node == TNULL || key == node->info)
		{
			return node;
		}
		if (key < node->info)
		{
			return SearchRbtptr(node->left, key);
		}
		else
		{
			return SearchRbtptr(node->right, key);
		}

	}

	void deletefix(Rbtptr x)
	{
		Rbtptr s;
		while (x != root && x->color == 0)
		{
			if (x == x->parent->left)
			{
				s = x->parent->right;
				if (x->color == 1)
				{
					s->color = 0;
					x->parent->color = 1;
					RotateLeft(x->parent);
					s = x->parent->right;
				}
				if (s->left->color == 0 && s->right->color == 0)
				{
					s->color = 1;
					x = x->parent;
				}
				else 
				{
					if (s->right->color == 0)
					{
						s->left->color = 0;
						s->color = 1;
						RotateLeft(s);
						s = x->parent->right;


						s->color = x->parent->color;
						x->parent->color = 0;
						s->right->color = 0;
						RotateRight(x->parent);
						x = root;
					}
				}
			}
			else 
			{
				s = x->parent->left;
				if (s->color == 1) 
				{
					s->color = 0;
					x->parent->color = 1;
					RotateRight(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == 0 && s->right->color == 0) 
				{
					s->color = 1;
					x = x->parent;
				}
				else
				
					if (s->left->color == 0)
					{
						s->right->color = 0;
						s->color = 1;
						RotateLeft(s);
						s = x->parent->left;

						s->color = x->parent->color;
						x->parent->color = 0;
						s->left->color = 0;
						RotateRight(x->parent);
						x = root;
					}
					else
					{
						return;
					}
				
			}
		}
		x->color = 0;
				
	}
	void rbtransplant(Rbtptr u, Rbtptr v)
	{
		if (u->parent == nullptr)
		{
			root = v;
		}
		else if (u == u->parent->left)
		{
			u->parent->left = v;
		}
		else
		{
			u->parent->right = v;
		}
		v->parent = u->parent;

	}
	void deleteNodeHelper(Rbtptr node, int key) {
		Rbtptr z = TNULL;
		Rbtptr x, y;
		while (node != TNULL) 
		{
			if (node->info == key)
			{
				z = node;
			}

			if (node->info <= key)
			{
				node = node->right;
			}
			else 
			{
				node = node->left;
			}
		}

		if (z == TNULL) 
		{
			cout << "Key not found in the tree" << endl;
			return;
		}

		y = z;
		int y_original_color = y->color;
		if (z->left == TNULL) 
		{
			x = z->right;
			rbtransplant(z, z->right);
		}
		else if (z->right == TNULL) 
		{
			x = z->left;
			rbtransplant(z, z->left);
		}
		else 
		{
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z)
			{
				x->parent = y;
			}
			else 
			{
				rbtransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbtransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0)
		{
			deletefix(x);
		}
	}
	void insertFix(Rbtptr k)
	{
		Rbtptr u;
		while (k->parent->color == 1)
		{
			if (k->parent == k->parent->parent->right) 
			{
				u = k->parent->parent->left;
				if (u->color == 1)
				{
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else 
				{
					if (k == k->parent->left)
					{
						k = k->parent;
						RotateRight(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					RotateLeft(k->parent->parent);
				}
			}
			else 
			{
				u = k->parent->parent->right;

				if (u->color == 1)
				{
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else 
				{
					if (k == k->parent->right) 
					{
						k = k->parent;
						RotateLeft(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					RotateRight(k->parent->parent);
				}
			}
			if (k == root) 
			{
				break;
			}
		}
		root->color = 0;
	}
	void printHelper(Rbtptr root, string indent, bool last) 
	{
		if (root != TNULL) 
		{
			cout << indent;

			if (last) 
			{
				cout << "R----";
				indent += "   ";
			}
			else
			{
				cout << "L----";
				indent += "|  ";
			}

			string sColor = root->color ? "RED" : "BLACK";
			cout << root->info << "(" << sColor << ")" << endl;
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}
	public:
	Redblacktree() 
	{
		TNULL = new RBT;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
	}
	void preorder() 
	{
		Preorder(this->root);
	}

	void inorder()
	{
		Inorder(this->root);
	}

	void postorder()
	{
		Postorder(this->root);
	}

	Rbtptr searchTree(int k) 
	{
		return SearchRbtptr(this->root, k);
	}

	Rbtptr minimum(Rbtptr node)
	{
		while (node->left != TNULL) 
		{
			node = node->left;
		}
		return node;
	}
	Rbtptr maximum(Rbtptr node)
	{
		while (node->right != TNULL)
		{
			node = node->right;
		}
		return node;
	}
	Rbtptr successor(Rbtptr x)
	{
		if (x->right != TNULL)
		{
			return minimum(x->right);
		}
		Rbtptr y = x->parent;
		while (y != TNULL && x == y->right)
		{
			x = y;
			y = y->parent;
		}
		return y;

	}
	Rbtptr predecessor(Rbtptr x)
	{
		if (x->left != TNULL)
		{
			return maximum(x->left);
		}
		Rbtptr y = x->parent;
		while (y != TNULL && x == y->left)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}
	void RotateLeft(Rbtptr x)
	{
		Rbtptr y = x->right;
		x->right = y->left;
		if (y->left != TNULL)
		{
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) 
		{
			this->root = y;
		}
		else if (x == x->parent->left) 
		{
			x->parent->left = y;
		}
		else 
		{
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;


	}
	void RotateRight(Rbtptr x)
	{
		Rbtptr y = x->left;
		x->left = y->right;
		if (y->right != TNULL) 
		{
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) 
		{
			this->root = y;
		}
		else if (x == x->parent->right) 
		{
			x->parent->right = y;
		}
		else 
		{
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;


	}
	void Insert(int key)
	{
		Rbtptr node = new RBT;
		node->parent = nullptr;
		node->info = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1;

		Rbtptr y = nullptr;
		Rbtptr x = this->root;

		while (x != TNULL)
		{
			y = x;
			if (node->info < x->info)
			{
				x = x->left;
			}
			else
			{
				x = x->right;
			}
		}
		node->parent = y;
		if (y == nullptr)
		{
			root = node;
		}
		else if (node->info < y->info)
		{
			y->left = node;
		}
		else
		{
			y->right = node;
		}
		if (node->parent == nullptr)
		{
			node->color = 0;
			return;
		}
		if (node->parent->parent == nullptr)
		{
			return;
		}

		insertFix(node);

	}
	Rbtptr getRoot()
	{
		return this->root;
	}

	void deleteNode(int data)
	{
		deleteNodeHelper(this->root, data);
	}
	void printTree()
	{
		if (root)
		{
			printHelper(this->root, " ", true);
		}
	}
	/*void Update(int old, int New, Rbtptr root)
	{
		int pos = 0;
		Rbtptr *current = new Rbtptr();
		if (root == TNULL)
		{
			cout << "Linked list not Initialized! " << endl;
			return;
		}
		current = root;

		while (current->next != TNULL)
		{
			if (current->data == old)
			{
				current->data = New;
				cout << old << " is found at position " << pos << " replaced with " << New << endl;
			}
			current = current->next;
			pos++;
		}

	}*/

};



int main()
{
	Redblacktree rbt;
	cout << "Insertion of Red Black Tree Values:- " << endl;
	cout << "After Insertion, Red Black Tree Is Created As Follows:- " << endl << endl;
	rbt.Insert(12);
	rbt.Insert(25);
	rbt.Insert(10);
	rbt.Insert(34);
	rbt.Insert(6);
	rbt.Insert(40);

	rbt.printTree();
	cout << endl << "After Deleting Red Black Tree Value:- " << endl<<endl;
	rbt.deleteNode(25);
	rbt.printTree();

	cout << endl << "25 is Deleted From Red Black Tree!" << endl;

	_getch();
	return 0;

}
/*
Follow me on my github ID https://github.com/Junaid-byte
Credits:-Junaid Jawed
*/
