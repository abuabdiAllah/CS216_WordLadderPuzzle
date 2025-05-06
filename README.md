Problem Specification:
1. In the terminal window, make the CS216 directory, which you created in Lab1, your current
working directory(~/CS216/)
2. Create a directory underneath the CS216 directory named PA3Part2. Make the directory
PA3Part2 your current working directory.
3. Use the command curl to download a file named PA3Part2Source.zip from the link
(https://www.cs.uky.edu/~yipike/CS216/PA3Part2Source.zip) and save the file into your current
working directory (~/CS216/PA3Part2/):
$ curl -O https://www.cs.uky.edu/~yipike/CS216/PA3Part2Source.zip
4. Unzip the file you downloaded from step 3 using the command:
$ unzip PA3Part2Source.zip
It contains FOUR files: PA3Part2.cpp, Graph.h, FourLetterWords_simple.txt and
FourLetterWords.txt.
5. Copy the source file named Graph.cpp, you created in Lab11 into your current working
directory (~/CS216/PA3Part2/)using the command:
$ cp ../PA3Part1/Graph.cpp ./
6. Compile the source files using the command:
$ g++ PA3Part2.cpp Graph.cpp -o PA3Part2
It cannot pass the compilation, because the main function in PA3Part2.cpp tries to use Graph
class as a template class. In this Lab assignment, you need to work on:
• Modify the definition of the class named Graph, and make it into a template class, so
that each vertex of the Graph can be labeled by any data type, and the data type will be
specified later.
• Complete the source code in PA3Part2.cpp, starting from the comment line “// your
code starts here...” so that it can solve the problem described below.
• Complete the definition of the function named WordBuckets_addEdges() in
PA3Part2.cpp, starting from the comment line “// provide your code here...”
The word ladder puzzle was invented in 1878, by Lewis Carroll, the author of Alice in
Wonderland. In a word ladder puzzle you must make the change occur gradually by changing
one letter at a time. At each step you must transform one word into another word, you are not
allowed to transform a word into a non-word. In this Lab assignment, we are trying to
demonstrate a word ladder puzzle for a small group of four-letter words only. For example, let us
solve the “ladder” from the word “FOOL” to the word “SAGE”, and remember we only have a
small set of four-letter words available. We can solve this problem using a graph algorithm
similar to what we have done in Lab11. Here is an outline of what we are going to do:
• Represent the relationships between the words as a graph: each four-letter word
represents a Vertex in the Graph; there is an edge from one word to another if the two
words are only different by a single letter.
• Use the graph algorithm named Breadth First Search (BFS) to find a shortest path from
the starting word to the ending word.
The illustration in Figure 1 below, shows how to solve the FOOL to SAGE word ladder
problem in a small group of four-letter words. Notice that the graph is an undirected graph.

<img width="615" alt="image" src="https://github.com/user-attachments/assets/1c68dd07-8033-42c6-89ea-deb771f8a570" />
Figure 1: A small word ladder graph
The following sequence of words shows one possible solution to the problem posed above:
fool-->pool-->poll-->pall-->pale-->page-->sage
In this Project Assignment, the Graph associated with Figure 1 is built from reading the
collection of 15 four-letter words in a file, named FourLetterWords_simple.txt. To figure out
how to connect the words, we could compare each word in the collection with every other. When
we compare two words, we are looking to see how many letters are different. If the two words
in question are different by only one letter, we can create an edge between them in the graph.
For a small set of words this approach would work fine; however let’s look at an example in the
collection of four-letter words from another input file, named FourLetterWords.txt. We have a
list of 7,186 four-letter words in the collection. Roughly speaking, comparing one word to every
other word on the list is an 𝑂(𝑛 ! ) algorithm. For 7,186 words, 𝑛 ! is more than 51 million
comparisons (not counting possible 4 pairs of character comparison in each word).
Remember there is an edge from one word to another if the two words are only different
by a single letter. To figure out if there is an edge between any two words, we need compare
each word in the collection with every other. When we compare two words, we are looking to
see how many letters are different. If the two words in question are different by only one letter,
we can create an edge between them in the graph. 






<img width="615" alt="image" src="https://github.com/user-attachments/assets/1c68dd07-8033-42c6-89ea-deb771f8a570" />
