# Airport-Lookup-System
A three-tiered airport lookup system that maintains databases of US places and US airports and is able to provide airports located near a given place. Uses a three tiered RPC system that implements binary search for place lookup and a K-d tree with nearest neighbor algorithm for airport lookup. 

THIS PROGRAM IS NOT FULLY FUNCTIONAL. DOES NOT RETURN THE ABSOLUTE NEAREST AIRPORTS TO THE LOCATION. ALGORITHM NEEDS TO BE FIXED 

# Getting Started 
- A console-like program with linux
- Ability to transfer files to a console directory 
- Download all the files and put them in the same directory 

# How to Run 
- Use the command "make" to compile the program with the Makefile
- Use the command "./airports_server&" to run the airport server
- Use the command "./places_server&" to run the places server 
- Use the command "./places_client localhost [city] [state]" to query the system

# Built With
- C
- IDL 
- SunRPC

# Contributors 
- Bailey Ilagan 
- Anthony Absher
- Matthew Menala 
