#line.split()[8] -> HTTP status code
import time
import sys

with open(sys.argv[1]) as file:
	for line in file:
		if line != '\n' and line.split()[2] != '-':
			sys.stdout.write(line)
			sys.stdout.flush()
			#time.sleep(0.1)
