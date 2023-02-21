all: programme_calcul

programme_calcul: programme_calcul.c
	python3 translator.py
	gcc -Wall programme_calcul.c -o programme_calcul

run: programme_calcul
	./programme_calcul fichier_traduit.bin data.bin

clean:
	rm -f programme_calcul

