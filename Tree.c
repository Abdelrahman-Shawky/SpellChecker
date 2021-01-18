#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct
{
    char *word;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(char *word)
{
    Node* n = malloc(sizeof(Node));
    n->word = malloc(30);
    strcpy(n->word,word);
    n->left = NULL;
    n->right = NULL;
    return n;
}

Node* insert(Node* node, char *word)
{
    if(node == NULL)
        return newNode(word);
    if(strcasecmp(word,node->word) < 0)
        node->left = insert(node->left,word);
    else if(strcasecmp(word,node->word) > 0)
        node->right = insert(node->right,word);
    return node;
}

//Node* search(Node* root,char *word)
//{
//    if(root == NULL)
//        return NULL;
//    else if (strcasecmp(word,root->word) == 0)
//        return root;
//    else if(strcasecmp(word,root->word) < 0)
//        return search(root->left,word);
//    else
//        return search(root->right,word);
//}

Node* search(Node* root,char *word)
{
    if(root == NULL)
        return -1;
    else if (strcasecmp(word,root->word) == 0)
        return 0;
    else if(strcasecmp(word,root->word) < 0)
        return search(root->left,word);
    else
        return search(root->right,word);
}

int count(Node* root)
{

    if(root == NULL)
        return 0;
    else
        return 1 + count(root->left) + count(root->right);

}

int max(int x, int y)
{
    if(x > y)
        return x;
    else
        return y;
}

int height(Node* root)
{
    if(root == NULL)
        return -1;
    else
        return 1 + max(height(root->left),height(root->right));
}

Node* FindMin(Node *root)
{
    if(root==NULL)
        return NULL;
    else if(root->left!=NULL)
        return FindMin(root->left);
    else
        return root;
}

Node* FindMax(Node *root)
{
    if(root==NULL)
        return NULL;
    else if(root->right!=NULL)
        return FindMax(root->right);
    else
        return root;
}

Node* FindNearest(Node* root, char *word)
{
    Node* nearest;
    while(root!=NULL)
    {
        nearest = root;
        if(strcasecmp(word,root->word) > 0)
            root=root->right;
        else if(strcasecmp(word,root->word) < 0)
            root=root->left;

    }
    return nearest;
}

Node* FindSuccessor(Node* root, char *word)
{
    Node* successor = newNode("No Successor");


    if(root==NULL)
        return NULL;
    else
        while(strcasecmp(word,root->word) != 0)
        {
            if(strcasecmp(word,root->word) > 0)
            {
                root=root->right;
            }
            else if (strcasecmp(word,root->word) < 0)
            {
                successor = root;
                root=root->left;
            }
        }
    if(root->right!=NULL)
        return FindMin(root->right);
    else if(root->right==NULL)
        return successor;
}

Node* FindPredecessor(Node* root, char *word)
{
    Node* predecessor = newNode("No Predecessor");


    if(root==NULL)
        return NULL;
    else
        while(strcasecmp(word,root->word) != 0)
        {
            if(strcasecmp(word,root->word) > 0)
            {
                predecessor = root;
                root=root->right;
            }
            else if (strcasecmp(word,root->word) < 0)
            {

                root=root->left;
            }
        }
    if(root->left!=NULL)
        return FindMax(root->left);
    else if(root->left==NULL)
        return predecessor;
}

Node* ReadFromFile(Node *root)
{

    FILE *f1;
    f1=fopen("EN-US-Dictionary.txt","r");
    if(f1==NULL)
    {
        printf("Error Reading File");
        exit(0);
    }
    char *word = malloc(30);
    fscanf(f1,"%s\n",word);
    root = insert(root,word);


    while(!feof(f1))
    {

        fscanf(f1,"%s\n",word);
        root = insert(root,word);
    }
    fclose(f1);
    return root;

}

void Investigate(Node* dictionary,char *sentence)
{
    char space[2]=" ";
    char *token=strtok(sentence,space);

    while (token!=NULL)
    {

        if(search(dictionary,token) == 0)
            printf("%s - Correct\n",token);
        else
        {
            printf("%s - Incorrect, Suggestions : %s %s %s\n",token,FindNearest(dictionary,token)->word,FindSuccessor(dictionary,FindNearest(dictionary,token)->word)->word,FindPredecessor(dictionary,FindNearest(dictionary,token)->word)->word);
        }
        token=strtok(NULL,space);
    }





}


int main()
{

    Node *dictionary = NULL;
    dictionary = ReadFromFile(dictionary);
    printf("Dictionary Loaded Successfully...!\n");
    printf("..................................\n");
    printf("Size = %d\n",count(dictionary));
    printf("..................................\n");
    printf("Height = %d\n",height(dictionary));
    printf("Enter A Sentence :\n");

    char *sentence = malloc(150);
    gets(sentence);
    Investigate(dictionary,sentence);





    return 0;
}
