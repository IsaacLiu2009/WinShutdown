// WinShutdown for timed shutdowns in Windows
// Copyright (C) 2024 IsaacLiu2009@outlook.com

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <cstdio>
#include <iostream>
#include <ctime>
#include <string>
void gets(std::string& str){
    std::getline(std::cin, str);
}
bool input_time(int* year, int* month, int* date, int* hour, int* minute, int* second){
    std::string target_time_str;
    gets(target_time_str);
    return sscanf(target_time_str.c_str(), "%d/%d/%d %d:%d:%d", year, month, date, hour, minute, second) == 6;
}
time_t get_target_time(){
    int year, month, date, hour, minute, second;
    year = month = date = hour = minute = second = -1;
    REINPUT:
    while (!input_time(&year, &month, &date, &hour, &minute, &second))
        puts("格式错误，请重新输入。");
    printf("您输入的时间是：%04d/%02d/%02d %02d:%02d:%02d\n", year, month, date, hour, minute, second);
    puts("请输入“YES”确认，输入“REINPUT”重新输入，输入其他内容退出。");
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
int main(){
    puts("WinShutdown 版权所有（C）2024 IsaacLiu2009@outlook.com\n本程序从未提供品质担保。这是款自由软件，欢迎你在满足一定条件后对其再发布。\n");
    RESTART:
    puts("时间格式：YYYY/MM/DD hh:mm:ss，请输入时间。");
    time_t target_time = get_target_time();
    puts("读入成功\n");
    time_t now = time(nullptr);
    time_t delta = target_time - now;
    if (delta <= 60){
        puts("为了保证您错误操作后来得及取消，请输入超过1分钟的时间。"); 
        system("pause");
        putchar('\n');
        goto RESTART;
    }
    if (delta > 315360000){
        puts("时间间隔过长，请输入不超过10年的时间。");
        system("pause");
        putchar('\n');
        goto RESTART;
    }
    char cmd[60];
    sprintf(cmd, "shutdown -s -t %lld", delta);
    system("shutdown -a");
    system(cmd);
    puts("如若错误操作，使用shutdown -a命令取消关机。");
    system("pause");
    return 0;
}
