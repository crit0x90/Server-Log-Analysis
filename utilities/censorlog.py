#The purpose of this file is to censor relevant user data (ip and username) from the 
#log file to protect the privacy of the users without disturbing the data patterns
#that this program will be scanning for

#line.split() @ [0] is the IP address
#line.split() @ [2] is the username

def createIPdict(ips):
	ips = list(set(ips)) #remove duplicates

	#create aliases to represent new IPs
	counter = 0
	ipalias = []
	while counter < len(ips):
		ipalias.append("IP"+str(counter))
		counter += 1
	
	#package each IP with an alias for mapping
	iplist = []
	for k, v in zip(ips, ipalias):
		iplist.append((k, v))

	return dict(iplist) ###final IP mapping

def createUserDict(names):
	names = list(set(names)) #remove duplicates

	#create aliases to represent new usernames
	counter = 0
	useralias = []
	while counter < len(names):
		useralias.append("user"+str(counter))
		counter += 1

	#package each user name with an alias for mapping
	userlist = []
	for k, v in zip(names, useralias):
		userlist.append((k, v))

	return dict(userlist) 

with open('../input/ezproxy_201737.log') as log:

	##############################################
	#create and populate the lists of ips and names
	names = []
	ips = []
	counter = 0
	for line in log:
		counter += 1
		if counter == 162913:
			print(line)

		line = line.split()
		
		ips.append(line[0])

		if(line[2] != '-' and 'auto-' not in line[2]):
			names.append(line[2])
	##############################################


	ipdict = createIPdict(ips)
	userdict = createUserDict(names) 

with open("output.log", 'w') as output:
	with open('../input/ezproxy_201737.log') as log:
		counter = 0
		for line in log:
			counter += 1
			line = line.replace(line.split()[0], ipdict[line.split()[0]])

			if line.split()[2] != '-':
				name = line.split()[2]
				if name in userdict:
					line = line.replace(line.split()[2], userdict[line.split()[2]])
				else:
					print('Error: Name could not be found, continuing')

			output.write(line)
			output.write("\n")
