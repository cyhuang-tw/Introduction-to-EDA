import sys

def ascii_62(char):
	asc = ord(char)
	if (asc > 96):
		return (35 + (asc - 96))
	elif (asc > 64):
		return (9 + (asc - 64))
	else:
		return (asc - 48)

def str2int(s):
	index = 0
	for i in range(len(s)):
		index += ascii_62(s[i]) * (62 ** i)
	return index

digit = 3

r = ["*4","Abc","bBc","c","ad","xyz","qqq","a",""]
table = []

hold = ""

for x in range(len(r)):
	rpt = r[x].find("*")

	if (rpt != -1):
		for y in range(str2int(r[x][rpt+1:])):
			table.append("")
		continue
	if (r[x] == ""):
		table.append("")
		continue
	if (hold == "" or len(r[x]) == digit):
		hold = s = r[x]
	if(len(r[x]) != digit):
		s = r[x] + hold[len(r[x]):]
	table.append(s)

for x in range(len(table)):
	print(table[x])

"""

for i in range(len(rList)):
	if (rList[i].find("*") != -1):
		rpt = str2int(rList[i][rList[i].find("*")+1:])
		for j in range(str2int(rList[i][rList[i].find("*")+1:])):
			table.append("")
		continue
	if (rList[i] == ""):
		table.append("")
		continue
	if(hold == "" or len(rList[i]) == digit):
		hold = s = rList[i]
	if(len(rList[i]) != digit):
		s = rList[i] + hold[len(rList[i]):]
	table.append(s)

"""
