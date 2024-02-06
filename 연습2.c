#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//����Ʈ���� �־� ��ȸ�� ������ȸ�� ����Ͽ���.

typedef int BTData;
typedef struct BinaryTreeNode {
	BTData data;
	struct BinaryTreeNode* left, * right, * parent;
}BinTree;

bool isBTEmpty(BinTree* B) {
	return B == NULL;
}

BinTree* creatBT(BTData x) {
	BinTree* newnode;
	newnode = (BinTree*)malloc(sizeof(BinTree));
	newnode->data = x;

	newnode->parent = NULL;
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode;
}

void makeLSubtree(BinTree* bt1, BinTree* bt2) { //bt2�� bt1�� ���� ����Ʈ���� ����
	bt1->left = bt2;
	bt2->parent = bt1;
}

void makeRSubtree(BinTree* bt1, BinTree* bt2) { //bt2�� bt1�� ������ ����Ʈ���� ����
	bt1->right = bt2;
	bt2->parent = bt1;
}

BinTree* getLSubtree(BinTree* bt) {
	return bt->left;
}

BinTree* getRSubtree(BinTree* bt) {
	return bt->right;
}

BTData getData(BinTree* bt) {
	return bt->data;
}

BinTree* search(BinTree* bt, BTData x) {
	if (bt != NULL) {
		search(bt->left, x);
		if (bt->data == x)
			return bt;
		search(bt->right, x);
	}
}

void deleteBT(BinTree* bt) { //deleteBT�� ���� ��ȸ�� �̿��Ͽ���.
	if (bt != NULL) {
		deleteBT(bt->left);
		deleteBT(bt->right);
		if (bt->parent != NULL) {
			if (bt == bt->parent->left) {
				bt->parent->left = NULL;
				free(bt);
			}
			else if (bt == bt->parent->right) {
				bt->parent->right = NULL;
				free(bt);
			}
		}
		else {
			bt = NULL;
		}
	}

}

void printBT(BinTree* bt) {
	if (bt != NULL) {
		printf(" [ %d ] ", bt->data);
		printBT(bt->left);
		//printf(" [ %d ] ", bt->data);
		printBT(bt->right);
	}
}

BinTree* searchBST(BinTree* bt, BTData x) {
	BinTree* p = bt;
	while (p != NULL) {
		if (x == p->data)
			return p;
		if (x < p->data)
			p = p->left;
		else p = p->right;
	}
	printf("ERROR: There is no key you looking for\n");
	return NULL;
}

void insertBST(BinTree* bt, BTData x) {
	BinTree* p = bt;
	BinTree* newnode = creatBT(x);
	while (p != NULL) {
		if (x == p->data) {
			printf("ERROR: There is already same key\n");
			free(newnode);
			return;
		}
		newnode->parent = p;
		if (x < p->data) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}

	if (bt == NULL)
		bt = newnode;
	if (x < newnode->parent->data) {
		newnode->parent->left = newnode;
	}
	else {
		newnode->parent->right = newnode;
	}
}

BinTree* searchBigBST(BinTree* bt) { //case 3 �� ����� �Լ�
	BinTree* q = NULL;
	while (bt != NULL) {
		q = bt;
		bt = bt->right;
	}
	return q;
}

void deleteBST(BinTree* bt, BTData x) {
	BinTree* p = bt;
	BinTree* replace = NULL;

	while (p->data != x)
	{
		if (p->data > x) {
			p = p->left;
			if (p == NULL) //������ ��尡 ����
				return;
		}
		else if (p->data < x) {
			p = p->right;
			if (p == NULL) //������ ��尡 ����
				return;
		}
	}

	if ((p->left == NULL) && (p->right == NULL)) { // ������ ����� ������ 0�� ���
		if (p->parent->left == p) {
			p->parent->left = NULL;
			free(p);
		}
		else {
			p->parent->right = NULL;
			free(p);
		}
	}
	else if ((p->left == NULL) ^ (p->right == NULL)) { //������ ����� ������ 1�� ���
		if (p->left != NULL) {
			p->parent->left = p->left;
			p->left->parent = p->parent;
			free(p);
		}
		else {
			p->parent->right = p->right;
			p->right->parent = p->parent;
			free(p);
		}
	}
	else if ((p->left != NULL) && (p->right != NULL)) { //������ ����� ������ 2�� ���
		replace = searchBigBST(p->left); //�İ��ڷ� ���� ����Ʈ������ ���� ū key ���� ����
		p->data = replace->data;
		deleteBST(p->left, replace->data);
	}
}




int main(void) {
	BinTree* BT1 = creatBT(40);
	insertBST(BT1, 30);
	insertBST(BT1, 59);
	insertBST(BT1, 77);
	insertBST(BT1, 95);
	insertBST(BT1, 24);
	insertBST(BT1, 37);
	printBT(BT1);
	BinTree* h = searchBigBST(BT1->left);
	printf("\n%d\n", h->data);
	deleteBST(BT1, 77);
	printBT(BT1);




	return 0;
}