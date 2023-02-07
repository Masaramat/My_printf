#include<stdarg.h>
#include<stdbool.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//putchar function to write characters to the standard output
int my_putchar(char c) {
  return write(1, &c, sizeof(c));
}
//putstr function to write a string to the standard output
void my_putstr(char* param_1)
{
    int index = 0;
     while (param_1[index] != '\0') {
        my_putchar(param_1[index]);
        index++;
    }

}

//this function is to reverse string after conversion
void reverse_string(char* param){
    int length = strlen(param);
    char temp;
    for(int i=0; i<length/2; i++){
        temp = param[i];
        param[i] = param[length -i -1];
        param[length-i-1] = temp;
    }
}
//this function converts the interger received to a string
char* toString(int param, char str[], int base){
    int sign = param;
    int result;
    int i=0;
    //removes the sign from the number
    if(param<0){
        param = param * -1;
    }
    if(base <2 || base >32){
        return str;
    }
    while(param){
        result = param % base;

        if(result >= 10){
            str[i++] = 65 + (result - 10);
        }else{
            str[i++] = 48 + result;
        }

        param /= base;
    }
    if(sign < 0 && base == 10){
        str[i++] = '-';
    }
    if(sign == 0){
        str[i++] = '0';
    }
    str[i] = '\0';
    
        
    reverse_string(str);

    return str; 

    
}
void print_float(double param){
    int integer_part = (int) param;
    double point = (double) param - integer_part;
    point *= 10000000;
    int double_part = (int) point;

    char* a_str = (char*) malloc(sizeof(integer_part) * sizeof(char*));
    toString(integer_part, a_str, 10 );
    char* b_str = (char*) malloc(sizeof(double_part) * sizeof(char*));
    toString(double_part, b_str, 10 );

    my_putstr(a_str);
    my_putchar('.');
    my_putstr(b_str);

}
int main(){
    // double a = 67.89;
    // int b = (int) a;
    // double c = (double) a-b;
    // c = c * 10000000;
    // int d = (int) c;

    // char* a_str = (char*) malloc(sizeof(b) * sizeof(char*) * 20);
    // toString(b, a_str, 10 );
    // char* b_str = (char*) malloc(sizeof(b) * sizeof(char*));
    // toString(d, b_str, 10 );
    
    // my_putstr(a_str);
    // my_putchar('.');
    // my_putstr(b_str);

    print_float(89.123);

    

    //printf("%s, and %s", a_str, b_str);
}