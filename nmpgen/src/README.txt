
1. generate testing data:
python shuffle.py [origin_file] [shuffled_file]

u will get a shuffled json file here.

2. generate input data:
python json2txt.py [map_json] [map_txt]

Turn the mapping in json file into txt file, and the result will be a list.
We have to copy and paste the mapping to "output.py" artificially. Note that this step should be done in .cpp file in final version.

3. predict the name mapping
python output.py [shuffled_file] [predict_mapping_json]

4. verify the answer
python verify.py [answer_file] [prediction_file]

Last, generate the prediction and compare it with the origin_file.
In summary, the .cpp file should generate "output.py" with the list of map_txt generated in step 2