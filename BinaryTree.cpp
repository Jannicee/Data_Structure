#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// menggunakan recursive
struct tree{
	int value;
	
	struct tree *left;
	struct tree *right;
}*root = NULL;

// create node
struct tree* createnode(int value){
	struct tree* node = (tree*)malloc(sizeof(tree));
	
	node->value = value;
	
	node->left = node->right = NULL;
	return node;
}

// insert/push
struct tree* insert(struct tree* node, int key){
// node yang kosong di tree yang kita punya
	if (node == NULL){
		node =createnode(key);
		return node;
	}
// kalau value yang masu di-insert belum ada/unik
	else if(node->value != key){ // key --> value baru yang mau masuk ke node
		// 1) kalau key yang mau di-insert > daripada value yang ada di tree
		if(key > node->value){
			node->right = insert(node->right, key);
		}
		// 2) kalau key yang mau di-insert < daripada value yang ada di tree
		else if (key < node->value){
			node->left = insert(node->left, key);
		}
	}
	return node;
}

// BST TRANSVERSAL
// preorder --> root, parent, baru ke leaf
// inorder --> baca dari leaf, parent, leaf, root, leaf, parent, leaf
// postorder --> leaf (semua leaf), parent, terakhir root (selalu mulai dari left branch, baru ke right)

// print
// In-order
void inorder(struct tree* node){
	// kalau tree-nya kosong
	if(node == NULL){
		return;
	}
	else {
		inorder(node->left);
		printf("%d ->", node->value);
		inorder(node->right);
	}
}

// Pre-order
void preorder(struct tree* node){
	// kalau tree-nya kosong
	if(node == NULL){
		return;
	}
	else {
		printf("%d ->", node->value);
		preorder(node->left);
		preorder(node->right);
	}
}

// Post-order
void postorder(struct tree* node){
	// kalau tree-nya kosong
	if(node == NULL){
		return;
	}
	else {
		postorder(node->left);
		postorder(node->right);
		printf("%d ->", node->value);
	}
}

// count jumlah node" tree yang ada / total node di BST
int count (struct tree* node){
	// kalau tree nya kososng
	if (node == NULL){
		return 0;
	}
	// kalau tree nya tdk kosong
	else {
		return (1 + count(node->left) + count(node->right)); //1 unt root
	}
}

// height of tree
int height(struct tree* node){
	// kalau tree nya kososng
	if (node == NULL){
		return 0;
	}
	// kalau tree nya tdk kosong
	else {
		int leftheight = height(node->left);
		int rightheight = height(node->right);
		
		if(leftheight > rightheight){
			return 1 + leftheight;	// 1 --> root nya
		} else {
			return 1 + rightheight;
		}
	}
}

// Minimum value
int minvalue(struct tree* node){
		// kalau tree nya kososng
	if (node == NULL){
		return 0;
	}
	// kalau tree nya tdk kosong
//	else{
//	struct tree *curr = node;
//	while (curr->left != NULL){
//	curr = curr->left;
//	}
//return curr->value;
	else if(node->left == NULL){
		return node->value;
		// print nilai left paling terakhir
	}
	return minvalue(node->left);	//next ke left branch until node->left == NULL
}

// Maximum value
int maxvalue(struct tree* node){
		// kalau tree nya kososng
	if (node == NULL){
		return 0;
	}
	// kalau tree nya tdk kosong
	else if(node->right == NULL){
		return node->value;
		// print nilai right paling terakhir
	}
	return maxvalue(node->right);	//next ke right branch until node->right == NULL
}

// Searching
void searching(struct tree* node, int target){	//target = value yg mau dicari
	if (node == NULL){
		return;
	}
	// kalau tree nya tdk kosong
	else if(node->value == target){
		printf("%d is found!\n", target);
		return;
	}
	
	if(target > node->value){
		return searching(node->right, target);
	}
	if(target < node->value){
		return searching(node->left, target);
	}
}


// deletion by predecessor	// jika valuenya punya child/ leaf
// find predecessor
struct tree* findpredecessor(struct tree* node){
	if(node == NULL){
	return NULL;}
	else if (node ->right == NULL){
	return node;
	}
	return findpredecessor(node->right);
}

struct tree* delete_by_predecessor(struct tree* node, int key){	//node is the root
	//kalau treenya kosong
	if (node == NULL) return 0;
	// kalau yg mau didelete lebih > dari value yang ada sekarang
	else if (key > node->value){
		node->right = delete_by_predecessor(node->right, key);
	}
	// kalau yg mau didelete lebih < dari value yang ada sekarang
	else if (key > node->value){
		node->left = delete_by_predecessor(node->left, key);
	}
	// kalau yang mau didelete == value tempat kita ada sekarang
	else {
		// 1. kalau bukan child/ leaf
		if(node->left == NULL && node->right == NULL){
			free(node);
			node = NULL;
			return node;
		}
		// 2. kalau punya 1 child
		if(node->left == NULL || node->right == NULL){
			if(node->left == NULL){
				return node->right;
			}
			else if(node->right == NULL){
				return node->left;
			}
			free(node);
		}
		// 3. kalau punya 2 child
		if(node->left != NULL && node->right != NULL){
		tree *temp = findpredecessor(node->left);
		node->value = temp->value;
		node->left = delete_by_predecessor(node->left, temp->value);
		}
	}
}


// deletion by successor
//find successor
struct tree* findsuccessor(struct tree* node){
	if (node == NULL){
		return NULL;
	}
	else if(node->left == NULL){
		return node;
	}
	return findsuccessor(node->left);
}

// deletion by successor
struct tree* delete_by_successor(struct tree* node, int key){
	if(node == NULL){
		return NULL;
	}
	else if(key > node->value){
		node->right = delete_by_successor(node->right, key);
	}
	else if(key < node->value){
		node->left = delete_by_successor(node->left, key);
	}
	else {
		// no child (leaf)
		if(node->left == NULL && node->right == NULL){
			free(node);
			return NULL;
		}
		// 1 child
		if(node->left == NULL || node->right == NULL){
			tree* temp = (node->left == NULL) ? node->right : node->left;
			free(node);
			return NULL;
		}
		// 2 child
		else if(node->left != NULL && node->right != NULL){
			tree* temp = findsuccessor(node->right);
			node->value = temp->value;
			node->right = delete_by_successor(node->right, temp->value);
		}
	}
}


// Delete
void deleteNode (struct tree* node, int find){
	struct tree* parent = node;
	
	while(node && node->value != find){
		if (find < node->value){
			parent = node;
			node = node->left;
		}
		else if (find > node->value){
			parent = node;
			node = node->right;
		}
	}
	
	if(!node){
		printf("%d is not found\n", find);
	} else if(node->value == find){
		root = delete_by_predecessor(root, find);	//disesuaikan casenya delete by successor/ predecessor
	}
}

int main (){
	root = insert(root, 54);	
	root = insert(root, 81);
	root = insert(root, 16);	
	root = insert(root, 20);	
	root = insert(root, 36);	
	root = insert(root, 63);	
	root = insert(root, 72);
	
	printf ("Total node in BST : %d\n", count(root));
	printf("Height of the tree : %d\n", height(root));
	
	printf("Inorder: "); inorder(root);
	printf("\n");
	printf("Preorder: "); preorder(root);
	printf("\n");
	printf("Postorder: "); postorder(root);
	printf("\n");
	
		deleteNode(root, 54); 
	printf("\nPreorder (after del 54): "); preorder(root);
		deleteNode(root, 9); 
	printf("\nPostorder (after del 9): "); postorder(root); 
		deleteNode(root, 81); 
	printf("\nInorder (after del 81): "); inorder(root); 
	
	puts(""); 
	printf("Min value: %d \n", minvalue(root)); 
	printf("Max value: %d \n", maxvalue(root)); 
	
	puts("");
	
	searching(root, 72);
	searching(root, 8);
	
	return 0;
}


