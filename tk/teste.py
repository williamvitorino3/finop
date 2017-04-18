# -*-coding: utf-8-*-

from tkinter import *
from tkinter import ttk
from calendar import monthcalendar as mc
import time

from clientesPorEstado import MostrarClientesPorEstado as mostrar

root = Tk()

class Main():
	def __init__(self, master):
		self.janela = master
		self.abas = ttk.Notebook(self.janela)
		self.abas.pack()
		self.frame1 = Frame(self.abas)
		self.label1 = Label(self.frame1, text="Aba 1")
		self.frame1.pack()
		self.label1.pack()
		self.abas.add(self.frame1, text="Aba 1")

		self.frame2 = Frame(self.abas)
		self.label2 = Label(self.frame2, text="Aba 2")
		self.frame2.pack()
		self.label2.pack()
		self.abas.add(self.frame2, text="Aba 2")

		self.frame3 = Frame(self.abas)
		self.label3 = Label(self.frame3, text="Aba 3")
		self.frame3.pack()
		self.label3.pack()
		self.abas.add(self.frame3, text="Aba 3")
		
		self.frame4 = Frame(self.abas)
		#self.label4 = Label(self.frame4, text="Aba 4")
		self.frame4.pack()
		self.abas.add(self.frame4, text="Aba 4")
		new = mostrar(self.frame4)
		#self.label4.pack()
		

class calendario(object):
	def selec_data(self, event=None):
	    try:
	        if self.wid:
	            self.wid.configure(relief=FLAT)
	    except:
	        pass
	    self.wid = event.widget
	    data = []
	    data.append(self.wid["text"])
	    data.append(self.mes)
	    data.append(self.ano)
	    self.wid.configure(relief=SUNKEN)
	    return data #Retona a data numa lista no formato dia, mes, ano, [00, 00, 0000]

	def soma_mes(self):
		self.mes = self.mes + 1
		if self.mes > 12:
		    self.mes = 1
		    self.ano = self.ano + 1
		self.widgets(self.mes, self.ano)

	def subtrai_mes(self):
	    self.mes -= 1
	    if self.mes < 1:
	        self.mes = 12
	        self.ano -= 1
	    self.widgets(self.mes, self.ano)

	def soma_ano(self):
	    self.ano += 1
	    self.widgets(self.mes, self.ano)

	def subtrai_ano(self):
	    self.ano -= 1
	    self.widgets(self.mes, self.ano)

	def ret_hoje(self, event=None):
	    self.tempo = time.localtime()
	    self.mes = int(self.tempo[1])
	    self.ano = int(self.tempo[0])
	    self.dia = int(self.tempo[2])
	    self.widgets(self.mes, self.ano, self.dia)

	def cal (self, master=None, mes=None, ano=None, dia=None):
	    self.f = Frame(master, height=40)
	    self.f.grid()
	    self.f1 = Frame(self.f)
	    self.f1.grid(row=0, column=0, sticky=N)
	    self.f2 = Frame(self.f)
	    self.f2.grid(row=2, column=0)
	    self.widgets( mes, ano, dia)
	    li = Button(self.f2, text='<<', command=self.subtrai_ano, width=1)
	    li.grid(row=0, column=0, sticky=W+S)
	    li1 = Button(self.f2, text='<', command=self.subtrai_mes, width=1)
	    li1.grid(row=0, column=1, sticky=E+S)
	    re = Button(self.f2, text='>', command=self.soma_mes, width=1)           
	    re.grid(row=0, column=3, sticky=W+S) 
	    re1 = Button(self.f2, text='>>', command=self.soma_ano, width=1)
	    re1.grid(row=0, column=4, sticky=E+S)

	def widgets(self, mes=None, ano=None, dia=None):
	    try:
	        if self.f3:
	            self.f3.destroy()
	    except:
	        pass
	    self.var1 = StringVar()
	    mes2 = str(mes)
	    if len(mes2) == 1:
	        mes2 = str(0)+mes2

	    ym = mes2+'/'+str(ano)
	    self.var1.set(ym)
	    self.ano_mes = Label(self.f2, textvariable=self.var1, cursor="watch")
	    
	    self.ano_mes.grid(row=0, column=2)
	    self.ano_mes.bind("<Button-1>", self.ret_hoje)
	    self.f3 = Frame(self.f)
	    self.f3.grid(row=1, column=0)
	    x = mc(ano, mes)
	    dias = ("S", "T", "Q", "Q" ,"S","S" ,"D")
	    for n in range(7):    
	        v = StringVar()
	        l = Label(self.f3, textvariable=v)
	        l.grid(row=0, column=n)
	        v.set(dias[n])
	    for n in range(7):
	        for o in range(len(x)):
	            var = StringVar()
	            if x[o][n] == 0:
	                b = Label(self.f3, text=" ", width=3)
	                b.grid(column=n, row=o+1)
	            else:
	                b = Label(self.f3, textvariable=var, foreground="blue", width=3, takefocus=1)
	    
	                if n == 5 or n == 6:
	                    b.configure(fg="red")
	                b.bind("<Button-1>", self.selec_data)
	                b.grid(column=n, row=o+1)
	                var.set(x[o][n])
	                if x[o][n] == dia:
	                    b.configure(bg="brown")
	        if len(x) == 5:
	            for n in range(7):
	                l = Label(self.f3, text="  ")
	                l.grid(row=o+2, column=n)
	        if len(x) == 4:
	            for n in range(7):
	                l = Label(self.f3, text="  ")
	                l.grid(row=o+2, column=n)
	                l = Label(self.f3, text="  ")
	                l.grid(row=o+3, column=n)

	def __init__(self, master=None):
	    self.tempo = time.localtime()
	    self.mes = int(self.tempo[1])
	    self.ano = int(self.tempo[0])
	    self.dia = int(self.tempo[2])
	    self.cal(master, self.mes, self.ano, self.dia)

if __name__ == "__main__":
    root.title("Calendário")
    root.geometry("200x170")
    #calendario(root)
    Main(root)
    root.mainloop()