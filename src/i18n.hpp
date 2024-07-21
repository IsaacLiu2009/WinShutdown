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
#include <utility>
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
    void loadText(const std::string &fileName) {
        mINI::INIStructure l10nData;
        (mINI::INIFile(fileName)).read(l10nData);
        for (const std::pair<std::string, std::string> &trans : l10nData["text"]) {
            const std::string &unlocalizedText = trans.first;
            std::string text;
            size_t i;
            for (i = 0; trans.second[i] != '"' && i < trans.second.size(); i++);
            for (i++; trans.second[i] != '"' && i < trans.second.size(); i++) {
                if (trans.second[i] != '\\') text.push_back(trans.second[i]);
                else switch (trans.second[++i]) {
                case '"': {
                    text.push_back('"');
                    break;
                }
                case '\\': {
                    text.push_back('\\');
                    break;
                }
                case 'n': {
                    text.push_back('\n');
                    break;
                }
                case 't': {
                    text.push_back('t');
                    break;
                }
                default: goto SKIP;
                }
            }
            // printf("%s = %s\n", unlocalizedText.c_str(), text.c_str()); //debug
            if (!text.empty() && this->l10n.count(unlocalizedText) == 0)
                this->l10n.emplace(unlocalizedText, text);
        SKIP:;
        }
        // for (const std::pair<std::string, std::string> &trans : this->l10n)
        //     printf("%s = %s\n", trans.first.c_str(), trans.second.c_str()); //debug
    }
public:
    I18n() {
        loadText(this->getLangFileName());
    }
    I18n &operator=(const I18n &i18n) = delete;
    I18n(const I18n &i18n) = delete;
    I18n &operator=(I18n &&i18n) {
        this->l10n = std::move(i18n.l10n);
        return *this;
    }
    I18n(I18n &&i18n) {
        *this = std::move(i18n);
    }
    I18n clone() const {
        I18n i18nClone;
        i18nClone.l10n = this->l10n;
        return i18nClone;
    }
    const std::string &get(const std::string &unlocalizedText) const {
        if (this->l10n.count(unlocalizedText) == 0) return unlocalizedText;
        return this->l10n.at(unlocalizedText);
    }
};

#endif