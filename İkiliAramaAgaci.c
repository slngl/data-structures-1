#include <stdio.h>
#include <stdlib.h>


struct node{
	int key;
	struct node *left, *right;
};

struct BST{
	struct node *kok;
};

struct BST* newBST(struct BST **agac){
	*agac=(struct BST*)malloc(sizeof(struct BST));
	if(agac==NULL){
		printf("Yeni ağaç için heapte yer ayrılamadı");
		exit(1);
	}
	(*agac)->kok=NULL;
}

int BST_bos_mu(struct BST *agac){
	if(agac->kok==NULL) return 1;
	return 0;
}

struct node* newNode(int value){
	struct node *temp;
	temp=(struct node*)malloc(sizeof(struct node));
	if(temp==NULL){
		printf("Yeni düğüm için heapte yer ayrılamadı");
		exit(1);
	}
		temp->key=value;
		temp->left=temp->right=NULL;
		return temp;
}

void ekle(struct BST *agac, int value){
	struct node *parent;
	struct node *dugum;
	struct node *cur;
	cur=agac->kok;

	while(cur!=NULL){
		parent=cur;
		if(value < cur->key) cur=cur->left;
		else if(value > cur->key) cur=cur->right;
		else return;
	}
	dugum=newNode(value);
	if(agac->kok==NULL){
		agac->kok=dugum;
		return;
	}
	if(value<parent->key) parent->left=dugum;
else parent->right=dugum;
}

int dugum_sayisi(struct node *kok){
	if(kok==NULL) return 0;
	return 1+dugum_sayisi(kok->left)+dugum_sayisi(kok->right);
}

int yaprak_sayisi(struct node *kok){
	if(kok==NULL) return 0;
	if(kok->left==NULL && kok->right==NULL) return 1;
	else return yaprak_sayisi(kok->left)+yaprak_sayisi(kok->right);
}

int icDugum_sayisi(struct node *kok){
	if(kok==NULL) return 0;
	else if(kok->left != NULL || kok->right != NULL){
		return icDugum_sayisi(kok->left)+icDugum_sayisi(kok->right)+1;
	}
	else return 0;
}

void Yok_Et(struct node **kok){
	if(*kok!=NULL){
		free(&(*kok)->left);
		free(&(*kok)->right);
		free(*kok);
		*kok=NULL;
	}
}

void inorder(struct node *kok){
	if(kok==NULL) return;
	inorder(kok->left);
	printf("%d\t", kok->key);
	inorder(kok->right);
}
void preorder(struct node *kok){
	if(kok==NULL) return;
	printf("%d", kok->key);
	preorder(kok->left);
	preorder(kok->right);
}

void inorder_Yazdir(struct BST *agac){
	if(agac==NULL) return;
	inorder(agac->kok);
	printf("\n\n");
}

void preorder_Yazdir(struct BST *agac){
	if(agac==NULL) return;
	preorder(agac->kok);
	printf("\n\n");
}
int main(int argc, char *argv[]) {
	struct BST *agac=NULL;
        newBST(&agac);

        ekle(agac,100);
        ekle(agac,50);
        ekle(agac,200);
        ekle(agac,25);
        ekle(agac,75);
        ekle(agac,20);
        inorder_Yazdir(agac);
	return 0;
}
