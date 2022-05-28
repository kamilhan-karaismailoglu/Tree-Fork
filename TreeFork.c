#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

void tree(int n);
void createTxtLeaf(int pid);
int createTxtRoot(int pidleft,int pidright);
int readF(int pid);

int main(int argc,char* argv[])
{       
    if (argc!=1)
    {   
        int h = atoi(argv[1]);

        if (h!=0) 
        {   
            tree(h); 
            return 0;
        }
        else
        {
            printf("*** 0'dan Buyuk Bir Deger Giriniz ***\n");
        }
    }   
    else
    {
        printf("USAGE: ./TreeFork <tree height>\n");
    }  
}

void tree(int n){ 
    
    if(n<=0) {createTxtLeaf(getpid()); return;}

    int left = fork();

    if (left != 0)                              // root
    {                                           
        printf("%d root => %d\n", n, getpid()); 

        waitpid(left, NULL, 0);
        int right = fork();
        waitpid(right, NULL, 0);

        if (right == 0)                         // right
        { 
            printf("%d right => %d\n", n, getpid());                            
            tree(n-1);
        }
        else if (right!=0) 
        {
            int result = createTxtRoot(left,right);
        }
    } 
    else                                        // left
    { 
        printf("%d left => %d\n", n, getpid());       
        tree(n-1);
    }
}

void createTxtLeaf(int pid)
{   
    char mystr[20];
    sprintf(mystr, "%d", pid); 
    strcat(mystr,".txt");

    FILE *dosya = fopen(mystr,"a");
    srand(getpid());
	int r = rand()%100;
    fprintf(dosya,"%d",r);   
    fclose(dosya);
}

int readF(int pid){ 
	wait(NULL);
	char filename[20];
	int result;
	sprintf(filename,"%d.txt",pid);
	
    FILE *fp = fopen(filename,"r");
	fscanf(fp,"%d",&result);
	fclose(fp);
	return result;
}

int createTxtRoot(int pidleft,int pidright)
{
	int left = readF(pidleft);
	int right = readF(pidright);
	char filename[20];
	sprintf(filename,"%d.txt",getpid());	
	
    FILE *fp = fopen(filename,"w");
	fprintf(fp,"%d",(left+right));	
	fclose(fp);
	return right+left;
}