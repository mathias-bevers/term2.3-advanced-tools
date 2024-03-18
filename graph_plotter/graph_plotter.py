import os
import json

file_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'full_results.json')

with open(file_path) as file:
    json_data = json.load(file)

print(json_data)
