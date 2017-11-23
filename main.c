/* ************************************************************************ *
 *                                                                          *
 * - Use this line for test.                                                *
 *                                                                          *
 * $./opt -c -g -Wall -W pedantic prog.c prog2.c opt.sh                     *
 * ************************************************************************ */

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>

#include "qmc.h"

int f4 (bool *table);
int f3 (bool *table);
int f2 (bool *table);

unsigned int_pow (int n, unsigned x);
size_t lines (unsigned int table_rowls);
void *createTable (unsigned int table_rowls);
unsigned int rows (unsigned int n_vars);

typedef int (*function) (bool*);

int
main (int argc, char **argv)
{
    int optch;
    static char optstring[] = "n:m:d:";

    unsigned int n_vars;
    unsigned int n_rows;

    bool *table = NULL;
    char *pch   = NULL;

    function f  = NULL;

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

            switch (n_vars)
            {
            case 2:
                f = f2;
                break;
            case 3:
                f = f3;
                break;
            case 4:
                f = f4;
                break;
            default:
                puts ("Unknown option!");
            }

            break;
        case 'm':
            pch = strtok (optarg, ",");

            while (pch != NULL)
            {
                table[atoi (pch)] = true;
                //printf ("%s\n", pch);
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

    f (table);
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

int f4 (bool* table)
{

    int *out;
    size_t out_size;
    size_t i, j;

    /* simplify the table */
    if (qmc_simplify (table, 4, &out, &out_size))
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

        for (j = 0; j < 4u; ++j)
        {
            switch (out[i * 4u + j])
            {
            case 0:    /* the literal is false */
                printf ("~");
            case 1:    /* the literal is true */
                switch (j)
                {
                case 0:
                    printf ("D");
                    break;
                case 1:
                    printf ("C");
                    break;
                case 2:
                    printf ("B");
                    break;
                case 3:
                    printf ("A");
                    break;
                }
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

int f3 (bool* table)
{

    int *out;
    size_t out_size;
    size_t i, j;

    /* simplify the table */
    if (qmc_simplify (table, 3, &out, &out_size))
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

        for (j = 0; j < 3u; ++j)
        {
            switch (out[i * 3u + j])
            {
            case 0:    /* the literal is false */
                printf ("~");
            case 1:    /* the literal is true */
                switch (j)
                {
                case 0:
                    printf ("C");
                    break;
                case 1:
                    printf ("B");
                    break;
                case 2:
                    printf ("A");
                    break;
                }
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

int f2 (bool* table)
{

    int *out;
    size_t out_size;
    size_t i, j;

    /* simplify the table */
    if (qmc_simplify (table, 2, &out, &out_size))
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

        for (j = 0; j < 2u; ++j)
        {
            switch (out[i * 2u + j])
            {
            case 0:    /* the literal is false */
                printf ("~");
            case 1:    /* the literal is true */
                switch (j)
                {
                case 0:
                    printf ("B");
                    break;
                case 1:
                    printf ("A");
                    break;
                }
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
