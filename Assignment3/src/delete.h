// Copyright Sindrilaru Catalina-Maria & Arghir Monica-Andreea, 312CA, 2022

#ifndef DELETE_H_
#define DELETE_H_

void delete_the_file(TreeNode *currentNode, char *filename);
void search_file_recursiv(TreeNode *currentNode, char *fileName, int *find);
void rm(TreeNode* currentNode, char* fileName);
void delete_empty_folder(TreeNode *currentNode, char *folderName);
void search_folder(TreeNode *currentNode, char *folderName, int *find);
void rmdir(TreeNode* currentNode, char* folderName);
void rmrec(TreeNode* currentNode, char* resourceName);
void freeTree(FileTree fileTree);

#endif  // DELETE_H_
