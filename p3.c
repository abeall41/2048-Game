/*
2048 game

This program will create a 4X4 and proceed to shift and combine 
numbers in an attempt to reach a 2048 block. This is done through
a series of array shifts. The algoritm consists of recording the 
directiong the user wants to shift then shifting all the non-zero 
arrays in that direction. Then all the non zero elements are check 
to see if any elements are the same and can be combined. then the 
elements in the array are shifted again. After this a 2 or a 4 is
randomly generated into a zero value array element. The position 
of this is chosen by randomly generating two numbers between 0 and 3
and then used for the position of the array. This element is then 
check to see if it has a zero value. If the value is zero then that 
element takes the 2 or 4 that was generated. If the value was not 
zero then the process is repeated until a non zero value is found. 

11/22/15
Alex Beall
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[])
{
/****************File setup******************/ 

int myseed = atoi(argv[1]);

FILE  *moves, *ending;

moves = fopen(argv[2], "w");
ending = fopen(argv[3], "w");

if (moves == NULL)
{printf("FIle %s cannot open!\n", argv[2]);
}
if (ending == NULL)
{printf("FIle %s cannot open!\n", argv[3]);
}
if (argc != 4)
{printf("Usage: executable seed moves ending\n");
 exit(0);
}
	
	

srand(myseed);					// Set the random number generator seed that will be used
	
/************************************Variables**********************************/
int i,j, A[4][4],T[4], x=0, z, m=0, c=1, s=0, k, w=0, q, p, e, r;
int score = 0, end=0;
char d;

/**************************************Loop*************************************/
	
/**********************Initilization**************************/
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
			A[i][j] = 0;
		}
	}
	// generate the first random number in a random location
	q = rand()%4;
		p = rand()%4;
		if (A[q][p] == 0)
		{
			A[q][p] = rand()%2*2+2;
			r=1;
		}

/**********************Main game**************************/
z=0;
while (score < 50000)
{	
	printf("\n\n*********Get to 2048!**********\n\n\n");
	
		for (i=0;i<4;i++)
		{
			for (j=0;j<4;j++)
			{
				if (A[i][j]==0)
				{
					printf("[    ]  ");
				}	
				else
				{
					printf("[%4d]  ", A[i][j]);
				}	
			}
			printf("\n");
		}
	//Check if the user has reached the 2048 block. Also check if any possible moves are remaining
	c=0;
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
			if (A[i][j]==2048)
			{
				printf("\n\tYou Win!\n\tScore: %d", score);
				exit(0);
			}			
			if(A[i][j] == 0)
			{
				continue;
			}
			if ((A[i][j]!=A[i-1][j])&&(A[i][j]!=A[i+1][j])&&(A[i][j]!=A[i][j-1])&&(A[i][j]!=A[i][j+1]))
			{
				c++;
			}
		}
	}
	//If no possible moves remain then end the game and print final board
//	printf("\n\tC=%d\n", c);
	if(c==14)
	{
		system("clear");
		printf("\n\tGAME OVER\n\tYour Score is: %d\n\n", score);
		for (i=0;i<4;i++)
		{
			for (j=0;j<4;j++)
			{
				printf("[%4d]  ", A[i][j]);
			}
			printf("\n");
		}
		for (i=0;i<4;i++)
		{
			for (j=0;j<4;j++)
			{
				if (A[i][j]==0)
				{
					fprintf(ending, "[    ]  ");
				}	
				else
				{
					fprintf(ending, "[%4d]  ", A[i][j]);
				}				
			}
			fprintf(ending, "\n");
		}
		exit(0);
	}

	//Game board directions and interface
	printf("\n\n   Moves: %d\tScore: %d\n\n", m, score);
	printf("Move: Right | Left | Up | Down | Quit\n");
	printf("Key:    d   |   a  |  w |   s  |   q \n");
	
	//Slide direction input
	printf("\nEnter direction to slide:");
	scanf("%c%c", &d);
	m++;
	
	//Running total of moves 
	fprintf(moves, "%c\n", d);
	
	// Check for invalid commands
	if ((d != 'a')&&(d != 'q')&&(d != 'w')&&(d != 's')&&(d != 'd'))
	{
		printf("\nERROR: Invalid Command\n");
		system("clear");
		continue;	
	}

	//Print the board
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
			if (A[i][j]==0)
			{
				printf("[    ]  ");
			}	
			else
			{
				printf("[%4d]  ", A[i][j]);
			}	
		}
		printf("\n");
	}
	
	system("clear");
	
/************************* Shift Right **********************************/
	if(d == 'd')
	{
		// check if anything can shift
		e=0;
		for (i=0;i<4;i++)
			{
				for (j=3;j>=0;j--)
				{
					if(A[i][j] == 0)
					{
						T[j]=0;
					}
					if(A[i][j] != 0)
					{
						T[j]=1;
					}
				}

				if(T[3]==0)
				{
					if((T[2]==0)&&(T[1]==0)&&(T[0]==0))
					{
						e++;
					}
				}
				if(T[3]==1)
				{
					if((T[2]==0)&&(T[1]==0)&&(T[0]==0))
					{
						e++;
					}
					else if((T[2]==1)&&(T[1]==0)&&(T[0]==0))
					{
						e++;
					}
					else if((T[2]==1)&&(T[1]==1)&&(T[0]==0))
					{
						e++;
					}
					else if((T[2]==1)&&(T[1]==1)&&(T[0]==1))
					{
						e++;
					}	
				}
			}
			
		printf("\nMoving Right\n");
		//shift every number to the right
		for(k=0; k<3; k++)
		{
			for (i=0;i<4;i++)
			{
				for (j=0;j<3;j++)
				{
					if(A[i][j+1] == 0)
					{
						A[i][j+1]=A[i][j];
						A[i][j]=0;
					}
				}
			}
		}
		
		//combine any matching
		r=0;
		for (i=0;i<4;i++)
		{
			for (j=3;j>0;j--)
			{
				if((A[i][j-1] == A[i][j])&&(A[i][j]!=0))
				{
					A[i][j]=A[i][j]*2;
					score = score + A[i][j];
					A[i][j-1]=0;
				}
				else
				{
					r++;
				}
			}
		}
		//If noting can shift or combine
		if((e==4)&&(r>=12))
		{
		system("clear");
		printf("\nERROR: Invalid Command\n");
		continue;
		}
		//shift every number to the right
		for(k=0; k<3; k++)
		{
			for (i=0;i<4;i++)
			{
				for (j=0;j<3;j++)
				{
					if(A[i][j+1] == 0)
					{
						A[i][j+1]=A[i][j];
						A[i][j]=0;
					}
				}
			}
		}
	}

/************************* Shift LEFT **********************************/
	if(d == 'a')
	{
		// check if anything can shift
		e=0;
		for (i=0;i<4;i++)
			{
				for (j=0;j<=3;j++)
				{
					if(A[i][j] == 0)
					{
						T[j]=0;
					}
					if(A[i][j] != 0)
					{
						T[j]=1;
					}
				}

				if(T[3]==0)
				{
					if((T[2]==0)&&(T[1]==0)&&(T[0]==0))
					{
						e++;
					}
				}
				if(T[0]==1)
				{
					if((T[1]==0)&&(T[2]==0)&&(T[3]==0))
					{
						e++;
					}
					else if((T[1]==1)&&(T[2]==0)&&(T[3]==0))
					{
						e++;
					}
					else if((T[1]==1)&&(T[2]==1)&&(T[3]==0))
					{
						e++;
					}
					else if((T[1]==1)&&(T[2]==1)&&(T[3]==1))
					{
						e++;
					}		
				}		
			}
			
		printf("\nMoving Left\n");
		//shift every number to the left
		for(k=0; k<3; k++)
		{
			for (i=0;i<4;i++)
			{
				for (j=3;j>0;j--)
				{
					if(A[i][j-1] == 0)
					{
						A[i][j-1]=A[i][j];
						A[i][j]=0;
					}
				}
			}
		}
		//combine any matching
		r=0;
		for (i=0;i<4;i++)
		{
			for (j=0;j<3;j++)
			{
				if((A[i][j+1] == A[i][j])&&(A[i][j]!=0))
				{
					A[i][j]=A[i][j]*2;
					score = score + A[i][j];
					A[i][j+1]=0;
				}
				else
				{
					r++;
				}
			}
		}
		if((e==4)&&(r>=12))
		{
		system("clear");
		printf("\nERROR: Invalid Command\n");
		continue;
		}
		//shift every number to the left
		for(k=0; k<3; k++)
		{
			for (i=0;i<4;i++)
			{
				for (j=3;j>0;j--)
				{
					if(A[i][j-1] == 0)
					{
						A[i][j-1]=A[i][j];
						A[i][j]=0;
					}
				}
			}
		}
	}
	
/************************* Shift Down **********************************/
	if(d == 's')
	{
		// check if anything can shift
		e=0;
		for (j=0;j<4;j++)
			{
				for (i=3;i>=0;i--)
				{
					if(A[i][j] == 0)
					{
						T[i]=0;
					}
					if(A[i][j] != 0)
					{
						T[i]=1;
					}
				}

				if(T[3]==0)
				{
					if((T[2]==0)&&(T[1]==0)&&(T[0]==0))
					{
						e++;
					}
				}
				if(T[3]==1)
				{
					if((T[2]==0)&&(T[1]==0)&&(T[0]==0))
					{
						e++;
					}
					else if((T[2]==1)&&(T[1]==0)&&(T[0]==0))
					{
						e++;
					}
					else if((T[2]==1)&&(T[1]==1)&&(T[0]==0))
					{
						e++;
					}
					else if((T[2]==1)&&(T[1]==1)&&(T[0]==1))
					{
						e++;
					}	
				}	
			}
		printf("\nMoving Down\n");
		//shift every number down
		for (k=0; k<3; k++)
		{
			for (j=0;j<4;j++)
			{
				for (i=3;i>0;i--)
				{
					if(A[i][j] == 0)
					{
						A[i][j]=A[i-1][j];
						A[i-1][j]=0; 
					}
				}
			}
		}
		
		//combine any matching
		r=0;
		for (j=0;j<4;j++)
		{
			for (i=3;i>0;i--)
			{
				if((A[i-1][j] == A[i][j])&&(A[i][j]!=0))
				{
					A[i][j]=A[i][j]*2;
					score = score + A[i][j];
					A[i-1][j]=0;
				}
				else
				{
					r++;
				}
			}
		}
		if((e==4)&&(r>=12))
		{
		system("clear");
		printf("\nERROR: Invalid Command\n");
		continue;
		}
		//shift every number down
		for (k=0; k<3; k++)
		{
			for (j=0;j<4;j++)
			{
				for (i=3;i>0;i--)
				{
					if(A[i][j] == 0)
					{
						A[i][j]=A[i-1][j];
						A[i-1][j]=0; 
					}
				}
			}
		}
	}
	
/************************* Shift Up **********************************/
	if(d == 'w')
	{
		// check if anything can shift
		e=0;
		for (j=0;j<4;j++)
			{
				for (i=0;i<4;i++)
				{
					if(A[i][j] == 0)
					{
						T[i]=0;
					}
					if(A[i][j] != 0)
					{
						T[i]=1;
					}
				}

				if(T[0]==0)
				{
					if((T[2]==0)&&(T[1]==0)&&(T[3]==0))
					{
						e++;
					}
				}
				if(T[0]==1)
				{
					if((T[1]==0)&&(T[2]==0)&&(T[3]==0))
					{
						e++;
					}
					else if((T[1]==1)&&(T[2]==0)&&(T[3]==0))
					{
						e++;
					}
					else if((T[1]==1)&&(T[2]==1)&&(T[3]==0))
					{
						e++;
					}
					else if((T[1]==1)&&(T[2]==1)&&(T[3]==1))
					{
						e++;
					}	
				}
			}
		printf("\nMoving Up\n");		
		//shift every number up
		for(k=0; k<3; k++)
		{
			for (j=0;j<4;j++)
			{
				for (i=0;i<3;i++)
				{
					if(A[i][j] == 0)
					{
						A[i][j]=A[i+1][j];
						A[i+1][j]=0;
					}
				}
			}
		}
		
		//combine any matching
		r=0;
		for (j=0;j<4;j++)
		{
			for (i=0;i<3;i++)
			{
				if((A[i+1][j] == A[i][j])&&(A[i][j]!=0))
				{
					A[i][j]=A[i][j]*2;
					score = score + A[i][j];
					A[i+1][j]=0;
				}
				else
				{
					r++;
				}
			}
		}
		if((e==4)&&(r>=12))
		{
		system("clear");
		printf("\nERROR: Invalid Command\n");
		continue;
		}
		//shift every number up
		for(k=0; k<3; k++)
		{
			for (j=0;j<4;j++)
			{
				for (i=0;i<3;i++)
				{
					if(A[i][j] == 0)
					{
						A[i][j]=A[i+1][j];
						A[i+1][j]=0;
					}
				}
			}
		}
	}

	
//User Quit
	if (d == 'q')
	{
		printf("\n\tThank you for Playing!\n\tScore: %d\n\n", score);
		for (i=0;i<4;i++)
		{
			for (j=0;j<4;j++)
			{
				if (A[i][j]==0)
				{
					fprintf(ending, "[    ]  ");
				}	
				else
				{
					fprintf(ending, "[%4d]  ", A[i][j]);
				}				
			}
			fprintf(ending, "\n");
		}
		exit(0);
	}
	
	// Number is randomly generated and place is randomly determined
	while(x==z)
	{
		q = rand()%4;
		p = rand()%4;
		if (A[q][p] == 0)
		{
			A[q][p] = rand()%2*2+2;
			x=z+1;
		}
	}
	z++;
}
	
return(0);
}

