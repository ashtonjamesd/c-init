#include <comet.h>

Project comet_build_project(void) {
   Project p = comet_project();

   comet_build_with(&p, GCC);
   
   comet_use_directory(&p, "src");
   comet_build_exe_called(&p, "build/exe");

   comet_cflags(&p, "-Wall -Wextra -Werror");
   comet_standard(&p, C99);
   
   return p;
}

int comet_fetch(Project *p) {
   if (!comet_fetch_header("ashtonjamesd/ctest", "ctest.h")) return 1;
   return 0;
}

int main(int argc, char *argv[]) {
   if (argc < 2) return 1;
   
   char *arg = argv[1];
   Project p = comet_build_project();
   if (strcmp(arg, "build") == 0) {
       return comet_build(&p);
   } else if (strcmp(arg, "fetch") == 0) {
       return comet_fetch(&p);
   }
   
   return 0;
}
