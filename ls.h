#ifndef LS_H
#define LS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

// Struct lưu trữ cờ (flags) để dễ dàng truyền qua các hàm
typedef struct {
    int l, a, A, R, t, S, r, n, i, s; // Thêm các cờ khác tùy ý
} LsOptions;

// Struct lưu trữ thông tin của một tệp/thư mục
typedef struct {
    char *name;
    char *path;
    struct stat st;
} FileInfo;

// Khai báo các hàm từ cmp.c
int cmp_lexicographical(const void *a, const void *b);
int cmp_time(const void *a, const void *b);
int cmp_size(const void *a, const void *b);

// Khai báo các hàm từ print.c
void print_long_format(FileInfo *fi, LsOptions *opts);
void print_normal(FileInfo *fi, LsOptions *opts);

#endif
