# MCE Algorithm
 This is my research project for Maximal Clique Enumeration(MCE) algorithm. The goal of my algorithm is to enumerate all maximal cliques larger than size *k*.
 
 In my algorithm, I combined three preprocessing preocedure:
 
 1. Filter Based on Degree
 2. Filter Based on *k-core* (Inspired by paper *Combining Efficient Preprocessing and Incremental MaxSAT Reasoning for MaxClique in Large Graphs*)
 3. Filter Based on Edges
 
 I have add greedy coloring procedure to my algorithm. I am still looking for a breakthrough to speed up my algorithm. I realized that I should change the way to represent graph to adjacency matrix and I will do that modification in next version.
 
 Shenghao Zou
