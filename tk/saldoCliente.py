import tkinter as tk
from os import system
from box import Box
from tkinter import ttk


class SaldoAtualCliente():
    """
    Mostra os dados do cliente.
    """
    def __init__(self):
        Dialog()
        self.janela = tk.Tk()
        self.janela.resizable(False, False)
        self.bg = "#cccccc"
        self.box_nome = Box(self.janela, text="Nome", bg=self.bg)
        self.box_saldo = Box(self.janela, text="Saldo", bg=self.bg)
        self._columns = ("Conta", "Variação", "Saldo")
        self.tela = tk.Frame(self.janela, bg=self.bg)
        self.list = ttk.Treeview(self.tela)
        self.scroll = ttk.Scrollbar(self.tela, orient=tk.VERTICAL,
                                    command=self.list.yview)
        self._main()

    def _main(self):
        self.janela.configure(bg=self.bg, bd=5)
        self.tela.configure(bg=self.bg)
        self.tela.pack(side=tk.BOTTOM)


        self.box_nome.pack(side=tk.LEFT)

        self.box_saldo.pack(side=tk.LEFT)

        self.list["columns"] = self._columns
        self.list["show"] = "headings"
        self.scroll.config(command=self.list.yview)

        self.list.column("Conta", width=100)
        self.list.heading("Conta", text="Conta")

        self.list.column("Variação", width=100)
        self.list.heading("Variação", text="Variação")

        self.list.column("Saldo", width=100)
        self.list.heading("Saldo", text="Saldo")

        self.scroll.pack(side=tk.RIGHT, fill=tk.Y)
        self.list.pack(side=tk.LEFT, fill=tk.X)
        self.main_loop()

    def getNome(self, src):
        with open("../buffer.csv", 'r') as file:
            return file.readline().split(",")[0]


    def getSaldo(self, src):
        with open("../buffer.csv", 'r') as file:
            return file.readline().split(",")[-1].rstrip("\n")

    def ler_dados(self, src):
        """
        Lê os dados do buffer.
        """
        with open("../buffer.csv", 'r') as file:
            for linhas in file.readlines()[1:]:
                for linha in linhas.splitlines():
                    dados = linha.split(",")
                    self.list.insert('', 'end', values=(dados))
            self.list.insert('', 'end', values="-")

        self.box_nome.listbox.insert(tk.END, self.getNome("~/IFCE/S3/LP1/finop"))
        self.box_saldo.listbox.insert(tk.END, "R$ " + self.getSaldo("~/IFCE/S3/LP1/finop"))

    def main_loop(self):
        self.ler_dados("~/IFCE/S3/LP1/finop")
        self.janela.wait_window()

class Dialog():
    def __init__(self, bg="#bbbbbb"):
        self.top = tk.Tk()
        self.top.resizable(False, False)
        self.top.configure(bg=bg)
        self.output = tk.Label(self.top, bg=bg, text="CPF")
        self.output.pack()

        self.input_cpf = tk.Entry(self.top, justify=tk.CENTER)
        self.input_cpf.focus_set()
        self.input_cpf.pack()

        self.send_button = tk.Button(self.top, bg="#000099",
            fg="white", text="Enviar", command=self._enviar)
        self.send_button.pack()
        self.top.wait_window()

    def _enviar(self):
        system("cd .. && ./finop cliente_saldo {0}".format(self.input_cpf.get().upper()))
        self.top.destroy()

class ReadDataDialog():
    def __init__(self):
        self.top = tk.Tk()
        self.top.configure(bg=bg, bd=5)
        self.top.title("Opções")
        self.output = tk.Label(self.top, bg=bg,
                               text="CPF")
        self.output.pack()

        self.input_cpf = tk.Entry(self.top, justify=tk.CENTER)
        self.input_cpf.focus_set()
        self.input_cpf.pack()

        self.send_button = tk.Button(self.top, bg="#000099",
            fg="white", text="Enviar", command=self._enviar)
        self.send_button.pack()

        self.main_loop()

    def _enviar(self):
        system("cd .. && ./finop cliente_saldo {0}".format(self.input_cpf.get().upper()))
        self.top.destroy()

    def main_loop(self):
        self.top.wait_window()
"""
class Box():
    def __init__(self, janela, text="", bd=2, height=1, bg="white"):
        self.janela = janela
        self.texto = text
        self.borda = bd
        self.fundo = bg
        self.tamanho = height
        self._main()

    def _main(self):
        self.frame = tk.Frame(self.janela, bd=self.borda, bg=self.fundo)
        self.label = tk.Label(self.frame, bd=self.borda, text=self.texto, bg=self.fundo)
        self.listbox = tk.Listbox(self.frame, height=self.tamanho)

    def pack(self, side=tk.TOP):
        self.frame.pack(side=side)
        self.label.pack(side=tk.TOP)
        self.listbox.pack(side=tk.BOTTOM)
"""
def main():
    SaldoAtualCliente()
