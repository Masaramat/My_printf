#include<stdarg.h>
#include<stdbool.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

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
void toString(int param, char str[], int base){
    int sign = param;
    int i, j;
    //removes the sign from the number
    if(param<0){
        param = param * -1;
    }
    do{
        //convert base 10 integer to base 8 and converts the base 8 to string
        //still a work in progress. I will have to write a different function to do this later
        if(base == 8){
            str[i++] = ((param % 8) * j++) + '0';
            //converts base 10 numbers to string 
        }else if(base == 10){
            str[i++] = param % 10 + '0';
        }
        
    }while((param /= 10)>0); 
    //if integer was negetive it adds the sign to the converted string     
    if(sign < 0){
        str[i++] = '-';
    } 
    //adds the null pointer to the resulting string
    str[i] = '\0'; 
    //reverses the string back to the way it was received
    reverse_string(str); 

    
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
//processes the flag received from the printf function
int process_flag(va_list arg, char flag){
    char c;
    char *str;
    //processes strings %s
    if(flag == 's'){
        str = va_arg(arg, char*);
        my_putstr(str);
        return sizeof(str);
    //processes characters %c
    }else if(flag == 'c'){
        c = (char) va_arg(arg, int);
        my_putchar(c);
        return sizeof(c);
    //processes double %d
    }else if(flag == 'd'){
        int j = va_arg(arg, int);
        char s[20];
        toString(j, s, 10);
        my_putstr(s);
        return sizeof(s);
    //supposed to process octal numbers
    }else if(flag == 'o'){
        int j = va_arg(arg, int);
        char s[20];
        toString(j, s, 8);
        my_putstr(s);
        return sizeof(s);
    //for error handling
    }else{

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
        my_printf("%d!\n", 90);



    return  0;
}