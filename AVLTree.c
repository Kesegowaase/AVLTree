#include<stdio.h> 
#include<stdlib.h> 

struct Node{
    int number;
    int height;
    struct Node *left; 
    struct Node *right; 
}; 

int Max(int leftHight,int rightHight){
    if(rightHight <= leftHight)
        return leftHight;
    else if(rightHight >= leftHight)
        return rightHight;
}

int height(struct Node *N){ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 

struct Node* newNode(int number){ 
    struct Node* node = (struct Node*) malloc(sizeof(struct Node)); 
    node->number   = number; 
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;  // new node is initially added at leaf 
    return node; 
} 

struct Node *rightRotate(struct Node *y){ 
    struct Node *x = y->left; 
    struct Node *z = x->right; 
    x->right = y; 
    y->left = z; 
    y->height = Max(height(y->left), height(y->right))+1; 
    x->height = Max(height(x->left), height(x->right))+1; 
    return x; 
} 
 
struct Node *leftRotate(struct Node *x){ 
    struct Node *y = x->right; 
    struct Node *z = y->left;
    y->left = x; 
    x->right = z; 
    x->height = Max(height(x->left), height(x->right))+1; 
    y->height = Max(height(y->left), height(y->right))+1; 
    return y; 
} 

int getBalance(struct Node *N) { 
    if (N == NULL) 
        return 0;
    int leftHeight = height(N->left);
    int rightHeight = height(N->right);
    return  leftHeight - rightHeight ; 
} 

struct Node* insert(struct Node* head, int number) 
{ 
    if (head == NULL) 
        return(newNode(number)); 
    if (number < head->number) 
        head->left  = insert(head->left, number); 
    else if (number > head->number) 
        head->right = insert(head->right, number); 
    else if(number == head -> number) 
        return head; 
  
    head->height = Max(height(head->left), height(head->right))+1; 
    printf("ss");
    int balance = getBalance(head); 
  
    // Left Left Case 
    if (balance > 1 && number < head->left->number){
        return rightRotate(head); 
    }
  
    if (balance < -1 && number > head->right->number){// Right Right  
        return leftRotate(head); 
    }
    
    if (balance > 1 && number > head->left->number){//Left Right
        head->left =  leftRotate(head->left); 
        return rightRotate(head); 
    } 
  
    if (balance < -1 && number < head->right->number){// Right Left 
        head->right = rightRotate(head->right); 
        return leftRotate(head); 
    } 
    return head; 
} 
  
void displayAllTree(struct Node* head){
    struct Node* temp = head;
    if(temp == NULL)
        return;
    displayAllTree(temp -> left);
    printf("%d\n",temp -> number);
    displayAllTree(temp -> right);
    
}

int balance(struct Node *head){
    int leftH;
    int rightH;
    if(head == NULL)
        return 0;
    if(head->left != NULL){
        leftH = head->left->height;
    }
    else{
        leftH = 0;
    }
    if(head->right != NULL){
        rightH = head->right->height;
    }
    else{
        rightH = 0;
    }
    return leftH - rightH;
}

void printChild(struct Node* head){
    int leftBalance = balance(head -> left);
    int rightBalance = balance(head -> right);
    if(head -> left != NULL)
        printf("%d (%d L) (%d B) ",head -> left ->number,head -> number,leftBalance);
    if(head -> right != NULL)
        printf("%d (%d R) (%d B) ",head -> right ->number,head -> number,rightBalance);
}

void level(struct Node *head,int firstLevel,int lastLevel){
    if(head == NULL)
        return;
    if(firstLevel == lastLevel){
        printChild(head);
        return;
    }
    firstLevel+=1;
    level(head -> left,firstLevel,lastLevel);
    level(head -> right,firstLevel,lastLevel);
}

int main() { 
    struct Node *root = NULL; 
    struct Node *temp = root;
    int number;
    while(1){
        scanf("%d",&number);
        if(number == -1)
            break;
        root = insert(root,number);
    }
    displayAllTree(root);
    temp = root;
    printf("\n");
    int topbalance = balance(temp);
    int height = root -> height;
    if(temp != NULL)
        printf("%d (%d B)\n",temp -> number,topbalance);
    for(int i=1;i < height;i++){
        level(temp,1,i);
        printf("\n");
        temp = root;
    }
    
     
} 
 
