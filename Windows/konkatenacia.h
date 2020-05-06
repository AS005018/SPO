#pragma once
#ifdef KONKATENACIA_EXPORTS
#define KONKATENACIA_API __declspec(dllexport)
#else
#define KONKATENACIA_API __declspec(dllimport)
#endif

extern "C" KONKATENACIA_API void fnkonkatenacia(char str[], int n);