import tkinter as tk
from os import system

from tkinter import ttk


class ListarClientes():
    """
    Mostra os clientes por estado.
    """
    def __init__(self):
        """
        Construtor da classe.
        """
        self.command()
        self.janela = tk.Tk()
        self.tela = tk.Frame(self.janela, bd=5)
        self.list = ttk.Treeview(self.tela)
        self.scroll = ttk.Scrollbar(self.tela, orient=tk.VERTICAL,
                                    command=self.list.yview)

        self._main()

    def _main(self):
        """
        Método principal da classe.
        """
        self.tela.configure(bg="#cccccc")
        self.tela.pack()
        _columns = ("Nome","CPF", "Saldo")
        self.list["columns"] = _columns
        self.list["show"] = "headings"
        self.scroll.config(command=self.list.yview)

        self.list.column("Nome", width=200)
        self.list.heading("Nome", text="Nome")
        self.list.column("CPF", width=100)
        self.list.heading("CPF", text="CPF")
        self.list.column("Saldo", width=100)
        self.list.heading("Saldo", text="Saldo")

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

    def command(self):
        system("cd .. && ./finop clientes_lista")

def main():
    ListarClientes()
