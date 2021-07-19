#define FUSE_USE_VERSION 26
#import<fuse.h>
#define C char*
C y="pat";o(C p,struct stat *s){memset(s,0,8);s->st_mode=1<<(strcmp(p,"/")?15:14)|777;s->st_size=(long)1<<62;}$(C j,C b,fuse_fill_dir_t f){f(b,y,0,0);}J(){}G(C p,C b,size_t l){for(int i=0;i<l;)memcpy(b+i,y,3),i+=3;b[l-1]='\0';return l;}struct fuse_operations k={.getattr=o,.open=J,.read=G,.readdir=$}; main(c,v)char**v;{fuse_main(c,v,&k,0);}
