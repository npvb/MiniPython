class BubbleSort:
	arreglo=[70, 40,90,60, 80, 100,900, 34, 98, 120, 109, 14]

	def main:
		aux=0
		print "Arreglo Antes de Ordenar-> ",arreglo," "
		for x in 0...11:
			for y in 1...11:
				aux = arreglo[y]
				if arreglo[y] < arreglo[y-1]:
					arreglo[y] = arreglo[y-1]
					arreglo[y-1] = aux

		print "Arreglo Despues de Ordenar->",arreglo