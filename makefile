archiver: main.o Archive.o unArchive.o listArchive.o checkArchive.o checkCorrupt.o getFileSize.o
	gcc main.o Archive.o unArchive.o listArchive.o checkArchive.o checkCorrupt.o getFileSize.o -o archiver
main.o: main.c
	gcc -c main.c
Archive.o: Archive.c
	gcc -c Archive.c
unArchive.o: unArchive.c
	gcc -c unArchive.c
listArchive.o: listArchive.c
	gcc -c listArchive.c
checkArchive.o: checkArchive.c
	gcc -c checkArchive.c
checkCorrupt.o: checkCorrupt.c
	gcc -c checkCorrupt.c
getFileSize.o: getFileSize.c
	gcc -c getFileSize.c
