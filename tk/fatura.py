import tkinter as tk
from box import Date
from os import system

class Fatura():
    """
    Mostra os clientes por estado.
    """
    def __init__(self):
        ReadDataDialog()
        self.janela = tk.Tk()
        self.bg = "#cccccc"
        self.tela = tk.Frame(self.janela, bd=5)
        self.texto = tk.Text(self.tela)
        self.scroll = tk.ttk.Scrollbar(self.tela, orient=tk.VERTICAL,
                                    command=self.texto.yview)
        self._main()

    def _main(self):

        self.janela.configure(bg=self.bg)
        self.tela.configure(bg=self.bg)
        self.tela.pack(side=tk.BOTTOM)
        self.texto.pack(side=tk.LEFT)
        self.scroll.config(command=self.texto.yview)
        self.scroll.pack(side=tk.RIGHT, fill=tk.Y)
        self.main_loop()

    def ler_dados(self, src):
        """
        Lê os dados do buffer.
        """
        with open("../extrato.txt", 'r') as file:
            self.texto.insert(tk.END, file.read())

    def main_loop(self):
        self.ler_dados("~/IFCE/S3/LP1/finop")
        self.janela.wait_window()


class ReadDataDialog():
    def __init__(self, bg="#bbbbbb"):
        self.top = tk.Tk()
        self.bg = bg
        self.entryes_frame = tk.Frame(self.top, bg=self.bg)

        self.output_cpf = tk.Label(self.entryes_frame, bg=self.bg, text="CPF")
        self.input_cpf = tk.Entry(self.entryes_frame, justify=tk.CENTER)

        self.send_button = tk.Button(self.top, bg="#000099",
            fg="white", text="Enviar", command=self._enviar)

        self.data = Date(self.entryes_frame, bg=self.bg)

        self.main()

    def _enviar(self):
        system("cd .. && ./finop fatura {0} {1}".format(self.input_cpf.get(), self.data.get()))
        self.top.destroy()
    
    def main(self):
        self.top.configure(bg=self.bg, bd=5)
        self.entryes_frame.pack()
        self.output_cpf.pack()
        self.input_cpf.pack()
        self.input_cpf.focus_set()
        self.data.pack(side=tk.TOP)
        self.send_button.pack(side=tk.BOTTOM)
        self.top.wait_window()

def main():
    Fatura()
