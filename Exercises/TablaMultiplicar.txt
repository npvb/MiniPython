class TablaMultiplicar:
	
	def mostrartabla(num):
		inicio = num
		fin = num * 12

		while inicio<=fin:
			print inicio, " "
			inicio = inicio + num
		
	def main:
		x = 1
		print "Ingrese Numero: "
		read x
		mostrartabla(x)