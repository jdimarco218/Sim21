#!/usr/bin/env python
from __future__ import print_function

import os
import sys

import matplotlib.pyplot as plt

def main():
    if len(sys.argv) < 2:
        print("Usage:")
        print("  plotResults.py <Player name>...")
        return

    player_list = sys.argv[1:]
    chips_lists = [[]]
    shoes_lists = [[]]
    label_list = []
    curr_list = 0

    for i in range(len(player_list)):
        dirPath = os.path.dirname(os.path.realpath(__file__))
        relativePath = "/../results/" + str(player_list[i]) + ".csv"
        resultsPath = dirPath + relativePath

        f = open(resultsPath, 'r')
        lines = f.readlines()
    
        for j in range(len(lines)):
            if "#" in lines[j]:
                curr_list += 1
                chips_lists.append([])
                shoes_lists.append([])
                label_list.append(str(player_list[i]))
            else:
                chips_lists[curr_list].append(lines[j].split(",")[0])    
                shoes_lists[curr_list].append(lines[j].split(",")[1])    

    # Set up the plot
    plt.clf()
    for i in range(curr_list):
        plt.plot(shoes_lists[i], chips_lists[i], label=label_list[i])

    # Display results!
    plt.legend(loc=2)
    plt.show()


# Entry point
if __name__ == "__main__":
    main()
