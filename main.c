#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>

#include "qmc.h"

int          g            (bool* table, size_t n);
unsigned     int_pow      (int, unsigned);
size_t       lines        (unsigned int );
void         *createTable (unsigned int );
unsigned int rows         (unsigned int );

int
main (int argc, char **argv)
{
    int optch;
    static char optstring[] = "n:m:d:";

    unsigned int n_vars;
    unsigned int n_rows;

    bool *table = NULL;
    char *pch   = NULL;

    while ((optch = getopt (argc, argv, optstring)) != -1)
    {
        switch (optch)
        {
        case 'n':

            n_vars      = (unsigned int)atoi (optarg);
            n_rows = rows (n_vars);

            table       = (bool*)createTable (n_rows);

            if (NULL == table)
            {
                printf ("%s\n", "Erro de alocação");
                exit (1);
            }

            for (int i=0; i<n_rows; i++)
            {
                table[i] =  false;
            }

            break;
        case 'm':
            pch = strtok (optarg, ",");

            while (pch != NULL)
            {
                table[atoi (pch)] = true;
                pch = strtok (NULL, ",");
            }

            break;
        case 'd':
            printf ("-d '%s' processed.\n", optarg);
            break;
        default:
            puts ("Unknown option!");
        }
    }

    for (int i=0; i<n_rows; i++)
    {
        printf ("table[%d]=%d\n",i,table[i]);
    }

    g (table, n_vars);
    free (table);

    return 0;

}

unsigned int rows (unsigned int n_vars)
{
    return int_pow (2, n_vars);
}

void *createTable (unsigned int table_rowls)
{
    return malloc (lines (table_rowls));
}

size_t lines (unsigned int table_rowls)
{
    return table_rowls * sizeof (bool);
}

unsigned int_pow (int n, unsigned x)
{
    unsigned i, a = n;
    switch (x)
    {
    case 0:
        return 1;
    case 1:
        return n;
    default:
        for (i = 1; i < x; ++i)
        {
            a *= n;
        }
        break;
    }
    return a;
}

int g (bool* table, size_t n)
{

    int *out;
    size_t out_size;
    size_t i, j;

    /* simplify the table */
    if (qmc_simplify (table, n, &out, &out_size))
    {
        fprintf (stderr, "Simpification failed!\n");
        /* No need to call qmc_free(out) if failed */
        return 1;
    }

    /* print the output */
    for (i = 0; i < out_size; ++i)
    {
        if (i > 0)
            printf (" + ");

        for (j = 0; j < n; ++j)
        {
            switch (out[i * n + j])
            {
            case 0:    /* the literal is false */
                printf ("~");
            case 1:    /* the literal is true */
                printf ("%c", (char) (64 + n - j));
                break;
            }
        }
    }

    if (out_size == 0) /* All table entries are true or false */
    {
        if (table[0])
            printf ("TRUE");
        else
            printf ("FALSE");
    }
    printf ("\n");

    qmc_free (out);

    return 0;
}