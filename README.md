Flight Simulator
=======

First milestone
-----------
_Contributors_: Alonsho, dorgamliel.  
[link](https://github.com/Alonsho/MileStone1) to our GitHub repository.

**Milestone description:** The main concept of this project is to send commands to a flight simulator (client to server), while receiving flight information from it, simultaneously  (also client to server, in the opposite direction).
Particularly, the program parses a text file, which contains a code in a made up programming language (instructions were given in advance), with flight instructions, and eventually sends it to the simulator server.

**Compilation instructions:** Simply compile all cpp files in repository. In addition, include -pthread in command. You may also use 'make compile' to compile and 'make run' to run the program. note the program recieves a script as an argument.
In order to run the program, download the flight simulator (attached link below), and run the simulator (**after** running the program) with the following commands (add it in "settings"):   
--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small    
--telnet=socket,in,10,127.0.0.1,5402,tcp  
Finally, Run the simulator.


**An important remark:** As written above, this project is in the making.  For now, only the first part of the whole project is complete. All of the description above relates to the current milestone.

A [link](https://www.flightgear.org/download/) to the flight simulator download.
