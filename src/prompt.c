#include "../include/prompt.h"

int cl_prompt (const char *question, char *answer, const size_t max_answer_length)
{
    int input_ok = 1;  

    // Show the user the question
    printf( "%s: ", question );

    // Throw away any existing input in the user's input-queue
    // (like if they answered with a really-long string previously)
    fflush(stdin);

    // Read a line of input from the user into <answer>, but not more
    // than <max_answer_length>-1 bytes are accepted (see fgets() for details)
    // If the fgets() returns EOF or an error, make sure we remember it
    if ( fgets( answer, max_answer_length, stdin ) == NULL )
        input_ok = 0;

    // return whether there was an error on input
    return input_ok;
}