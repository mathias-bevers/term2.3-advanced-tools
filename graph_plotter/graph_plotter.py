import os
import json
import matplotlib.pyplot as plt
from collections import defaultdict

# ---------------------------------------------------------------- VARIBLES
current_directory = os.path.dirname(os.path.realpath(__file__))
test_types = defaultdict(list)
iterations = list()

# ---------------------------------------------------------------- FUNCTIONS
def format_data(json_data):
    for iteration in json_data:
        if type(json_data[iteration]) is not dict:
            continue
        iterations.append(iteration)
        for test_type in json_data[iteration]:
            test_types[test_type].append(json_data[iteration][test_type])

def plot_data():
    for key in test_types:
        plt.plot(iterations, test_types[key], label=key, marker='o')

    plt.legend()
    plt.xticks(rotation = 20)

    # to save as png, it should be done before plt.show()
    plt.savefig(os.path.join(current_directory, 'graph.png'))
    plt.show()

# ---------------------------------------------------------------- MAIN LOOP


with open(os.path.join(current_directory, 'full_results.json')) as file:
    json_data = json.load(file)

format_data(json_data)
plot_data()
