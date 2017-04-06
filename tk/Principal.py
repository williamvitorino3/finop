import tkinter as tk
from os import system


class Principal():
    """Classe que implementa a janela principal do projeto."""
    def __init__(self, janela):
        self.janela = janela
        self.widgets()

    def widgets(self):
        """
        Método que organizaos widgets da tela.

        :return: None.
        """

        self.frame_logo = tk.Frame(self.janela)
        self.label_logo = tk.Label(self.frame_logo, text=self.ler_buffer("./logo.sh"))
        self.label_logo.configure(background='black', fg='white', font=("Monospace", 10, "bold"))

        self.frame_buttons = tk.Frame(self.janela, height=10)
        self.button1 = tk.Button(self.janela, text="Listar clientes por estado", bd=3)
        self.button1.configure(width=40, background='black', fg='white', font=("Monospace", 10))

        self.button2 = tk.Button(self.janela, text="Saldo atual do cliente", bd=3)
        self.button2.configure(width=40, background='black', fg='white', font=("Monospace", 10))

        self.button3 = tk.Button(self.janela, text="Listar saldo dos clientes", bd=3)
        self.button3.configure(width=40, background='black', fg='white', font=("Monospace", 10))

        self.button4 = tk.Button(self.janela, text="Extrato mês atual", bd=3)
        self.button4.configure(width=40, background='black', fg='white', font=("Monospace", 10))

        self.button5 = tk.Button(self.janela, text="Extrato mês anterior", bd=3)
        self.button5.configure(width=40, background='black', fg='white', font=("Monospace", 10))

        self.button6 = tk.Button(self.janela, text="Fatura do cartão de crédito", bd=3)
        self.button6.configure(width=40, background='black', fg='white', font=("Monospace", 10))

        self.button_exit = tk.Button(self.janela, text="Sair", command=self.janela.quit, bd=3)
        self.button_exit.configure(width=40, background='black', fg='white', font=("Monospace", 10))

        self.frame_logo.pack(side=tk.TOP)
        self.frame_buttons.pack(side=tk.LEFT)

        self.label_logo.pack()

        self.button1.pack()
        self.button2.pack()
        self.button3.pack()
        self.button4.pack()
        self.button5.pack()
        self.button6.pack()
        self.button_exit.pack()

    def ler_buffer(self, comando):
        """
        Lê a o arquivo de saída gerado a partir do argumento comando.

        :return: None
        """

        system("{0} > out.txt".format(comando))
        file = open("out.txt", 'r')
        entrada = file.read()
        file.close()
        return entrada
