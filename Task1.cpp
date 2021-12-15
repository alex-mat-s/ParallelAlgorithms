#include <iostream>
#include <string.h>
using namespace std;

unsigned countWords(char *str)
{
    int state = 0;
    unsigned num = 0; 
    while (*str){
        if (*str == ' ') 
            state = 0;
        else if (*str == '\\' || *str == '\\'){
            ++str;
            if (*str == 't' || *str == 'n'){
                state = 0;
            }
        }
        else if (state == 0){
            state = 1;
            ++num;
        }
        ++str;
    }
 
    return num;
}

int main(int argc, char* argv[]){
    int count = 0;
	unsigned int state = 0;

    count = countWords(argv[1]);
    
    cout << "Number of words: " << count;

    return 0;
}

