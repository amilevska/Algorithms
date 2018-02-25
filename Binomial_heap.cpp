#include <iostream>
#include <cstdlib>
using namespace std;


struct node
{
	int n;
	node* par;
	node* child;
	node* bro;
	int degree;
};


class BinomialHeap
{
private:
	node *H;
	node *Hr;
	int count;
public:
	node* Initialize();
	node* Create_node(int);
	node* Unite(node*, node*);
	node* Insert(node*, node*);
	node* Merge(node*, node*);
	node* Extract_Min(node*);
	node* Search(node*, int);
	int Link(node*, node*);
	int Revert_list(node*);
	int Display(node*);
	int Decrease_key(node*, int, int);
	int Delete(node*, int);

	BinomialHeap()
	{
		H = Initialize();
		Hr = Initialize();
		int count = 1;
	}
};


node* BinomialHeap::Initialize()
{
	node* np;
	np = NULL;
	return np;
}


// Linking nodes

int BinomialHeap::Link(node* y, node* z)
{
	y->par = z;
	y->bro = z->child;
	z->child = y;
	z->degree = z->degree + 1;
	return 0;
}


node* BinomialHeap::Create_node(int k)
{
	node* p = new node;
	p->n = k;
	return p;
}


node* BinomialHeap::Insert(node* H, node* x)
{
	node* H1 = Initialize();
	x->par = NULL;
	x->child = NULL;
	x->bro = NULL;
	x->degree = 0;
	H1 = x;
	H = Unite(H, H1);
	return H;
}


node* BinomialHeap::Unite(node* H1, node* H2)
{
	node *H = Initialize();
	H = Merge(H1, H2);
	if (H == NULL)
		return H;
	node* prev_x;
	node* next_x;
	node* x;
	prev_x = NULL;
	x = H;
	next_x = x->bro;
	while (next_x != NULL)
	{
		if ((x->degree != next_x->degree) || ((next_x->bro != NULL)
			&& (next_x->bro)->degree == x->degree))
		{
			prev_x = x;
			x = next_x;
		}
		else
		{
			if (x->n <= next_x->n)
			{
				x->bro = next_x->bro;
				Link(next_x, x);
			}
			else
			{
				if (prev_x == NULL)
					H = next_x;
				else
					prev_x->bro = next_x;
				Link(x, next_x);
				x = next_x;
			}
		}
		next_x = x->bro;
	}
	return H;
}


node* BinomialHeap::Merge(node* H1, node* H2)
{
	node* H = Initialize();
	node* y;
	node* z;
	node* a;
	node* b;
	y = H1;
	z = H2;
	if (y != NULL)
	{
		if (z != NULL)
		{
			if (y->degree <= z->degree)
				H = y;
			else if (y->degree > z->degree)
				H = z;
		}
		else
			H = y;
	}
	else
		H = z;
	while (y != NULL && z != NULL)
	{
		if (y->degree < z->degree)
		{
			y = y->bro;
		}
		else if (y->degree == z->degree)
		{
			a = y->bro;
			y->bro = z;
			y = a;
		}
		else
		{
			b = z->bro;
			z->bro = y;
			z = b;
		}
	}
	return H;
}


int BinomialHeap::Display(node* H)
{
	if (H == NULL)
	{
		cout << "The Heap is empty" << endl;
		return 0;
	}
	cout << "The roots are: " << endl;
	node* p;
	p = H;
	while (p != NULL)
	{
		cout << p->n;
		if (p->bro != NULL)
			cout << "-->";
		p = p->bro;
	}
	cout << endl;
}


node* BinomialHeap::Extract_Min(node* H1)
{
	Hr = NULL;
	node* t = NULL;
	node* x = H1;
	if (x == NULL)
	{
		cout << "There is nothing to Extract" << endl;
		return x;
	}
	int min = x->n;
	node* p = x;
	while (p->bro != NULL)
	{
		if ((p->bro)->n < min)
		{
			min = (p->bro)->n;
			t = p;
			x = p->bro;
		}
		p = p->bro;
	}
	if (t == NULL && x->bro == NULL)
		H1 = NULL;
	else if (t == NULL)
		H1 = x->bro;
	else if (t->bro == NULL)
		t = NULL;
	else
		t->bro = x->bro;
	if (x->child != NULL)
	{
		Revert_list(x->child);
		(x->child)->bro = NULL;
	}
	H = Unite(H1, Hr);
	return x;
}


int BinomialHeap::Revert_list(node* y)
{
	if (y->bro != NULL)
	{
		Revert_list(y->bro);
		(y->bro)->bro = y;
	}
	else
	{
		Hr = y;
	}
	return 0;
}


node* BinomialHeap::Search(node* H, int k)
{
	node* x = H;
	node* p = NULL;
	if (x->n == k)
	{
		p = x;
		return p;
	}
	if (x->child != NULL && p == NULL)
		p = Search(x->child, k);
	if (x->bro != NULL && p == NULL)
		p = Search(x->bro, k);
	return p;
}


int BinomialHeap::Decrease_key(node* H, int i, int k)
{
	int temp;
	node* p;
	node* y;
	node* z;
	p = Search(H, i);
	if (p == NULL)
	{
		cout << "Incorect key" << endl;
		return 0;
	}
	if (k > p->n)
	{
		cout << "Error! New key is > than current key" << endl;
		return 0;
	}
	p->n = k;
	y = p;
	z = p->par;
	while (z != NULL && y->n < z->n)
	{
		temp = y->n;
		y->n = z->n;
		z->n = temp;
		y = z;
		z = z->par;
	}
	cout << "Key reduced" << endl;
}


int BinomialHeap::Delete(node* H, int k)
{
	node* np;
	if (H == NULL)
	{
		cout << "\n Empty Heap!";
		return 0;
	}
	Decrease_key(H, k, -1000);
	np = Extract_Min(H);
	if (np != NULL)
		cout << "Node Deleted" << endl;
}

//Menu
int main()
{
	int n, m, l, i;
	BinomialHeap bh;
	node* p;
	node *H;
	H = bh.Initialize();
	char ch;
	while (1)
	{
		cout << "Operations on Binomial heap" << endl;
		cout << "----------------------------" << endl;
		cout << "1)Insert element in the heap" << endl;
		cout << "2)Extract Minimum key node" << endl;
		cout << "3)Decrease key" << endl;
		cout << "4)Display Heap" << endl;
		cout << "5)Delete node" << endl;
		cout << "6)Exit" << endl;
		cout << "Enter Your Choice: ";
		cin >> l;
		switch (l)
		{
		case 1:
			cout << "Enter element to insert: ";
			cin >> m;
			p = bh.Create_node(m);
			H = bh.Insert(H, p);
			break;
		case 2:
			p = bh.Extract_Min(H);
			if (p != NULL)
				cout << "The node with minimum key: " << p->n << endl;
			else
				cout << "Heap is empty" << endl;
			break;
		case 3:
			cout << "Enter key to be decreased: ";
			cin >> m;
			cout << "Enter new key value: ";
			cin >> l;
			bh.Decrease_key(H, m, l);
			break;
		case 4:
			cout << "The Heap is: " << endl;
			bh.Display(H);
			break;
		case 5:
			cout << "Enter key to delete: ";
			cin >> m;
			bh.Delete(H, m);
			break;
		case 6:
			exit(1);
		default:
			cout << "Wrong Choice";
		}
	}
	return 0;
}