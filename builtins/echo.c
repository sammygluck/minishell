/*
1. Start the echo command implementation.

2. Initialize a flag to track if the '-n' option is used.
   - Set the flag to false initially.

3. Check if the first argument after "echo" is '-n'.
   - If yes, set the '-n' flag to true.
   - Skip this argument for the rest of the processing.

4. Loop through each argument provided to the echo command (starting from the first argument or the second if '-n' was found):
   - Print the argument to standard output.
   - If there are more arguments:
       - Print a space after the current argument to separate from the next one.

5. After all arguments are processed:
   - If the '-n' flag is not set:
       - Print a newline character to end the output.

6. End of echo command implementation.

*/

ft_echo()
{
   flag_n;
   int i;

   i = 0;
   flag_n = (first_argument_is_n);
   if flag_n
      i++;
   while (arguments)
      printf(arugment)
   if flag_n
      printf("\n");
   return (0);

}