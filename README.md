# comet

Build and run your C projects from C.

## Install

```
curl -fsSL https://raw.githubusercontent.com/ashtonjamesd/comet/main/install.sh | bash
```

## Quick start

```bash
comet init myapp
cd myapp

comet run
```

## Project structure

`comet init myapp` generates the following:

```
myapp/
├── build.c        # build configuration
├── src/
│   └── main.c     # entry point
├── test/
│   └── main.c     # test entry point
└── build/         # compiled output
```

## build.c

Every project has a configurable `build.c` that defines how it compiles.

```c
#include <comet.h>

int main(void) {
   Project p = comet_project();

   comet_build_with(&p, GCC);
   comet_use_directory(&p, "src");
   comet_build_exe_called(&p, "build/myapp");

   comet_optimize_with(&p, GCC_O2);
   comet_warnings(&p, WARN_ALL | WARN_EXTRA | WARN_PEDANTIC);
   comet_standard(&p, C17);

   comet_build(&p);
   return 0;
}
```

## Commands

```
comet init <name>    scaffold a new project
comet build         compile the project
comet run           build and run
comet clean         remove build artifacts
```

## License

MIT