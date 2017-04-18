# -*- coding: utf-8 -*-

import tkinter as tk
from tkinter import ttk
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
        self.fonte_button = ("Capture it", 10)
        self.bg_button = "black"
        self.fg_button = "white"
        self.bd_button = 3
        self.width_button = 40
        self.frame_logo = tk.Frame(self.janela, bd=5, bg=self.bg_button)
        self.label_logo = tk.Label(self.frame_logo, text="FINOP")
        self.frame_buttons = tk.Frame(self.janela, height=10, bd=5)
        self.label_logo.configure(background='black', fg='white', font=("Capture it 2", 80))
        self.label_logo.pack()
        self.frame_logo.pack(side=tk.TOP)
        self.widgets()


    def widgets(self):
        """
        Método que organizaos widgets da tela.

        :return: None.
        """


        self.button1 = tk.Button(self.janela, text="Listar clientes por estado", bd=self.bd_button,
                                 command=op1.main, width=self.width_button,
                                 background=self.bg_button, fg=self.fg_button,font=self.fonte_button)

        self.button2 = tk.Button(self.janela,text="Saldo atual do cliente", bd=self.bd_button,
                                 command=op2.main, width=self.width_button,
                                 background=self.bg_button, fg=self.fg_button, font=self.fonte_button)

        self.button3 = tk.Button(self.janela, text="Listar saldo dos clientes", bd=self.bd_button,
                                width=self.width_button, background=self.bg_button,
                                fg=self.fg_button, font=self.fonte_button, command=op3.main)

        self.button4 = tk.Button(self.janela, text="Extrato mês atual", bd=self.bd_button,
                                 command=op4.main, width=self.width_button,
                                 bg=self.bg_button,fg=self.fg_button, font=self.fonte_button)

        self.button5 = tk.Button(self.janela, text="Extrato mês anterior", bd=self.bd_button,
                                 width=self.width_button, background=self.bg_button,
                                 fg=self.fg_button, font=self.fonte_button, command=op5.main)

        self.button6 = tk.Button(self.janela, text="Fatura do cartão de crédito", bd=self.bd_button,
                                 width=self.width_button, background=self.bg_button, fg=self.fg_button,
                                 font=self.fonte_button, command=op6.main)

        self.button_exit = tk.Button(self.janela, text="Sair", command=self.janela.quit, bd=self.bd_button,
                                     width=self.width_button, background=self.bg_button, fg=self.fg_button,
                                     font=self.fonte_button)



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

    def run(self):
        self.janela.mainloop()
