#include "../lib/claim.h"
#include "../src/comet.h"

static Project p;

describe("comet tests")

before(setup_project) {
   p = comet_project();
}

should(set_exe_name) {
   comet_build_exe_called(&p, "myapp");
   expect_eq(p.exe_name, "myapp");
}

should(set_compiler) {
   comet_build_with(&p, CLANG);
   expect(p.compiler == CLANG);
}

should(set_standard) {
   comet_standard(&p, C11);
   expect(p.standard == C11);

   comet_standard(&p, C99);
   expect(p.standard == C99);
}

should(set_cflags) {
   comet_cflags(&p, "-DDEBUG");
   expect_eq(p.cflags, "-DDEBUG");
}

should(set_warnings) {
   comet_warnings(&p, WARN_ALL | WARN_EXTRA);
   
   expect(p.warnings & WARN_ALL);
   expect(p.warnings & WARN_EXTRA);
   expect(!(p.warnings & WARN_ERROR));
}

should(grow_sources_on_overflow) {
   expect(p.srcs_capacity == 1);

   comet_add_source_file(&p, "a.c");
   comet_add_source_file(&p, "b.c");
   comet_add_source_file(&p, "c.c");

   expect(p.srcs_count == 3);
   expect(p.srcs_capacity >= 3);
}

should(add_source_file) {
   comet_add_source_file(&p, "src/main.c");

   expect(p.srcs_count == 1);
   expect_eq(p.srcs[0], "src/main.c");
}

should(create_project_with_defaults) {
   expect(p.compiler == GCC);
   expect(p.srcs_count == 0);
   expect(p.srcs_capacity == 1);
   expect_null(p.cflags);
   expect_eq(p.exe_name, "output");
   expect(p.command_count == 0);
}

static int dummy_cmd(Project *p) {
   (void)p;
   return 42;
}

static int another_cmd(Project *p) {
   (void)p;
   return 7;
}

should(register_single_command) {
   comet_command(&p, "build", dummy_cmd);

   expect(p.command_count == 1);
   expect_eq(p.commands[0].name, "build");
   expect(p.commands[0].func == dummy_cmd);
}

should(register_multiple_commands) {
   comet_command(&p, "build", dummy_cmd);
   comet_command(&p, "fetch", another_cmd);

   expect(p.command_count == 2);
   expect_eq(p.commands[0].name, "build");
   expect_eq(p.commands[1].name, "fetch");
   expect(p.commands[1].func == another_cmd);
}

should(run_matched_command) {
   comet_command(&p, "build", dummy_cmd);
   comet_command(&p, "fetch", another_cmd);

   char *argv1[] = {"comet", "build"};
   expect(comet_run(&p, 2, argv1) == 42);

   char *argv2[] = {"comet", "fetch"};
   expect(comet_run(&p, 2, argv2) == 7);
}

should(run_unknown_command_returns_error) {
   comet_command(&p, "build", dummy_cmd);

   char *argv[] = {"comet", "nope"};
   expect(comet_run(&p, 2, argv) == 1);
}

should(run_with_no_args_returns_error) {
   comet_command(&p, "build", dummy_cmd);

   char *argv[] = {"comet"};
   expect(comet_run(&p, 1, argv) == 1);
}

int main(void) {
   return test_results();
}
