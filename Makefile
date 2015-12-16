CC = g++
	
all:
		@echo 'ERROR: no platform defined.'
		@echo 'LINUX USERS: make linux'
		@echo 'MAC OS X USERS: make macosx'
	 	@echo 'WINDOWS USERS: make win'

linux : 
		@echo 'Building Odysseus Utility for Linux...'
		@$(CC) Odysseus.cpp -o Odysseus
		@echo 'Succesfully built Odysseus Utility for Linux'

macos : 
		@echo 'Building Odysseus Utility for OS X...'
		@$(CC) Odysseus.cpp
		@ mv a.out Odysseus
		@echo 'Succesfully built Odysseus Utility for OS X'

win :
		@echo Building Odysseus Utility for Windows...
		@$(CC) win_Odysseus.cpp -o Odysseus
		@echo Succesfully built Odysseus Utility for Windows		