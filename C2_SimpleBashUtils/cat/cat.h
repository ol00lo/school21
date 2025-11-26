#ifndef CAT_H
#define CAT_H
#include "flags.h"

int parse_arguments(int argc, char* argv[], Flags* flags, char*** files,
                    int* file_count);

void my_cat(const char* filename, const Flags* flags);

#endif