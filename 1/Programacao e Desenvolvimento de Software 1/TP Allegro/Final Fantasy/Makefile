ALLEGRO_VERSION=5.0.10
MINGW_VERSION=4.7.0
FOLDER=C:\Estudos\UFMG\PDS1\TP

FOLDER_NAME=\Allegro524_mingw-w64-gcc81_posix_dwarf
PATH_ALLEGRO=$(FOLDER)$(FOLDER_NAME)
LIB_ALLEGRO=\lib\liballegro_monolith.dll.a
INCLUDE_ALLEGRO=\include

all:ffantasy.exe

	
ffantasy.exe: ffantasy.o
	gcc -o ffantasy.exe ffantasy.o $(PATH_ALLEGRO)$(LIB_ALLEGRO)

ffantasy.o: ffantasy.c
	gcc -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -c ffantasy.c	
	
	
clean:
	del ffantasy.o
	del ffantasy.exe

