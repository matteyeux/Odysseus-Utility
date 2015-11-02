CC = g++

all:
	@echo 'Building Odysseus-Utility...'
	@$(CC) Odysseus.cpp -o Odysseus
	@echo 'Succesfully built Odysseus'
