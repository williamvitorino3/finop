import tkinter as tk
from tkinter.ttk import Progressbar
from os import system
from threading import _start_new_thread as thread


class LoadBar():
	def __init__(self, master):
		self.janela = master
		self.progresso = Progressbar(self.janela)

	def start(self, command=""):
		self.progresso.pack()
		thread(self.progresso.start, ())
		print("Start")
		#system(command)

	def stop(self):
		self.progresso.stop()
		self.janela.destroy()
		print("Stop")

def main():
	load = LoadBar(tk.Tk())
	load.start()
