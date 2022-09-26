// Copyright Sindrilaru Catalina-Maria & Arghir Monica-Andreea, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "create.h"
#include "delete.h"
#include "cd_copy_move.h"

/* function that moves the current node to the given node */
TreeNode *cd_one_arg(TreeNode *currentNode, char *p)
{
	/* checking if the given node it's a symbol for the parent
	of the current node */
	if (strcmp(p, "..") == 0) {
		return currentNode->parent;
	}

	/* verifying the validity of the node */
	if (currentNode == NULL || currentNode->content == NULL) {
		return NULL;
	}

	/* going through the children and returning the node we want */
	List *children = ((FolderContent *)currentNode->content)->children;

	ListNode *child = children->head;

	while (child != NULL) {
		TreeNode *childs_info = child->info;

		if (strcmp(childs_info->name, p) == 0) {
			return childs_info;
		}

		child = child->next;
	}

	return NULL;
}

/* function that moves the current node we're in, to the node
we want by a given path */
TreeNode* cd(TreeNode* currentNode, char* path)
{
	/* saving the initial node */
	TreeNode *initial_node = currentNode;

	/* making a copy of the path because we will modify the string */
	char *copy_path = malloc(strlen(path) + 1);
	DIE(!copy_path, "Malloc failed\n");
	memcpy(copy_path, path, strlen(path) + 1);

	/* getting the folders of the path one by one using
	the previous function */
	char *p = strtok(path, "/ ");

	while (p) {
		currentNode = cd_one_arg(currentNode, p);

		if (currentNode == NULL) {
			printf("cd: no such file or directory: %s\n", copy_path);

			currentNode = initial_node;

			free(copy_path);
			return currentNode;
		}

		p = strtok(NULL, "/ ");
	}

	/* eliberating the memory we don't need and returning the node we wanted */
	free(copy_path);

	return currentNode;
}



/* function that copies a file from its source to a given destination */
void cp(TreeNode* currentNode, char* source, char* destination)
{
	/* saving the initial node to not lose it and making
	a copy of the source */
    TreeNode *initial_node = currentNode;

	char *copy_source = malloc(strlen(source) + 1);
	DIE(!copy_source, "Malloc failed\n");
	memcpy(copy_source, source, strlen(source) + 1);

	/* getting the file we want to copy */
	char *p = strtok(source, "/ ");

	while (p) {
		currentNode = cd_one_arg(currentNode, p);

		p = strtok(NULL, "/ ");
	}

	/* if the source is not a file we free the used memory,
	reset the current folder and exit the program */
	if (currentNode->type == FOLDER_NODE) {
		printf("cp: -r not specified; omitting directory '%s'\n", copy_source);

		currentNode = initial_node;

		free(copy_source);
		return;
	}

	/* copying the file name and its content */
	char *new_file_name = malloc(strlen(currentNode->name) + 1);
	DIE(!new_file_name, "Malloc failed\n");
	memcpy(new_file_name, currentNode->name, strlen(currentNode->name) + 1);

	char *new_file_content;

	/* if there is no content we only initialize the new file content
	with a string terminator */
	if (currentNode->content != NULL) {
		new_file_content =
			malloc(strlen(((FileContent *)currentNode->content)->text) + 1);
		DIE(!new_file_content, "Malloc failed\n");
		memcpy(new_file_content, ((FileContent *)currentNode->content)->text,
			strlen(((FileContent *)currentNode->content)->text) + 1);

	} else {
		new_file_content = strdup("\0");
		DIE(!new_file_content, "Malloc failed\n");
	}

	/* setting the current node to the initial one to be able to get
	the destination */ 
	currentNode = initial_node;

	char *copy_destination = malloc(strlen(destination) + 1);
	DIE(!copy_destination, "Malloc failed\n");
	memcpy(copy_destination, destination, strlen(destination) + 1);

	p = strtok(destination, "/ ");

	while (p) {
		currentNode = cd_one_arg(currentNode, p);

		/* if the destination doesn't exist we free all the use memory
		before existing the program */
		if (currentNode == NULL) {
			printf("cp: failed to access '%s': Not a directory\n",
				copy_destination);

			currentNode = initial_node;

			free(new_file_content);
			free(new_file_name);
			free(copy_source);
			free(copy_destination);

			return;
		}

		p = strtok(NULL, "/ ");
	}

	/* if the destination is a folder we use the touch function
	to copy the data */
	if (currentNode->type == FOLDER_NODE) {
		touch(currentNode, new_file_name, new_file_content);

	/* if the destination is a file and the content exists we free the
	content it has and put the new content in it */
	} else if (currentNode->type == FILE_NODE &&
				currentNode->content != NULL) {
		free(((FileContent *)currentNode->content)->text);

		((FileContent *)currentNode->content)->text =
			malloc(strlen(new_file_content) + 1);
		DIE(!((FileContent *)currentNode->content)->text, "Malloc failed\n");
		memcpy(((FileContent *)currentNode->content)->text, new_file_content,
			strlen(new_file_content) + 1);

		free(new_file_content);
		free(new_file_name);
	}

	currentNode = initial_node;

	free(copy_source);
	free(copy_destination);
}


/* function that moves a file or a folder (with all it's data)
to a given destination */
void mv(TreeNode* currentNode, char* source, char* destination)
{
	/* saving the initial node to not lose it and making
	a copy of the destination */
    TreeNode *initial_node = currentNode;

	char *copy_destination = malloc(strlen(destination) + 1);
	DIE(!copy_destination, "Malloc failed\n");
	memcpy(copy_destination, destination, strlen(destination) + 1);

	/* getting the destination */
	char *p = strtok(destination, "/ ");

	while (p) {
		currentNode = cd_one_arg(currentNode, p);

		if (currentNode == NULL) {
			printf("mv: failed to access '%s': Not a directory\n",
				copy_destination);

			currentNode = initial_node;

			free(copy_destination);

			return;
		}

		p = strtok(NULL, "/ ");
	}

	/* getting the source */
	TreeNode *source_node = initial_node;

	p = strtok(source, "/ ");

	while (p) {
		source_node = cd_one_arg(source_node, p);
		p = strtok(NULL, "/ ");
	}

	/* if the destination is a file we changed its content
	with the one from the source */
	if (currentNode->type == FILE_NODE) {
		free(((FileContent *)currentNode->content)->text);

		char *new_file_content =
			malloc(strlen(((FileContent *)source_node->content)->text) + 1);
		DIE(!new_file_content, "Malloc failed\n");
		memcpy(new_file_content, ((FileContent *)source_node->content)->text,
			strlen(((FileContent *)source_node->content)->text) + 1);

		((FileContent *)currentNode->content)->text =
			malloc(strlen(new_file_content) + 1);
		DIE(!((FileContent *)currentNode->content)->text, "Malloc failed\n");
		memcpy(((FileContent *)currentNode->content)->text, new_file_content,
			strlen(new_file_content) + 1);

		/* going through the sources parent children and deletes the source file */
		List *children = ((FolderContent *)source_node->parent->content)->children;
		ListNode *child = children->head;

		while (child != NULL && strcmp(child->info->name, source_node->name) != 0) {
			child = child->next;
		}

		delete_the_file(source_node->parent, source_node->name);
		free(child);

		/* resetting the current folder and eliberating all the memory used */
		currentNode = initial_node;

		free(new_file_content);
		free(copy_destination);

		return;
	}

	/* if the destination isn't a file we create the child in it */
	create_new_child(source_node, currentNode);

	List *children = ((FolderContent *)initial_node->content)->children;
	ListNode *child = children->head;

	/* recreating the sources connections to delete the data */
	if (strcmp(child->info->name, source_node->name) == 0) {
		children->head = children->head->next;

		currentNode = initial_node;

		free(child);
		free(copy_destination);

		return;
	}

	ListNode *prev;

	while (child != NULL && strcmp(child->info->name,
		source_node->name) != 0) {
		prev = child;
		child = child->next;
	}

	prev->next = child->next;
	free(child);

	currentNode = initial_node;

	free(copy_destination);
}
