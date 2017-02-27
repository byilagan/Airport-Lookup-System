Team Members
------------
Matthew Wenala (merging places server and airport client, binary search, readme,  debugging)
Anthony Absher (kd tree, knn algorithm, debugging)
Bailey Ilagan (IDL programs and code generation, merging places server and airport client 3-d places array, debugging, insertion sort)

Data Structures and Algorithms
------------------------------
	Places Data Structure
	---------------------
	- Uses a 3-d array to keep track of all the places data
	- First layer: all the state codes (StateNode)
 	- Second layer: all the letters the cities could start with (alphaNode)
 	- Third layer: all the cities (placeData)
	- Insertion sort is used on the state codes to put them in alpha order

 	Places Algorithm
 	----------------
 	- binary search at each layer of 3-d array
 	- error checking for ambiguitys and city not found

 	Airport Data Structure
 	----------------------
 	- Use a kd-tree to store all the airport data

 	Airport Algorithm
 	-----------------
 	- Uses a NthNearestNeighbor adaptation of the the third party function
 	- allow for the input of coodrinates and output of the 5 closest airorts


Third Party Code
----------------
- http://www.geeksforgeeks.org/k-dimensional-tree/ (kd tree) 

Strengths
---------
- Uses binary search on each layer of the 3-d array which has a total time complexity of O(3log(n))
- Nearest Neaighbor search runs O(log(n)) on average

Weakness
--------
- Program does not give the absolute closest airports
- Airports may repeat in the output

Instructions
------------
1. Compile using Makefile using "make"
2. Run airport server using "./airports_server&"
3. Run places server using "./places_server&"
4. Run client using "./places_client localhost [city] [state]"
	hint: Maybe need to do "Seattle City" instead of "Seattle" to remove any ambiguity