// Copyright Sindrilaru Catalina-Maria & Arghir Monica-Andreea, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "search.h"
#include "delete.h"

/* function that deletes the given file from the folder we're in */
void delete_the_file(TreeNode *currentNode, char *filename)
{
	List *children = ((FolderContent *)currentNode->content)->children;
	ListNode *child = children->head;

	/* if the first child is the one we look for */
	if (strcmp(child->info->name, filename) == 0) {
		/* changing the head of the list */
		children->head = children->head->next;

		/* freeing the content of it, the name and the info */
		free(child->info->name);

		if (((FileContent *)child->info->content) != NULL) {
			free(((FileContent *)child->info->content)->text);
			free((FileContent *)child->info->content);
		}

		free(child->info);

		/* if the list of children gets empty we also free its memory */
		if (children->head == NULL) {
			free(children->head);
			free(children);
			free((FolderContent *)currentNode->content);
		}

		return;
	}

	/* in the other case we go through all the children and
	re-do the connections */
	ListNode *prev;

	while (child != NULL && strcmp(child->info->name, filename) != 0) {
		prev = child;
		child = child->next;
	}

	prev->next = child->next;

	/* again freeing all the memory */
	free(child->info->name);

	if (((FileContent *)child->info->content) != NULL) {
		free(((FileContent *)child->info->content)->text);
		free((FileContent *)child->info->content);
	}

	free(child->info);
	free(child);
}

/* function that searches a file to delete it */
void search_file_recursiv(TreeNode *currentNode, char *fileName, int *find)
{
	if (currentNode == NULL || *find != 0 || currentNode->content == NULL) {
		return;
	}

	List *children = ((FolderContent *)currentNode->content)->children;

	/* going through the children and deleting the file we want
	when we find it */
	ListNode *child = children->head;

	while (child != NULL) {
		TreeNode *childs_info = child->info;

		if (strcmp(childs_info->name, fileName) == 0 &&
			childs_info->type == FILE_NODE) {
			delete_the_file(currentNode, fileName);

			*find = 1;
			return;
		}

		/* if we find a folder with the same name instead of a file we put
		a certain value in the find variable */
		if (strcmp(childs_info->name, fileName) == 0 &&
			childs_info->type == FOLDER_NODE) {
			*find = -1;
			return;
		}

		/* if we reach this we continue to look for the file */
		if (childs_info->type == FOLDER_NODE) {
			search_file_recursiv(childs_info, fileName, find);
		}

		child = child->next;
	}
}

/* function that deletes a file */
void rm(TreeNode* currentNode, char* fileName)
{
	/* we use the previous function to treat each case */
	int find = 0;
	search_file_recursiv(currentNode, fileName, &find);

	if (find == 0) {
		printf("rm: failed to remove '%s': No such file or directory\n",
			fileName);
	}

	if (find == -1) {
		printf("rm: cannot remove '%s': Is a directory\n", fileName);
	}
}


/* function that deletes an empty folder */
void delete_empty_folder(TreeNode *currentNode, char *folderName)
{
	if (currentNode == NULL || currentNode->content == NULL) {
		return;
	}

	List *children = ((FolderContent *)currentNode->content)->children;

	ListNode *child = children->head;

	/* if the folder we want to delete it's the first child
	of the current folder */
	if (strcmp(child->info->name, folderName) == 0) {
		children->head = children->head->next;

		/* freeing its memory */
		free(child->info->name);
		free(child->info);

		/* if there are no children left we also free the memory used*/
		if (children->head == NULL) {
			free(children->head);
			free(children);
			free((FolderContent *)currentNode->content);
		}

		return;
	}

	/* if it's not the first child we re-do its connections */
	ListNode *prev;

	while (child != NULL && strcmp(child->info->name, folderName) != 0) {
		prev = child;
		child = child->next;
	}

	prev->next = child->next;

	/* eliberating the memory */
	free(child->info->name);
	free(child->info);
	free(child);
}


/* function that searches a folder in order to delete it */
void search_folder(TreeNode *currentNode, char *folderName, int *find)
{
	if (currentNode == NULL || *find != 0 || currentNode->content == NULL) {
		return;
	}

	List *children = ((FolderContent *)currentNode->content)->children;

	ListNode *child = children->head;

	while (child != NULL) {
		TreeNode *childs_info = child->info;

		if (strcmp(childs_info->name, folderName) == 0 &&
			childs_info->type == FOLDER_NODE) {
			if (childs_info->content == NULL) {
				delete_empty_folder(currentNode, folderName);
				*find = 1;
			/* if the folder isn't empty we put a certain value
			in the find variable */
			} else {
				*find = -2;
			}
			return;
		}

		/* if we find a file with the same name we also put a
		certain value in the find variable */
		if (strcmp(childs_info->name, folderName) == 0 &&
			childs_info->type == FILE_NODE) {
			*find = -1;
			return;
		}

		/* if we find a folder we go and search again */
		if (childs_info->type == FOLDER_NODE) {
			search_folder(childs_info, folderName, find);
		}

		child = child->next;
	}
}

/* function that wants to delete a folder */
void rmdir(TreeNode* currentNode, char* folderName)
{
	/* based on the value of find we delete or print certain messages */
	int find = 0;
	search_folder(currentNode, folderName, &find);

	if (find == 0) {
		printf("rmdir: failed to remove '%s': No such file or directory\n",
			folderName);
	}

	if (find == -1) {
		printf("rmdir: failed to remove '%s': Not a directory\n",
			folderName);
	}

	if (find == -2) {
		printf("rmdir: failed to remove '%s': Directory not empty\n",
			folderName);
	}
}

/* recursive function that deletes a folder and all the data contained by it
or a file */
void rmrec(TreeNode* currentNode, char* resourceName)
{
	/* getting the data that has to be deleted */
	TreeNode *childs_info = find_folder(currentNode, resourceName);

	/* verifying if it exits */
	if (childs_info == NULL) {
		printf("rmrec: failed to remove '%s': No such file or directory\n",
			resourceName);
		return;
	}

	/* if it's a folder that has to be deleted */
	if (childs_info->type == FOLDER_NODE) {
		/* if it doesn't have content */
		if (childs_info->content == NULL) {
			delete_empty_folder(currentNode, childs_info->name);

		/* if it has content we have to delete it too */
		} else {
			List *children = ((FolderContent *)childs_info->content)->children;
			ListNode *child = children->head;

			/* going through the children and checking which one is a folder
			and which one is a file */
			while (child != NULL) {
				/* if it's a folder we use the same function for it */
				if (child->info->type == FOLDER_NODE) {
					rmrec(childs_info, child->info->name);
					/* otherwise we only delete the file */
				} else {
					delete_the_file(childs_info, child->info->name);
				}

				ListNode *aux = child;

				child = child->next;
				free(aux);
			}
			/* after deleting the content we delete the empty folder
			remained */
			delete_empty_folder(childs_info->parent, childs_info->name);
		}
	} else {
		delete_the_file(childs_info->parent, childs_info->name);
	}
}

/* function that eliberates all the memory used by the program */
void freeTree(FileTree fileTree)
{
	TreeNode *root = fileTree.root;

	/* going through roots content until it's all freed */
	if (root->content != NULL) {
		/* getting the list of its children and the first child of it */
		List *children = ((FolderContent *)root->content)->children;
		ListNode *child = children->head;

		/* going through all the children the root has */
		while (child != NULL) {
			/* recursive deleting and freeing all the memory for the child */
			rmrec(root, child->info->name);
			ListNode *aux = child;

			child = child->next;
			/* also freeing the memory for the structure of the child itself */
			free(aux);
		}
	}

	free(root->name);
	free(root);
}

