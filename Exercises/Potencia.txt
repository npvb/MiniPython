class CalcularPotencia:
	
	def Potencia(base,expo):
		if expo>1:
			return base*Potencia(base,expo-1)
		elif expo == 1:
			return base
		else:
			return 1

	def main:
		a = 1
		b = 1

		print "Ingrese Base:"
		read a
		print "Ingrese Potencia: "
		read b
		print "Potencia: ",Potencia(a,b)