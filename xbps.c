#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
	//TODO: xbps wrapper with syntax such as
	//xbps install
	//xbps remove
	//xbps source
	

	if(argc < 2)
	{
		fprintf(stderr, "too few args on %s use -h for help\n", argv[0]);
	}
	else
	{
		//DONT LOSE THIS SNIPPET OF CODE DONT DELETE FOR SOME UNGODLY REASON ARGV[1] JUST WONT COMPARE UNLESS ITS LIKE THIS
		char prog[30];
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
		fprintf(stdout, "%s\n", prog);
		int pkg_num = 0;
		//there will be 2 loops 1 will find the position in argv that the option tag is in
		//the second will find the position of the package tag
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
		if(pkg_num == 0)
		{
			fprintf(stderr, "ERR: you need option -o\n");
		}
		char* pkgs[100];
		int ltime = 0;
		for(int i = pkg_num; i < argc; i++)
		{
			pkgs[ltime] = argv[i];
			ltime += 1;
		}
		pkgs[ltime] = NULL;
		execv(prog, pkgs);
	}

	return 0;
}
