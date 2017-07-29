#! /usr/bin/env python3

from subprocess import *
from time import *
import sys
import os
import resource

class Colour:
    PURPLE = '\033[95m'
    CYAN = '\033[96m'
    DARKCYAN = '\033[36m'
    BLUE = '\033[94m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    END = '\033[0m'
    


def test(test_path, content):
    #info = resource.getrusage(resource.RUSAGE_CHILDREN)
    #print(info)
    bcontent = str.encode(content)
    t1 =time()
    p1 = Popen(["../TextMiningApp", "../words.bin"], stdout=PIPE, stdin=PIPE, stderr=PIPE)
    out1 = p1.communicate(input=bcontent)[0]
    t2 = time()
    p2 = Popen(["../ref/linux64/TextMiningApp", "../ref/linux64/words.bin"], stdout=PIPE, stdin=PIPE, stderr=PIPE)
    out2 = p2.communicate(input=bcontent)[0]
    t3 = time()
    if (out1 == out2):
        print(Colour.GREEN + "Match" + Colour.END)
    else:
        print(Colour.RED + "FAIL" + Colour.END)
    #print(info)
    print("SpellChecker made it in " + str(t2 - t1)[:6] + "s")
    print("The ref made it in " + str(t3 - t2)[:6] + "s")
    print("-----------------------------------------")
    
    
    


def check_folder(directory, path):
    for item in os.listdir(path):
        if not os.path.isfile(os.path.join(path, item)):
            print("\n\n#####  Testing files in " + item + "  #####\n\n")
            check_folder(item, os.path.join(path, item))
            
        else:
            file_path = os.path.join(path, item)
            with open(file_path, 'r') as f:
                f_content = f.read()
                print(f_content)
            test(file_path, f_content)
                
walk_dir = sys.argv[1]

print('walk_dir = ' + walk_dir)

# If your current working directory may change during script execution, it's recommended to
# immediately convert program arguments to an absolute path. Then the variable root below will
# be an absolute path as well. Example:
# walk_dir = os.path.abspath(walk_dir)
check_folder("poupou", walk_dir)                    
                
                                                                                                                    
