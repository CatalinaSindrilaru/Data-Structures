// Copyright Sindrilaru Catalina-Maria & Arghir Monica-Andreea, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "search.h"

/* function that searches a folder or a file in the given folder */
TreeNode *search_node_recursive(TreeNode *currentNode,
									char *arg, int *writted)
{
	/* verifying if the given folder and its content are valid */
	if (currentNode == NULL || currentNode->content == NULL) {
		return NULL;
	}

	/* getting the list of children it has */
	List *children = ((FolderContent *)currentNode->content)->children;

	/* getting the first child */
	ListNode *child = children->head;

	/* going through the kids */
	while (child != NULL) {
		/* getting the info that it holds */
		TreeNode *childs_info = child->info;

		/* verifying if the node it's a file and displaying its content */
		if (strcmp(childs_info->name, arg) == 0 &&
			childs_info->type == FILE_NODE) {
			printf("%s: %s\n", childs_info->name,
					((FileContent *)childs_info->content)->text);

			/* setting the value to one to know we found what
			we were looking for */
			*writted = 1;
			return NULL;
		}

		/* if it's not a file we return the info of the folder we found */
		if (strcmp(childs_info->name, arg) == 0) {
			return childs_info;
		}

		/* if it's not a file but neither what we're searching, we continue
		to look for it recursively */
		if (childs_info->type == FOLDER_NODE) {
			search_node_recursive(childs_info, arg, writted);
		}

		child = child->next;
	}
}

/* function that returns the information of a certain folder or file */
TreeNode *find_folder(TreeNode *currentNode, char *resourceName)
{
	if (currentNode == NULL || currentNode->content == NULL) {
		return NULL;
	}

	List *children = ((FolderContent *)currentNode->content)->children;

	ListNode *child = children->head;

	while(child != NULL) {
		TreeNode *childs_info = child->info;

		if (strcmp(childs_info->name, resourceName) == 0) {
			return childs_info;
		}

		if (childs_info->type == FOLDER_NODE) {
			find_folder(childs_info, resourceName);
		}

		child = child->next;
	}
}
