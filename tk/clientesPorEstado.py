import tkinter as tk
from os import system
from tkinter import ttk


class MostrarClientesPorEstado():
    """
    Mostra os clientes por estado.
    """
    def __init__(self):
        Dialog()
        self.janela = tk.Tk()
        self.janela.resizable(False, False)
        self.janela.title("Clientes por Estado")
        self.tela = tk.Frame(self.janela, bd=5)
        self.bg = "#cccccc"
        self.tela.configure(bg=self.bg)
        self.tela.pack()
        _columns = ("ID", "Nome","CPF", "Telefone",
                    "Município", "Contas")
        self.list = ttk.Treeview(self.tela, show="headings", columns=_columns)
        self.scroll = ttk.Scrollbar(self.tela, orient=tk.VERTICAL, command=self.list.yview)
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
        self.list.pack(side=tk.LEFT, fill=tk.Y)
        self.main_loop()


    def ler_dados(self, src):
        """
        Lê os dados do buffer.
        """
        with open("../buffer.csv", 'r') as file:
            for linhas in file.readlines():
                for linha in linhas.rstrip("\n").splitlines():
                    dados = linha.split(",")
                    self.list.insert('', 'end', values=(dados))
            self.list.insert('', 'end', values='-')

    def main_loop(self):
        self.ler_dados("~/IFCE/S3/LP1/finop")
        self.janela.wait_window()

class Dialog():
    def __init__(self, bg="#cccccc"):
        self.top = tk.Tk()
        self.top.resizable(False, False)
        self.top.configure(bg=bg, bd=5)
        self.top.title("Opções")
        self.output = tk.Label(self.top, bg=bg, font=("Capture it", 10),
                               text="Estado")
        self.output.pack()

        self.input_estado = tk.Entry(self.top, justify=tk.CENTER, font=("Capture it", 10))
        self.input_estado.focus_set()
        self.input_estado.pack(side=tk.LEFT)

        self.send_button = tk.Button(self.top, bg="#000099",
                                     fg="white", text="Enviar", command=self._enviar)
        self.send_button.pack(side=tk.RIGHT)
        self.top.wait_window()

    def _enviar(self):
        opcao = self.input_estado.get().upper()
        system("cd .. && ./finop clientes_estado {0}".format(opcao))
        self.top.destroy()
        

def main():
    MostrarClientesPorEstado()
