#include "systeminfo.hpp"
#include <iostream>
#include <unistd.h>

int main (int argc, char **argv)
{
	int pid = 0;

	if (argc == 2)
		pid = (int)strtoul(argv[1], NULL, 10);
	else
		pid = getpid();
		
	printf("pid=%d\n", pid);

	for (int t(0); t < (int)Trait::N; t++) {
		std::cout << SystemInfo::getName((Trait)t) << " - " << 
			     SystemInfo::getSystemProperty((Trait)t, pid) << "\n";
	}
	
	return 0;
}
