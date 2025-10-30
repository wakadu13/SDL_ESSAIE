gcc -x c -std=c17 -g src/*.c src/waka/*.c -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -Wall -o bin/monprogramme
cd .\bin
.\monprogramme.exe