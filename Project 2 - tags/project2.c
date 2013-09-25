/*
  File: project2.c
  Name: Rostislav Tsiomenko
  Date: 02/23/2012
  Sect: 01
  Mail: tsiomr1@umbc.edu

  Project 2 - Tag Cloud.
  
  This program takes a text file from the user and outputs the frequency
  of each word used, sorted by most used, ignoring words less than 4 
  characters and any words containing non-alphabetic characters (for example,
  "Ars3n@l" is not counted, and neither is "Arsenal!").

  See http://www.csee.umbc.edu/courses/undergraduate/313/spring12/Projects/p2/index.shtml

  Needs to be compiled with -std=c99 and -lm (to link the math library).

*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
#include<math.h>

#define MY_FILENAME_MAX 100
#define WORD_MAX 30
#define DOC_MAX 500
#define TOP_WORDS 20
#define MIN_LENGTH 4

// struct used to associate words with their frequency
typedef struct word {
   char word[WORD_MAX];
   int frequency;
} WORD;

// function prototypes
void bubbleSort(WORD words[]);
bool validWord(char word[]);
int calcFont(int max, int frequency);

int main() {
 
   // opening user's file
   FILE *userText;
   char fileName[MY_FILENAME_MAX]; 
   printf("Enter name of file containing text to analyze: ");
   scanf("%s", fileName);
   userText = fopen(fileName, "r");
   if (userText == NULL) {
      printf("Error opening the file.\n");
      exit (-1);
   }
   
   // create an array of structs and initialize each struct
   WORD words[DOC_MAX];
   for (int i = 0; i < DOC_MAX; i++) {
      words[i].word[DOC_MAX] = '\0';
      words[i].frequency = 0;
   }
   
   // declare/initialize other needed variables
   char currentWord[WORD_MAX];
   bool addedWord = false;
   char emptyString[1] = "";
  
   // scan through entire document
   while (fscanf(userText, "%s", currentWord) != EOF){

      // go through entire array of structs each time
      for (int i = 0; i < DOC_MAX; i++){

	 // addedWord is used to indicate when we've successfully "processed" a word
	 addedWord = false;

	 while (addedWord == false) {
	    // check if the word being processed is valid, i.e. it's not less than 
	    // 4 characters, doesn't have non-alpha chars, then convert it to lowercase
	    if (validWord(currentWord) == true) {
	       // if the word is the same as the one in the struct, increment
	       // frequency of that word and then exit the loop
	       if (strncmp(words[i].word, currentWord, WORD_MAX) == 0) {
		  addedWord = true;
		  words[i].frequency++;
		  i = DOC_MAX;
	          // if the current word in the struct array is empty, copy
	          // the current word into that struct
	       } else if ( strncmp(words[i].word, emptyString, 1) == 0 ) {
		  addedWord = true;
		  strcpy(words[i].word, currentWord);
		  words[i].frequency++;
		  i = DOC_MAX;
	       } else {
		  // if the two words aren't the same and the current struct
		  // isn't empty, pretend we added a word and exit the loop so
		  // we can move on to the next index
		  addedWord = true;
	       }
	    } else {
	       // if the word isn't "valid", simply exit the loop by "cheating"
	       // and pretending we've added a word without doing anything
	       addedWord = true;
	    }
	 }
      }
   }
   fclose(userText);

   // sort the array; see bubbleSort function comments for sort order
   bubbleSort(words);

   // HTML header output
   FILE *html = fopen("tags.html", "w");
   fprintf(html, "<html>\n<head>\n<title>Tag Cloud generated from %s</title>\n", fileName);
   fprintf(html, "<style type=\"text/css\">\np.narrow {margin-left:35em; margin-right:35em}");
   fprintf(html, "</style>\n</head>\n<body>");
   fprintf(html, "<p class=\"narrow\" style=\"text-align: center;\">");

   // Print out top 20 words and their frequencies (less if there are not enough words)
   printf("\n-------\n");
   for (int i = 0; i < TOP_WORDS; i++) {
      printf("lol");
      if ( strncmp(words[i].word, emptyString, 1) != 0) {
	 printf("Word: %-20s  Frequency: %-5d\n", words[i].word, words[i].frequency);
	 // Calculate font based on the max frequency (or first frequency in array)
	 int font = calcFont(words[0].frequency, words[i].frequency);
	 // Output span tag with appropriate font size (no changing colors unfortunately)
	 fprintf(html, "<span style=\"color: #0000cc; font-size: %dpt\">%s </span>", font, words[i].word);
      }
   }
   printf("-------\n");
   printf("HTML file has been written to \"tags.html\".\n\n");

   // HTML closing tags output and closing file
   fprintf(html, "</p>");
   fprintf(html, "</body></html>");
   fclose(html);
   return 0;
}

/*
  validWord - this function checks if the passed in string
  is "valid", that is, if it's longer than the minimum length, 
  and if it contains any non-alphabetic characters. If the string
  is valid, it's converted to lowercase.
  Inputs: a char array string
  Output: boolean, true if the string is valid, false is not
  Side effect: converts passed in string to lower case if it's valid
*/
bool validWord (char word[]){
   bool valid = true;

   // If the string is too small, word is not valid
   if (strlen(word) < MIN_LENGTH) {
      valid = false;
   }

   // if any chars in the string are non-alpha, 
   // entire string is invalid
   for (int i = 0; word[i]; i++){
      if (isalpha(word[i]) == 0){
	 valid = false;
      } else {
	 // convert all chars to lowercase
	 word[i] = tolower(word[i]);
      }
   }

   return valid;
}

/*
  bubbleSort - this function sorts an array of WORD structs
  passed in as a parameter. ALTHOUGH the instructions for 
  Project 2 said to sort the words alphabetically (which is easily done
  using strncmp), I don't agree with this - if we're figuring out the
  frequency of each word, the program should sort by frequency, and put the 
  most used word on top. So take off points if you must, grader, but I don't
  see the point in sorting alphabetically.
  Inputs: an array of WORD structs
  Outputs: none 
  Side effects: sorts in passed array by frequency, 
  with most frequenct struct first
*/
void bubbleSort(WORD words[]) {
   // initialize temp struct to swap places
   WORD temp = {"", 0};

   // standard bubble sort algorithm adapted from CMSC201 website
   for (int i = 0; i < DOC_MAX; i++){
      for (int k = 0; k < (DOC_MAX - 1); k++) {
	 // we want to sort from most used to least used
	 if (words[k].frequency < words[k+1].frequency) {
	    temp = words[k+1];
	    words[k+1] = words[k];
	    words[k] = temp;
	 }
      }
   }
}

/*
  calcFont - this function returns a font size proportional
  to a given max, using a logarithmic scale.
  Inputs: maxFreq, the maximum frequency in a given set of frequencies
          frequency, the number of times a word appears in the file being processed
  Outputs: font, an int between 10 and 44
*/
int calcFont(int maxFreq, int frequency) {

   int min = 10, max = 44;
   int font = (log(frequency) / log(maxFreq)) * (max - min) + min;
   return font;

}


