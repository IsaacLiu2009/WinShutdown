// i18n for WinShutdown
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

#ifndef WIN_SHUTDOWN_I18N_8596c30e_69e2_4a04_ba76_678bc422f136
#define WIN_SHUTDOWN_I18N_8596c30e_69e2_4a04_ba76_678bc422f136
#include "io.hpp"
#include <string>
#include <unordered_map>
#define MINI_CASE_SENSITIVE
#include "mini/ini.h"
class I18n {
    std::unordered_map<std::string, std::string> l10n;
    std::string getLangFileName() {
        FILE *fp = fopen("language.txt", "r");
        std::string fileName;
        fgets(fileName, fp);
        fclose(fp);
        return fileName.append(".ini");
    }
    void loadLangFile(const std::string &&fileName) {
        mINI::INIStructure l10nData;
        (mINI::INIFile(fileName)).read(l10nData);
        for (const auto &trans: l10nData["message"]){
            const std::string &unlocalizedName = trans.first;
            std::string localizedName;
            size_t i;
            for (i = 0; trans.second[i] != '"' && i < trans.second.size(); i++);
            for (i++; trans.second[i] != '"' && i < trans.second.size(); i++){
                if (trans.second[i] != '\\') localizedName.push_back(trans.second[i]);
                else switch (trans.second[++i]){
                    case '"': {
                        localizedName.push_back('"');
                        break;
                    }
                    case '\\': {
                        localizedName.push_back('\\');
                        break;
                    }
                    case 'n': {
                        localizedName.push_back('\n');
                        break;
                    }
                    case 't': {
                        localizedName.push_back('t');
                        break;
                    }
                }
            }
            printf("%s = %s\n", unlocalizedName.c_str(), localizedName.c_str());
            if (!localizedName.empty() && this->l10n.count(unlocalizedName) == 0)
                this->l10n.emplace(unlocalizedName, localizedName);
        }        
    }
public:
    I18n() {
        loadLangFile(this->getLangFileName());
    }
    const std::string& getL10n(const std::string &unlocalizedName) {
        if (!this->l10n.count(unlocalizedName) == 0) return unlocalizedName;
        return this->l10n[unlocalizedName];
    }
    const char *getL10n(const char *unlocalizedName) {
        if (!this->l10n.count(unlocalizedName) == 0) return unlocalizedName;
        return this->l10n[unlocalizedName].c_str();
    }
};
#endif