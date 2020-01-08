#include <stdio.h>

#include <stdlib.h>

struct node{
	int key;
	struct node *left, *right;
	int height;
};

struct node *newNode(int key){
	struct node *yeni=(struct node*)malloc(sizeof(struct node));
	yeni->height=1;
	yeni->key=key;
	yeni->left=yeni->right=NULL;
	return yeni;
}

int height(struct node *node){
	if(node==NULL) return 0;
	return node->height;
}

struct node *rightRotate(struct node *x){
	struct node *y=x->left;
	struct node *T=y->right;
	y->right=x;
	x->left=T;
	y->height=max(height(y->left),height(y->right))+1;
	x->height=max(height(x->left),height(x->right))+1;
	return y;
}

struct node *leftRotate(struct node *x){
	struct node *y=x->right;
	struct node *T=y->left;
	y->left=x;
	x->right=T;
	y->height=max(height(y->left),height(y->right))+1;
	x->height=max(height(x->left),height(x->right))+1;
	return y;
}

struct node *minValue(struct node *root){
	struct node *curr=root;
	if(curr==NULL) return NULL;
	while(curr->left != NULL) curr=curr->left;
	return curr;
}

int getBalance(struct node *node){
	if(node==NULL) return 0;
	return height(node->left)-height(node->right);
}

int max(int a, int b){
	return a>b ? a:b;
}

struct node *insert(struct node *node, int key){
	int balance;
	if(node==NULL) return newNode(key);								//****
	if(node->key < key) node->right=insert(node->right,key);		//**** Düğümün eklendiği yer
	else node->left=insert(node->left,key);							//****
	node->height=max(height(node->left),height(node->right))+1;		//düğümün derinliği
	balance=getBalance(node);										//denge kontrolu için sol derinlik-sag derinlik
	if(balance>1 && key <node->left->key)	//sol-sol dengesizlği
		return rightRotate(node);
	if(balance<-1 && key>node->right->key)	//sağ-sağ dengesizliği
		return leftRotate(node);
	if(balance>1 && key>node->left->key){	//sol-sağ dengesizliği
		node->left=leftRotate(node->left);		
		return rightRotate(node);
	}
	if(balance<-1 && key<node->right->key){	//sağ-sol dengesizliği
		node->right=rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

void preOrder_yardimci(struct node *node) {
    if(node!=NULL){
        printf("%d (%2d) ",node->key,node->height);
        preOrder_yardimci(node->left);
        preOrder_yardimci(node->right);
    }
    
}

void preOrder(struct node *node) {
    preOrder_yardimci(node);
    printf("\n");
}

int main(int argc, char** argv) {
    struct node *root=NULL;
    
    root=insert(root,40);
    //root=insert(root,35);
    root=insert(root,38);
    root=insert(root,60);
    root=insert(root,80);
    root=insert(root,50);
    root=insert(root,21);
    
    preOrder(root);
    return 0;
}
