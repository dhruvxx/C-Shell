#include "headers.h"
#include "echo.h"

void echo (char * commands) {
	int i;
	size_t n = sizeof(commands);
	while (commands) 
	{
		for(i = 0; i < sizeof(commands) ; i++)
		{
			if(commands[i] == ' ' && commands[i+1] == ' ' || commands[i-1] == ' ')
			{
				for(int j = i; j < i; j++)
				{
					commands[j] = commands[j+1];
				}
				i--;
			}
			else
				i++;
		}
		// for(int k = 1; k < n-1 ; k++)
		// {
		// 	if(commands[k] != NULL)
		// 		printf("%s ", commands[k]);
		// }
		// if (commands[n - 1] != NULL)
		printf("%s ", commands);
		commands = strtok(NULL, " ");
	}
	printf("\n");
}