proteinTranslator: obj/protein_utils.o obj/file_utils.o
	gcc -Wall -g obj/file_utils.o obj/protein_utils.o src/proteinTranslator.c -o proteinTranslator

obj/protein_utils.o: src/protein_utils.c src/protein_utils.h
	gcc -Wall -g src/protein_utils.c -c -o obj/protein_utils.o

obj/file_utils.o: src/file_utils.c src/file_utils.h 
	gcc -Wall -g src/file_utils.c -c -o obj/file_utils.o

clean: 
	rm -rf obj/* proteinTranslator proteinTranslator.dSYM