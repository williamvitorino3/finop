import tkinter as tk


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
        self.listbox = tk.Listbox(self.frame, height=self.tamanho, justify=tk.CENTER)

    def pack(self, side=tk.TOP):
        self.frame.pack(side=side)
        self.label.pack(side=tk.TOP)
        self.listbox.pack(side=tk.BOTTOM)


class Date():
    def __init__(self, janela, text="", bd=2, height=1, bg="white"):
        self.janela = janela
        self.texto = text
        self.borda = bd
        self.fundo = bg
        self.tamanho = height
        self._main()

    def _main(self):
        self.frame = tk.Frame(self.janela, bd=self.borda, bg=self.fundo)
        self.frame_month = tk.Frame(self.janela, bd=self.borda, bg=self.fundo)
        self.label_month = tk.Label(self.frame_month, text="Mês", bg=self.fundo)
        self.box_month = tk.Spinbox(self.frame_month, justify=tk.CENTER, from_=1, to=31, width=7)
        self.frame_year = tk.Frame(self.janela, bd=self.borda, bg=self.fundo)
        self.label_year = tk.Label(self.frame_year, text="Ano", bg=self.fundo)
        self.box_year = tk.Spinbox(self.frame_year, justify=tk.CENTER, width=7)

    def pack(self, side=tk.TOP):
        self.frame.pack(side=side)
        self.frame_month.pack(side=tk.LEFT)
        self.label_month.pack()
        self.box_month.pack()
        self.frame_year.pack(side=tk.RIGHT)
        self.label_year.pack()
        self.box_year.pack()

    def get(self):
        return self.box_month.get() + " " + self.box_year.get()