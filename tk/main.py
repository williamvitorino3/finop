#!/usr/bin/env python3

import tkinter as tk
from Principal import Principal

def full_screan(janela):
    """
    Retorna as coordenadas da janela.

    :argument janela: Instância da classe Tk()

    :return: String.
    """
    return "{0}x{1}".format(janela.winfo_screenwidth(),
                            janela.winfo_screenheight())


win = tk.Tk()
#win.geometry(full_screan(win))
win.title("tkFinop")
Principal(win)
win.configure(background='black')

win.mainloop()
