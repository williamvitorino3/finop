import tkinter as tk
from os import system
from tkinter import ttk
import load
from threading import _start_new_thread as thread
#from tkinter.ttk import Progressbar


class MostrarClientesPorEstado():
    """
    Mostra os clientes por estado.
    """
    def __init__(self):
        ReadDataDialog()
        self.janela = tk.Tk()
        self.tela = tk.Frame(self.janela, bd=5)
        self.tela.configure(bg="#cccccc")
        self.tela.pack()
        _columns = ("ID", "Nome","CPF", "Telefone",
                    "Município", "Contas")
        self.list = ttk.Treeview(self.tela)
        self.scroll = ttk.Scrollbar(self.tela, orient=tk.VERTICAL,
                                    command=self.list.yview)
        #self.list.insert('', 'end', text='Listbox', values=('15KB Yesterday mark'))
        self.list["columns"] = _columns
        self.list["show"] = "headings"
        self.scroll.config(command=self.list.yview)

        self.list.column("ID", width=30)
        self.list.heading("ID", text="ID")
        self.list.column("Nome", width=200)
        self.list.heading("Nome", text="Nome")
        self.list.column("CPF", width=100)
        self.list.heading("CPF", text="CPF")
        self.list.column("Telefone", width=100)
        self.list.heading("Telefone", text="Telefone")
        self.list.column("Município", width=100)
        self.list.heading("Município", text="Município")
        self.list.column("Contas", width=50)
        self.list.heading("Contas", text="Contas")
        self.scroll.pack(side=tk.RIGHT, fill=tk.Y)
        self.list.pack(side=tk.LEFT, fill=tk.X)
        self.main_loop()


    def ler_dados(self, src):
        """
        Lê os dados do buffer.
        """
        file = open("../buffer.csv", 'r')

        for linhas in file.readlines():
            for linha in linhas.rstrip("\n").splitlines():
                dados = linha.split(",")
                self.list.insert('', 'end', values=(dados))
        file.close()

    def main_loop(self):
        self.ler_dados("~/IFCE/S3/LP1/finop")
        self.janela.wait_window()


class ReadDataDialog():
    def __init__(self, bg="#bbbbbb"):
        self.top = tk.Tk()
        #self.load = LoadBar(self.top)
        self.top.configure(bg=bg, bd=5)
        self.output = tk.Label(self.top, bg=bg,
                               text="Estado")
        self.output.pack()

        self.input_estado = tk.Entry(self.top)
        self.input_estado.focus_set()
        self.input_estado.pack()

        self.send_button = tk.Button(self.top, bg="#000099",
            fg="white", text="Enviar", command=self._enviar)
        self.send_button.pack()

        self.main_loop()

    def _enviar(self):
        opcao = self.input_estado.get().upper()
        system("cd .. && ./finop clientes_estado {0}".format(opcao))
        self.top.destroy()

    def main_loop(self):
        self.top.mainloop()

def main():
    MostrarClientesPorEstado()
