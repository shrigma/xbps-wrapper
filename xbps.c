#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "too few args on %s use -h for help\n", argv[0]);
	}
	else
	{
		char prog[30];
		/* this checks to see which options are used */
		if(strcmp(argv[1], "-h") == 0)
		{
			const static char helptext[] = "xbps [options] [program]\n"
			"-h for help (this screen)\n"
			"-i for installation mode\n"
			"-r for removal mode\n"
			"-q for query mode\n"
			"-o for the packages & options\n";
			fprintf(stdout, "%s", helptext);
			return 0;
		}
		/* these options are used to call on the right program */
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
		int pkg_num = 0;
		/****************************************
		* this loop finds -o's position in argv *
		* so that it can store all the options  *
		* in a seperate variable called pkgs    *
		*****************************************/
		for(int i = 2; i < argc; i++)
		{
			if(strcmp(argv[i], "-o") == 0)
			{
				pkg_num = i;
				fprintf(stdout, "found pkg_num at %i\n", pkg_num);
			}
			if(pkg_num != 0)
			{
				fprintf(stdout, "exiting loop\n");
				break;
			}
		}
		/* if there are no options cause an error and exit */
		if(pkg_num == 0)
		{
			fprintf(stderr, "ERR: you need option -o\n");
			return 1;
		}
		char* pkgs[100];
		int ltime = 0;
		/* this adds all the options to the pkgs variable */
		for(int i = pkg_num; i < argc; i++)
		{
			pkgs[ltime] = argv[i];
			ltime += 1;
		}
		pkgs[ltime] = NULL;
		/* this executes the program with the given options */
		/************************************************ 
		 *if you called this as   xbps -i -o -S emacs   *
		 *the equivilent would be xbps-install -S emacs *
		 ************************************************/
		execv(prog, pkgs);
	}

	return 0;
}
