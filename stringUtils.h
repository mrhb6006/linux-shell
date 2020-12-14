//
// Created by mrhb on 12/13/20.
//

#ifndef SHELL_STRINGUTILS_H
#define SHELL_STRINGUTILS_H

#endif //SHELL_STRINGUTILS_H

char *strRemove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}

char *strRemove(char *str, const int index) {
    memmove(str + index, str + index + 1, strlen(str) - index);
    return str;
}

int getSplitedArrayLength(char *string,char *splitBy) {
    int n = 0;
    char *copy = (char *) malloc(strlen(string) * sizeof(char));
    strcpy(copy, string);
    char *temp = strtok(copy, splitBy);
    while (temp != NULL) {
        temp = strtok(NULL, splitBy);
        n++;
    }
    return n;
}

bool contain(char *string,char *subString) {
    return (strstr(string, subString) != NULL);
}

void split(char* cmd ,char **args,char *splitBy) {
    int n=0;
    char *command;
    while( (command=strsep(&cmd,splitBy)) != NULL ){
        args[n++]=command;
    }
    args[n]=NULL;
}