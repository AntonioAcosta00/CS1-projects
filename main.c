#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "leak_detector_c.h"
#define MAXLEN 51

FILE *file;



    
                  /* COP 3502C Programming Assignment 4 
                  This program is written by: Antonio Acosta */ 



typedef struct itemNode
{
  char name[MAXLEN];
  int count;
  struct itemNode *left, *right;
}itemNode;

typedef struct treeNameNode
{
  char treeName[MAXLEN];
  struct treeNameNode *left, *right;
  itemNode *theTree;
}treeNameNode;

treeNameNode * buildNameTree(int namesN, treeNameNode *root);
treeNameNode * createTreeNameNode(char name[MAXLEN]);
treeNameNode * insertNameTree(treeNameNode *root,treeNameNode *ins);
treeNameNode * searchNameNode(treeNameNode *root, char treeName[MAXLEN]); 
treeNameNode * buildItemTree(int itemsI, treeNameNode *root);
itemNode* createItemNode();
itemNode* insertItemTree(itemNode* root, itemNode *insItem);
void traverse_in_traverse(treeNameNode *root); 
void inorderN(treeNameNode *root);
void inOrderI(itemNode *root);
void search(treeNameNode* root);
void itemBefore(treeNameNode* root);
void heightBalance(treeNameNode* root);
void count(treeNameNode* root);
void reduce(treeNameNode* root);
void deleteItem(treeNameNode* root);
void deleteName(treeNameNode* root);
itemNode * searchItemNode(itemNode * root, char nameOf[MAXLEN]);
void queries(treeNameNode * root, int queriesQ);
int findItemsCountBefore(itemNode *root, char item[MAXLEN]);
int height(itemNode * root);
int absoluteVal(int left, int right);
int total(itemNode* root);
void freeWholeItem(itemNode* root);
itemNode* delItemNode(itemNode *root , char nameOfItem[MAXLEN]);
itemNode * minItem(itemNode * root);
treeNameNode* delNameNode(treeNameNode* root, char nameofTree[MAXLEN]);
treeNameNode * minName(treeNameNode* root);
void reduce(treeNameNode* root);
void freeAll(treeNameNode* root);


// Code Start


// Inserts the names into the BST correctly.
treeNameNode * insertNameTree(treeNameNode *root,treeNameNode *ins)
{
  if(root == NULL)
  {
    return ins;
    
  }
  else
  {
    if(strcmp(root->treeName, ins->treeName) > 0 ) // my data has to go to the left (smaller)
    {
      if(root->left != NULL) 
      {
        root->left = insertNameTree(root->left, ins);
      }
      else
      {
        root->left = ins;
      }
    }
    else // my data has to go to the right (bigger)
    {
      if(root->right != NULL) 
      {
        root->right = insertNameTree(root->right, ins);
      }
      else
      {
        root->right = ins;
      }
    }
    
  }

  return root;
}




// Allocates space for the treeNameNode initilizing it as well.
// YOU COMMENTED OUT CREATE ITEM NODE BECAUSE YOU THINK YOU DON'T NEED IT.
treeNameNode * createTreeNameNode(char name[MAXLEN])
{
  treeNameNode* ins = malloc(sizeof(treeNameNode));
  ins->left = NULL;
  ins->right = NULL;
  strcpy(ins->treeName, name);
  //ins->theTree = createItemNode();

  return ins;
}



// Insert to the name tree and return the root of the name tree
treeNameNode * buildNameTree(int namesN, treeNameNode *root)
{


  char name[MAXLEN];
  
  for(int i = 0; i < namesN;i++)
    {
      
      scanf("%s ", name);
      treeNameNode* ins = createTreeNameNode(name);
      
      root = insertNameTree(root, ins);
    }


  return root;
}







// Item Functions





// Makes sure the items go in the BST correctly 
itemNode* insertItemTree(itemNode *root, itemNode *ins)
{
  if(root == NULL)
  {
    return ins;
  }
  else
  {
    if(strcmp(root->name, ins->name) > 0) // my data has to go to the left (smaller)
    {
      if(root->left != NULL) 
      {
        root->left = insertItemTree(root->left, ins);
      }
      else
      {
        root->left = ins;
      }
    }
    else // my data has to go to the right (bigger)
    {
      if(root->right != NULL) 
      {
        root->right = insertItemTree(root->right, ins);
      }
      else
      {
        root->right = ins;
      }
    }
      return root;
  }

}



// Creates multiple item trees for however many item the user requests
treeNameNode * buildItemTree(int itemsI, treeNameNode *root)
{
  char nameSearch[MAXLEN], nameOf[MAXLEN];
  int itemNum;
  treeNameNode* tempRoot;
  itemNode* insItem;
  for(int i = 0;i < itemsI;i++)
    {

      // Take user input I times
      scanf("%s %s %d", nameSearch, nameOf, &itemNum);
      

      // Everytime search for the name and make hold it for editing
      tempRoot = searchNameNode(root, nameSearch);

      



      // Create the item you're about to insert
      itemNode * insItem = createItemNode();
      strcpy(insItem->name, nameOf);
      insItem->count = itemNum;





      // Insert it through BST
      tempRoot->theTree = insertItemTree(tempRoot->theTree, insItem);


    }
  return root;
}


// allocates space and initializes the rest of item node
itemNode* createItemNode()
{
  itemNode* insItem = malloc(sizeof(itemNode));
  insItem->left  = NULL;
  insItem->right = NULL;
  return insItem;
}

// Search function for the name using strcmp
treeNameNode* searchNameNode(treeNameNode* root, char treeName[MAXLEN])
{

  
  if(root == NULL)
  {
    return 0;
  }
  else
  {
    if(strcmp(root->treeName, treeName) == 0)
    {
      return root;
    }
    else if(strcmp(root->treeName, treeName) > 0)
    {
      searchNameNode(root->left, treeName);
    }
    else if(strcmp(root->treeName, treeName) < 0) 
    {
      searchNameNode(root->right, treeName);
    }
  }

}






// Printing Functions First Part of them.



// Printing function to print out the fancy == text using the rest of the functions
void traverse_in_traverse(treeNameNode *root)
{
  if(root != NULL)
  {
    traverse_in_traverse(root->left);
    printf("===%s===\n",root->treeName);
    fprintf(file, "===%s===\n",root->treeName);
    inOrderI(root->theTree);
    printf("\n");
    fprintf(file, "\n");
    traverse_in_traverse(root->right);
  }
}

void printfix(treeNameNode* root)
{
  inorderN(root);
  printf("\n");
  fprintf(file, "\n");
  traverse_in_traverse(root);
}


// Printing the Names
void inorderN(treeNameNode *root)
{
  if(root != NULL)
  {
    inorderN(root->left);
    printf("%s ", root->treeName);
    fprintf(file,"%s ", root->treeName);
    inorderN(root->right);
  }
}


// Printing the Items
void inOrderI(itemNode *root)
{
  if(root != NULL)
  {

    inOrderI(root->left);
    printf("%s ", root->name);
    fprintf(file, "%s ", root->name);
    inOrderI(root->right);
  }
}









// Queries Function Stuff (suffering)


void queries(treeNameNode * root, int queriesQ)
{
  char func[MAXLEN];
  for(int i = 0; i < queriesQ; i++)
    {

      scanf("%s ", func);

      // search for the name
      if(strcmp(func, "search") == 0)
      {
        search(root);
      }
      
      // count items before
      if(strcmp(func, "item_before") == 0)
      {
        itemBefore(root);
      }

      //check if the height is balanced correctly 
      if(strcmp(func, "height_balance") == 0)
      {
        heightBalance(root);
      }

      // count the amount of items
      if(strcmp(func, "count") == 0)
      {
        count(root);
      }
      
      // reduce the count of a given item
      if(strcmp(func, "reduce") == 0)
      {
        reduce(root);
      }

      // delete an item from a tree
      if(strcmp(func, "delete") == 0)
      {
        deleteItem(root);
      }

      //delete a whole name from the tree
      if(strcmp(func, "delete_name") == 0)
      {
        deleteName(root);
      }
    }
  
}


// search if an item exists.
void search(treeNameNode* root)
{
  char nameOfItem[MAXLEN];
  char nameOfTree[MAXLEN];
  scanf("%s %s", nameOfTree, nameOfItem);
  treeNameNode * tempN = searchNameNode(root, nameOfTree);
  if(tempN == 0)
  {
    printf("%s does not exist\n", nameOfTree);
    fprintf(file, "%s does not exist\n", nameOfTree);
  }
  else
  {
    itemNode* tempI = searchItemNode(tempN->theTree, nameOfItem);
    if(tempI == 0)
    {
      printf("%s not found in %s\n", nameOfItem, tempN->treeName);
      fprintf(file, "%s not found in %s\n", nameOfItem, tempN->treeName);
    }
    else
    {
      printf("%d %s found in %s\n", tempI->count, tempI->name, tempN->treeName);
      fprintf(file, "%d %s found in %s\n", tempI->count, tempI->name, tempN->treeName);
    }
  }
  
}

// This should be almost a copy of searchNameNode
itemNode * searchItemNode(itemNode * root, char nameOf[MAXLEN])
{
  if(root == NULL)
  {
    return 0;
  }
  else
  {
    if(strcmp(root->name, nameOf) == 0)
    {
      return root;
    }
    else if(strcmp(root->name , nameOf) > 0) // searches the left child
    {
      return searchItemNode(root->left, nameOf);
    }
    else if(strcmp(root->name, nameOf) < 0) // searches the right child
    {
      return searchItemNode(root->right, nameOf);
    }
  }
}



// searches for the item before
void itemBefore(treeNameNode* root)
{
  char nameOfTree[MAXLEN], nameOfItem[MAXLEN];
  treeNameNode *tempN;
  itemNode * tempI;
  
  int count = 0;
  
  scanf("%s %s", nameOfTree, nameOfItem);

  // search for the actual names and items you're looking for
  tempN = searchNameNode(root, nameOfTree);
  tempI = searchItemNode(tempN->theTree, nameOfItem);


  // return the item before count
  count = findItemsCountBefore(tempN->theTree, nameOfItem);
  printf("item before %s: %d\n", tempI->name, count);
  fprintf(file, "item before %s: %d\n", tempI->name, count);
  
  
}


int findItemsCountBefore(itemNode *root, char item[MAXLEN])
{
  int count = 0;
  if(root == NULL)
  {
    return 0;
  }
  else if(strcmp(root->name, item) < 0) // checking the right child
  {
    count++;
    count += findItemsCountBefore(root->left, item);
    count += findItemsCountBefore(root->right, item);
  }
  else // checks the left child
  {
    count = count + findItemsCountBefore(root->left, item);
  }
  return count;
}

// checks and returns the height balance
// This one is pain :D

void heightBalance(treeNameNode* root)
{
  char nameOfTree[MAXLEN];
  treeNameNode* tempN;

  scanf("%s ", nameOfTree);

  // search for required name
  tempN = searchNameNode(root, nameOfTree);

  // find each height of the respective tree
  int right = height(tempN->theTree->right);
  int left = height(tempN->theTree->left);

  // included math for absolute value
  int diff = abs(left - right);

  if(diff > 1)
  {
    printf("%s: left height %d, right height %d, difference %d, not balanced\n", tempN->treeName, left, right, diff);
    fprintf(file, "%s: left height %d, right height %d, difference %d, not balanced\n", tempN->treeName, left, right, diff);
  }
  else
  {
    printf("%s: left height %d, right height %d, difference %d, balanced\n", tempN->treeName, left, right, diff);
    fprintf(file,"%s: left height %d, right height %d, difference %d, balanced\n", tempN->treeName, left, right, diff);
  }
  
}


// finds the height of certain paths
int height(itemNode* root)
{

  // credit mycodeschool on youtube, helped me through this one lol

  
  int left;
  int right;

  // If there is no node it's considered -1
  // causes the edge to be balanced out
  if(root == NULL)
  {
    return -1;
  }

  
  left = height(root->left);
  right = height(root->right);

  // checks which one is the max and adds 1
  if(left > right)
  {
    return 1 + left;
  }
  else
  {
    return 1 + right;
  }
}




void count(treeNameNode* root)
{
  int count = 0;
  char nameOfTree[MAXLEN];
  treeNameNode * tempN;
  scanf("%s ", nameOfTree);

  // search for the tree
  tempN = searchNameNode(root, nameOfTree);

  // counts the total amount of items within that item tree
  count = total(tempN->theTree);

  printf("%s count %d\n", tempN->treeName, count);
  fprintf(file, "%s count %d\n", tempN->treeName, count);
  
  
}

int total(itemNode* root)
{
  int count = 0;
  if(root != NULL)
  {
    count += total(root->left);
    count += total(root->right);
    return count + root->count;
  }
  return 0;
}


void reduce(treeNameNode* root)
{
  char nameOfTree[MAXLEN], nameOfItem[MAXLEN];
  int reduce;

  scanf("%s %s %d", nameOfTree, nameOfItem, &reduce);
  treeNameNode* tempN = searchNameNode(root, nameOfTree);
  itemNode* tempI = searchItemNode(tempN->theTree, nameOfItem);
  tempI->count -= reduce;
  if(tempI->count > 0)
  {
    printf("%s reduced\n", tempI->name);
    fprintf(file,"%s reduced\n", tempI->name);
  }
  else if(tempI->count <= 0)
  {
    printf("%s reduced\n", tempI->name);
    fprintf(file, "%s reduced\n", tempI->name);
    tempN->theTree = delItemNode(tempN->theTree, nameOfItem);
  }
}


// should be extremely similar to namedel again
void deleteItem(treeNameNode* root)
{
  char nameOfTree[MAXLEN], nameOfItem[MAXLEN], storeName[MAXLEN];
  treeNameNode* tempN;
  itemNode* delItem;

  
  scanf("%s %s", nameOfTree, nameOfItem);
  
  tempN = searchNameNode(root, nameOfTree);
  delItem = searchItemNode(tempN->theTree, nameOfItem);
  
  strcpy(storeName, delItem->name);
  tempN->theTree = delItemNode(tempN->theTree, nameOfItem);


  printf("%s deleted from %s\n", storeName, tempN->treeName);
  fprintf(file, "%s deleted from %s\n", storeName, tempN->treeName);
  
  
  
    
}


// should be really similar to delNameNode
itemNode* delItemNode(itemNode * root, char nameOfItem[MAXLEN])
{

  if(root == NULL)
  {
    return root;
  }
  if(strcmp (nameOfItem, root->name) < 0)
  {
    root->left = delItemNode(root->left, nameOfItem);
  }
  else if(strcmp(nameOfItem, root->name) > 0)
  {
    root->right = delItemNode(root->right, nameOfItem);
  }
  else
  {
    if(root->left == NULL)
    {
      itemNode * tempI = root->right;
      free(root);
      return tempI;
    }
    else if (root->right == NULL)
    {
      itemNode * tempI = root->left;
      free(root);
      return tempI;
    }

    // searches for the minimum
    itemNode* tempI = minItem(root->right);
    strcpy(root->name, tempI->name);
    root->count = tempI->count;
    root->right = delItemNode(root->right, tempI->name);
  }

  return root;
}

// should be very similar to minName
itemNode * minItem(itemNode * root)
{
  itemNode* tempI = root;
  while(tempI && tempI->left != NULL)
    {
      tempI = tempI->left;
    }
  return tempI;
}



void freeWholeItem(itemNode* root)
{
  if(root != NULL)
  {
    freeWholeItem(root->left);
    freeWholeItem(root->right);
    free(root);
  }
}

treeNameNode* delNameNode(treeNameNode* root, char nameOfTree[MAXLEN])
{

  if(root == NULL)
  {
    return root;
  }
  if(strcmp(nameOfTree, root->treeName) < 0)
  {
    root->left = delNameNode(root->left, nameOfTree);
  }
  else if(strcmp(nameOfTree, root->treeName) > 0)
  {
    root->right = delNameNode(root->right, nameOfTree);
  }
  else
  {
    if(root->left == NULL)
    {
      treeNameNode * tempN = root->left;
      free(root);
      return tempN;
    }
    else if (root->right == NULL)
    {
      treeNameNode * tempN = root->right;
      free(root);
      return tempN;
    }

    // searches for the minimum
    treeNameNode* tempN = minName(root->right);
    strcpy(root->treeName, tempN->treeName);
    root->right = delNameNode(root->right, tempN->treeName);
  }

  
}

treeNameNode * minName(treeNameNode* root)
{
  treeNameNode * tempN = root;
  while(tempN && tempN->left != NULL)
    {
      tempN = tempN->left;
    }
  return tempN;
}

void deleteName(treeNameNode* root)
{
  char nameOfTree[MAXLEN], storeName[MAXLEN];
  treeNameNode* tempN;
  itemNode* delItem;

  scanf("%s ", nameOfTree);
  tempN = searchNameNode(root, nameOfTree);\

  strcpy(storeName, tempN->treeName);
  freeWholeItem(tempN->theTree);

  root = delNameNode(root, nameOfTree);
  printf("%s deleted\n", storeName);
  fprintf(file, "%s deleted\n", storeName);
  
}

void freeAll(treeNameNode* root)
{
  if(root != NULL)
  {
    if(root->theTree != NULL)
    {
      freeWholeItem(root->theTree);
    }
    freeAll(root->left);
    freeAll(root->right);
    free(root);
  }
}


int main()
{

  atexit(report_mem_leak);
  file = fopen("out.txt", "w");
  int namesN, itemsI ,queriesQ;

  
  scanf("%d %d %d", &namesN, &itemsI, &queriesQ);
  treeNameNode* root = NULL;


  // Things to do within here
  // The program.
  // :) 
  // 11/23 done.
  root = buildNameTree(namesN, root);
  buildItemTree(itemsI, root);
  inorderN(root);
  printf("\n");
  fprintf(file, "\n");
  traverse_in_traverse(root);
  
  queries(root, queriesQ);

  // Free memory Leaks
  freeAll(root);


  fclose(file);
  return 0;
}