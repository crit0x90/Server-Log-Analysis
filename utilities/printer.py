#line.split()[8] -> HTTP status code
import time
import sys
with open('../input/output.log') as file:
	for line in file:
		if line != '\n' and line.split()[2] != '-':
			print(line.split()[2])
			sys.stdout.flush()
			time.sleep(2)
