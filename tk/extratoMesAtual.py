import tkinter as tk
from os import system
from tkinter import ttk
from box import Box

class ExtratoCliente():
    """
    Mostra os clientes por estado.
    """
    def __init__(self):
        ReadDataDialog()
        self.janela = tk.Tk()
        self.bg = "#cccccc"
        self.tela = tk.Frame(self.janela, bd=5)
        self.saldos = tk.Frame(self.janela)
        self.list = ttk.Treeview(self.tela)
        self.scroll = ttk.Scrollbar(self.tela, orient=tk.VERTICAL,
                                    command=self.list.yview)
        self.box_saldo_atual = Box(self.saldos, text="Saldo Atual", bg=self.bg)
        self.box_saldo_anterior = Box(self.saldos, text="Saldo anterior", bg=self.bg)
        self._main()

    def _main(self):
        self.saldos.pack()
        
        self.box_saldo_atual.pack(side=tk.LEFT)
        self.box_saldo_atual.listbox.insert(tk.END, self.getSaldoAtual("~/IFCE/S3/LP1/finop"))
        self.box_saldo_anterior.pack(side=tk.RIGHT)
        self.box_saldo_anterior.listbox.insert(tk.END, self.getSaldoAnterior("~/IFCE/S3/LP1/finop"))

        self.janela.configure(bg=self.bg)
        self.tela.configure(bg=self.bg)
        self.tela.pack(side=tk.BOTTOM)
        _columns = ("Data", "Operação","Valor")
        self.list["columns"] = _columns
        self.list["show"] = "headings"
        self.scroll.config(command=self.list.yview)

        self.list.column("Data", width=100)
        self.list.heading("Data", text="Data")
        self.list.column("Operação", width=100)
        self.list.heading("Operação", text="Operação")
        self.list.column("Valor", width=100)
        self.list.heading("Valor", text="Valor")
        self.scroll.pack(side=tk.RIGHT, fill=tk.Y)
        self.list.pack(side=tk.LEFT, fill=tk.X)
        self.main_loop()

    def getSaldoAnterior(self, src):
        with open("../buffer.csv", 'r') as file:
            return file.readline().split(",")[-1].rstrip()

    def getSaldoAtual(self, src):
        with open("../buffer.csv", 'r') as file:
            return file.readlines()[-1].split(",")[-1].rstrip()    

    def ler_dados(self, src):
        """
        Lê os dados do buffer.
        """
        file = open("../buffer.csv", 'r')

        self.dados = file.readlines()

        for linhas in self.dados[1:-1]:
            for linha in linhas.rstrip("\n").splitlines():
                info = linha.split(",")
                self.list.insert('', 'end', values=(info))
        file.close()

    def main_loop(self):
        self.ler_dados("~/IFCE/S3/LP1/finop")
        self.janela.wait_window()


class ReadDataDialog():
    def __init__(self, bg="#bbbbbb"):
        self.top = tk.Tk()
        self.top.configure(bg=bg, bd=5)
        self.output_conta = tk.Label(self.top, bg=bg,
                               text="Conta")
        self.output_conta.pack()

        self.input_conta = tk.Entry(self.top, justify=tk.CENTER)
        self.input_conta.focus_set()
        self.input_conta.pack()

        self.output_cpf = tk.Label(self.top, bg=bg,
                               text="CPF")
        self.output_cpf.pack()
        self.input_cpf = tk.Entry(self.top, justify=tk.CENTER)
        self.input_cpf.pack()

        self.send_button = tk.Button(self.top, bg="#000099",
            fg="white", text="Enviar", command=self._enviar)
        self.send_button.pack()

        self.main_loop()

    def _enviar(self):
        system("cd .. && ./finop extrato_atual {0} {1}".format(
                self.input_conta.get(), self.input_cpf.get()))
        self.top.destroy()
    
    def main_loop(self):
        self.top.mainloop()

def main():
    ExtratoCliente()
