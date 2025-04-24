#include<stdio.h>
#include<string.h>




unsigned getNum(char c1, char c2){
    unsigned out = 0;
    if(c1 <= '9' && c1 >= '0'){
        out += c1-'0';
    }
    else if (c1>='A' && c1 <= 'F')
    {
        out += c1-'A'+10;
    }
    else
    {
        printf("Invalid character");
    }
    out *= 16;
    if(c2 <= '9' && c2 >= '0'){
        out += c2-'0';
    }
    else if (c2>='A' && c2 <= 'F')
    {
        out += c2-'A'+10;
    }
    else
    {
        printf("Invalid character");
    }
    return out;
}



int main(){
    //Variables
    char message[32];
    
    printf("Enter a packet: ");
    scanf("%s", message);
    printf("Message: %s\n", message);
    
    printf("Code: ");
    for (int i = 0; i < 32; i += 2)
    {
        unsigned num = getNum(message[i], message[i+1]);
        printf("%d ", num);
    }
    return 0;
}


//Teszt: 0123456789ABCDEF0123456789ABCDEF