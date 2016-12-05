#!/usr/bin/env python3

#####################################
##### Autor = William Vitorino. #####
#####################################

from os import system

system("git add *")
system('git commit -m "{0}"'.format(input("Comentários do commit:\n>>> ")))
system("git push origin master")
