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
#define Manager		"manager"					//user name of the manger
#define Password	"123456"					//password of the manger
//Menu
void studentMenu()
{
	printf("====================You're in the student area====================\n");
	char ch;
	printf("1.Search a book\n2.List all the books\n3.Borrow a book\n4.Return a book\n5.Personal library information\n6.Save and exit\n");
	for (;;)
	{
		ch = getch();
		switch (ch)
		{
		case '1':
			search_a_book();
			break;
		case '2':
			search_book();
			break;
		case '3':
			borrowbook();
			break;
		case '4':
			returnbook();
			break;
		case '5':	
			search_borrow(curr_user, NULL);
			break;
		case '6':
			printf("====================Leave the student area====================\n");
			return;
		default:
			continue;
		}
		printf("1.Search a book\n2.List all the books\n3.Borrow a book\n4.Return a book\n5.Personal library information\n6.Save and exit\n");
	}
}
void ManagerMenu()
{
	printf("============You're in the manager area==========\n");
	char ch;
	printf("1.Add a book\n2.Remove a book\n3.Change information of a book\n4.List all the books\n5.List all the information of users\n6.Exit\n");
	for (;;)
	{
		ch = getch();	
		switch (ch)
		{
		case '1':
			addbook();
			break;
		case '2':
			removebook();
			break;
		case '3':
			changebook();
			break;
		case '4':
			search_book();
			break;
		case '5':
			search_user();
			break;
		case '6':
			printf("============Leave the manager area==========\n");
			return;
		default:
			continue;
		}
		printf("1.Add a book\n2.Remove a book\n3.Change information of a book\n4.List all the books\n5.List all the information of users\n6.Exit\n");
	}
}
void mainMeun()
{
	libopen();
	printf("==========================Welcome to the library information system!==========================\n");
	printf("==============================Please choose what you want to do!==============================\n");
	char ch;
	printf("1.Login\n2.Register\n3.Save data and exit\n");
	for (;;)
	{
		ch = getch();
		switch (ch)
		{
		case '1':
			curr_user = login_user();
			if (curr_user != NULL)
			{
				if (libstrcmp(curr_user->name, Manager))
				{
					ManagerMenu();
				}
				else
				{
					studentMenu();
				}
			}
			break;
		case '2':
			register_user();
			break;
		case '3':
			libexit();
			return;
		default:
			continue;
		}
		printf("1.Login\n2.Register\n3.Save data and exit\n");
	}
}


