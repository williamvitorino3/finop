import tkinter as tk
from os import system

import clientesPorEstado as op1
import saldoCliente as op2
import listaClientes as op3
import extratoMesAtual as op4
import Extrato as op5
import fatura as op6


class Principal():
    """Classe que implementa a janela principal do projeto."""
    def __init__(self, janela):
        self.janela = janela
        self.fonte_button = ("Monospace", 10)
        self.bg_button = "black"
        self.fg_button = "white"
        self.bd_button = 3
        self.width_button = 40
        self.frame_logo = tk.Frame(self.janela)
        self.label_logo = tk.Label(self.frame_logo, text=self.ler_buffer("./logo.sh"))
        self.frame_buttons = tk.Frame(self.janela, height=10)
        self.widgets()

    def widgets(self):
        """
        Método que organizaos widgets da tela.

        :return: None.
        """

        self.label_logo.configure(background='black', fg='white', font=("Monospace", 10, "bold"))
        
        self.button1 = tk.Button(self.janela, text="Listar clientes por estado", bd=self.bd_button,
                                 command=self.clientes_estado, width=self.width_button,
                                 background=self.bg_button, fg=self.fg_button,font=self.fonte_button)

        self.button2 = tk.Button(self.janela,text="Saldo atual do cliente", bd=self.bd_button,
                                 command=self.saldo_cliente, width=self.width_button,
                                 background=self.bg_button, fg=self.fg_button, font=self.fonte_button)

        self.button3 = tk.Button(self.janela, text="Listar saldo dos clientes", bd=self.bd_button,
                                width=self.width_button, background=self.bg_button,
                                fg=self.fg_button, font=self.fonte_button, command=self.listarClientes)

        self.button4 = tk.Button(self.janela, text="Extrato mês atual", bd=self.bd_button,
                                 command=self.extratoAtual, width=self.width_button,
                                 bg=self.bg_button,fg=self.fg_button, font=self.fonte_button)

        self.button5 = tk.Button(self.janela, text="Extrato mês anterior", bd=self.bd_button,
                                 width=self.width_button, background=self.bg_button,
                                 fg=self.fg_button, font=self.fonte_button, command=self.extrato)

        self.button6 = tk.Button(self.janela, text="Fatura do cartão de crédito", bd=self.bd_button,
                                 width=self.width_button, background=self.bg_button, fg=self.fg_button,
                                 font=self.fonte_button, command=self.fatura)

        self.button_exit = tk.Button(self.janela, text="Sair", command=self.janela.quit, bd=self.bd_button)
        self.button_exit.configure(width=self.width_button, background=self.bg_button, fg=self.fg_button, font=self.fonte_button)

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

    def sair(self):
        raise Exception(" error")

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
    
    def restart(self):
        self.janela = tk.Tk()
        self.janela.title("tkFinop")
        self.janela.configure(background='black')
        Principal(self.janela)

    def clientes_estado(self):
        self.janela.destroy()
        op1.main()
        self.restart()
    
    def saldo_cliente(self):
        self.janela.destroy()
        op2.main()
        self.restart()

    def listarClientes(self):
        self.janela.destroy()
        op3.main()
        self.restart()

    def extratoAtual(self):
        self.janela.destroy()
        op4.main()
        self.restart()

    def extrato(self):
        self.janela.destroy()
        op5.main()
        self.restart()
    
    def fatura(self):
        self.janela.destroy()
        op6.main()
        self.restart()

    def run(self):
        self.janela.mainloop()
