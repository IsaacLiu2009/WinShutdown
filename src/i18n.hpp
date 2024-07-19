// i18n for WinShutdown
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

#ifndef WIN_SHUTDOWN_I18N_8596c30e_69e2_4a04_ba76_678bc422f136
#define WIN_SHUTDOWN_I18N_8596c30e_69e2_4a04_ba76_678bc422f136
#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>
#define MINI_CASE_SENSITIVE
#include "mini/ini.h"
class I18n {
    std::unordered_map<std::string, std::string> l10n;
    const char *getLangFileName() {
        FILE *fp = fopen("language.txt", "r");
        char name[20];
        fgets(name, 11, fp);
        fclose(fp);
        return strcat(name, ".ini");
    }
    void inputL10nFile() {
        mINI::INIFile l10nFile(this->getLangFileName());
        mINI::INIStructure l10nData;
        l10nFile.read(l10nData);
        for (const auto &section: l10nData) for (const auto &l10nPair: section.second){
            l10n[l10nPair.first] = l10nPair.second;
        }
    }
public:
    std::string getL10n(std::string unlocalizedName) {
        if (this->l10n.count(unlocalizedName) == 0) return unlocalizedName;
        return this->l10n[unlocalizedName];
    }
    const char *getL10n(const char *unlocalizedName) {
        if (this->l10n.count(std::string(unlocalizedName)) == 0) return unlocalizedName;
        return this->l10n[std::string(unlocalizedName)].c_str();
    }
};
#endif
