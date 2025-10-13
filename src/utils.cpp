#include "../include/utils.h"

string replaceAll(string str, const string &oldSub, const string &newSub) {
    size_t pos = 0;
    while ((pos = str.find(oldSub, pos)) != string::npos) {
        str.replace(pos, oldSub.size(), newSub);
        pos += newSub.size();
    }
    return str;
}
