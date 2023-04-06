import numpy as np
import matplotlib.pyplot as plt

#make a function to generate our data to plot
def generate_data(true_values, num_experiments):
    #initialize empty array to be appended with the data
    data = []
    for true_value in true_values:
        measured_values = np.random.normal(true_value, 1, num_experiments)
        data.append((true_value, measured_values))
    return data
#configurable parametes to pass our generate_data function
true_values = np.linspace(0, 10, 100)
num_experiments = 100
data = generate_data(true_values, num_experiments)

plt.figure(figsize=(10, 6))
for true_value, measured_values in data:
    plt.scatter([true_value] * num_experiments, measured_values, alpha=0.5, edgecolors='none', color='blue')
plt.xlabel('True Parameter Value')
plt.ylabel('Measured Value')
plt.title('Neyman Construction')
plt.show()
