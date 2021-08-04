#include <stdio.h>
#include <string.h>
#include <unistd.h>
//this is terrible code with way too many if statements
int main(int argc, char* argv[])
{
				const static char helptext[] = "xbps [options] [program]\n"
        "-h for help (this screen)\n"
        "-i for installation mode\n"
        "-r for removal mode\n"
        "-q for query mode\n"
        "any option after the  mode option is passed through to xbps-[mode]\n";
        if(argc < 2)
        {
                        fprintf(stdout, "%s", helptext);
                        return 0;
        }
        char prog[30];
        /* this checks to see which options are used */
        if(strcmp(argv[1], "-h") == 0)
        {
                fprintf(stdout, "%s", helptext);
                return 0;
        }
        /* mode options */
        else if (strcmp(argv[1], "-i") == 0)
        {
                strcpy(prog, "/bin/xbps-install");
        }
        else if (strcmp(argv[1], "-r") == 0)
        {
                strcpy(prog, "/bin/xbps-remove");
        }
        else if (strcmp(argv[1], "-q") == 0)
        {
                strcpy(prog, "/bin/xbps-query");
        }
        /* this grabs the options/packages */
        char* pkgs[100];
        int ltime = 0;
        for(int i = 1; i < argc; i++)
        {
                pkgs[ltime] = argv[i];
                ltime += 1;
        }
        pkgs[ltime] = NULL;
        /* this executes the appropriate xbps command
         * xbps -i -Su becomes
         * xbps-install -Su*/
        execv(prog, pkgs);
        return 0;
}
