import sys

if __name__ == '__main__':

	f = open(sys.argv[1],'r')
	txt = open(sys.argv[2],'w')
	txt.write("[")

	for line in open(sys.argv[1]):
		line = f.readline()
		if (len(line) == 1):
			inline = " "
		else:
			inline = line[:-1]
		txt.write('"' + inline + '"' + ',')

	txt.write("]")

