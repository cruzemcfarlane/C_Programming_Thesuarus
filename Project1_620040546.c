//620040546
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error_message();

main(int argc, char *argv[]){
       //check if the user entered data at the commandline
       if(argc == 3){
	       FILE *fpt, *fpt2;
	       char dic_file[20] = {""}; strcpy(dic_file, argv[1]); //file we are reading from
	       char out_file[20] = {""}; strcpy(out_file, argv[2]); //file we are printing to
	       
	       char dic_word[20] = {""}; //Search for words in file
	       
	       char word_list[200] = {""}; //store all the suggested words (max 10)
	       char *list_pt = word_list; //pointer to list of suggested words
	       char add = -20; //adjust the word list pointer by increments of 20

	       char original_word[20] = {""}; //Take user input
	       char input_word[20] = {""}; //Make copy of user input so we can manipulate it
	       int word_count = 0; //no more than 10 words

	       int len; //size of string entered by user
	       int select; //will be used to help select which word to use & insert into the output file
	       int var = 0; //will be used to help find array element

	       printf("Please enter a word: ");
	       scanf("%s", original_word); //request a word from the user
	       printf("\n");

	       strcpy(input_word, original_word); //copy user input
	       
	       fpt = fopen(dic_file, "r"); //open the file
	       
	       //check if the word exists in the dictionary
	       while(1){
		        fscanf(fpt, "%s", dic_word);

		        //if it does, tell the user we found it
		        if(strcmp(dic_word, input_word) == 0){
		                    printf("Found: %s\n", dic_word);
		                    break;
		        }//end if
		        
		        //if it does not, stop searching
		        else if(feof(fpt)){
		             printf("\nThis word doesn't exists in our thesaurus: %s!!!\n", input_word);
		             break;
		        }//end else
	       }//end while
	       
	       len = strlen(input_word); //set len as the size of user string input
	       printf("\nSuggestions found: \n");
	       
	       //search if there are words matching the user's entry
	       while(len > 0 && word_count < 11){
		                fseek(fpt, 1, SEEK_SET); //always start searching from the begining of the file
		                input_word[len--] = 0; //remove the last byte of the user's entry
		                
		                //now check if there is a matching
		                while(1){
		                         fscanf(fpt, "%s", dic_word);

		                         //if there is a matching, display it
		                         if(strcmp(input_word, dic_word) == 0){
		                                               printf("\t\t\t%d. %s\n", ++var, dic_word);
		                                               word_count++; //check when the limit of 10 words has been reached
								
							       add = add + 20; //adjust the word_list pointer
							       strcpy(list_pt+add, dic_word); //store the word into word_list array
		                                               break;
		                         }//end if
		                         
		                         //if we didn't find a matching, stop search
		                         else if(feof(fpt)){
		                              break;
		                         }//end else
		                }//end while
	       }//end while
	       fclose(fpt); //close the file being read from
	       
	       //if words were found, ask the user to decide what to do next
	       if(word_count > 0){
			printf("\nSelect a word from the list to use (# only)\n(To use your original instead, press 0): ");
			scanf("%d", &select);
			
			//either write the user's original input to the file
			if(select == 0){
				fpt2 = fopen(out_file, "w");
				fprintf(fpt2, "%s", original_word);
				fclose(fpt2);
				printf("\nSUCCESSFULL CREATED: %s, WITH ENTRY: %s\n", out_file, original_word);			
			}			
			
			//or write the one of the word options to the file
			else if(select >= 1 && select <= var){
				select--;
				fpt2 = fopen(out_file, "w");
				fprintf(fpt2, "%s", (list_pt+(select*20))); //move pointer to specific word & store it
				fclose(fpt2);
				printf("\nSUCCESSFULL CREATED: %s, WITH ENTRY: %s\n", out_file, (list_pt+select*20));
			}
			
			//should the user enter foolishness, display an error message
			else{
				printf("ERROR: Out of range!\n");
			}
	       }
	      
	      //if no words were suggested, just write the original word entered by user to the file
	      else{
			fpt2 = fopen(out_file, "w");
			fprintf(fpt2, "%s", original_word);
			fclose(fpt2);
			printf("\nHOWEVER, SUCCESSFULL CREATED: %s, WITH ENTRY: %s\n", out_file, original_word);		
			
	      }
	}//end if
	
	else{
		error_message(); //display error messages for commandline input
	}//end else
}//end main

//error messages for the commandline
void error_message(){
	printf("Error: improper argument(s)\n");
	printf("1. We are using the commandline for entry here\n");
	printf("2. Only 2 entry\n");
	printf("3. 1st entry should be where we are reading from\n");
	printf("4. 2nd entry should be where we are writing to\n");
	printf("5. Please add file extensions, eg .txt, .words\n");
}// end error_message
