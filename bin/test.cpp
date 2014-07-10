//#include "../LibExt2.h"
#include <stdio.h>
//#include "../winapi.h"
#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <iconv.h>
#include <errno.h>
//#include "Script.h"
#include <unistd.h>
typedef void (*fPy_SetLibPath)(const char*);

main()
{
	char current_absolute_path[512];
	//获取当前程序绝对路径
	int cnt = readlink("/proc/self/exe", current_absolute_path, 512);
	if (cnt < 0 || cnt >= 512)
	{
		printf("***Error***\n");
		exit(-1);
	}
	//获取当前目录绝对路径，即去掉程序名
	int i;
	for (i = cnt; i >=0; --i)
	{
		if (current_absolute_path[i] == '/')
		{
			current_absolute_path[i+1] = '\0';
			break;
		}
	}
	printf("current absolute path:%s\n", current_absolute_path);

	char* eInfo = NULL;
	void* hDll = NULL;
	char soPath[512];
	char* error;
	sprintf(soPath , "%s%s" , current_absolute_path , "libScript.so");
	hDll = dlopen (soPath, RTLD_LAZY);  
	if (!hDll) {  
		fprintf (stderr, "%s\n", dlerror());  
		exit(1);  
	}  

	fPy_SetLibPath fsetlibpath = (fPy_SetLibPath)dlsym(hDll, "Py_SetLibPath");  
	if ((error = dlerror()) != NULL)  {  
		fprintf (stderr, "%s\n", error);  
		exit(1);  
	}  

	(*fsetlibpath)(soPath);  
	dlclose(hDll);  
	return 0;
}
