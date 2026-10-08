#include "ls.h"

void print_long_format(FileInfo *fi, LsOptions *opts) {
    // 1. Quyền truy cập cơ bản
    printf((S_ISDIR(fi->st.st_mode)) ? "d" : "-");
    printf((fi->st.st_mode & S_IRUSR) ? "r" : "-");
    printf((fi->st.st_mode & S_IWUSR) ? "w" : "-");
    printf((fi->st.st_mode & S_IXUSR) ? "x" : "-");
    printf((fi->st.st_mode & S_IRGRP) ? "r" : "-");
    printf((fi->st.st_mode & S_IWGRP) ? "w" : "-");
    printf((fi->st.st_mode & S_IXGRP) ? "x" : "-");
    printf((fi->st.st_mode & S_IROTH) ? "r" : "-");
    printf((fi->st.st_mode & S_IWOTH) ? "w" : "-");
    printf((fi->st.st_mode & S_IXOTH) ? "x" : "-");

    // 2. Số lượng links
	printf(" %lu", (unsigned long)fi->st.st_nlink);
    // 3. User & Group
    if (opts->n) {
        printf(" %u %u", fi->st.st_uid, fi->st.st_gid);
    } else {
        struct passwd *pw = getpwuid(fi->st.st_uid);
        struct group  *gr = getgrgid(fi->st.st_gid);
        printf(" %s %s", pw ? pw->pw_name : "unknown", gr ? gr->gr_name : "unknown");
    }

    // 4. Size & Time & Name
    printf(" %5lld", (long long)fi->st.st_size);

    char time_buf[64];
    struct tm *tm_info = localtime(&fi->st.st_mtime);
    strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", tm_info);

    printf(" %s %s\n", time_buf, fi->name);
}

void print_normal(FileInfo *fi, LsOptions *opts) {
    // Tránh lỗi cảnh báo compiler cho opts chưa dùng tới
    (void)opts; 
    printf("%s\n", fi->name);
}
