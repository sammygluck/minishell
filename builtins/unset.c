/*
1. Start the unset command implementation.

2. Check if any arguments are provided to the unset command.
   - If no arguments are provided, simply return from the function as there's nothing to unset.

3. Loop through each argument provided to the unset command:
   - For each argument (which represents an environment variable name to unset):
       - Remove the variable from the 't_env' list:
           - Search for a node in the list that matches the variable name.
           - If found, remove the node from the list and free its memory.
       - Remove the variable from the 'char **env' array:
           - Search for an entry in the array that starts with the variable name followed by '='.
           - If found, remove this entry from the array.
               - This might involve shifting subsequent elements and possibly resizing the array.

4. For resizing the 'char **env' array (if required):
   - If an entry is removed:
       - Allocate a new array with a size one less than the current array.
       - Copy all entries except the removed one to the new array.
       - Free the old array and update the pointer to point to the new array.

5. Repeat steps 3 and 4 for each argument provided to the unset command.

6. End of unset command implementation.

*/