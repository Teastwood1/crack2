// Thomas Eastwood
// 10-23-2025 - CS46 Prof. Brown


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings

#define STR_MAX 256

char* trim(char *str) {
    char *p = strchr(str, '\n');
    if (p) *p = '\0';
    return str;
}



// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    // Hash the plaintext
    char *plainHash = md5(plaintext, strlen(plaintext));

    // Open the hash file
    FILE *hashFile = fopen(hashFilename, "r");
    
    char *output = NULL;
    char line[STR_MAX];


    // Loop through the hash file, one line at a time.
    while(fgets(line, sizeof(line), hashFile)) {

        // Trim newline
        char *newline = strchr(line, '\n');
        if (newline) *newline = '\0';

        // Attempt to match the hash from the file to the
        // hash of the plaintext.
        if(strcmp(plainHash,line)==0)
        {
            output = strdup(plainHash); // allocate returnable memory
            break;
        }

    }

    // If there is a match, you'll return the hash.
    // If not, return NULL.

    // Before returning, do any needed cleanup:
    //   Close files?
    //   Free memory?
    fclose(hashFile);
    free(plainHash);

    // Modify this line so it returns the hash
    // that was found, or NULL if not found.
    return output;
}


int main(int argc, char *argv[])
{

    char dictionaryFileName[STR_MAX] = "rockyou100k.txt";
    char targetFileName[STR_MAX] = "hashes04.txt";

    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }


    // Open the dictionary file for reading.
    FILE *dictionary = fopen(dictionaryFileName, "r");
    

    // For each dictionary word, pass it to tryWord, which
    // will attempt to match it against the hashes in the hash_file.
    char line[STR_MAX];
    int count = 0;
    while(fgets(line, sizeof(line), dictionary)) {

        // If we got a match, display the hash and the word. For example:
        // 5d41402abc4b2a76b9719d911017c592 hello
        char *match = tryWord(trim(line),targetFileName);
        if(match){
            printf("%s = %s\n", match, trim(line));
            count++;
            }

    }
    
    // Close the dictionary file
    // Display the number of hashes that were cracked.
    // Free up any malloc'd memory?
    fclose(dictionary);
    printf("\nFile: \t\t%s\nDictionary: \t%s\n", targetFileName, dictionaryFileName);
    printf("\nFound [%04d] matches total\n", count);
}

