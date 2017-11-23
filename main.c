/* ************************************************************************ *
 *                                                                          *
 * - Use this line for test.                                                *
 *                                                                          *
 * $./opt -c -g -Wall -W pedantic prog.c prog2.c opt.sh                     *
 * ************************************************************************ */

#include <stdio.h>
#include <unistd.h>

int
main (int argc, char **argv)
{
    int optch;
    static char optstring[]= "m:d:";

    while ( (optch = getopt (argc, argv, optstring)) != -1 )
        switch (optch)
        {
        case 'm':
            printf ("-W '%s' processed.\n",optarg);
            break;
        case 'd':
            printf ("-W '%s' processed.\n",optarg);
            break;
        default:
            puts ("Unknown option!");
        }

    for (; optind < argc; ++optind)
        printf ("argv[%d] = '%s'\n", optind, argv[optind]);

    return 0;

}

