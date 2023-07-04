# Minishell
To create the "minishell" program, you will need to implement a shell that follows the provided requirements. Here's a step-by-step guide to help you get started:

1. Set up your project structure:
   - Create a directory for your project, e.g., "minishell".
   - Place all your source code files (`.c`), header files (`.h`), and the Makefile in this directory.

2. Write the necessary code:
   - Implement the main shell loop that displays the prompt and waits for user input.
   - Parse the user input to separate commands and arguments.
   - Implement the built-in commands (echo, cd, pwd, export, unset, env, exit).
   - Handle redirections (input/output redirection, append mode, here documents).
   - Implement piping between commands.
   - Handle environment variable expansion.
   - Handle special characters and quotes.
   - Implement signal handling for ctrl-C, ctrl-D, and ctrl-\\.

3. Define a Makefile:
   - Create a file named `Makefile` in your project directory.
   - Define the necessary rules (`all`, `clean`, `fclean`, `re`).
   - Specify the dependencies and compilation commands for your program.

4. Use the provided external functions:
   - Use the functions from the `readline` library to handle user input and history.
   - Use other necessary external functions as specified in the requirements.

5. Use the authorized functions from Libft:
   - If you have a separate Libft library, include the necessary header files (`libft.h`).
   - Link your program with the Libft library during compilation.

6. Test your program:
   - Compile your program using the Makefile (`make` command).
   - Test different commands, built-ins, redirections, and piping scenarios to ensure they work correctly.
   - Verify that your shell handles signal inputs and built-in commands as expected.

7. Address potential memory leaks:
   - While the `readline` function may cause memory leaks, make sure that your own code does not have memory leaks. Free any dynamically allocated memory appropriately.

Remember to thoroughly test your shell to ensure it meets all the requirements and behaves as expected. Good luck with your project!
