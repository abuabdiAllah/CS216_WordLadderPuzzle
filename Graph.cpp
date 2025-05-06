/*
 * File: Graph.cpp
 * Course: CS216-002
 * Project: Project 3 Part 2
 * Purpose: Declaration of Graph class
 *          This class represents an undirected Graph (no weight on each edge)
 *          using adjacent map representation
 *          It contains one private data memeber: adjMap
 *          which represents the mapping from a Vertex, say u (key) to a set of vertices (value) which directly connect to u 
 *
 * Author: adam ibn Ahmed
 */
#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "Graph.h"
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <set>



// default constructor
template <typename T>
Graph<T>::Graph()
{
} 

// to check if an edge exists between v and w
template <typename T>
bool Graph<T>::hasEdge(T v, T w) const
{
	for (auto i = adjMap.begin(); i != adjMap.end(); i++)
    	{
        	if (i->first == v)//traverses the map until finds key  v                                      
		{
			set<T> mapValue;
            		mapValue = i->second; //set value of v to local set "mapValue"

			for (auto it = mapValue.begin(); it != mapValue.end(); it++)
    			{
        			if (*it == w)
        			{
            				return true;
        			}
			}
            		return false; //went through for loop and didn't return true: must be false	
        	}
	}
        //if it traverses the map and doesn't find the key v  //would have been better written like this for part one to be more applicable to cases where the checked point isn't the first one!
        cout<< "No vertex labeled: " << v << endl;
	return false;
}



// to add an edge beween v and w to the graph
template <typename T>
void Graph<T>::addEdge(T v, T w)
{
	static vector<set<T>> bucketInside(7185); 
	static int wordNumber = -1;
	 
	if(adjMap.find(v) != adjMap.end()) //the key in map so: this is not the 1st run for this word. Thus, we want to keep the vector index number the same since we are still dealing w/ the same word
          {
		bucketInside[wordNumber].insert(w);//insert the linked word into the set of v
          	adjMap[v] = bucketInside[wordNumber];
          }
        else // if the key doesn't exist (i.e.,not in map), we have finsihed with previous word
          {	
		wordNumber++; //so we can change the correlated set to the one correlated to next letter
		bucketInside[wordNumber].insert(w);//insert the linked word into the set of v
                adjMap[v].insert(bucketInside[wordNumber].begin(), bucketInside[wordNumber].end());
         }
}



template <typename T>
int Graph<T>::BFS(T s, T t, map<T, int>& distance, map<T, T>& go_through) const
{
	//check if s or t does not exist in map
	if ((adjMap.find(s) == adjMap.end()) || (adjMap.find(t) == adjMap.end())) return INVALID_VERTEX;

	//set the keys of distance to be the keys found in adjMap and intialize the values as -1
	for (auto i = adjMap.begin(); i != adjMap.end(); i++)
        {
                distance[i->first] = -1;
	}		

	
	//create empty double-ended queue
	deque<T> Q;

	//deal with starting point
	distance[s] = 0; //distance from starting point to itself is zero
	go_through[s] = s; //going from s to s will make us go through s
	Q.push_back(s);
	T current = s;

	//go through BFS process
	while((Q.size() != 0) && (current != t))
	{
		current = Q.front(); //at the beginning this is still s
		for (auto i = adjMap.begin(); i != adjMap.end(); i++)
        	{
                if (i->first == current)//traverses the map until finds key current                                     
                	{
                        	set<T> mapValue;
                        	mapValue = i->second; //set value of v to local set "mapValue"
				for (auto it = mapValue.begin(); it != mapValue.end(); it++)
                                {
                                        if (distance[*it] == -1)
                                        {
                                                distance[*it] = distance[current] + 1;
                                                //cout<< *it;
                                                //cout << distance[*it];
                                                go_through[*it] = current;
                                                Q.push_back(*it);
                                        }
                                }
    			}
		}	
		Q.pop_front(); //its done with the first item, needs to work on next item
	}
	return distance[t];
}




//map<T, set<T> > adjMap;
//const int NOPATH = -1;
//const int INVALID_VERTEX = -2;

#endif  /* GRAPH_CPP */
