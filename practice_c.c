#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX_CODE_LENGTH 7

//����Ʈ���� �־� ��ȸ�� ������ȸ�� ����Ͽ���.

typedef int itemStock;
typedef struct {
	char itemCod[MAX_CODE_LENGTH];
	itemStock stock;
} BTData;

typedef struct BinaryTreeNode {
	BTData data;
	struct BinaryTreeNode* left, * right, * parent; //�θ� ��忡 ������ �����ϰ� parent�����͸� �ϳ� �� �������
}treeNode;

bool isBTEmpty(treeNode* B) {
	return B == NULL;
}

treeNode* creatBT(BTData x) {
	treeNode* newnode;
	newnode = (treeNode*)malloc(sizeof(treeNode));
	newnode->data = x;

	newnode->parent = NULL;
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode;
}

BTData search(treeNode* bt, const char x[MAX_CODE_LENGTH]) {
	if (bt != NULL) {
		search(bt->left, x);
		if (strcmp(bt->data.itemCod, x) == 0)
			return bt->data;
		search(bt->right, x);
	}
}

void printBT(treeNode* bt) {
	if (bt != NULL) {
		printBT(bt->left);
		printf("������ȣ: %s, ���: %d\n",bt->data.itemCod,bt->data.stock);
		printBT(bt->right);
	}
}

treeNode* searchBST(treeNode* bt, const char x[MAX_CODE_LENGTH]) { //�ʿ信 ���� ����ü�� �ʿ��� ��� Ʈ����尡 �ʿ��� search������ �ִ� �׷��� �ΰ� �� �������
	/*treeNode* p = bt;
	while (p != NULL) {
		if (strcmp(x,bt->data.itemCod) == 0)
			return p;
		if (strcmp(x,bt->data.itemCod) < 0)
			p = p->left;
		else p = p->right;
	}
	printf("���� ������ȣ �Դϴ�.\n");
	return NULL;*/
	treeNode* p = bt;
	if (p == NULL) {
		printf("���� ������ȣ �Դϴ�.\n");
		return NULL;
	}
	if (strcmp(x, p->data.itemCod) == 0)
		return p;
	if (strcmp(x, p->data.itemCod) < 0)
		return searchBST(p->left, x);
	else
		return searchBST(p->right, x);

}

void insertBST(treeNode* bt, BTData x) {
	treeNode* p = bt;
	treeNode* newnode = creatBT(x);
	while (p != NULL) { //������ ��ġã��
		if (strcmp(p->data.itemCod,x.itemCod) == 0) {
			printf("�����ϴ� ��ǰ�ڵ��Դϴ�.\n");
			printf("��ǰ�ڵ� %s�� ���� %d�� �Դϴ�.", x.itemCod, p->data.stock + x.stock);
			p->data.stock += x.stock;
			free(newnode);

			return;
		}
		newnode->parent = p; //������ ��ġ�� �θ��� ����
		if (strcmp(x.itemCod,p->data.itemCod) < 0) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}

	if (strcmp(x.itemCod,newnode->parent->data.itemCod) < 0) { //����
		newnode->parent->left = newnode;
	}
	else {
		newnode->parent->right = newnode;
	}
}

treeNode* searchBigBST(treeNode* bt) { //case 3 �� ����� �Լ�
	treeNode* q = NULL;
	while (bt != NULL) {
		q = bt;
		bt = bt->right;
	}
	return q;
}

treeNode* deleteBST(treeNode* bt, BTData x) { //������ ��带 ��ȯ
	treeNode* p = bt;
	treeNode* replace = NULL;

	while (strcmp(p->data.itemCod, x.itemCod) != 0) 
	{
		if (strcmp(x.itemCod, p->data.itemCod) < 0) { 
			p = p->left;
			if (p == NULL) { //������ ��尡 ����
				printf("����� ��ǰ�� �����ϴ�. ���� ��ȣ�� �ٽ� Ȯ���� ���ʽÿ�.\n");
				return NULL;
			}
		}
		else if (strcmp(x.itemCod, p->data.itemCod) > 0) { 
			p = p->right;
			if (p == NULL) { //������ ��尡 ����
				printf("����� ��ǰ�� �����ϴ�. ���� ��ȣ�� �ٽ� Ȯ���� ���ʽÿ�.\n");
				return NULL;
			}
		}
	}

	if ((p->left == NULL) && (p->right == NULL)) { // ������ ����� ������ 0�� ���
		if (p->parent == NULL) { //��Ʈ��带 �����ϴ� ���
			//free(p);

			return bt;
		}
		else if (p->parent->left == p) {
			p->parent->left = NULL;
			//free(p);
			return p;
		}
		else {
			p->parent->right = NULL;
			//free(p);
			return p;
		}
	}
	else if ((p->left == NULL) ^ (p->right == NULL)) { //������ ����� ������ 1�� ���
		if (p->parent == NULL) {
			if (p->left != NULL) {
				//free(p);
				bt = p->left;
				bt->parent = NULL;
				return p;
			}
			else {
				//free(p);
				bt = p->right;
				bt->parent = NULL;
				return p;
			}
		}
		else if ((p->left != NULL) && p->parent != NULL) {
			p->parent->left = p->left;
			p->left->parent = p->parent;
			//free(p);
			return p;
		}
		else if ((p->right != NULL) && p->parent != NULL)
		{
			p->parent->right = p->right;
			p->right->parent = p->parent;
			//free(p);
			return p;
		}
	}
	else if ((p->left != NULL) && (p->right != NULL)) { //������ ����� ������ 2�� ���
		replace = searchBigBST(p->left); //�İ��ڷ� ���� ����Ʈ������ ���� ū key ���� ����
		p->data = replace->data;
		treeNode* come;
		come = deleteBST(p->left, replace->data);
		return come;
		
	}
}

void deletememory(treeNode* d) {
	if (d)
		free(d);
	else
		return;
}

void printmenu() {
	printf("*==== S E L E C T  M E N U ====*\n\n");
	printf("\t1 : ���Ȯ��\n");
	printf("\t2 :\t�԰�\n");
	printf("\t3 :\t���\n");
	printf("\t4 :\t�˻�\n");
	printf("\t5 :\t����\n\n");
	printf("*===============================*\n");
}




int main(void) {

	printmenu();
	int command;
	BTData input;
	BTData output = {NULL};
	char code[MAX_CODE_LENGTH] = { NULL };
	int number = 0;
	int save = 0; //3������ ������
	treeNode* first = NULL;
	treeNode* outcome = NULL;
	treeNode* deleted = NULL;

	while (1) {
		scanf("%d", &command);
		if (command == 1) {	//���Ȯ��
			printf("\n[��ü ��� ���]\n");
			if (first != NULL) {
				printBT(first);
			}
			else {
				printf("��� �����ϴ�.\n");
			}
		}
		else if (command == 2) { //�԰�
			printf("[�԰�] ������ȣ�� �Է��ϼ���. : ");
			scanf("%s", code);
			printf("[�԰�] �԰� ������ �Է��ϼ���. : ");
			scanf("%d", &number);
			strcpy(input.itemCod, code);
			input.stock = number;

			if (isBTEmpty(first)) {
				first = creatBT(input);
			}
			else {
				insertBST(first, input);
			}

			char code[MAX_CODE_LENGTH] = { NULL }; //�ٽ� �ʱ�ȭ�� ���༭ Ȥ�� �ڵ尡 ���̴� �� �����Ѵ�.
			int number = 0;
		}
		else if (command == 3) { //���
			printBT(first);
			printf("[���] ������ȣ�� �Է��ϼ���. : ");
			scanf("%s", code);
			outcome = searchBST(first, code);

			if (outcome) { //�����ϴ� ������ȣ�̸�
				printf("[���] ��� ������ �Է��ϼ���. : ");
				scanf("%d", &number);
				save = outcome->data.stock; //�ؿ� ����Ʈ���� ���� ����
				outcome->data.stock = outcome->data.stock - number;

				if (outcome->data.stock <= 0) { //�ش� ����ȣ�� ������ Ʈ����� ����
					printf("��� ��� �����Ǿ� %d���� ����մϴ�.\n", save);
					strcpy(input.itemCod, code);
					input.stock = save;
					deleted = deleteBST(first, input);
					deletememory(deleted);
					outcome = NULL;
					deleted = NULL;
				}
				else {
					printf("���� ���� %d�� �Դϴ�.\n", outcome->data.stock);
				}
			}
			char code[MAX_CODE_LENGTH] = { NULL };
			int number = 0;
		}
		else if (command == 4) { //�˻�
			printf("[��� ���� �˻�] ������ȣ�� �Է��ϼ���. : ");
			scanf("%s", code);
			outcome = searchBST(first, code);

			if (outcome != NULL) {
				printf("��ǰ�ڵ� %s�� ���� %d�� �Դϴ�.\n", outcome->data.itemCod, outcome->data.stock);
			}
			else {
				printf("��ǰ�� ã�� �� �����ϴ�.\n");
			}

			char code[MAX_CODE_LENGTH] = { NULL };
			outcome = NULL;
		}
		else if (command == 5) { //����
			printf("���α׷��� �����մϴ�.");
			break;
			
		}
		else {
			printf("�߸��� �Է��Դϴ�.\n");
		}
		printf("\n");
		printmenu();
	}



	return 0;
}