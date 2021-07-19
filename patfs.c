#define FUSE_USE_VERSION 26

#include <assert.h>
#include <errno.h>
#include <fuse.h>
#include <limits.h>
#include <string.h>

static int getattr_callback(const char *path, struct stat *stbuf) {
  memset(stbuf, 0, sizeof(struct stat));

  if (strcmp(path, "/") == 0) {
    stbuf->st_mode = S_IFDIR | 0755;
    stbuf->st_nlink = 2;
    return 0;
  }

  stbuf->st_mode = S_IFREG | 0777;
  stbuf->st_nlink = 1;
  stbuf->st_size = LONG_MAX;
  return 0;
}

static int readdir_callback(const char *path, void *buf, fuse_fill_dir_t filler,
                            off_t offset, struct fuse_file_info *fi) {
  (void)offset;
  (void)fi;

  filler(buf, ".", NULL, 0);
  filler(buf, "..", NULL, 0);
  filler(buf, "pat", NULL, 0);

  return 0;
}

static int open_callback(const char *path, struct fuse_file_info *fi) {
  return 0;
}

static int read_callback(const char *path, char *buf, size_t size, off_t offset,
                         struct fuse_file_info *fi) {

  const char *pat = "pat";

  int i = 0;
  while (i < size) {
    memcpy(buf + i, pat, 3);
    i += 3;
  }
  buf[size - 1] = '\0';
  return size;
}

static struct fuse_operations fuse_pat_operations = {
    .getattr = getattr_callback,
    .open = open_callback,
    .read = read_callback,
    .readdir = readdir_callback,
};

int main(int argc, char *argv[]) {
  return fuse_main(argc, argv, &fuse_pat_operations, NULL);
}
