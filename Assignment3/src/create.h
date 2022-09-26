// Copyright Sindrilaru Catalina-Maria & Arghir Monica-Andreea, 312CA, 2022

#ifndef CREATE_H_
#define CREATE_H_

char *strdup(char *arg);
List *create_list();
FileTree createFileTree(char* rootFolderName);
void mkdir(TreeNode* currentNode, char* folderName);
void touch(TreeNode* currentNode, char* fileName, char* fileContent);
void create_new_child(TreeNode* new_child, TreeNode* new_parent);

#endif  // CREATE_H_
