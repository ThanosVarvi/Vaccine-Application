
vaccineMonitor : vaccineMonitor.c
	gcc -o vaccineMonitor vaccineMonitor.c 

clean:
	rm -f *.o vaccineMonitor

	# ./vaccineMonitor -c inputFile.txt -b 64