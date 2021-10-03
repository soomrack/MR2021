#include <stdio.h>
#include <string.h>

int main() {
    char string[100] = "AAAaaBBCCD";
    char substring[100] = "aaB";
    int substring_is_in_string;
    for (int i = 0; i < strlen(string) - strlen(substring); i++) {
        substring_is_in_string = 1;
        for (int j = 0; j < strlen(substring); j++) {
            if (string[i] != substring[j]){
                printf("%d %d", string[i], substring[i]);
                substring_is_in_string = 0;
            }
        }
        if (substring_is_in_string) {
            break;
        }
    }
    if (strstr(string, substring) != NULL){
        printf("Yes");
    }
    else{
        printf("No");
    }
}
