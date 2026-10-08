#include "ls.h"

int reverse_sort = 0;

int main(int argc, char *argv[]) {
    LsOptions opts = {0};
    int opt;

    // Phân tích tham số đầu vào[cite: 1]
    while ((opt = getopt(argc, argv, "AacdFfhiklnqRrSstuw")) != -1) {
        switch (opt) {
            case 'l': opts.l = 1; break;
            case 'a': opts.a = 1; break;
            case 't': opts.t = 1; break;
            case 'r': opts.r = 1; reverse_sort = 1; break;
            case 'S': opts.S = 1; break;
            case 'n': opts.n = 1; opts.l = 1; break;
        }
    }

    const char *dir_path = (optind == argc) ? "." : argv[optind];
    DIR *dir = opendir(dir_path);
    if (!dir) {
        perror("opendir");
        return 1;
    }

    int capacity = 10;
    int count = 0;
    FileInfo *files = malloc(capacity * sizeof(FileInfo));
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (!opts.a && entry->d_name[0] == '.') continue; // Bỏ qua file ẩn nếu không có -a[cite: 1]

        if (count >= capacity) {
            capacity *= 2;
            files = realloc(files, capacity * sizeof(FileInfo));
        }

        files[count].name = strdup(entry->d_name);
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);
        files[count].path = strdup(full_path);
        lstat(full_path, &files[count].st);
        count++;
    }
    closedir(dir);

    // Sắp xếp
    if (opts.S) {
        qsort(files, count, sizeof(FileInfo), cmp_size); // Sắp xếp theo kích thước[cite: 1]
    } else if (opts.t) {
        qsort(files, count, sizeof(FileInfo), cmp_time); // Sắp xếp theo thời gian
    } else {
        qsort(files, count, sizeof(FileInfo), cmp_lexicographical); // Mặc định sắp xếp theo tên[cite: 1]
    }

    // In kết quả
    for (int i = 0; i < count; i++) {
        if (opts.l) {
            print_long_format(&files[i], &opts); // In định dạng dài[cite: 1, 2]
        } else {
            print_normal(&files[i], &opts);
        }
        free(files[i].name);
        free(files[i].path);
    }
    free(files);
    return 0;
}
