// C-style I/O Helper in C++
// Copyright (C) 2024 IsaacLiu2009@outlook.com

// This header is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or any later version.

// This header is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this header. If not, see <https://www.gnu.org/licenses/>.

#ifndef C_STYLE_IO_HELPER_6eca1fd7_b011_4da8_88cf_e951491dad15
#define C_STYLE_IO_HELPER_6eca1fd7_b011_4da8_88cf_e951491dad15

#include <cstdio>
#include <string>
#define printfP _printf_p
#define sprintfP _sprintf_p
#define fprintfP _fprintf_p

std::string& fgets(std::string &str, FILE* fp) {
    char nxt = getc(fp);
    while (nxt == '\n') nxt = getc(fp);
    while (nxt != '\n') {
        if (nxt == EOF) return str;
        str.insert(str.end(), nxt);
        nxt = getc(fp);
    }
    return str;
}
std::string& gets(std::string &str) {
    return fgets(str, stdin);
}
int fscans(FILE* fp, std::string &str) {
    char nxt = getc(fp);
    if (nxt == EOF) return EOF;
    while (nxt == '\n' || nxt == ' ' || nxt == '\t') nxt = getc(fp);
    if (nxt == EOF) return EOF;
    while (nxt != '\n' && nxt != ' ' && nxt != '\t' && nxt != EOF) {
        str.push_back(nxt);
        nxt = getc(fp);
    }
    return 1;
}
int scans(std::string &str){
    return fscans(stdin, str);
}

void fputs(const std::string &str, FILE* fp) {
    fputs(str.c_str(), fp);
}
void puts(const std::string &str) {
    puts(str.c_str());
}


void noOutputSystem(const char *cmd) {
    freopen("NUL", "w", stdout);
    system(cmd);
    fflush(stdout);
    freopen("CON", "w", stdout);
}

#endif