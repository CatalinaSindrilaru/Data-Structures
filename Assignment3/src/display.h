// Copyright Sindrilaru Catalina-Maria & Arghir Monica-Andreea, 312CA, 2022

#ifndef DISPLAY_H_
#define DISPLAY_H_

void ls(TreeNode* currentNode, char* arg);
void pwd(TreeNode* treeNode);
void display_from_current_folder(TreeNode *currentNode, int *nr_dir,
									int *nr_files, int level);
void tree(TreeNode* currentNode, char* arg);

#endif  // DISPLAY_H_
