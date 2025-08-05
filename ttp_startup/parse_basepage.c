#include <stdint.h>
#include <stdbool.h>
#include <osbind.h>

#define MAX_ARGS 16
#define MAX_CMDLINE 127

static char * argv_out[MAX_ARGS];
static char args_buffer[MAX_ARGS][MAX_CMDLINE];

extern int main(int argc, char *argv[]);

struct cmdline 
{
    uint8_t len;
    char cmdline[MAX_CMDLINE];
};



int parse_basepage(void *basepage)
{
    int argc = 0;
    int i = 0;

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
        int in_quotes = 0;

        /* Check for quoted argument */
        if (input->cmdline[i] == '"') 
        {
            in_quotes = 1;
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
                    break;
                }
            }

            if (arg_len < sizeof(args_buffer[0]) - 1) 
            {
                args_buffer[argc][arg_len++] = c;
            }
            i++;
        }
        args_buffer[argc][arg_len] = '\0';
        argv_out[argc] = args_buffer[argc];
        argc++;

        /* Skip trailing whitespace after quoted argument */
        while (i < input->len && (input->cmdline[i] == ' ' || input->cmdline[i] == '\t' || input->cmdline[i] == '\n')) 
        {
            i++;
        }
    }

    return main(argc, argv_out);
}
