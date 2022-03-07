#include <stdio.h>
#include <conio.h>
int a[9], b;

int check(char c, char d, char e) {

if (((c == '0') && (d == '0')) && (e == '0')) {
printf("win");

}
return(0);

}

void bebebeprint() {
    printf("%c|", a[0]);
    printf("%c|", a[1]);
    printf("%c\n", a[2]);
    printf("- - -\n");
    printf("%c|", a[3]);
    printf("%c|", a[4]);
    printf("%c\n", a[5]);
    printf("- - -\n");
    printf("%c|", a[6]);
    printf("%c|", a[7]);
    printf("%c\n", a[8]);
}

int main() {

    bebebeprint();

    for(int i=0; i<=9;i++) {
        scanf(" %d", &b);

        scanf(" %c", &a[b]);


        bebebeprint();


        check(a[0],a[1],a[2]);
        check(a[3],a[4],a[5]);
        check(a[6],a[7],a[8]);
        check(a[0],a[3],a[6]);
        check(a[1],a[4],a[7]);
        check(a[2],a[5],a[8]);
        check(a[0],a[4],a[7]);
        check(a[2],a[4],a[6]);
    };


return 0;
}
