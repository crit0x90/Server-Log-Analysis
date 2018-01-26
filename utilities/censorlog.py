#The purpose of this file is to censor relevant user data (ip and username) from the 
#log file to protect the privacy of the users without disturbing the data patterns
#that this program will be scanning for

#line.split() @ [0] is the IP address
#line.split() @ [2] is the username

with open('../input/ezproxy_201737.log') as log:

	##############################################
	#create and populate the lists of ips and names
	names = []
	ips = []
	for line in log:
		#print(line.split(), "\n")
		line = line.split()
		
		ips.append(line[0])

		if(line[2] != '-'):
			names.append(line[2])
	##############################################


	##############################################
	#IP Block
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

	ipdict = dict(iplist) ###final IP mapping
	#End IP Block
	##############################################


	##############################################
	#User Block
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

	userdict = dict(userlist) ###final user mapping
	#End User Block
	##############################################


with open("output.log", 'w') as output:
	with open('../input/ezproxy_201737.log') as log:
		for line in log:
			line = line.replace(line.split()[0], ipdict[line.split()[0]])
			if line.split()[2] != '-':
				name = line.split()[2]
				line = line.replace(line.split()[2], userdict[line.split()[2]])

			output.write(line)
			output.write("\n")
