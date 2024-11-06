#include <stdio.h>
#include <string.h>

void process_cmd(const char* cmd) {
    // Fix the command comparison logic
    if (strcmp(cmd, "clear") == 0) {
        Reset();
    } 
    else if (strcmp(cmd, "help") == 0) {
        _term_help();
    }
    else if (strcmp(cmd, "version") == 0 || strcmp(cmd, "ver") == 0) {
        printf("CeanOS version: 0.0.3-alpha\n");
    }
    else if (strcmp(cmd, "fetch") == 0) {
        _get_sysinfo();
    }
    else if (strcmp(cmd, "exit") == 0) {
        halt();
    }
    else if (strcmp(cmd, "shutdown") == 0) {
        printf("shutting down...\n");
        printf("not actually doing that\n");
    }
    else if (strcmp(cmd, "compdate") == 0) {
        printf("date: " __DATE__ "\nat: " __TIME__);
    }
    else if (strcmp(cmd, "dumpreg") == 0) {
        dump_registers();
    }
    else if (strcmp(cmd, "testpanic") == 0) {
        trigger_test_panic();
    }
    else {
        printf("%s: command not found\n", cmd);
    }
} 