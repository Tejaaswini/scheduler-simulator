import matplotlib.pyplot as plt
import csv

# Read Gantt chart data from CSV
def read_gantt_chart(file_name):
    gantt_data = []
    try:
        with open(file_name, mode='r') as file:
            reader = csv.reader(file)
            for row in reader:
                gantt_data.append((row[0], int(row[1]), int(row[2])))
    except FileNotFoundError:
        print(f"Error: {file_name} not found!")
        exit(1)
    return gantt_data

# Plot Gantt chart
def plot_gantt_chart(data):
    fig, ax = plt.subplots(figsize=(10, 2))
    for idx, (process, start, end) in enumerate(data):
        if process == "Idle":
            ax.barh(0, end - start, left=start, color='gray', edgecolor='black')
            ax.text(start + (end - start) / 2, 0, process, ha='center', va='center', color='white')
        else:
            ax.barh(0, end - start, left=start, edgecolor='black')
            ax.text(start + (end - start) / 2, 0, process, ha='center', va='center', color='white')
    
    ax.set_xlabel("Time")
    ax.set_yticks([])
    ax.set_title("Gantt Chart")
    plt.show()

if __name__ == "__main__":
    gantt_file = "gantt_chart.csv"
    gantt_data = read_gantt_chart(gantt_file)
    plot_gantt_chart(gantt_data)
