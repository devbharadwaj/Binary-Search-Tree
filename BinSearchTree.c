#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node* left;
	struct node* right;
};

struct node* newnode(int data)
{
	struct node *neonode = malloc(sizeof(struct node));
	neonode->data = data;
	neonode->left = NULL;
	neonode->right = NULL;

	return neonode;
}


struct node* insert(struct node* node, int data)
{
	if (node == NULL)
	{
		return newnode(data);
	}
	else
	{
		if (data <= node->data) 
			node->left = insert(node->left, data);
		else
			node->right = insert(node->right, data);
		return node;
	}
}

int lookup(struct node* node, int data)
{
	if (node == NULL)
	{
		printf("\nValue: %d Not found\n", data);
		return 0;
	}
	if(data == node->data)
	{
		printf("\nNode with value: %d found.\n", data);
		return 1;
	}
	else
	{
		if (data <= node->data)
		{
			return lookup(node->left,data);
		}
		else
		{
			return lookup(node->right,data);
		}
	}
	
}

int size(struct node* node)
{
	int count = 0;
	if (node == NULL)
		return count;
	if (node != NULL)
		count++;
	if (node->left != NULL)
		count = count + size(node->left);
	if (node->right != NULL)
		count = count + size(node->right);

	return count;
}


int maxDepth(struct node* node)
{
	if (node == NULL)
		return 0;
	else
	{
		int ldepth = maxDepth(node->left);
		int rdepth = maxDepth(node->right);
	
		if (ldepth > rdepth)
			return ldepth+1;
		else
			return rdepth+1;
	}

}

int minValue(struct node* node)
{
	while (node->left != NULL)
		node = node->left;
	return node->data;
}

int maxValue(struct node* node)
{
	while (node->right != NULL)
		node = node->right;
	return node->data;
}

void inorder(struct node* node)
{
	if (node->left != NULL)
		inorder(node->left);
	printf("%d",node->data);
	if (node->right != NULL)
		inorder(node->right);
}

void postorder(struct node* node)
{
	if (node->left != NULL)
		postorder(node->left);
	if (node->right != NULL)
		postorder(node->right);
	printf("%d",node->data);
}

int haspathsum(struct node *node, int sum)
{
	int res = 0;
	sum = sum - node->data;
	if (node->right == NULL && node->left == NULL)
	{	
		if (sum == 0)
			res = 1;
	}
	else
	{	if (node->left != NULL)
			res = haspathsum(node->left,sum);
		if (node->right != NULL && res == 0)
			res = haspathsum(node->right,sum);
	}
	return res;
}
int pathno = 1;

void printp(int nodearray[], int length)
{
	int i = 0;
	printf("Path %d: ", pathno++);
	for (i=0;i<length;i++)
		printf( "%d",nodearray[i]);
	printf("\n");
}
void checkpath(struct node* node, int nodearray[], int length)
{
	if (node == NULL)
		return;
	nodearray[length] = node->data;
	length++;

	if (node->left == NULL && node->right == NULL)
		printp(nodearray,length);
	
	if (node->left != NULL)
		checkpath(node->left, nodearray, length);
	if (node->right != NULL)
		checkpath(node->right, nodearray, length);
}
	

void printpath(struct node* node)
{
	int nodearray[100];
	checkpath(node, nodearray, 0);
}

void mirror(struct node* node)
{
	struct node *temp;
	temp = node->left;
	node->left = node->right;
	node->right = temp;

	if (node->right != NULL)
		mirror(node->right);
	if (node->left != NULL)
		mirror(node->left);
}

void doubletree(struct node *node)
{
	if (node == NULL)
		return;
	struct node *newnode = malloc(sizeof(struct node));
	newnode->data = node->data;
	newnode->left = node->left;
	newnode->right = NULL;
	node->left = newnode;
	doubletree(node->right);
	node = node->left;
	doubletree(node->left);
}

int sametree(struct node *a, struct node *b)
{
	int ret = 0;
	if (a == NULL && b == NULL)
		return 0;
	if (a == NULL || b == NULL)
		return 1;
	if (a->data == b->data)
	{
		ret = sametree(a->left, b->left);
		if (ret == 0)
		ret = sametree(a->right, b->right);
	}
	else return 1;
	return ret;
}

int counttrees(int num)
{
	int sum = 0;
	int i,left, right;

	if (num <= 1)
		return 1;
	else
	{
		for (i = 1; i <= num; i++)
		{
			left = counttrees(i - 1);
			right = counttrees(num - i);
		
			sum += left * right;
		}
	}
	return sum;
}

int leftValue(struct node *node)
{
	struct node *left;
	if (node->left != NULL)
	{
		left = node->left;
		return left->data;
	}
	else 
		return node->data - 1;
}

int rightValue(struct node *node)
{
	struct node *right;
	if (node->right != NULL)
	{
		right = node->right;
		return right->data;
	}
	else
		return node->data;
}
int isBST(struct node* node)
{
	if (node == NULL)
		return 1;

	int temp;
	int small = leftValue(node);
	int big   = rightValue(node);
	
	if (small < node->data && big >= node->data)
	{
		temp = isBST(node->left);
		if (temp == 1)
		temp = isBST(node->right);
	}
	else 
		return 0;
	return temp;
}
/**********************************************************************************************************************************/

int _print_t(struct node *tree, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5,i;

    if (!tree) return 0;

    sprintf(b, "(%03d)", tree->data);

    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}

int print_t(struct node *tree)
{
    char s[20][255];
    int i;
    for (i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}
/**********************************************************************************************************************************/

int main()
{
	struct node* root = NULL;
	root = insert(root,5);
	root = insert(root,8);
	root = insert(root,3);
	root = insert(root,9);
	root = insert(root,2);
	root = insert(root,6);
	root = insert(root,7);
	root = insert(root,1);
	root = insert(root,4);	
	print_t(root);
	lookup(root,2);
	lookup(root,9);
	int s;
	s = size(root);	
	printf("\nNumber of Nodes: %d\n", s);
	int depth = 0;
	depth = maxDepth(root);
	printf("\nMaximum Depth: %d\n", depth);
	int minvalue;
	minvalue = minValue(root);
	printf("\nMinimum Value: %d\n", minvalue);
	printf("\nInorder traversal\n");
	inorder(root);
	printf("\n");
	printf("\nPostorder traversal\n");
	postorder(root);
	printf("\n");
	int bol = 0, val = 12;
	printf("\nHas Path Sum %d?", val);
	bol = haspathsum(root,val);
	if (bol == 1)
	printf(" Yes!\n");
	else 
	printf(" No!\n");
	printf("\nAll Paths:\n"); 
	printpath(root);
	int isb = 0;
	isb = isBST(root);
	if (isb == 1)
	printf("\nTree is BST\n");
	else
	printf("\nTree is non-BST\n");
	mirror(root);
	print_t(root);
	isb = isBST(root);
	if (isb == 1)
	printf("\nTree is BST\n");
	else
	printf("\nTree is non-BST\n");
	doubletree(root);
	print_t(root);
	int same = 0;
	same = sametree(root, NULL);
	if (same == 0)
	printf("\nIdentical tree\n");
	else 
	printf("\nDifferent trees\n");
	int count = 5, treecount;
	treecount = counttrees(count);
	printf("\nTree Count for %d: %d\n", count, treecount);
	return 0;
}
