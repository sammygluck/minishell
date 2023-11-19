#include <minishell.h>

/*
    I've divided the expander in three parts:
    1. Initial clean, which removes the $ sign from $'string' places
    2. Expand $VAR correctly and replace the $VAR with the string it represents
    3. Remove quotes to be removed

    part 1. is complete
    part 2. is outlined below
    part 3. has yet to be done
*/


/*
GOAL: replace string with other string
STEP 1: figure out the main loop
*/

/*
STEP 1: main loop

struct_begin_end;
init struct;
done = is_there_stuff_to_replace(struct_begin_end);
while (done)
    to_replace = extract(begin, end, string);
    replace_string = make_replace_string(env_var, to_replace)
    new_string = replace(old_string, replace_string, begin_end);
    done = is_there_stuff_to_replace(struct_begin_end, new_string);
    free(to_replace);
    free(replace_string);
    old_string = new_string;
    free(old_string);
return (new_string);
*/

/*
STEP 2: is_there_stuff_to_replace(struct_begin_end, new_string);

begin = begin value;
end = end value;

new_begin = find_begin_value(new_string, last_end_value);
new_end = find_end_value(new_string, begin_value);

*/

/*
STEP 3: find begin & end value

a.
find_begin_value(string, last end value)
{
    while(string[end + 1])
    {
        if !in_single_quote && $ found
            begin value = string[end + 1]
        return (begin_value)
        end++;
    }
    return (nothing found)
}

b.
find_end_value(string, begin_value)
{
    while(string[begin_value])
    {
        if is_space || end of string
            return string[here]
        begin_value++
    }
}

c. 
in_single_quote(string, current_place)
//need to find suitable solution. probably modification of in_quote
//needs to be able to return 1/0 given a string and an index

*/

/*
STEP 4: extract(string, begin, end); //is it possible to skip this step and jump straight to compare

    return (ft_strndup(&string[begin], end-begin);//check veracity of that
*/

/*
STEP 5: make_replace_string

make_replace_string(extracted, env_list)
{
    if no chars after $ (i.e. is space or '\0')
        return ($);
    else  if after $ is ?
        replace string = exit_code
    else
        check if VAR exist in env_list
            if it does
                return (the var value);
            if it doesn't
                return (empty string);

}
*/
/*
var extractor(string, env_list)
{
    head = env_list;
    while(head->next)
    {
        if (ft_strcmp(head->name, &string[1]))
            return (ft_strdup(head->value));
        head = head->next;
    }
    return (ft_strdup(""));
}

*/

/*
STEP 6: replace string between beginning and end

replace(old_string, to_replace, begin_end)
{
    new_string = malloc(strlen(old_string) + strlen(to_replace))
    //copy until $
    while(i < begin)
        new_string[j] = old_string[i]
    while(i >= begin && <= end)
        i++
    //copy to_replace
    i = 0
    while(to_replace[i])
        new_string[j] = to_replace[i]
    //copy from end var
    i = end + 1;
    while (old_string[i])
        new_string[j] = old_string[i];
    new_string[j] = '\0';
    return (new_string);
}
*/
