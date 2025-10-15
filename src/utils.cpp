#include "../include/utils.h"

string replaceAll(string str, const string &oldSub, const string &newSub) {
    size_t pos = 0;
    if((oldSub[0]=='e'||oldSub[0]=='E') && (oldSub.size()==1 || isdigit(oldSub[1]))){
        while ((pos = str.find(oldSub, pos)) != string::npos) {
            if((str[pos]=='e'||str[pos]=='E') && pos>0 && pos<(str.size()-1) && isdigit(str[pos-1])){
                pos+=oldSub.size();
                continue;
            }
            str.replace(pos, oldSub.size(), newSub);
            pos += newSub.size();
        }
    }
    else{
        while ((pos = str.find(oldSub, pos)) != string::npos) {
            str.replace(pos, oldSub.size(), newSub);
            pos += newSub.size();
        }
    }
    return str;
}
