#include "ls.h"

extern int reverse_sort;

int cmp_lexicographical(const void *a, const void *b) {
    FileInfo *fa = (FileInfo *)a;
    FileInfo *fb = (FileInfo *)b;
    int res = strcmp(fa->name, fb->name);
    return reverse_sort ? -res : res;
}

int cmp_time(const void *a, const void *b) {
    FileInfo *fa = (FileInfo *)a;
    FileInfo *fb = (FileInfo *)b;
    int res;
    if (fa->st.st_mtime < fb->st.st_mtime) res = 1;
    else if (fa->st.st_mtime > fb->st.st_mtime) res = -1;
    else res = strcmp(fa->name, fb->name);
    return reverse_sort ? -res : res;
}

int cmp_size(const void *a, const void *b) {
    FileInfo *fa = (FileInfo *)a;
    FileInfo *fb = (FileInfo *)b;
    int res;
    if (fa->st.st_size < fb->st.st_size) res = 1;
    else if (fa->st.st_size > fb->st.st_size) res = -1;
    else res = strcmp(fa->name, fb->name);
    return reverse_sort ? -res : res;
}
