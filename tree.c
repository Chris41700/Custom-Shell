#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

void tree(){
    int fid = fork();
    if(fid==0){ // If fork is successful make the directory
        mkdir("dir0",0777); // Make dir0 
        exit(0); // Terminates child fork
    }
    else if(fid<0){ // If fork is not successfull print fork failed.
        printf("fork failed");
    }
    else {
        wait(NULL);	// waits for child fork to complete
    	chdir("dir0"); // change directory to dir0
        FILE *t1 = fopen("t1.txt","wb"); // Create t1.txt
        fclose(t1);
        FILE *t2 = fopen("t2.txt","wb"); // Create t2.txt
        fclose(t2);
        FILE *t3 = fopen("t3.txt","wb"); // Create t3.txt
        fclose(t3);
        mkdir("dir1",0777); // Make empty dir1
	}
}

int main() // test function
{
    tree();
    return 0;
}