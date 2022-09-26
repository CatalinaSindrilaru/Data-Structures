// Copyright Sindrilaru Catalina-Maria & Arghir Monica-Andreea, 312CA, 2022

#ifndef SEARCH_H_
#define SEARCH_H_

TreeNode *search_node_recursive(TreeNode *currentNode,
									char *arg, int *writted);
TreeNode *find_folder(TreeNode *currentNode, char *resourceName);

#endif  // SEARCH_H_
