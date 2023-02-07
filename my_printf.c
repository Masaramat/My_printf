#include<stdarg.h>
#include<stdbool.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>



char* my_downcase(char* param_1)
{
   for(int i=0; param_1[i] != '\0'; i++){
       if(param_1[i] >=65 && param_1[i]<= 90){
           param_1[i] = param_1[i] + 32;
       }

   }
   return param_1;
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

//this one prints floating point numbers
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
//processes the flag received from the printf function
int process_flag(va_list arg, char flag){
    char c;
    char *str;
    int j;
    double g;
    
    switch (flag) {
        //processes strings %s
        case 's':
            str = va_arg(arg, char*);
            my_putstr(str);
            return sizeof(str);
            break;
         //processes characters %c
        case 'c':
            c = (char) va_arg(arg, int);
            my_putchar(c);
            return sizeof(c);
            break;
        //processes double %d
        case 'd':
            j = va_arg(arg, int);
            char* s = (char*) malloc(sizeof(j) * sizeof(char*));
            s = toString(j, s, 10);
            my_putstr(s);
            return sizeof(s);
            break;
        //to process octal numbers
        case 'o':
            j = va_arg(arg, int);
            s = (char*) malloc(sizeof(j) * sizeof(char*));
            s = toString(j, s, 8);
            my_putstr(s);
            return sizeof(s);
            break;
        //handle unsigned integers
        case 'u':
            j = va_arg(arg, int);
            unsigned int u = (unsigned int) j;
            s = (char*) malloc(sizeof(u) * sizeof(char*));
            s = toString(u, s, 10);
            my_putstr(s);
            return sizeof(s);
            break;
        //handle hex numbers %x
        case 'x':
            j = va_arg(arg, int);
            s = (char*) malloc(sizeof(char) * sizeof(j));
            s = toString(j, s, 16);
            s = my_downcase(s);
            my_putstr(s);
            return sizeof(s);
        //handle hex numbers %X
        case 'X':
            j = va_arg(arg, int);
            s = (char*) malloc(sizeof(char) * sizeof(j));
            s = toString(j, s, 16);
            my_putstr(s);
            return sizeof(s);
            break;
        //handle floating point numbers
        case 'f': 
            g = va_arg(arg, double);
            print_float(g);
            return sizeof(s);

    } 

    return 1;

}
    

//my printf function
int my_printf(char *format, ...){
    va_list args;
    int i = 0;
    bool is_flag = false;

    va_start(args, format);
    while(format[i] != '\0'){
        if(is_flag){
           //processes flag if character % is found in the string
            process_flag(args, format[i]);
            is_flag = false;
            //flags true if % is found
        }else if(format[i] == '%'){
            is_flag = true;
        }else{
            //prints the format strings if no flag is found
            my_putchar(format[i]);
        }
        i++;
    }
    va_end(args);

    return *format;
}

int main(){
        my_printf("Hello world!\n");
        my_printf("%c!\n", 'H');
        my_printf("%c%c%c%c%c!\n", 'H', 'e', 'l', 'l', 'o');
        my_printf("%f!\n", 89.90);
    return  0;
}