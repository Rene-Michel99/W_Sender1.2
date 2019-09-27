#include <iostream>
#include <sstream>
#include <stdio.h>
#include <windows.h>

using namespace std;


std::string getCurrentFolder(){
    char currentFolder[100];
    GetCurrentDirectoryA(sizeof(currentFolder), currentFolder);

    for(size_t i=0;i<sizeof(currentFolder)-1;i++){
        if(currentFolder[i]=='\\'){
            currentFolder[i]='/';
        }
    }
    std::stringstream ss;
    ss << currentFolder;
    return ss.str();
}

int main(){

    cout << getCurrentFolder();

    return 0;
}
