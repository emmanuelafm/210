import re
import string
from collections import defaultdict 

filename = 'CS210_Project_Three_Input_File.txt'
newfile = 'frequency.dat'

def ListFrequency():
    # Creates defaultdict named item_frequencies
    item_frequencies = defaultdict(int) 

    # Opens file
    with open(filename, "r") as infile:
        # Reads each item without counting newline
	    lines = infile.read().splitlines()
	    for row in lines:
            # Adds frequency of item
		    item_frequencies[row] += 1
     
    # Prints each item and its frequency
    for item, freq in item_frequencies.items():
        print(item + ": " + str(freq))
    return 0
 

def ItemFrequency(v):
    count = 0

    # Opens file
    with open(filename, 'r') as infile:
        lines = infile.read().splitlines()
        for row in lines:
            # String must equal "row" to be added to "count"
            if v == row:
                count += 1

    # Prints user input and how many times the input appears in the list
    print(v, count)
    return 0 



def FileTransfer():
    item_frequencies = defaultdict(int) 
    
    # Opens file and reads each item
    with open(filename, "r") as infile:
	    lines = infile.read().splitlines()
	    for row in lines:
            # Adds frequency of item to defaultdict
		    item_frequencies[row] += 1   

    # Writes item and its frequency onto the new file, frequency.dat
    with open(newfile, 'w') as outfile:
        for item, freq in item_frequencies.items():
            outfile.write(item + " " + str(freq) + "\n")

    return 0 