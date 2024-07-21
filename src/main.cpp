// WinShutdown for timed shutdowns in Windows
// Copyright (C) 2024 IsaacLiu2009@outlook.com

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "io.hpp"
#include <cstdlib>
#include <ctime>
#include <string>
#include "i18n.hpp"
const I18n i18n;
bool input_time(int *year, int *month, int *date, int *hour, int *minute, int *second) {
    std::string target_time_str;
    gets(target_time_str);
    return sscanf(target_time_str.c_str(), "%d/%d/%d %d:%d:%d", year, month, date, hour, minute, second) == 6;
}
time_t get_target_time() {
    int year, month, date, hour, minute, second;
    year = month = date = hour = minute = second = -1;
    REINPUT:
    while (!input_time(&year, &month, &date, &hour, &minute, &second))
        puts(i18n.get("inputTime.wrongFormat"));
    printfP(i18n.get("inputTime.time").c_str(), year, month, date, hour, minute, second);
    putchar('\n');
    puts(i18n.get("inputTime.confirm"));
    std::string cmd;
    gets(cmd);
    if (cmd == "REINPUT") goto REINPUT;
    else if (cmd != "YES") exit(0);
    tm target_time;
    target_time.tm_year = year - 1900;
    target_time.tm_mon = month - 1;
    target_time.tm_mday = date;
    target_time.tm_hour = hour;
    target_time.tm_min = minute;
    target_time.tm_sec = second;
    target_time.tm_isdst = 0;
    return mktime(&target_time);
}
int main() {
    noOutputSystem("chcp 65001");
    puts(i18n.get("license.start"));
    puts(i18n.get("inputTime.title"));
    time_t delta = get_target_time() - time(nullptr);
    puts(i18n.get("inputTime.success")); putchar('\n');
    if (delta <= 60) {
        puts(i18n.get("shutdown.tooShortTime"));
        system("pause");
        return 0;
    }
    if (delta > 315360000) {
        puts(i18n.get("shutdown.tooLongTime"));
        system("pause");
        return 0;
    }
    char cmd[60];
    noOutputSystem("shutdown -a");
    sprintf(cmd, "shutdown -s -t %lld", delta);
    noOutputSystem(cmd);
    puts(i18n.get("bye"));
    system("pause");
    return 0;
}
