#include "usk-plugin.h"

void loop()
{
	printk();
}

export_vtable_t exports = { "bubblesort", loop };
