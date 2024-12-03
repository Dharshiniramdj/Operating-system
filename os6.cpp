//dharshini j
//192324059
 #include <stdio.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
};

void swap(struct Process *xp, struct Process *yp) {
    struct Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (processes[j].priority < processes[min_index].priority)
                min_index = j;
        }
        swap(&processes[min_index], &processes[i]);
    }
}

int main() {
    int n, current_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].process_id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
                swap(&processes[j], &processes[j + 1]);
        }
    }

    printf("\nGantt Chart:\n-----------\n");
    while (1) {
        int flag = 1;
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].arrival_time <= current_time) {
                flag = 0;
                printf("| P%d ", processes[i].process_id);
                processes[i].remaining_time--;
                if (processes[i].remaining_time == 0) {
                    printf("|");
                    printf("\n");
                }
            }
        }
        if (flag)
            break;
        current_time++;
    }

    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_turnaround_time += current_time - processes[i].arrival_time;
        total_waiting_time += (current_time - processes[i].arrival_time) - processes[i].burst_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);

    return 0;
}

