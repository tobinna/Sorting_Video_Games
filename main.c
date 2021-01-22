#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 256 
#define MAX_NB_GAMES 18626



int swapnum =0;
int comparison = 0;



struct Game {
	int score, release_year;
	
	char title[MAX_BUFFER], platform[MAX_BUFFER];
};

struct Game arrt[385];
 
void swap(struct Game* a, struct Game * b) 
{ 
    struct Game t = *a; 
    *a = *b; 
    *b = t; 
} 
  


int partition (struct Game arr[], int low, int high) 
{ 
    int pivot = arr[high].score;    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        comparison++;
        // If current element is smaller than the pivot 
        if (arr[j].score < pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
        else if (arr[j].score > pivot){
          swapnum++;
        }
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 

int partition_year (struct Game arr[], int low, int high) 
{ 
    int pivot = arr[high].release_year;    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        comparison++;
        // If current element is smaller than the pivot 
        if (arr[j].release_year < pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
        else if (arr[j].release_year > pivot){
          swapnum++;
        }
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 

int
next_field( FILE *f, char *buf, int max ) {
	int i=0, end=0, quoted=0;
	
	for(;;) {
		// fetch the next character from file		
		buf[i] = fgetc(f);
		// if we encounter quotes then flip our state and immediately fetch next char
		if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
		// end of field on comma if we're not inside quotes
		if(buf[i]==',' && !quoted) { break; }
		// end record on newline or end of file
		if(feof(f) || buf[i]=='\n') { end=1; break; } 
		// truncate fields that would overflow the buffer
		if( i<max-1 ) { ++i; } 
	}

	buf[i] = 0; // null terminate the string
	return end; // flag stating whether or not this is end of the line
}

void
fetch_game (  FILE *csv, struct Game *p) {
	char buf[MAX_BUFFER];
  next_field( csv, p->title, MAX_BUFFER );
  next_field( csv, p->platform, MAX_BUFFER ); 
	next_field( csv, buf, MAX_BUFFER );      // load id into buffer as string
	p->score = atoi(buf);                       // then parse to integer
  next_field( csv, buf, MAX_BUFFER );
	p->release_year = atoi(buf); 
  
}
  

void quickSort(struct Game arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 
void quickSort_year(struct Game arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition_year(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 



void
print_pokemon( struct Game p ) {
	printf("\t| Score: %i |\t%s ", 
			p.score, p.title );
	//printf(" --------------------------------------------------------------\n");
	printf("| %s | Release Year: %i |\n",
			p.platform, p.release_year);
	printf(" --------------------------------------------------------------\n");
	
}

void sort_array(struct Game ar[]){
  int arr[MAX_NB_GAMES];
  for(int i=0; i<MAX_NB_GAMES; i++){
    arr[i] = ar[i].score; 
  }
    int n = sizeof(arr)/sizeof(arr[0]); 
    quickSort(ar, 0, n-1); 
  //   printf("Sorted array: \n"); 
  //   for(int i=0; i<MAX_NB_GAMES; i++){
  //   print_pokemon(ar[i]);
  // }
  printf("COMPARISON:\t%i\n", comparison);
  printf("SWAPS:\t%i\n", swapnum);
}
void print_top_ten(struct Game arr[], int MAX){
  int i=1;
  while (i<11){
    printf("RANK:\t%i", i);
    print_pokemon(arr[MAX-i]);
    i++;
  }
  // while (arr[MAX-i].score == 10){
  //   printf("RANK:\t%i", i);
  //   print_pokemon(arr[MAX-i]);
  //   i++;
  // }
}

void sort_array_year(struct Game ar[]){
  
  int j = 0;
  int i = 1;
  while (ar[MAX_NB_GAMES-i].score == 10){
    arrt[j] = ar[MAX_NB_GAMES-i];
    j++;
    i--;
  }
  //print_top_ten(arrt, j);
  
    int n = 385/sizeof(arrt[0]); 
    //n = j;
    quickSort_year(arrt, arrt[0].release_year, arrt[j].release_year); 
  //   printf("Sorted array: \n"); 
  //   for(int i=0; i<MAX_NB_GAMES; i++){
  //   print_pokemon(ar[i]);
  // }
  printf("COMPARISON:\t%i\n", comparison);
  printf("SWAPS:\t%i\n", swapnum);
  
}

void print_array(struct Game arrt[]){
  int i;
  for (i=0; i<385; i++){
    print_pokemon(arrt[i]);
  }
}


  
// Driver program to test above functions 
int main(int argc, char *argv[]) {

  FILE* f = (FILE*)malloc( sizeof( FILE ) ); 
  int nbGames = 0;
  struct Game * pArray = (struct Game*)malloc( sizeof( struct Game ) *MAX_NB_GAMES );
	//struct Game pArray[MAX_NB_GAMES];		
	struct Game p;
  
	
	f = fopen("ign (1).csv", "r");
	if(!f) { 
		printf("unable to open %s\n", argv[1]); 
		return EXIT_FAILURE; 
	}
	
	fetch_game( f, &p ); // discard the header data in the first line
	
	while(!feof(f)) {
		
		fetch_game( f, &pArray[nbGames] );
		//print_pokemon( pArray[nbGames] );
		// printf("\n");
		nbGames++;
	}
  sort_array(pArray);

  print_top_ten(pArray, MAX_NB_GAMES);

  //sort_array_year(pArray);
  //print_array(arrt);

  fclose(f);
	return EXIT_SUCCESS;
 
} 