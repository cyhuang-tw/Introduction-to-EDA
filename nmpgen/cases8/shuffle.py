import json, random
import sys

if __name__ == '__main__':

    with open(sys.argv[1], 'r') as fp:
        obj = json.load(fp)
    input_list = list(obj.keys())
    random.shuffle(input_list) 
    #output_list = list(obj.keys())
    output_list = list(obj.values())
    
    random.shuffle(output_list)

    input_list.sort()
    output_list.sort()

    a = [input_list,output_list]

    with open(sys.argv[2], 'w') as w:
        string = json.dumps(a)
        w.write(string)

    fp.close()
    w.close()