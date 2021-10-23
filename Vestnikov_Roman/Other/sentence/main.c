#include <stdio.h>
#include <string.h>
int main() {
    int j=0;
    int i=0;
   int c=0;
   int d=0;
    const int N=50;
    char stroka[N];
    char poisk[N-1];

    printf("Ведите строку\n");
    scanf("%s",stroka);
    printf("Ведите слово для поиска\n");
    scanf("%s",poisk);
    int dlina_str= strlen(stroka);
    int dlina_poisk= strlen(poisk);
    for (i=0;i<N;i++)
    {
        j=0;
        c=0;
        d=0;
        if (stroka[i]==poisk[j])
        {
            j++;
            c++;
            for (d=i+1;stroka[d]==poisk[j]&&j<=dlina_poisk;d++,j++,c++);
            if (c>=dlina_poisk) break;
        }
    }
    //printf("c=%d\n",j);//

    if (c>=dlina_poisk)
        printf("Слово есть");
    else  printf("Слова нет");
    return 0;
}



