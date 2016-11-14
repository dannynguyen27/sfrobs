#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;

int frobcmp(const void* a_r, const void* b_r)
{
    const char** a_rtemp = (const char**) a_r;
    const char* a = *a_rtemp;

    const char** b_rtemp = (const char**) b_r;
    const char* b = *b_rtemp;

    int i = 0;
    int j = 0;
    
    while (true)
    {   
        // Both terms terminate at the same time.
        if (a[i] == ' ' && b[j] == ' ')
            break;

        // If a is a prefix of b, return -1 since shorter words are less than longer words
        if (a[i] == ' ')
        {
            return -1;
        }
    
        // If b is a prefix of a, return 1 since b is shorter than a
        if (b[j] == ' ')
        {
            return 1;
        }
        
        // If intial character is a newline character, don't use it for comparison
        if (a[0] == '\n')
        {
            i++;
            continue;
        }

        if (b[0] == '\n')
        {
            j++;
            continue;
        }

        // Compares defrobnicated byte
        char temp_a = a[i] ^ 42;
        char temp_b = b[j] ^ 42;
    
        // a goes before b
        if (temp_a < temp_b)
        {
            return -1;
        }

        // b goes before a
        else if (temp_a > temp_b)
        {
            return 1;
        }

        // check next character
        else
        {
            i++;
            j++;
        }
    }
    return 0;
}

int main(void) {
    int numTerms = 0;
    char** terms;

    // Finds an address suitable for a double pointer
    terms = malloc(sizeof(char*));

    // Memory allocation failed
    if (terms == NULL)
    {
        fprintf(stderr, "Not enough memory allocation");
        exit(1);
    }

    // Repeat until end of file is reached
    while (true)
    {
        // Starts with a string of size 40
        int size = 40;
        char* temp = malloc(sizeof(char) * size);

        if (temp == NULL)
        {
            fprintf(stderr, "Not enough memory allocation");
            exit(1);
        }

        // Keeps track of the number of characters 
        int numLetters = 0;
        int c = getchar();

        // Checks if file is initially empty
        if (c == EOF)
        {
            break;
        }
                
        while (c != EOF)
        {
            // If need be, allocate additional memory
            if (numLetters >= size)
            {
                size += 30;
                temp = realloc(temp, size);

                // Not enough memory available
                if (temp == NULL)
                {
                    fprintf(stderr, "Not enough memory allocation");
                    exit(1);
                }
            }

            // Converts integer value into character
            char c_ascii = c;

            // Checks for space delimiter
            if (c_ascii == ' ')
            {
                // Appends final space character
                temp[numLetters] = ' ';
                break;
            }
                
            // Adds character to array
            temp[numLetters] = c_ascii;
            
            numLetters++;
            c = getchar();
        }

        // Reached end of file
        if (c == EOF)
        {
            // If the last word does not have a final space delimiter, add it
            if (temp[numLetters-1] != ' ')
            {
                temp[numLetters] = ' ';
            }
        }
        
        // Add string to array of Strings
        terms[numTerms] = temp;
        numTerms++;        
        
        // Allocate additional mmeory to find one more word
        terms = realloc(terms, (numTerms + 1) * sizeof(char*));

        if (terms == NULL)
        {
            fprintf(stderr, "Not enough memory allocation");
            exit(1);
        }
    } 
    
    // Allocate memory back to true size
    terms = realloc(terms, (numTerms) * sizeof(char*));  

    if (terms == NULL)
    {
        fprintf(stderr, "Not enough memory allocation");
        exit(1);
    }

    int tempCounter = 0;

    qsort(terms, numTerms, sizeof(char*), frobcmp);

    for (int i = 0; i < numTerms; i++)
    {
        int j = 0;
        while (true)
        {
            // If first time has a newline character in front, don't print it out
            if ((i == 0) && (j == 0) && (terms[i][j] == '\n'))
            {
                j++;
                continue;
            }

            char letterToPrint = terms[i][j];

            if (letterToPrint != ' ')
            {
                putchar(letterToPrint);
                j++;                
            }
            else
            {
                putchar(letterToPrint);
                break;
            }
        }
    }

    for (int i = 0; i < numTerms; i++)
    {
        char* tempCharPointer = (char*) terms[i];

        // Checks to see if the pointer is null
        if (tempCharPointer)
        {
            free(tempCharPointer);
            terms[i] = NULL;
        }
    }

    if (terms)
        free(terms);

    exit(0);
}