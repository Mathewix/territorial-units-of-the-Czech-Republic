#include <libds/heap_monitor.h>
#include "HlavnyProgram.h"



int main()
{	
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);
	initHeapMonitor();
	HlavnyProgram hp = HlavnyProgram("CR.csv");
	hp.program();
	return 0;
}
