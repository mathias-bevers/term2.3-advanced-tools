import os
import json
import matplotlib.pyplot as plt
import numpy as np
from collections import defaultdict

# ---------------------------------------------------------------- VARIBLES
current_directory = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'results')
test_types = defaultdict(list)
iterations = list()

# ---------------------------------------------------------------- FUNCTIONS
def average(collection):
    return sum(collection) / len(collection)

def format_data(json_data):
    for iteration in json_data:
        if type(json_data[iteration]) is not dict:
            continue
        iterations.append(iteration)
        for test_type in json_data[iteration]:
            test_types[test_type].append(json_data[iteration][test_type])

def plot_data(name):
    short_name = name.lstrip('full_results').rstrip('.json')
    max_value = 0;
    data = [] 
    texts = []
    for key in test_types:
        cur = test_types[key]
        data.append(cur)
        t = max(cur) 
        texts.append(f'min: {min(cur)}\nmax: {t}\navg: {average(cur)}')
        if( t > max_value):
            max_value = t

    fig, ax = plt.subplots()
    ax.set_ylim([0, max_value + max_value* 0.1 if max_value > 0 else 0.1])
    ax.boxplot(data, patch_artist=True, labels=test_types.keys())
    props = dict(boxstyle='round', facecolor='wheat', alpha=0.5)
    # ax.text(0.05, 0.95, texts[0], transform=ax.transAxes, fontsize=14, verticalalignment='top', bbox=props)

    plt.title(short_name)

    # to save as png, it should be done before plt.show()
    plt.savefig(os.path.join(current_directory, file_name + '_graph.png'))

# ---------------------------------------------------------------- MAIN LOOP

for file_name in os.listdir(os.path.join(current_directory)):
    if file_name.endswith('.json'):
        test_types.clear()
        iterations.clear()

        with open(os.path.join(current_directory, file_name)) as file:
            json_data = json.load(file) 

            format_data(json_data)
            plot_data(file_name)