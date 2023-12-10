#include "minishell.h"

// Assuming ft_isspace and ft_isdigit are predefined functions.

// Helper functions for str_to_longlong_with_overflow_check
void process_sign_and_whitespace(char **str, int *sign);
int convert_to_number(char *str, long long *number, int sign);

// Main functions
long long str_to_longlong_with_overflow_check(char *str, int *overflow);
long truncate_to_exit_code(long long number);
int validate_and_process_exit_code(char *input_str);

// Definitions of the functions

void process_sign_and_whitespace(char **str, int *sign) 
{
    *sign = 1;
    while (ft_isspace(**str))
        (*str)++;
    if (**str == '+' || **str == '-') 
    {
        if (**str == '-')
            *sign = -1;
        (*str)++;
    }
}

int convert_to_number(char *str, long long *number, int sign) {
    *number = 0;
    while (*str) 
    {
        if (!ft_isdigit(*str))
            return (1); // Indicates invalid character
        if (*number > LLONG_MAX / 10 || (*number == LLONG_MAX / 10 && *str - '0' > LLONG_MAX % 10)) 
            return (1); // Indicates overflow
        *number = *number * 10 + (*str - '0');
        str++;
    }
    *number *= sign;
    return (0); // Indicates no overflow
}

long long str_to_longlong_with_overflow_check(char *str, int *overflow) {
    long long number;
    int sign;

    process_sign_and_whitespace(&str, &sign);
    *overflow = convert_to_number(str, &number, sign);
    return (number);
}

long truncate_to_exit_code(long long number) 
{
    if (number < 0) 
        return (256 + number % 256);
    else 
        return (number % 256);
}

int validate_and_process_exit_code(char *input_str) {
    int overflow;
    long exit_code; 
    long long num;
    
    overflow = 0;
    num = str_to_longlong_with_overflow_check(input_str, &overflow);
    if (overflow)
        return (-1); // Handle overflow
    else 
    {
        exit_code = truncate_to_exit_code(num);
        return (exit_code); // Use the exit_code as needed
    }
}

