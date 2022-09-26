// Copyright Sindrilaru Catalina-Maria & Arghir Monica-Andreea, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "create.h"

char *strdup(char *arg)
{
	int length = strlen(arg);
	char *dup = malloc(length + 1);
	char *dup_offset;

	dup_offset = dup;
	while(*arg) {
		*dup_offset = *arg;
		dup_offset++;
		arg++;
	}

	*dup_offset = '\0';
	return(dup);
}

/* function that creates an empty list */
List *create_list()
{
	List *list = malloc(sizeof(List));
	DIE(!list, "Malloc failed\n");
	list->head = NULL;

	return list;
}

/* function that creates a FileTree structure  */
FileTree createFileTree(char* rootFolderName)
{
	FileTree file_tree;
	/* allocating memory for the root node */
	file_tree.root = malloc(sizeof(TreeNode));
	DIE(!file_tree.root, "Malloc failed\n");

	int length = strlen(rootFolderName);

	/* allocating memory for the name and setting it */
	file_tree.root->name = malloc(length + 1);
	DIE(!file_tree.root->name, "Malloc failed\n");

	memcpy(file_tree.root->name, rootFolderName, length + 1);

	/* setting the type to folder */
	file_tree.root->type = FOLDER_NODE;

	/* initializing the parent to NULL and its content until further changes*/
	file_tree.root->parent = NULL;
	file_tree.root->content = NULL;

	/* freeing the memory for the name that was allocated by strdup
	in the main function */
	free(rootFolderName);

	return file_tree;
}

/* function that creates a new folder in the folder we're in */
void mkdir(TreeNode* currentNode, char* folderName)
{
	/* if the folders content hasn't been created yet */
	if (currentNode->content == NULL) {
		currentNode->content = malloc(sizeof(FolderContent));
		DIE(!currentNode->content, "Malloc failed\n");

		((FolderContent *)currentNode->content)->children =
			create_list();
	}

	List *children = ((FolderContent *)currentNode->content)->children;

	ListNode *child = children->head;

	/* if the folder doesn't have any children we create the first one*/
	if (child == NULL) {
		/* allocating memory for the child and its info */
		children->head = malloc(sizeof(ListNode));
		DIE(!children->head, "Malloc failed\n");

		TreeNode *new_childs_info = malloc(sizeof(TreeNode));
		DIE(!new_childs_info, "Malloc failed\n");

		/* setting the characteristics of the childs info */
		new_childs_info->parent = currentNode;

		new_childs_info->name = malloc(strlen(folderName) + 1);
		DIE(!new_childs_info->name, "Malloc failed\n");
		memcpy(new_childs_info->name, folderName, strlen(folderName) + 1);

		new_childs_info->type = FOLDER_NODE;
		new_childs_info->content = NULL;

		children->head->info = new_childs_info;
		children->head->next = NULL;

		free(folderName);

		return;
	}

	/* if there are existing children already we go through them to see
	if there is one with the same name */
	while (child != NULL) {
		TreeNode *childs_info = child->info;

		if (strcmp(childs_info->name, folderName) == 0) {
			printf("mkdir: cannot create directory '%s': File exists\n",
				folderName);

			free(folderName);

			return;
		}

		child = child->next;
	}

	/* adding the new folder to the front of the list of children
	of the current folder */
	ListNode *new_folder = malloc(sizeof(ListNode));
	DIE(!new_folder, "Malloc failed\n");

	TreeNode *new_folders_info = malloc(sizeof(TreeNode));
	DIE(!new_folders_info, "Malloc failed\n");

	new_folders_info->parent = currentNode;

	new_folders_info->name = malloc(strlen(folderName) + 1);
	DIE(!new_folders_info->name, "Malloc failed\n");
	memcpy(new_folders_info->name, folderName, strlen(folderName) + 1);

	new_folders_info->type = FOLDER_NODE;
	new_folders_info->content = NULL;

	new_folder->info = new_folders_info;

	new_folder->next = children->head;
	children->head = new_folder;

	free(folderName);
}



/* function that creates a new file in the current folder */
void touch(TreeNode* currentNode, char* fileName, char* fileContent)
{
	/* if the current folder doesn't have content we alloc memory for it */
	if (currentNode->content == NULL) {
		currentNode->content = malloc(sizeof(FolderContent));
		DIE(!currentNode->content, "Malloc failed\n");

		((FolderContent *)currentNode->content)->children = create_list();
	}

	List *children = ((FolderContent *)currentNode->content)->children;
	ListNode *child = children->head;

	/* if there are no other children we have to create them */
	if (child == NULL) {
		children->head = malloc(sizeof(ListNode));
		DIE(!children->head, "Malloc failed\n");

		TreeNode *new_childs_info = malloc(sizeof(TreeNode));
		DIE(!new_childs_info, "Malloc failed\n");

		new_childs_info->parent = currentNode;

		new_childs_info->name = malloc(strlen(fileName) + 1);
		DIE(!new_childs_info->name, "Malloc failed\n");
		memcpy(new_childs_info->name, fileName, strlen(fileName) + 1);

		new_childs_info->type = FILE_NODE;
		new_childs_info->content = NULL;

		children->head->info = new_childs_info;

		/* copying the content of the file (if it's given) which is a string */
		if (fileContent[0] != '\0') {
			new_childs_info->content = malloc(sizeof(FileContent));
			DIE(!new_childs_info->content, "Malloc failed\n");

			((FileContent *)new_childs_info->content)->text =
				malloc(strlen(fileContent) + 1);
			DIE(!((FileContent *)new_childs_info->content)->text,
				"Malloc failed\n");
			memcpy(((FileContent *)new_childs_info->content)->text,
				fileContent, strlen(fileContent) + 1);
		}

		children->head->next = NULL;

		free(fileContent);
		free(fileName);

		return;
	}

	while (child != NULL) {
		TreeNode *childs_info = child->info;

		/* if there already is a file with the same name */
		if (strcmp(childs_info->name, fileName) == 0) {
			free(fileName);
			free(fileContent);

			return;
		}

		child = child->next;
	}

	ListNode *new_file = malloc(sizeof(ListNode));
	DIE(!new_file, "Malloc failed\n");

	TreeNode *new_files_info = malloc(sizeof(TreeNode));
	DIE(!new_files_info, "Malloc failed\n");

	new_files_info->parent = currentNode;

	new_files_info->name = malloc(strlen(fileName) + 1);
	DIE(!new_files_info->name, "Malloc failed\n");
	memcpy(new_files_info->name, fileName, strlen(fileName) + 1);

	new_files_info->type = FILE_NODE;

	new_file->info = new_files_info;
	new_files_info->content = NULL;

	new_file->next = children->head;
	children->head = new_file;

	if (fileContent[0] != '\0') {
		new_files_info->content = malloc(sizeof(FileContent));
		((FileContent *)new_files_info->content)->text =
			malloc(strlen(fileContent) + 1);
		DIE(!((FileContent *)new_files_info->content)->text,
				"Malloc failed\n");
		memcpy(((FileContent *)new_files_info->content)->text, fileContent,
			strlen(fileContent) + 1);
	}

	free(fileContent);
	free(fileName);
}

/* function that creates a new child in a given folder */
void create_new_child(TreeNode* new_child, TreeNode* new_parent)
{
	if (new_parent->content == NULL) {
		new_parent->content = malloc(sizeof(FolderContent));
		((FolderContent *)new_parent->content)->children =
			malloc(sizeof(List));
		DIE(!new_parent->content, "Malloc failed\n");

		((FolderContent *)new_parent->content)->children->head = NULL;
	}

	List *children = ((FolderContent *)new_parent->content)->children;
	ListNode *child = children->head;

	/* if there aren't any children we allocate memory and
	do the connections */
	if (child == NULL) {
		children->head = malloc(sizeof(ListNode));
		DIE(!children->head, "Malloc failed\n");

		children->head->info = new_child;
		children->head->next = NULL;

		new_child->parent = new_parent;

		return;
	}

	/* adding the node to the front of the list */
	ListNode *new_folder = malloc(sizeof(ListNode));
	DIE(!new_folder, "Malloc failed\n");

	new_folder->info = new_child;

	new_folder->next = children->head;
	children->head = new_folder;

	new_child->parent = new_parent;
}
