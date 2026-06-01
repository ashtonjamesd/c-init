#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>

#include "cinit.h"

int help() {
    printf("usage: cinit <name> [path]\n");
    printf("  - name: the name of your project\n");
    printf("\n");

    return 0;
}


int main(int argc, char *argv[]) {
    // Project p = cinit_project();
    // cinit_build_with(&p, GCC);
    // cinit_optimize_with(&p, GCC_O3);

    // cinit_use_directory(&p, "src");
    // cinit_build(&p);

    if (argc < 2) {
        fprintf(stderr, "usage: cinit <name>\n");
        return 1;
    }

    bool quiet = false;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--quiet") == 0) {
            quiet = true;
        }

        if (strcmp(argv[i], "help") == 0) return help();
        if (strcmp(argv[i], "--help") == 0) return help();
        if (strcmp(argv[i], "-h") == 0) return help();
    }

    ProjectScaffolder ps = {
        .quiet = quiet,
    };

    char *name = argv[1];

    #define SRC "src"
    #define BUILD "build"
    #define TEST "test"
    #define LIB "lib"

    #define MAIN_C "main.c"
    #define BUILD_C "build.c"
    #define CINIT_C "cinit.h"

    printf("scaffolding project..\n\n");

    if (!create_project_directory(SRC, ps)) return 1;
    if (!create_project_directory(BUILD, ps)) return 1;
    if (!create_project_directory(TEST, ps)) return 1;
    if (!create_project_directory(LIB, ps)) return 1;

    if (!create_project_file(SRC "/" MAIN_C)) return 1;
    if (!setup_main_c(SRC "/" MAIN_C)) return 1;

    if (!create_project_file(TEST "/" MAIN_C)) return 1;
    if (!setup_main_c(TEST "/" MAIN_C)) return 1;

    if (!create_project_file(BUILD_C)) return 1;
    if (!setup_build_c(BUILD_C)) return 1;

    if (!create_project_file(LIB "/" CINIT_C)) return 1;
    if (!setup_cinit_c(LIB "/" CINIT_C)) return 1;
    
    printf("\ncompleted c project scaffold!\n\n");
    
    return 0;
}