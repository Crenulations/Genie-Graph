
# Genie-Graph
 
Genie Graph is a program for creating complex graphs of any kind using a custom "genetic processor" model. 

The program takes a gene file, consisting of a series of byte pairs (the operator and operand) and processes them based on a defined instruction set. This architecture is loosley based on 8bit processors such as the MOS 6502. 

Each node on the graph acts like its own version of this processor, each with seperate registers and instances of the code. The instruction set includes not only standard instructions such as jump, load registers, increment, etc.. They also contain instructions for spawning new nodes, forming new graph edges, and communicating with neighboring nodes. 

The effect of this is a system of graph creation which can create arbitrarily complex structures which can react intelligently to changes in its generation. 

Genie Graph can also be mutated similar to other evolutionary models. A single change to the gene code can produce anything from small to massive effects. By defining a loss function you can guide the evolutionary process in any number of directions.


Genie Graph is written mostly in C++ but a python version is in progress.


## Usage/Examples

![alt text](https://s11.gifyu.com/images/SgAha.gif)

