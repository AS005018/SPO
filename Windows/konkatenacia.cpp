#include "pch.h"
#include "framework.h"
#include "konkatenacia.h"
#include "cstring"
#include "iostream"
#pragma warning(disable : 4996).

void fnkonkatenacia(char str[], int n)
{
	char s[1000];
	strcpy(s, str);
	for (int i = 0; i < n; i++) {
		strcat(str, s);
	}
	std::cout << "Result: " << std::endl;
	std::cout << str;
}