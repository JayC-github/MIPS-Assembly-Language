// cowrie.c a simple shell
// This program was written by Jay (z5261536)
// on 2019.11.24

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <spawn.h>
#include <limits.h>
#include <ctype.h>
#include <glob.h>

// PUT EXTRA `#include'S HERE


#define MAX_LINE_CHARS 1024
#define INTERACTIVE_PROMPT "cowrie> "
#define DEFAULT_PATH "/bin:/usr/bin"
#define WORD_SEPARATORS " \t\r\n"
#define DEFAULT_HISTORY_SHOWN 10

// These characters are always returned as single words
#define SPECIAL_CHARS "!><|"

// PUT EXTRA `#define'S HERE
#define MAX 1024

static void execute_command(char **words, char **path, char **environment);
static void do_exit(char **words);
static int is_executable(char *pathname);
static char **tokenize(char *s, char *separators, char *special_chars);
static void free_tokens(char **tokens);

// PUT EXTRA FUNCTION PROTOTYPES HERE
static char **globbing(char **command); // for subset 3


int main(void) {
    //ensure stdout is line-buffered during autotesting
    setlinebuf(stdout);

    // Environment variables are pointed to by `environ', an array of
    // strings terminated by a NULL value -- something like:
    //     { "VAR1=value", "VAR2=value", NULL }
    extern char **environ;

    // grab the `PATH' environment variable;
    // if it isn't set, use the default path defined above
    char *pathp;
    if ((pathp = getenv("PATH")) == NULL) {
        pathp = DEFAULT_PATH;
    }
    char **path = tokenize(pathp, ":", "");

    char *prompt = NULL;
    // if stdout is a terminal, print a prompt before reading a line of input
    if (isatty(1)) {
        prompt = INTERACTIVE_PROMPT;
    }
        
    // main loop: print prompt, read line, execute command
    while (1) {
        if (prompt) {
            fputs(prompt, stdout);
        }
        
        char line[MAX_LINE_CHARS];
        if (fgets(line, MAX_LINE_CHARS, stdin) == NULL) {
            break;
        }
        
        char **command_words = tokenize(line, WORD_SEPARATORS, SPECIAL_CHARS);               
        
        execute_command(command_words, path, environ);
        free_tokens(command_words);

    }

    free_tokens(path);
    return 0;
}


//
// Execute a command, and wait until it finishes.
//
//  * `words': a NULL-terminated array of words from the input command line
//  * `path': a NULL-terminated array of directories to search in;
//  * `environment': a NULL-terminated array of environment variables.
//
static void execute_command(char **words, char **path, char **environment) {
    assert(words != NULL);
    assert(path != NULL);
    assert(environment != NULL);

/*===============================SUBSET 2=====================================*/
// add code which saves every command executed.
// Each command should be appended to the file $HOME/.cowrie_history
// history n ---> prints the last n commands. 
// If n is not specified it should default to 10.
// ! n which prints command n and then executes it.
// If n is not specified the last command should be executed and printed.     
    
    // grab the 'HOME' enviroment variable;
    char *home = getenv("HOME");
    if (home == NULL) {
        printf("No $HOME enviroment\n");
        home = ".";
    }
    // get the file '$HOME'/.cowrie_history
    char *basename = ".cowrie_history";
    char history_path[PATH_MAX];
    snprintf(history_path, sizeof(history_path), "%s/%s", home, basename);
        
    
    if (strcmp(words[0], "history") == 0) {
        // open the $HOME/.history file and read each command
        // array of string for printf (history)
        char history[MAX][MAX];
        FILE *history_file = fopen(history_path, "r");
        
        // get all the command in the history_file and store into array history
        int i = 0;
        while (fgets(history[i], MAX, history_file) != NULL) {
            i++;
        }
         
        // The starting position in the array history to print;    
        int n;  
        // if n is not specified it should print the last 10 commands
        if (words[1] == NULL) {
            n = i - 10;
        } else { // words[1] != NULL eg. history 3 => print the last 3 command
        
            if (!atoi(words[1])) {
                fprintf(stderr, "history: %s: numeric argument required\n", words[1]);
                return;
            }
            
            if (words[2] != NULL) {
                fprintf(stderr, "history: too many arguments\n");
                return;
            }  
            
            n = i - atoi(words[1]);    
        }
        
        // less then n(10) commands in the history, printf from position 0
        if (n < 0) {
            n = 0;
        }
        
        while (n < i) {
            printf("%d: %s", n, history[n]); 
            n++;
        }
        
        // open the $HOME/.history file and append history command
        history_file = fopen(history_path, "a+");
        for (i = 0; words[i] != NULL; i++) {
            fprintf(history_file, "%s ", words[i]);
        } 
        
        fprintf(history_file, "\n");
        fclose(history_file);
        return;
    
    } else {
        if (strcmp(words[0], "!") != 0) {
            // open the $HOME/.history file and append each command except "!"
            FILE *history_file = fopen(history_path, "a+");
            int i;
            for (i = 0; words[i] != NULL; i++) {
                fprintf(history_file, "%s ", words[i]);
            } 
            
            fprintf(history_file, "\n");
            fclose(history_file);
        }
    }
    
    // ! n which prints command n and then executes it. 
    // n is not specified the last command should be executed and printed. 
    if (strcmp(words[0], "!") == 0) {
        // open the $HOME/.history file and read each command
        char history[MAX][MAX];
        FILE *history_file = fopen(history_path, "r");
        
        int i = 0;
        while (fgets(history[i], MAX, history_file) != NULL) {
            i++;
        }
         
        int position;
        // if n is not specified the last command should be executed and printed    
        if (words[1] == NULL) {
            position = i - 1;
        } else { // print command n and executes it  eg. !n --> print/execute n
            position = atoi(words[1]);
        }
        
        printf("%s", history[position]);
        char **command = tokenize(history[position], WORD_SEPARATORS, SPECIAL_CHARS);
        execute_command(command, path, environment);
        return;    
    }
    
        
/*================================SUBSET 3====================================*/
    
    // expand all the words which have '*', '?', '[', or '~' and then execute
    words = globbing(words);

    
/*============================================================================*/    
    
    
    char *program = words[0];

    if (program == NULL) {
        // nothing to do
        return;
    }

    if (strcmp(program, "exit") == 0) {
        do_exit(words);
        // do_exit will only return if there is an error
        return;
    }
       
    
/*================================SUBSET 0====================================*/
        
    // if the cd has no argument should change directory to the value specified 
    // in the home environment variable
    // chdir success return 0, fail return -1
    if (strcmp(program, "cd") == 0) {
        // cd has no argument
        if (words[1] == NULL) {
            chdir(getenv("HOME"));
        } else {
            if(chdir(words[1]) != 0) {
                fprintf(stderr, "cd: %s: No such file or directory\n", words[1]);
                return;
            }
        }
        
        return;
    }
     
    // pwd--show current working directory 
    // char buf[PATH_MAX] getcwd(buf, sizeof(buf));
    if (strcmp(program, "pwd") == 0) {
        printf("current directory is '%s'\n", getcwd(NULL, 0));
        return;
    }

/*================================SUBSET 1====================================*/
    

    // pathname or filename ?
    char *command = NULL;
    // words is filename --> search in **path
    if (strrchr(program, '/') == NULL) {
        int i = 0;
        for (i = 0; path[i] != NULL; i++) {
            char *file = malloc(strlen(path[i]) + strlen(program) + 2);
            sprintf(file, "%s/%s", path[i], program);
            
            if (is_executable(file)) {
                command = file;
                break;
            }
            free(file);
        }        
        
        if (path[i] == NULL) {
            fprintf(stderr, "%s: command not found\n", program);
            return;  
        }      
    
    // words is pathname --> word 0 directly use (strrchr(program, '/') != NULL)
    } else {       
        if (is_executable(program)) {
            command = program;         
        } else {
            fprintf(stderr, "%s: command not found\n", program);
            return;  
        }
    }
    
    // no program is executable
    if (command == NULL) {
        printf("%s: command not found\n", program);
        return;
    } else {
        pid_t pid;
        posix_spawn(&pid, command, NULL, NULL, words, environment); 
        
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            status = WEXITSTATUS(status);
        }   
        printf("%s exit status = %d\n", command, status);
        return;
    }
    
}


// PUT EXTRA FUNCTIONS HERE

// Subset 3 - Globbing
// If any of the characters '*', '?', '[', or '~' appears in a word that word 
// should be replaced by all of the words matching that word using the glob 
// This may result in the words list becoming longer than initially.  
static char **globbing(char **command) {
    // new line that include all the words list after using the glob
    char *new_line = malloc(MAX*sizeof(char));
    
    int i;    
    for (i = 0; command[i] != NULL; i++) {
        // the words include the following character
        if (strchr(command[i],'*') != NULL || 
            strchr(command[i],'?') != NULL || 
            strchr(command[i],'[') != NULL || 
            strchr(command[i],'~') != NULL) {
            
            glob_t matches;
            glob(command[i], GLOB_NOCHECK|GLOB_TILDE, NULL, &matches);
            for (int j = 0; j < matches.gl_pathc; j++) {
                strcat(new_line, matches.gl_pathv[j]);
                strcat(new_line, " ");
            }
        
        // command [i] is a normal word and new_line is still empty
        } else if (i == 0){
            strcpy(new_line, command[i]);            
            strcat(new_line, " ");
        // command [i] is a normal word and new_line is not empty
        } else {
            strcat(new_line, command[i]);
            strcat(new_line, " ");
        }       
    }
    
    // tokenize the new_line into commands
    char **new_command = tokenize(new_line, WORD_SEPARATORS, SPECIAL_CHARS);
    free(new_line);
    return new_command;
}



//
// Implement the `exit' shell built-in, which exits the shell.
//
// Synopsis: exit [exit-status]

// Examples:
//     % exit
//     % exit 1
//
static void do_exit(char **words) {
    int exit_status = 0;

    if (words[1] != NULL) {
        if (words[2] != NULL) {
            fprintf(stderr, "exit: too many arguments\n");
        } else {
            char *endptr;
            exit_status = (int)strtol(words[1], &endptr, 10);
            if (*endptr != '\0') {
                fprintf(stderr, "exit: %s: numeric argument required\n", words[1]);
            }
        }
    }

    exit(exit_status);
}


//
// Check whether this process can execute a file.
// Use this function when searching through the directories
// in the path for an executable file
//
static int is_executable(char *pathname) {
    struct stat s;
    return
        // does the file exist?
        stat(pathname, &s) == 0 &&
        // is the file a regular file?
        S_ISREG(s.st_mode) &&
        // can we execute it?
        faccessat(AT_FDCWD, pathname, X_OK, AT_EACCESS) == 0;
}


//
// Split a string 's' into pieces by any one of a set of separators.
//
// Returns an array of strings, with the last element being `NULL';
// The array itself, and the strings, are allocated with `malloc(3)';
// the provided `free_token' function can deallocate this.
//
static char **tokenize(char *s, char *separators, char *special_chars) {
    size_t n_tokens = 0;
    // malloc array guaranteed to be big enough
    char **tokens = malloc((strlen(s) + 1) * sizeof *tokens);


    while (*s != '\0') {
        // We are pointing at zero or more of any of the separators.
        // Skip leading instances of the separators.
        s += strspn(s, separators);

        // Now, `s' points at one or more characters we want to keep.
        // The number of non-separator characters is the token length.
        //
        // Trailing separators after the last token mean that, at this
        // point, we are looking at the end of the string, so:
        if (*s == '\0') {
            break;
        }

        size_t token_length = strcspn(s, separators);
        size_t token_length_without_special_chars = strcspn(s, special_chars);
        if (token_length_without_special_chars == 0) {
            token_length_without_special_chars = 1;
        }
        if (token_length_without_special_chars < token_length) {
            token_length = token_length_without_special_chars;
        }
        char *token = strndup(s, token_length);
        assert(token != NULL);
        s += token_length;

        // Add this token.
        tokens[n_tokens] = token;
        n_tokens++;
    }

    tokens[n_tokens] = NULL;
    // shrink array to correct size
    tokens = realloc(tokens, (n_tokens + 1) * sizeof *tokens);

    return tokens;
}


//
// Free an array of strings as returned by `tokenize'.
//
static void free_tokens(char **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}
