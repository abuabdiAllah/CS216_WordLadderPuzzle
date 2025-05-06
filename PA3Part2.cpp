/*
 *course: CS216-002
 *Project: Project 3 Part 2
 *Purpose: to demonstrate a simple Word Ladder, using four-letter words as examples 
 *         create a graph from reading the collection of words in an input file
 *         each vertex is labeled with a four-letter word. If two words are only different by a single letter, there is an edge between them.
 *         repeatedly ask the user to choose a source vertex(word1), then a destination vertex(word2) (type enter to quit)
 *         and calculate how many steps of the "Word Ladder" from word1 to word2, 
 *         which is the distance of the shortest path from the source to the destination in the Graph
 *         then display the "Word Ladder" from word1 to word2, which is
 *         the shortest path from the source to the destination in the Graph
 *         It is the second part of Project 3.
 *Author: (adam ibn Ahmed)
 */

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <stack>
#include <algorithm>     // for transform() function
#include "Graph.h"

using namespace std;

// declare global variable (constant only)
const int ARGUMENTS = 1;   // define the required command line arguments

// define a function to decide the collection of edges for a graph
// using "Word Buckets Approach"
Graph<string> WordBuckets_addEdges(const vector<string>& words);

int main(int argc, char* argv[])
{
    // Check whether the number of command line arguments match the required one 
    if (argc != ARGUMENTS+1)
    {
	cout << "Warning: need exactly " << ARGUMENTS << " command line argument." << "\n";
        cout << "Usage: " << argv[0] << " inputfile_name" << "\n";
        return 1;
    }

    ifstream in_file;
    in_file.open(argv[1]);
    // Check whether the input file can be open successfully or not
    if (!in_file.good())
    {
        cout << "Warning: cannot open file named " << argv[1] << "!" << "\n";
        return 2;
    }
    
    // Read data from the input file, assume "good data" from the input file
    // each line of the input file constains one word from English dictionary
    string word;
    vector<string> words;

    while (in_file >> word)
    {
        // convert word to all lower-case letters
        // if assume that each word from the input file is in lower-case letters, this step can be ignored
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        words.push_back(word);
    }
    // close the input file
    in_file.close();

    // build the graph based on the collection of words
    // each word in the collection represents a Vertex in the graph
    // there is an edge from one word to another if these two words are only different by a single letter
    Graph<string> wordsG = WordBuckets_addEdges(words);


/*    if (wordsG.hasEdge("pale", "pull"))
            cout << "Assumption: it is a connected graph!" << endl;//used to check map is set-up properly
    else
            cout << "Assumption: it is a disjoint graph!" << endl;*/


    string word1, word2;

    while (true)
    {
        cout << "\n" << "\n";
        cout << "Welcome to CS216 Word Ladder!" << "\n";
        cout << "Please give me two English words, and I will convert the first into the second by modifying one letter at a time." << "\n";
        cout << "For the Demo purpose, let us try four-letter words only." << "\n";
        cout << "Please type the FIRST four-letter word (or type Enter to quit): " << "\n";
	    getline(cin, word1);
        
        if (word1 == "")
            break;
        
        cout << "Please type the SECOND four-letter word (or type Enter to quit): " << "\n";
	    getline(cin, word2);
        
        if (word2 == "")
            break;

        // convert both word1 and word2 to all lower-case letters
        transform(word1.begin(), word1.end(), word1.begin(), ::tolower);
        transform(word2.begin(), word2.end(), word2.begin(), ::tolower);
	
	
        map<string,int> distance;
	    map<string, string> go_through;
        int dis = wordsG.BFS(word1, word2, distance, go_through);//using BFS in Graph.cpp
        // Display the ladder distance from word1 to word2
        // Display the shortest path on the word ladder from word1 to word2
        // the ladder distance is defined as the number of edges on the shortest path from one vertex to another
        // the ladder distance of the same vertex to itself is 0 
        // if word1 and word2 are the same word, your program should display "Two words should be different." 
        // there is no path from word1 to word2 if its ladder distance is -1
        // there is no path from word1 to word2 if its ladder distance is -2, which means either word1 or/and word2 is invalid
        if ( dis == NOPATH || dis == INVALID_VERTEX)
	{
	    cout << "Invalid source Vertex and/or destination Vertex!" << "\n";//added to mimic samp outp
            cout << "There is no path from [" << word1 << "] to [" << word2 << "]" << "\n";
	}
        else if ( dis == 0)
        {
            cout << "Two words should be different." << "\n";
        }
        else
        {
            cout << "The ladder distance from [" << word1 << "] to [" << word2 << "] is " << dis << "-step away." << "\n";
            cout << "A ladder from [" << word1 << "] to [" << word2 << "]:" << "\n";
            // your code starts here...
	    vector<string> path; //make a vectro of backwards path, then reverse & print out correct path
	    
	    //get backwards
	    string nextVertex = word2;
            while (go_through[nextVertex] != word1)
            {
                path.push_back(go_through[nextVertex]);//at the end, in shaa Allah, vector has all strings (excluding word1 and word2) between word1 and word2 but backwards
                nextVertex = go_through[nextVertex];
            }

	    //print forwards
	    cout << word1;
	    reverse(path.begin(), path.end());
	    for(int i = 0; i < path.size(); i++)
	    {
	    	cout << " ---> " ;
		cout << path[i];
	    }
	    cout << " ---> " << word2 << "\n";
        }   
    }

    cout << "Thank you for using this program, bye..." << "\n";
    return 0;
}

/* define a function to decide the collection of edges for a graph
 * using "Word Buckets Approach"
 * Purpose: build a graph based on the collection of vertices
 *          each word stored in the vector, represents a Vertex in the graph
 *          there is an edge from one word to another 
 *          if these two words are only different by a single letter
 *@param words vector<string>: representing the collection of vertices, each string stored in the vector forms a vertex
 *@return Graph<string>: representing the graph built by
 *                       (1) the collection of vertices from words;
 *                       (2) the collection of edges are decided by if any two words are only different by a single letter
 *                         e.g. there is an edge between "cool" and "pool", but there is no edge between "cool" and "poll"
 *
 */
Graph<string> WordBuckets_addEdges(const vector<string>& words)
{    
    // build the graph
    // there is an edge from one word to another if the two words are only different by a single letter.
    // use "Word Bucket" solution described in Lab12 to efficiently decide whether an edge between two vertices
    Graph<string> wordsG; 
    // provide your code here 
    // implement "Word Buckets Approach" to decide if you need to call addEdge() member function between two vertices
	for(int i = 0; i < words.size(); i++)
	{
		for(int j = 0; j < words.size(); j++)
		{
			if(words[i] == words[j])   //use multiple if statements as "buckets", though not the intended ones as it seems
			{
				continue;
			}
			else if((words[i].substr(0,1) != words[j].substr(0,1)) && (words[i].substr(1,3) == words[j].substr(1,3)))//the first char is different but the rest is the same
			{
				wordsG.addEdge(words[i],words[j]);
			}

			else if((words[i].substr(0,1) == words[j].substr(0,1)) && (words[i].substr(1,1) != words[j].substr(1,1)) && (words[i].substr(2,2) == words[j].substr(2,2)))//the second char is different but the rest is the same
			{
				wordsG.addEdge(words[i],words[j]);
   			}


			else if((words[i].substr(0,2) == words[j].substr(0,2)) && (words[i].substr(2,1) != words[j].substr(2,1)) && (words[i].substr(3,1) == words[j].substr(3,1)))//the third char is different but the rest is the same
			
			{
				 wordsG.addEdge(words[i],words[j]);
			}	


			else if((words[i].substr(0,3) == words[j].substr(0,3)) && (words[i].substr(3,1) != words[j].substr(3,1)))//the last char is different but the rest is the same
			{
				 wordsG.addEdge(words[i],words[j]);
			}

		}
	}
    return wordsG;
}

