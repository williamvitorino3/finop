import tkinter as tk


class MostrarClientesPorEstado():
    """
    Mostra os clientes por estado.
    """
    def __init__(self):
        ReadDataDialog()
        self.janela = tk.Tk()

        self.frame_id = tk.Frame(self.janela)
        self.label_id = tk.Label(self.frame_id, text="ID")
        self.listbox_id = tk.Listbox(self.frame_id, width=3)
        self.label_id.pack()
        self.listbox_id.pack()

        self.frame_nome = tk.Frame(self.janela)
        self.label_nome = tk.Label(self.frame_nome, text="Nome")
        self.listbox_nome = tk.Listbox(self.frame_nome, width=20)
        self.label_nome.pack()
        self.listbox_nome.pack()

        self.frame_cpf = tk.Frame(self.janela)
        self.label_cpf = tk.Label(self.frame_cpf, text="CPF")
        self.listbox_cpf = tk.Listbox(self.frame_cpf, width=15)
        self.label_cpf.pack()
        self.listbox_cpf.pack()

        self.frame_fone = tk.Frame(self.janela)
        self.label_fone = tk.Label(self.frame_fone, text="Telefone")
        self.listbox_fone = tk.Listbox(self.frame_fone, width=15)
        self.label_fone.pack()
        self.listbox_fone.pack()

        self.frame_municipio = tk.Frame(self.janela)
        self.label_municipio = tk.Label(self.frame_municipio, text="Município")
        self.listbox_municipio = tk.Listbox(self.frame_municipio, width=15)
        self.label_municipio.pack()
        self.listbox_municipio.pack()

        self.frame_contas = tk.Frame(self.janela)
        self.label_contas = tk.Label(self.frame_contas, text="Contas")
        self.listbox_contas = tk.Listbox(self.frame_contas, width=3)
        self.label_contas.pack()
        self.listbox_contas.pack()

        self.frame_id.pack(side=tk.LEFT)
        self.frame_nome.pack(side=tk.LEFT)
        self.frame_cpf.pack(side=tk.LEFT)
        self.frame_fone.pack(side=tk.LEFT)
        self.frame_municipio.pack(side=tk.LEFT)
        self.frame_contas.pack(side=tk.LEFT)
        self.janela.mainloop()

        self.ler_dados("~/IFCE/S3/LP1/finop")

    def ler_dados(self, src):
        """
        Lê os dados do buffer.
        """
        file = open("buffer.csv", 'r')
        print(file.readlines())
        """
        for linha in file.readlines():
            dados = dados.split(", ")
            self.listbox_id.insert(tk.END, dados[0])
            self.listbox_nome.insert(tk.END, dados[1])
            self.listbox_cpf.insert(tk.END, dados[2])
            self.listbox_fone.insert(tk.END, dados[3])
            self.listbox_municipio.insert(tk.END, dados[4])
            self.listbox_contas.insert(tk.END, dados[5])
        """
        file.close()


class ReadDataDialog():
    def __init__(self):
        self.top = tk.Tk()
        self.output = tk.Label(self.top, text="Estado")
        self.output.pack()

        self.input_estado = tk.Entry(self.top)
        self.input_estado.pack()

        self.send_button = tk.Button(self.top, text="Enviar", command=self._enviar)
        self.send_button.pack()

        self.main_loop()

    def _enviar(self):
        with open("buffer.txt", 'w') as bff:
            bff.write(self.input_estado.get().upper())
        self.top.destroy()

    def main_loop(self):
        self.top.mainloop()

def main():
    MostrarClientesPorEstado()

if __name__ == '__main__':
    main()
