import os
import numpy as np

folder_path = "C:/Users/leobr/Desktop/PACS/PlockY/build/examples/output"

# Get all the files in the folder
files = os.listdir(folder_path)

# Sort the files based on the first integer in the file name
sorted_files = sorted(files, key=lambda x: int(x.split("_")[1]), reverse=True)

sol_split = None
# Read the data from the files
with open("C:/Users/leobr/Desktop/PACS/PlockY/examples/sol_split.csv", "r") as file:
    data = file.read()
    data = data.split("\n")
    data = data[:-1]
    data_float = [float(d) for d in data]
    sol_split = np.array(data_float, dtype=np.float32)


norm = []

for file_name in sorted_files:
    file_path = os.path.join(folder_path, file_name)
    if file_name[-5] == "1":
        with open(file_path, 'r') as file:
            data = file.read()
            data = data.split("\n")
            data = data[:-1]
            data_float = [float(d) for d in data]
            data_array = np.array(data_float, dtype=np.float32)

            norm.append(np.linalg.norm(data_array - sol_split))


from matplotlib import pyplot as plt

plt.plot(norm)
plt.show()



        