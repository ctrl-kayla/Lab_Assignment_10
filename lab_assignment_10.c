/* Kayla Butler
COP 3502 Section 3
Lab Assignment 10 
18 April 2024 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 19 // Assuming maximum length of a word is 19

// Trie structure
struct Trie
{	
    int word;
    struct Trie *children[26];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie* node = pTrie;

    for (int i = 0; word[i] != '\0'; i++) // Interate to end of word
    {
        int idx = word[i] - 'a';
        if (node->children[idx] == NULL) // if node doesn't exist
        {
            node->children[idx] = createTrie();
        }
        node = node->children[idx];
    }

    node->word = 1; // End of word
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie* node = pTrie;

    for(int i = 0; word[i] != '\0'; i++) // Not equal to string terminator
    {
        int idx = word[i] - 'a'; // Character
        if (node->children[idx] == NULL){
            return 0;
        }
        node = node->children[idx];
    }
    return node->word;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for (int i = 0; i < 26; i++)
    {
        if (pTrie->children[i] != NULL)
        {
            deallocateTrie(pTrie->children[i]);
        }
    }

    free(pTrie);
}


// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* trie = malloc(sizeof(struct Trie));

    trie->word = 0;

    // Each point to NULL
    for (int i = 0; i < 26; i++)
    {
        trie->children[i] = NULL;
    }

    // return pointer to new root
    return trie;

}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *fp = fopen(filename, "r"); // Open file for reading

    // Check if file exists
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return 0;
    }

    int numWords = 0;
    char word[MAXLEN];
    fscanf(fp, "%d", &numWords);

    for (int i = 0; i < numWords; i++)
    {
        pInWords[i] = (char*)malloc(sizeof(char*) * MAXLEN + 1);
        fscanf(fp, "%s", pInWords[i]);
    }

    fclose(fp);
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}