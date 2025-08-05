/**
 * Basepage command line parser for TOS
 * 
 * @file parse_basepage.c
 * 
 * @copyright Copyright (c) 2025 Matthias Arndt <marndt@final-memory.org>
 *            
 *            The MIT License applies. See the file LICENSE for details.
 * 
 * @brief parses a given TOS basepage command line into tokens and calls main() with the token list
 * @details The following details need to be observed
 *          - a maximum of MAX_ARGS is parsed
 *          - leading spaces or TAB characters are ignored
 *          - arguments on the given command line may be in quotes with " character
 *          - tokens are separated by space or TAB characters
 * 
 *          Caveats:
 *          - limitation to the 126/127 character limit given by TOS
 *          - no support for xargs or other command line extensions
 *          - No environment variable decoding or passing
 *          - limitation of parameters passed to main()
 *          - no globbing (the user program needs to decode *.* arguments)
 * 
 */
#include <stdint.h>
#include <stdbool.h>
#include <osbind.h>

#define MAX_ARGS 16       /** maximum number of arguments processed in the */
#define MAX_CMDLINE 127   /** GEMDOS constant on maximum length of command line (compatible with CP/M) */

static char * argv_out[MAX_ARGS];                /** pointer array to command line arguments for use by the user */
static char args_buffer[MAX_ARGS][MAX_CMDLINE];  /** internal buffer for decoded arguments as NUL terminated strings */

extern int main(int argc, char *argv[]);         /** C standard prototype for main function */

/**
 * @brief structure of CP/M style command line
 */
struct cmdline 
{
    uint8_t len;                   /** the first byte contains the length of the command line */
    char cmdline[MAX_CMDLINE];     /** command line buffer which is not necessarily NUL terminated */
};

/**
 * @brief decode the given TOS basepage for command line arguments 
 * @param[in] basepage points to the basepage of current program, passed by the startup code
 * @return result from main() function to be used as exit code from the startup code
 */
int parse_basepage(void *basepage)
{
    int argc = 0;
    int i = 0;

    /* decode BASEPAGE pointer and convert to CP/M style internal structure */
    struct cmdline * input = (struct cmdline *)(((BASEPAGE *)basepage)->p_cmdlin);

    while ((i < input->len) && (argc < MAX_ARGS)) 
    {
        /* Skip leading whitespace */
        while (i < input->len && (input->cmdline[i] == ' ' || input->cmdline[i] == '\t' || input->cmdline[i] == '\n')) 
        {
            i++;
        }
        if (i >= input->len) 
        {
            break; /* stop collecting arguments if buffers run out */
        }
        
        uint32_t arg_len = 0;
        bool in_quotes = false;

        /* Check for quoted argument */
        if (input->cmdline[i] == '"') 
        {
            in_quotes = true;
            i++; /* Skip opening quote */
        }

        while (i < input->len) 
        {
            char c = input->cmdline[i];
            if (in_quotes) 
            {
                if (c == '"') 
                {
                    i++; /* Skip closing quote */
                    break;
                }
            } 
            else 
            {
                if (c == ' ' || c == '\t' || c == '\n') 
                {
                    break; /* stop token on next whitespace or end of command line */
                }
            }

            if (arg_len < (sizeof(args_buffer[0]) - 1)) 
            {
                args_buffer[argc][arg_len++] = c;
            }
            i++;
        }
        args_buffer[argc][arg_len] = '\0'; /* terminate argument found with NUL */
        argv_out[argc] = args_buffer[argc];
        argc++;

        /* Skip trailing whitespace after quoted argument */
        while (i < input->len && (input->cmdline[i] == ' ' || input->cmdline[i] == '\t' || input->cmdline[i] == '\n')) 
        {
            i++;
        }
    }

    /* pass the determined arguments to the user code: */
    return main(argc, argv_out);
}
