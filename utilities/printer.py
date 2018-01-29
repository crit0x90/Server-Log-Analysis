#line.split()[8] -> HTTP status code

with open('../input/ezproxy_201737.log') as file:
	for line in file:
		print(line.split()[8])