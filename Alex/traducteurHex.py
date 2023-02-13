# Traduction des instructions assembleur en hexadecimal


OP_CODES = {
	'stop': 0,
	'add': 1,
	'sub': 2,
	'mult': 3,
	'div': 4,
	'and': 5,
	'or': 6,
	'xor': 7,
	'shl': 8,
	'shr': 9,
	'slt': 10,
	'sle': 11,
	'seq': 12,
	'load': 13,
	'store': 14,
	'jmp': 15,
	'braz': 16,
	'branz': 17,
	'scall': 18
}


# charge les instructions en assemblage depuis un fichier et les stocke dans une liste
def load_ASM(fileName):

	# place les lignes du fichier dans un tableau et supprime les espaces de fin de ligne
	lines = [line.rstrip('\n') for line in open(fileName)]
	# Retire les lignes vides
	lines = [line for line in lines if line != '']
	return lines


# reçoit une liste d'instructions d'assemblage et les convertit en listes de nombres
def analyze_instructions(asmInstructions):

	# Transforme chaque instruction en une liste de mots
	asmInstructions = [instruction.split() for instruction in asmInstructions]

	numInstructions = []
	# Converti chaque mot d'instruction en un nombre
	for asmInstr in asmInstructions:
		numInstr = []

		# Converti le nom de l'opération avec le code (Dico OP_CODE)
		numInstr.append(OP_CODES[asmInstr[0]])

		# converti les registres et les valeurs immédiates en valeurs numériques
		if len(asmInstr) > 1:

			# Retire le premier charatere 'r' du mot et garde seulement le nombre
			numInstr.append(int(asmInstr[1][1:]))

			# 0 -->  La valeur est un registre,
			# 1 --> La valeur est une valeur immediate
			if asmInstr[2][0] == 'r':
				numInstr.append(0)
			else:
				numInstr.append(1)

			# Supprime le premier caractère 'r' ou '#' d'un mot et ne garde que le nombre.
			numInstr.append(int(asmInstr[2][1:]))

			numInstr.append(int(asmInstr[3][1:]))

		numInstructions.append(numInstr)

	return numInstructions


# Reçoit une liste de listes de nombres et les convertit en instructions hexadécimales
def compute_hex_instructions(numInstructions):

	hexInstructions = []

	for numInstr in numInstructions:
		decInstr = 0
		decInstr += numInstr[0] << 27

		if len(numInstr) > 1:
			decInstr += numInstr[1] << 22
			decInstr += numInstr[2] << 21
			decInstr += numInstr[3] << 5
			decInstr += numInstr[4]

		hexInstructions.append(hex(decInstr))

	return hexInstructions


# Reçoit une liste d'instructions hexadecimale et un nom de fichier et écrit les instructions dans le fichier
def output_hex_instructions(hexInstructions, fileName):

	outputFile = open(fileName, 'w')
	for instr in hexInstructions:
		outputFile.write(instr + '\n')


inputFileName = 'data.txt'
outputFileName = 'hexInstructions.txt'

asmInstructions = load_ASM(inputFileName)
numInstructions = analyze_instructions(asmInstructions)
hexInstructions = compute_hex_instructions(numInstructions)

output_hex_instructions(hexInstructions, outputFileName)
