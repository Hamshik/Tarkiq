#include "Scanner.h"
#include <stdint.h>

extern bool isError;

char *  Scanner::unescapeStr(const char *in, size_t in_len, size_t *out_len, int *err_index, const char **err_msg) {
    if (err_index) *err_index = -1;
    if (err_msg) *err_msg = "invalid escape sequence";
    if (out_len) *out_len = 0;
    if (!in) return NULL;

    size_t cap = in_len + 1;
    char *out = (char *)calloc(1,cap);
    if (!out) return NULL;

    size_t j = 0;
    for (size_t i = 0; i < in_len; i++) {
        unsigned char c = (unsigned char)in[i];
        if (c != '\\') {
            if (j + 1 >= cap) {
                cap = cap * 2 + 8;
                char *p = (char *)realloc(out, cap);
                if (!p) { free(out); return NULL; }
                out = p;
            }
            out[j++] = (char)c;
            continue;
        }

        if (i + 1 >= in_len) {
            if (err_index) *err_index = (int)i;
            if (err_msg) *err_msg = "trailing backslash";
            free(out);
            return NULL;
        }

        unsigned char e = (unsigned char)in[++i];
        switch (e) {
            case 'n': out[j++] = '\n'; break;
            case 't': out[j++] = '\t'; break;
            case 'r': out[j++] = '\r'; break;
            case '0': out[j++] = '\0'; break;
            case '\\': out[j++] = '\\'; break;
            case '"': out[j++] = '"'; break;
            case '\'': out[j++] = '\''; break;
            case 'b': out[j++] = '\b'; break;
            case 'f': out[j++] = '\f'; break;
            case 'v': out[j++] = '\v'; break;
            case 'a': out[j++] = '\a'; break;

            case 'x': {
                if (i + 1 >= in_len) {
                    if (err_index) *err_index = (int)(i - 1);
                    if (err_msg) *err_msg = "expected hex digits after \\x";
                    free(out);
                    return NULL;
                }
                int h1 = convetHexToInt((unsigned char)in[i + 1]);
                if (h1 < 0) {
                    if (err_index) *err_index = (int)(i - 1);
                    if (err_msg) *err_msg = "expected hex digits after \\x";
                    free(out);
                    return NULL;
                }
                int v = h1;
                i += 1;
                if (i + 1 < in_len) {
                    int h2 = convetHexToInt((unsigned char)in[i + 1]);
                    if (h2 >= 0) {
                        v = (v << 4) | h2;
                        i += 1;
                    }
                }
                if (v == 0) {
                    if (err_index) *err_index = (int)(i - 1);
                    if (err_msg) *err_msg = "NUL in string is not supported";
                    free(out);
                    return NULL;
                }
                out[j++] = (char)(unsigned char)v;
                break;
            }

            default:
                if (err_index) *err_index = (int)(i - 1);
                if (err_msg) *err_msg = "unknown escape sequence";
                free(out);
                return NULL;
        }

        if (j + 1 >= cap) {
            cap = cap * 2 + 8;
            char *p = (char *)realloc(out, cap);
            if (!p) { free(out); return NULL; }
            out = p;
        }
    }

    out[j] = '\0';
    if (out_len) *out_len = j;
    return out;
}