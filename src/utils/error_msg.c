#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void log_msg(const char *msg) {
    printf("%s\n", msg);
}

void logf_msg(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    int n = vsnprintf(NULL, 0, fmt, ap);
    va_end(ap);

    if (n < 0) return;

    char *buf = malloc((size_t)n + 1);
    if (!buf) return;

    va_start(ap, fmt);
    vsnprintf(buf, (size_t)n + 1, fmt, ap);
    va_end(ap);

    log_msg(buf);
    free(buf);
}
