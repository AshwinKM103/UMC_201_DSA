import random 
from tqdm import tqdm   
from splaytree import SplayTree
import math
import plotly.graph_objects as go

"""
For ease of implementation, we have adjusted the input set that will be used to construct the splay tree. 
We know that the input set contains n elements and they are not in any particular order.
So we have done a mapping from the set to 1 to n. We first sort the elements of the input set and then map them to 1 to n.
Example : Input set is {1,10,432,54,234} -> {1,2,5,3,4} 
Map them: 1 -> 1, 10 -> 2, 54 -> 3, 234 -> 4, 432 -> 5
Similarly, map the entries of the query array.
Example : Query array is [1,1,10,432,54,234,432] -> [1,1,2,5,3,4,5]

This adjustment simplifies implementation and avoids complexity with unordered input elements.

For robustness, we use depth as cost metric. We caluclate the amortized cost as total dept traversed divided by total occurences of x in the query array.
"""

x_vals = []  # For m values
y_vals = []  # For c values
z_vals = []  # For amortized costs

n = int(input("Enter the value of n: "))
x = int(input("Enter the value of x: "))

query_lengths=[1000,10000,100000,1000000] # Query lengths : m
c_vals=[x for x in range(1,101)]       

def generator(m, c, x, n):
    num_x = (m * c) // 100
    result = [x] * num_x
    count_nonx = m - num_x
    for i in range(count_nonx):
        result.append(random.randint(1, n + 1))
    random.shuffle(result)
    return result

tree = SplayTree()

for i in range(1,n+1):
    tree.insert(i)

for m in tqdm(query_lengths):
    for c in tqdm(c_vals,colour='green'):
        query_list=generator(m,c,x,n)
        total_depths=0
        total_occurences=0
        for query in query_list:
            if query == x:
                key, dep = tree.search(x)
                total_occurences+=1
                total_depths+=dep
            else:
                key, dep = tree.search(query)
        amortized_cost = float(total_depths/total_occurences)
        # print(query_list)
        # Append values to the respective lists
        x_vals.append(m)
        y_vals.append(c)
        z_vals.append(amortized_cost)

x_vals = [int(math.log10(x)) for x in x_vals]

# Create a 3D scatter plot (Alternatively, you can use a surface plot)
fig = go.Figure(data=[go.Scatter3d(
    x=x_vals,
    y=y_vals,
    z=z_vals,
    mode='markers',
    marker=dict(
        size=5,
        color=z_vals,                # Color by amortized cost
        colorscale='Viridis',         # Color scale
        colorbar=dict(title='Amortized Cost')
    )
)])

# Set titles and labels
fig.update_layout(
    scene=dict(
        xaxis_title='Query Length (log(m))',
        yaxis_title='c Value in %',
        zaxis_title='Amortized Cost'
    ),
    title='3D Plot of Amortized Cost vs Query Length and c Value'
)

# Show the plot
fig.show()