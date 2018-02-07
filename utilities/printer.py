#line.split()[8] -> HTTP status code
import time
with open('../input/output.log') as file:
	for line in file:
		if line != '\n' and line.split()[2] != '-':
			print(line.split()[2])
			time.sleep(2)
