#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct word{


int length;
char *wrd;
struct word *nxt;

}word;

word* readFromFile() {
    FILE *fptr = fopen("WORDS.txt", "r");

    if (fptr == NULL) {
        perror("Error opening file");
        return NULL;
    }

    char receive[100];
    word *Head = NULL;

    while (fgets(receive, sizeof(receive), fptr)) {
        int len = strlen(receive);

        if (len > 0 && receive[len - 1] == '\n') {
            receive[len - 1] = '\0';

            word *newnode = (word*)malloc(sizeof(word));
            if (newnode == NULL) {
                perror("Memory allocation failed");
                fclose(fptr);
                return NULL;
            }

            newnode->length = len - 1;
            newnode->wrd = strdup(receive);
            newnode->nxt = Head;
            Head = newnode;
        }
    }

    fclose(fptr);
    return Head;
}

void freeWords(word *head) {
    word *current = head;
    while (current != NULL) {
        word *next = current->nxt;
        free(current->wrd); // Free the duplicated word
        free(current);     // Free the node
        current = next;
    }
}
// this function reads words from a file and will generate a random word with required lenght
char* words();


// this function is responsible for drawing the shape for hangman
void draw(int figure);

// this function gives a string of dashes that has the same size of the word which we will fill during the game
char* start(int len);

// this function is where the operation of the game happens
void game();

// this function will put the correct letter instead of a dash
void reveal(char* word,char *unkown,char letter);

// this function checks if the letter exists in the string and returns indexes
int state(char *word,char letter);

int main()
{
    word *Head=readFromFile();
    int diff,tottal_misses=9;
    printf("\n~~~~~~~~~~~~~WELCOME TO HANGMAN GAME~~~~~~~~~~~~~~~\n");
    printf("             please choose difficulty\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n1-->Easy   2-->Medium   3-->Hard\n");
    scanf("%d",&diff);

// checking if difficulty is valid
 while(diff<1||diff>3){

    fflush(stdin);
    system("cls");
    printf("HEEY incorrect difficulty!!!\nchoose again:\n");

    printf("1-->Easy   2-->Medium   3-->Hard\n");

    scanf("%d",&diff);

     }

 system("cls");

 int low_easy=2,up_easy=6,low_mid=7,up_mid=11,low_diff=12,high_diff=15,miss=0,p;
 // the difficulties are based on lower and upper bonds of amount of letter which is shown here

    if(diff==1)
        {

      game(Head,low_easy,up_easy);
     }

    else if (diff==2)
        {
        game(Head,low_mid,up_mid);
    }

    else if(diff==3)
        {
        game(Head,low_diff,high_diff);
    }

    printf("~~~~~~press 1 if you would like to play again otherwise press 0~~~~~~\n");
    scanf("%d",&p);

    if(p==1)
    {
        // will clear the screen and restart the game
        system("cls");
        main();
    }

 freeWords(Head);
    return 0;
}

char* words(word *Head,int len){
   int l=0,k;

   char *pass;

   pass=(char*)malloc(sizeof(char)*len);
   srand(time(NULL));

   k=rand()%30;  // to generate a random word from the file
   int x=-1;
   word *current=Head;

   while(current!=NULL){


    if(current->length==len){
        x++;
    }
    if(x==k)return current->wrd;

   current=current->nxt;

   }

   return pass;
}

char* start(int len){

   int k=0;
   char *initial=(char*)malloc(sizeof(char)*len);
for(int i=0;i<len;i++)
    initial[k++]='-';
   initial[k]='\0';
    return initial;
}

void game(word *Head,int low,int up){
 char letter;
 int miss=0,tottal_misses=11;

     srand(time(NULL));

    int len=(rand()%(up-low+1))+low; // here we will generate a random length for the word with respect to lower and upper bonds

    char*unknown=start(len);

    char*word=words(Head ,len);

        do{
            draw(miss); // to draw the shape
            printf("\n \n");
            puts(unknown);

              // in the case of a wrong input
                do{
                  fflush(stdin);
                  printf("enter a letter:");
                  scanf("%c",&letter);
                 }while((tolower(letter)<'a')||(tolower(letter)>'z'));

           if(state(word,letter)>-1)
           {
                 if(state(unknown,letter)<0)
                 {
                 reveal(word,unknown,letter);
                 }
            }

           else
           {
               miss++;
           }

  }while((miss<11)&&state(unknown,'-')>=0);


  if(miss<11)
            {

           printf("      *             *     ****    *.*****.    \n");
           printf("       *     *     *     *    *   *       * \n");
           printf("        *   * *   *      *    *   *       *\n");
           printf("         ***   ***        ****    *       *\n");
           puts(word);

            }

  else
  {
         system("cls");
         printf("  _ _ _  \n |     | \n |     | \n( )    |\n/|\\    |\n |     |\n |     |\n/ \\    |\n     __|__ ");
        printf("\n\n       *         ****        *****  **********\n");
        printf("       *        *    *      *            *\n");
        printf("       *       *      *      * * *       *\n");
        printf("       *        *    *            *      *\n");
        printf("       *****     ****        *****       *\n\n");
        printf("the correct word is :");
        puts(word);

  }
// free the memmory

free(unknown);
free(word);
}

void reveal(char *word,char *unknown,char letter ){
  int j=0;
   while(j<strlen(unknown))
     {
        if(tolower(word[j])==tolower(letter))
        {
         unknown[j]=word[j];
        }
      j++;
    }
   }

int state(char *word,char letter)
{
    int k=0;
    do{
        if(tolower(word[k])==tolower(letter))
        {
            return k;
        }
        k++;
    }while(k<strlen(word));

    return -1;
}

void draw(int input){

	system("cls");// will clear the the old drawing to put the new one

	switch(input)
	{

	    case 0:
	        	printf("\n\n\n\n\n        \n        \n        \n     _");
	        break;
	    case 1:
	        	printf("\n\n\n\n\n        \n        \n        \n     ____");
	        break;
		case 2:
		    	printf("\n\n\n\n\n        \n        \n        \n     __|__");
			break;
		case 3:
		     printf("\n\n\n\n\n       |\n       |\n       |\n     __|__");
			break;
		case 4:
		     printf("  _ _ _ \n       |\n       |\n       |\n       |\n       |\n       |\n       |\n     __|__ ");
			break;
		case 5:
		     printf("  _ _ _  \n |     | \n |     | \n       |\n       |\n       |\n       |\n       |\n     __|__ ");
			break;
		case 6:
		     printf("  _ _ _  \n |     | \n |     | \n( )    |\n       |\n       |\n       |\n       |\n     __|__ ");
			break;
		case 7:
		     printf("  _ _ _  \n |     | \n |     | \n( )    |\n/      |\n       |\n       |\n       |\n     __|__ ");
		break;
		case 8:
		     printf("  _ _ _  \n |     | \n |     | \n( )    |\n/ \\    |\n       |\n       |\n       |\n     __|__ ");
			break;
		case 9:
		    printf("  _ _ _  \n |     | \n |     | \n( )    |\n/|\\    |\n |     |\n |     |\n       |\n     __|__ ");
			break;
		case 10:
			printf("  _ _ _  \n |     | \n |     | \n( )    |\n/|\\    |\n |     |\n |     |\n/      |\n     __|__ ");
			break;
		case 11:
			printf("  _ _ _  \n |     | \n |     | \n( )    |\n/|\\    |\n |     |\n |     |\n/ \\    |\n     __|__ ");
			break;

	}
}
