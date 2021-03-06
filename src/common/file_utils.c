/**************************************************************************
 *
 * Copyright (c) 2020 Alexis Lopez Zubieta <contact@azubieta.net>
 *
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_utils.h"
#include "string_utils.h"
#include "string_list.h"

char** apprun_read_lines(FILE* fp) {
    char** result = NULL;
    if (fp) {
        unsigned result_capacity = 512;
        unsigned count = 0;
        result = calloc(result_capacity, sizeof(char*));

        char buffer[1024];
        while (fgets(buffer, 1024, fp) != NULL) {
            if (count == result_capacity) {
                result_capacity = result_capacity * 2;
                result = apprun_extend_string_array(result, result_capacity);
            }

            char* str = apprun_string_remove_trailing_new_line(buffer);
            result[count] = str;
            count++;
        }

        result = adjust_string_array_size(result);
    }

    return result;
}

char** apprun_file_read_lines(const char* filename) {
    char** result = NULL;

    FILE* fp = fopen(filename, "r");
    if (fp) {
        result = apprun_read_lines(fp);
        result = adjust_string_array_size(result);
        fclose(fp);
    }

    return result;
}

void apprun_file_copy(const char* source_path, const char* target_path) {
    FILE* source, * target;

    source = fopen(source_path, "r");
    target = fopen(target_path, "w");

    if (source == NULL) {
        fprintf(stderr, "Unable to read file: %s\n", source_path);
        exit(1);
    }

    if (target == NULL) {
        fprintf(stderr, "Unable to write file: %s\n", target_path);
        exit(1);
    }


    int ch;
    while ((ch = fgetc(source)) != EOF)
        fputc(ch, target);

    fclose(source);
    fclose(target);
}




