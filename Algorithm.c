#include"Add.h"
#include"Borrow.h"
#include"Change.h"
#include"Login.h"
#include"Register.h"
#include"Remove.h"
#include"Return.h"
#include"Search.h"
#include"Menu.h"
#include"Algorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BookLen		sizeof(Book)
#define UserLen		sizeof(User)
#define Manager		"manager"					//user name of he manager 
#define Password	"123456"					//password of manager



//string comparison function
int libstrcmp(const char* str1, const char* str2)
{
	//if not, return 0
	int len = strlen(str1);
	if (len != strlen(str2))
	{
		return 0;
	}
	while (len--)    // Match from the last character
	{
		if (str1[len] != str2[len])
		{
			return 0;
		}
	}
	return 1;
}


//A function that prevents strings from getting too long
void libchecklen(char* str, int max_len)
{
	int len = strlen(str);
	if (len + 1 > max_len)
	{
		*(str + max_len) = '\0';
	}
}

//Load user data
void libgetuser()
{
	FILE* fd = fopen("user.txt", "r");//Read the file
	if (fd == NULL)
	{
		return;
	}
	int i = 0;//number of borrowing book
	User* work = huser;//working pointer
	User* user_new = NULL;
	while (!feof(fd))
	{
		i = 0;
		user_new = (User*)malloc(UserLen);
		memset(user_new, 0, UserLen);
		fscanf(fd, "%s%s", user_new->name, user_new->password);
		//Read the borrowing information 
		while (!feof(fd))
		{
			char* temp = (char*)malloc(bookId_max);//Allocate memory for book ID
			memset(temp, 0, bookId_max);
			fscanf(fd, "%s", temp);
			if (libstrcmp(temp, "****"))
			{
				free(temp);
				break;
			}
			else
			{
				user_new->borrow[i] = temp;
			}	
			i++;
		}
		if (*user_new->name == '\0' || *user_new->password == '\0')
		{
			free(user_new);
		}
		else
		{
			work->next = user_new;
			work = work->next;
		}
		
	}
	fclose(fd);
}

//Load book data
void libgetbook()
{
	FILE* fd = fopen("book.txt", "r");//Read the open file 
	if (fd == NULL)
	{
		return;
	}
	int i = 0;
	Book* work = hbook;
	Book* book_new = NULL;
	while (!feof(fd))
	{
		book_new = (Book*)malloc(BookLen);
		memset(book_new, 0, BookLen);
		fscanf(fd, "%s%s%s%d%f", book_new->name, book_new->author_name, book_new->BookId, &book_new->count, &book_new->version);
		//If the book information is empty, it means something is wrong. Release the node and start the next loop
		if (*book_new->name == '\0' || book_new->author_name == '\0' || book_new->BookId == '\0')
		{
			free(book_new);
		}
		//If nothing goes wrong, add it to the list
		else
		{
			work->next = book_new;
			work = work->next;
		}
	}
	fclose(fd);
}

//Write into user data
void libputuser(int is_change, User* user)
{
	FILE* fd;
	User* w = huser;
	int i = 0;
	if (is_change)
	{
		fd = fopen("user.txt", "w");
		while (w->next)
		{
			i = 0;
			w = w->next;
			fprintf(fd, "%s\n%s\n", w->name, w->password);
			while (i < borrow_max )
			{
				if(w->borrow[i] != NULL)
					fprintf(fd, "%s\n", w->borrow[i]);
				i++;
			}
			fprintf(fd, "%s\n", "****");
		}
	}
	else
	{
		fd = fopen("user.txt", "a+");
		if (user)
		{
			fprintf(fd, "%s\n%s\n", user->name, user->password);
			while (i < borrow_max && !feof(fd))
			{
				if (w->borrow[i] != NULL)
					fprintf(fd, "%s\n", w->borrow[i]);
				i++;
			}
			fprintf(fd, "%s\n", "****");
		}
	}
	fclose(fd);
}

//Write into book data
void libputbook(int is_del, Book* book)	//The first parameter indicates whether the book information has been changed or deleted
//If so, reload the entire file
//Otherwise, reload the file
{										
	FILE* fd;
	Book* w = hbook;
	if (is_del)
	{
		fd = fopen("book.txt", "w");
		while (w->next)
		{
			w = w->next;
			fprintf(fd, "%s\n%s\n%s\n%d\n%f\n", w->name, w->author_name, w->BookId, w->count, w->version);
		}
	}
	else
	{
		fd = fopen("book.txt", "a+");
		if (book)
		{
			fprintf(fd, "%s\n%s\n%s\n%d\n%f\n", book->name, book->author_name, book->BookId, book->count, book->version);
		}
	}
	fclose(fd);
}
//Gets an available lending slot for the current user
int libemptybox()
{
	int i;
	for (i = 0; i < borrow_max; i++)
	{
		if (curr_user->borrow[i] == NULL)
		{
			return i;
		}
	}
	return -1;
}

//Return the user pointer to the name
User* checkuser(const char* user_name)
{
	User* w = huser;
	while (w->next)
	{
		w = w->next;
		if (libstrcmp(user_name, w->name))
		{
			return w;
		}
	}
	return NULL;
}

//Add the new user to the linked list
void adduser(User* user)
{
	User* w = huser;
	while (w->next)
	{
		w = w->next;
	}
	w->next = user;
}
//Free the data
void libfreesource()
{
	Book* w_b = hbook;
	Book* t_b = hbook;
	User* w_u = huser;
	User* t_u = huser;
	int i;
	while (w_b->next)//Free the data of books
	{
		w_b = w_b->next;
		free(t_b);
		t_b = w_b;
	}
	free(w_b);
	while (w_u->next)//Free the data of users
	{
		for (i = 0; i < borrow_max; i++)
		{
			if (w_u->borrow[i] != NULL)
			{
				free(w_u->borrow[i]);
			}
		}
		w_u = w_u->next;
		free(t_u);
		t_u = w_u;
	}
	for (i = 0; i < borrow_max; i++)
	{
		if (w_u->borrow[i] != NULL)
		{
			free(w_u->borrow[i]);
		}
	}
	free(w_u);

}

//Open the system
void libopen()
{
	FILE* fd = fopen("user.txt", "r");
	if (fd == NULL)
		fd = fopen("user.txt", "w");
	fclose(fd);

	fd = fopen("book.txt", "r");
	if (fd == NULL)
		fd = fopen("book.txt", "w");
	fclose(fd);

	huser = (User*)malloc(UserLen);
	memset(huser, 0, UserLen);
	//Enter manager information into the header
	strcpy(huser->name, Manager);
	strcpy(huser->password, Password);
	hbook = (Book*)malloc(BookLen);
	memset(hbook, 0, BookLen);
	libgetuser();
	libgetbook();
}

//Exit the system
void libexit()
{
	libputbook(1, NULL);
	libputuser(1, NULL);
	libfreesource();
}

