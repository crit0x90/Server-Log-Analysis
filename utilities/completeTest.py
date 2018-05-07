import time
import sys

def toSeconds(timeString):
	h, m, s = timeString.split(':')
	time = (int(h) * 3600) + (int(m) * 60) + int(s)
	return time

with open(sys.argv[1]) as file:
	curTime = 0
	for line in file:
		if line != '\n':
			#sleep for the delta t between requests
			t = toSeconds(line.split()[3][13:])
			print(t-curTime)
			time.sleep(t - curTime)
			curTime = t
			sys.stdout.write(line)
			sys.stdout.flush()
			