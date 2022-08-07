#include <stdio.h>
#include <ctype.h>

int main()
{
    int c;
    int i = 0;

    char s[1000] = "";
    
    while(i<1000){
        c = getchar();
        s[i]=c;
        if(c == EOF){break;}
        i++;
    }

 if (i > 0)
    {
        if ((isalpha(s[i - 1])) && (s[i - 1]) >= 97 && s[i - 1] <= 122)
        {
            s[i - 1] = s[i - 1] - 32;
        }
    }

    s[i]='\0';
    printf("%s",s);


    return 0;
}