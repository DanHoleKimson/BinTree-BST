#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX_CODE_LENGTH 7

//이진트리에 있어 순회는 중위순회를 사용하였다.

typedef int itemStock;
typedef struct {
	char itemCod[MAX_CODE_LENGTH];
	itemStock stock;
} BTData;

typedef struct BinaryTreeNode {
	BTData data;
	struct BinaryTreeNode* left, * right, * parent; //부모 노드에 접근이 용이하게 parent포인터를 하나 더 만들었다
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
		printf("관리번호: %s, 재고: %d\n",bt->data.itemCod,bt->data.stock);
		printBT(bt->right);
	}
}

treeNode* searchBST(treeNode* bt, const char x[MAX_CODE_LENGTH]) { //필요에 따라 구조체가 필요한 경우 트리노드가 필요한 search연산이 있다 그래서 두개 다 만들었다
	/*treeNode* p = bt;
	while (p != NULL) {
		if (strcmp(x,bt->data.itemCod) == 0)
			return p;
		if (strcmp(x,bt->data.itemCod) < 0)
			p = p->left;
		else p = p->right;
	}
	printf("없는 관리번호 입니다.\n");
	return NULL;*/
	treeNode* p = bt;
	if (p == NULL) {
		printf("없는 관리번호 입니다.\n");
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
	while (p != NULL) { //삽입할 위치찾기
		if (strcmp(p->data.itemCod,x.itemCod) == 0) {
			printf("존재하는 상품코드입니다.\n");
			printf("상품코드 %s의 재고는 %d개 입니다.", x.itemCod, p->data.stock + x.stock);
			p->data.stock += x.stock;
			free(newnode);

			return;
		}
		newnode->parent = p; //삽입할 위치의 부모노드 연결
		if (strcmp(x.itemCod,p->data.itemCod) < 0) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}

	if (strcmp(x.itemCod,newnode->parent->data.itemCod) < 0) { //연결
		newnode->parent->left = newnode;
	}
	else {
		newnode->parent->right = newnode;
	}
}

treeNode* searchBigBST(treeNode* bt) { //case 3 에 사용할 함수
	treeNode* q = NULL;
	while (bt != NULL) {
		q = bt;
		bt = bt->right;
	}
	return q;
}

treeNode* deleteBST(treeNode* bt, BTData x) { //삭제할 노드를 반환
	treeNode* p = bt;
	treeNode* replace = NULL;

	while (strcmp(p->data.itemCod, x.itemCod) != 0) 
	{
		if (strcmp(x.itemCod, p->data.itemCod) < 0) { 
			p = p->left;
			if (p == NULL) { //삭제할 노드가 없음
				printf("출고할 물품이 없습니다. 관리 번호를 다시 확인해 보십시오.\n");
				return NULL;
			}
		}
		else if (strcmp(x.itemCod, p->data.itemCod) > 0) { 
			p = p->right;
			if (p == NULL) { //삭제할 노드가 없음
				printf("출고할 물품이 없습니다. 관리 번호를 다시 확인해 보십시오.\n");
				return NULL;
			}
		}
	}

	if ((p->left == NULL) && (p->right == NULL)) { // 삭제할 노드의 차수가 0인 경우
		if (p->parent == NULL) { //루트노드를 삭제하는 경우
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
	else if ((p->left == NULL) ^ (p->right == NULL)) { //삭제할 노드의 차수가 1인 경우
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
	else if ((p->left != NULL) && (p->right != NULL)) { //삭제할 노드의 차수가 2인 경우
		replace = searchBigBST(p->left); //후계자로 왼쪽 서브트리에서 가장 큰 key 값을 선택
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
	printf("\t1 : 재고확인\n");
	printf("\t2 :\t입고\n");
	printf("\t3 :\t출고\n");
	printf("\t4 :\t검색\n");
	printf("\t5 :\t종료\n\n");
	printf("*===============================*\n");
}




int main(void) {

	printmenu();
	int command;
	BTData input;
	BTData output = {NULL};
	char code[MAX_CODE_LENGTH] = { NULL };
	int number = 0;
	int save = 0; //3번에서 쓸꺼다
	treeNode* first = NULL;
	treeNode* outcome = NULL;
	treeNode* deleted = NULL;

	while (1) {
		scanf("%d", &command);
		if (command == 1) {	//재고확인
			printf("\n[전체 재고 출력]\n");
			if (first != NULL) {
				printBT(first);
			}
			else {
				printf("재고가 없습니다.\n");
			}
		}
		else if (command == 2) { //입고
			printf("[입고] 관리번호를 입력하세요. : ");
			scanf("%s", code);
			printf("[입고] 입고 수량을 입력하세요. : ");
			scanf("%d", &number);
			strcpy(input.itemCod, code);
			input.stock = number;

			if (isBTEmpty(first)) {
				first = creatBT(input);
			}
			else {
				insertBST(first, input);
			}

			char code[MAX_CODE_LENGTH] = { NULL }; //다시 초기화를 해줘서 혹시 코드가 꼬이는 걸 방지한다.
			int number = 0;
		}
		else if (command == 3) { //출고
			printBT(first);
			printf("[출고] 관리번호를 입력하세요. : ");
			scanf("%s", code);
			outcome = searchBST(first, code);

			if (outcome) { //존재하는 관리번호이면
				printf("[출고] 출고 수량을 입력하세요. : ");
				scanf("%d", &number);
				save = outcome->data.stock; //밑에 프린트문을 위해 저장
				outcome->data.stock = outcome->data.stock - number;

				if (outcome->data.stock <= 0) { //해당 출고번호를 가지는 트리노드 삭제
					printf("재고가 모두 소진되어 %d개만 출고합니다.\n", save);
					strcpy(input.itemCod, code);
					input.stock = save;
					deleted = deleteBST(first, input);
					deletememory(deleted);
					outcome = NULL;
					deleted = NULL;
				}
				else {
					printf("남은 재고는 %d개 입니다.\n", outcome->data.stock);
				}
			}
			char code[MAX_CODE_LENGTH] = { NULL };
			int number = 0;
		}
		else if (command == 4) { //검색
			printf("[재고 수량 검색] 관리번호를 입력하세요. : ");
			scanf("%s", code);
			outcome = searchBST(first, code);

			if (outcome != NULL) {
				printf("상품코드 %s의 재고는 %d개 입니다.\n", outcome->data.itemCod, outcome->data.stock);
			}
			else {
				printf("상품을 찾을 수 없습니다.\n");
			}

			char code[MAX_CODE_LENGTH] = { NULL };
			outcome = NULL;
		}
		else if (command == 5) { //종료
			printf("프로그램을 종료합니다.");
			break;
			
		}
		else {
			printf("잘못된 입력입니다.\n");
		}
		printf("\n");
		printmenu();
	}



	return 0;
}