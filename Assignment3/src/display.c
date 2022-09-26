// Copyright Sindrilaru Catalina-Maria & Arghir Monica-Andreea, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "cd_copy_move.h"
#include "search.h"
#include "display.h"


/* function that displays what is in the given node or
in the folder we're in */
void ls(TreeNode* currentNode, char* arg)
{
	List *children;

	/* treating the case in which we're not given a specific node and we have
	to display the content of the folder we're in */
	if (arg[0] == '\0' || strcmp(arg, currentNode->name) == 0) {
		/* verifying if the data we're given it's valid */
		if (currentNode == NULL || currentNode->content == NULL) {
			return;
		}

		children = ((FolderContent *)currentNode->content)->children;

		/* going through the children it has and displaying them all */
		ListNode *child = children->head;

		while (child != NULL) {
			TreeNode *childs_info = child->info;

			printf("%s\n", childs_info->name);

			child = child->next;
		}

		return;
	}

	/* copying the node we're in to know what to come back to */
	TreeNode *initial_node = currentNode;

	/* setting the value to 0 to know if we've found a file or not */
	int writted = 0;

	currentNode = search_node_recursive(currentNode, arg, &writted);

	/* if we've found a file we exit the function and reset the current node */
	if (writted == 1) {
		currentNode = initial_node;
		return;
	}

	/* if we didn't find nothing, we print a specific message
	and reset the current node */
	if (currentNode == NULL || currentNode->content == NULL) {
		printf("ls: cannot access '%s': No such file or directory\n", arg);
		currentNode = initial_node;
		return;
	}

	children = ((FolderContent *)currentNode->content)->children;

	/* displaying the children */
	ListNode *child = children->head;

	while (child != NULL) {
		TreeNode *childs_info = child->info;

		printf("%s\n", childs_info->name);

		child = child->next;
	}

	currentNode = initial_node;
}

/* function that shows where we're at in the file system */
void pwd(TreeNode* treeNode)
{
	if (strcmp(treeNode->name, "root") == 0) {
		printf("root\n");
		return;
	}

	/* allocating memory for a number of strings */
	char **strings = malloc(MAX_NUMBER_OF_STRINGS * sizeof(char *));
	DIE(!strings, "Malloc failed\n");

	for (int i = 0; i < MAX_NUMBER_OF_STRINGS; i++) {
		strings[i] = malloc(MAX_LENGTH_OF_STRING * sizeof(char));
		DIE(!strings[i], "Malloc failed\n");
	}

	/* counter for the number of folders we're going through */
	int cnt = 0;

	/* going through the given node until we reach the root and
	putting them in the strings array */
	while (strcmp(treeNode->name, "root") != 0) {
		memcpy(strings[cnt], treeNode->name, strlen(treeNode->name) + 1);

		cnt += 1;

		treeNode = treeNode->parent;
	}

	/* printing the path */
	printf("root");

	for (int i = cnt - 1; i >= 0; i--) {
		printf("/%s", strings[i]);
	}

	printf("\n");

	/* eliberating the memory used for the strings */
	for (int i = 0; i < MAX_NUMBER_OF_STRINGS; i++) {
		free(strings[i]);
	}

	free(strings);
}

/* function that prints the whole data contained by the current folder */
void display_from_current_folder(TreeNode *currentNode, int *nr_dir,
									int *nr_files, int level)
{
	if (currentNode == NULL || currentNode->content == NULL) {
		return;
	}

	List *children = ((FolderContent *)currentNode->content)->children;

	ListNode *child = children->head;

	while (child != NULL) {
		TreeNode *childs_info = child->info;

		/* if the child is a folder */
		if (childs_info->type == FOLDER_NODE) {
			/* depending on which level the child is on, we print a
			certain number of spaces */
			for (int i = 0; i < level; i++) {
				printf("    ");
			}

			printf("%s\n", childs_info->name);

			*nr_dir += 1;

			/* recursive call of the function for the data of the child */
			display_from_current_folder(childs_info, nr_dir,
										nr_files, level + 1);

		} else {
			for (int i = 0; i < level; i++){
				printf("    ");
			}

			printf("%s\n", childs_info->name);

			*nr_files += 1;
		}

		child = child->next;
	}
}

/* function that displays a hierarchy of the file system of the current folder
or of the given folder */
void tree(TreeNode* currentNode, char* arg)
{
	/* keeping the number of directories, the files and the level */
	int nr_dir = 0, nr_files = 0, level = 0;

	/* if there isn't an argument given to the function */
	if (arg[0] == '\0') {
		display_from_current_folder(currentNode, &nr_dir, &nr_files, level);

		printf("%d directories, %d files\n", nr_dir, nr_files);

		return;
	}

	TreeNode *initial_node = currentNode;

	char *copy_path = malloc(strlen(arg) + 1);
	DIE(!copy_path, "Malloc failed\n");
	memcpy(copy_path, arg, strlen(arg) + 1);

	char *p = strtok(arg, "/ ");

	while (p) {
		currentNode = cd_one_arg(currentNode, p);

		if (currentNode == NULL || currentNode->type == FILE_NODE) {
			printf("%s [error opening dir]\n\n", copy_path);
			printf("%d directories, %d files\n", nr_dir, nr_files);

			currentNode = initial_node;

			free(copy_path);
			return;
		}

		p = strtok(NULL, "/ ");
	}

	/* after we changed the folder we are in */
	display_from_current_folder(currentNode, &nr_dir, &nr_files, level);
	printf("%d directories, %d files\n", nr_dir, nr_files);

	currentNode = initial_node;

	free(copy_path);
}

