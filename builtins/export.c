/*
1. Start the export command implementation.

2. Check if any arguments are provided to the export command.
   - If no arguments are provided:
       - Display all environment variables in a sorted manner.
           - Use the 't_env' list or 'char **env' array as per your shell design.
           - If using 't_env', sort the list based on the variable names and then print.
           - If using 'char **env', convert it to a list, sort, and then print.
       - Each variable should be printed in the format "declare -x NAME='value'".
   - If arguments are provided:
       - Loop through each argument:
           - Check if the argument is in the format "KEY=VALUE".
               - If yes, add or update the variable in both 't_env' list and 'char **env' array.
               - If the format is incorrect, display an error message for that argument.

3. For adding or updating environment variables:
   - In 't_env' list:
       - Search for the variable by KEY.
       - If found, update its VALUE.
       - If not found, add a new node with KEY and VALUE.
   - In 'char **env' array:
       - Search for the variable by KEY.
       - If found, update its VALUE.
       - If not found, allocate new memory for the new "KEY=VALUE" string and add it to the array.

4. Optional: Implement functionality to handle variables without '='.
   - If a variable is provided without '=', treat it as a variable with an empty value.
   - Or, only add the variable name to the environment without changing its value if it already exists.

5. End of export command implementation.

*/