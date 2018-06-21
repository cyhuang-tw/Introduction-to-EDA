import json
import sys

if __name__ == '__main__':

	answer = json.load(open(sys.argv[1],'r'))
	predict = json.load(open(sys.argv[2],'r'))

	print (answer == predict)

	answer = list(answer.keys())
	predict = list(predict.keys())

	answer.sort()
	predict.sort()

	for i in range(len(answer)):
		if (answer[i] != predict[i]):
			print (i," ",answer[i]," ",predict[i])

	#print (file1,'\n')
	#print (file2)
