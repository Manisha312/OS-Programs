#include <stdio.h>
#include <string.h>
struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int priority;
    int response_time;
};
void FCFS();
void SJF_Non_pre();
void SJF_pre();
void RoundRobin();
void Priority_Non_pre();
void Priority_pre();
void main() {

    int choice;
    while (choice != 5) {
        printf("\n\n1.First Come First Serve(FCFS)\n2.Shortest Job First(SJF):Non-premptive\n3.Shortest Job First(SJF):Premptive\n4.Round Robin Scheduling(RR)\n5.Priority Scheduling:Non-premptive\n6.Priority Scheduling:Premptive\n6.Exit\n");
        printf("Enter the Choice: \n");
        scanf("%d",&choice);
        
        switch (choice) {
            case 1: 
                FCFS();
                break;
            case 2: 
                SJF_Non_pre();
                break;
            case 3:
                SJF_pre();
                break;
            case 4:
            	RoundRobin();
            	break;
            case 5:
                Priority_Non_pre();
                break;
            case 6:
                Priority_pre();
                break;
            default :
                printf("Chose the correct Options : \n");

        }
    }
}

void FCFS() {
    
	int bt[10]={0},at[10]={0},tat[10]={0},wt[10]={0},ct[10]={0};
	int i,j,k,n,sum=0;
	float totalTAT=0,totalWT=0;

	printf("Enter number of process:");
	scanf("%d",&n);

	printf("Enter arrival time and burst time for each process\n\n");

	for( i=0;i<n;i++)
	{
		printf("Process:%d\n",i+1);
		printf("Arrival time of process	:");
		scanf("%d",&at[i]);
	
	printf("Burst time of process:	");
		scanf("%d",&bt[i]);
		
		printf("\n");
	}
		
	//calculate completion time of processes 	

	for(j=0;j<n;j++)
	{
		sum+=bt[j];
		ct[j]+=sum;
	}
//calculate turnaround time and waiting times 

	for(k=0;k<n;k++)
	{
		tat[k]=ct[k]-at[k];
		totalTAT+=tat[k];
	}

	//calculate waiting time
	for(k=0;k<n;k++)
	{
		wt[k]=tat[k]-bt[k];
		totalWT+=wt[k];
	}
	
	printf("Solution: \n\n");
	printf("P#\t AT\t BT\t CT\t TAT\t WT\t\n\n");
	
	for(i=0;i<n;i++)
	{
		printf("P%d\t %d\t %d\t %d\t %d\t %d\n",i+1,at[i],bt[i],ct[i],tat[i],wt[i]);
	}
		
	printf("\n\nAverage Turnaround Time = %.2f\n",totalTAT/n);
	printf("Average WT = %.2f\n\n",totalWT/n);
}

void SJF_Non_pre () {
    int n,i,idx,mn,min_arrival_time,max_completion_time;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;
    int is_completed[100];
    
    int current_time = 0;
    int completed = 0;
    int prev = 0;
    memset(is_completed,0,sizeof(is_completed));
    
    printf("Enter the number of processes: ");
  scanf("%d",&n);
  for(i = 0; i < n; i++) {
        printf("Enter arrival time of process %d:",i+1);
        scanf("%d",&p[i].arrival_time);
        printf("Enter burst time of process %d: ",i+1 );
        scanf("%d",&p[i].burst_time);
        p[i].pid = i+1;
        printf("\n");
    }
     while(completed != n) {
         idx = -1;
         mn = 10000000;
        for( i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(p[i].burst_time < mn) {
                    mn = p[i].burst_time;
                    idx = i;
                }
                if(p[i].burst_time == mn) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mn = p[i].burst_time;
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) {
            p[idx].start_time = current_time;
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;
            
            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;
            total_idle_time += p[idx].start_time - prev;

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
            prev = current_time;
        }
        else {
            current_time++;
        }
        
    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    avg_response_time = (float) total_response_time / n;
	printf("P#\t AT\t BT\tST\t CT\t TAT\t WT\tRT\t\n\n");

    for(i = 0; i < n; i++) {
		printf("P%d\t %d\t %d\t %d\t %d\t %d \t %d\t %d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].start_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time,p[i].response_time);
    }
    printf("\nAverage Turnaround Time = %.2f",avg_turnaround_time);
    printf("\nAverage Waiting Time =%.2f ",avg_waiting_time);
    printf("\nAverage Response Time =%.2f\n\n ",avg_response_time);
}
void SJF_pre () {
	int n,i,idx,mn,min_arrival_time,max_completion_time;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;
    int burst_remaining[100];
    int is_completed[100];
    
    int current_time = 0;
    int completed = 0;
    int prev = 0;
    memset(is_completed,0,sizeof(is_completed));
    
    printf("Enter the number of processes: ");
  scanf("%d",&n);
  for(i = 0; i < n; i++) {
        printf("Enter arrival time of process %d:",i+1);
        scanf("%d",&p[i].arrival_time);
        printf("Enter burst time of process %d: ",i+1 );
        scanf("%d",&p[i].burst_time);
        p[i].pid = i+1;
        burst_remaining[i] = p[i].burst_time;
        printf("\n");
    }
   while(completed != n) {
        int idx = -1;
        int mn = 10000000;
        for(i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(burst_remaining[i] < mn) {
                    mn = burst_remaining[i];
                    idx = i;
                }
                if(burst_remaining[i] == mn) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mn = burst_remaining[i];
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            if(burst_remaining[idx] == p[idx].burst_time) {
                p[idx].start_time = current_time;
                total_idle_time += p[idx].start_time - prev;
            }
            burst_remaining[idx] -= 1;
            current_time++;
            prev = current_time;
            
            if(burst_remaining[idx] == 0) {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                total_response_time += p[idx].response_time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else {
             current_time++;
        }  
    }


    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    avg_response_time = (float) total_response_time / n;
	printf("P#\t AT\t BT\tST\t CT\t TAT\t WT\tRT\t\n\n");

    for(i = 0; i < n; i++) {
		printf("P%d\t %d\t %d\t %d\t %d\t %d \t %d\t %d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].start_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time,p[i].response_time);
    }
    printf("\nAverage Turnaround Time = %.2f",avg_turnaround_time);
    printf("\nAverage Waiting Time =%.2f ",avg_waiting_time);
    printf("\nAverage Response Time =%.2f \n",avg_response_time);
}


void RoundRobin() {
    int st[10],bt[10],et[10],at[10],wt[10],tat[10],n,tq;
    int i,count=0,swt=0,stat=0,temp,sq=0;
    float awt=0.0,atat=0.0;

    printf("\nEnter number of processes : ");
    scanf("%d",&n);

    printf("\n enter brust time and arriavl time\n");
 	for (i = 0; i < n; i++) {
   	printf("P%d  \nbrust time ", i + 1);
   	scanf("%d", & bt[i]);
   	printf("ariavl time   :  ");
   	scanf("%d", & at[i]);
   	et[i] = 0;
   	wt[i] = 0;
 	}
    printf("\nEnter time quantum :");
    scanf("%d",&tq);

    while (1) {
        for(i=0,count=0; i<n; i++) {
            temp = tq;
            if (st[i] == 0) {
                count++;
                continue;
            }
            
            if (st[i] > tq) {
                st[i] = st[i] - tq;
            } else {
                if (st[i] >=0) {
                    temp = st[i];
                    st[i] = 0;
                }
                sq = sq + temp;
                tat[i] = sq;
            }
        }
        if (n == count) {
            break;
        }
    }
    for(i=0; i<n; i++) {
        wt[i] = tat[i] - bt[i];
        swt = swt + wt[i];
        stat = stat + tat[i];
    }
    awt = (float)swt/n;
    atat = (float)stat/n;
    printf("Process number\tBurst time\tWaiting Time\tTurn Around time\n");
    for(i=0; i<n; i++) {
        printf("\n%d\t\t%d\t\t%d\t\t%d",i+1,bt[i],wt[i],tat[i]);
    }
    printf("\nAverage Waiting Time is %.2f \n\nAverage Turn Around Time is %.2f\n\n",awt,atat);

}

void Priority_pre() {
    int n,i,idx,mn,min_arrival_time,max_completion_time;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;
    int burst_remaining[100];
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));

    
    int current_time = 0;
    int completed = 0;
    int prev = 0;
    
    printf("Enter the number of processes: ");
  scanf("%d",&n);
  for(i = 0; i < n; i++) {
        printf("Enter arrival time of process %d:",i+1);
        scanf("%d",&p[i].arrival_time);
        printf("Enter burst time of process %d: ",i+1 );
        scanf("%d",&p[i].burst_time);
        printf("Enter priority of the process %d : ",i+1);
        scanf("%d" ,&p[i].priority);
        p[i].pid = i+1;
        printf("\n");
    }
   while(completed != n) {
        int idx = -1;
        int mx = -1;
        for(i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(p[i].priority > mx) {
                    mx = p[i].priority;
                    idx = i;
                }
                if(p[i].priority == mx) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mx = p[i].priority;
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) {
            p[idx].start_time = current_time;
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;
            
            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;
            total_idle_time += p[idx].start_time - prev;

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
            prev = current_time;
        }
        else {
            current_time++;
        }
        
    }


    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    avg_response_time = (float) total_response_time / n;
	printf("P#\t AT\t BT\tPRI\tST\t CT\t TAT\t WT\tRT\t\n\n");

    for(i = 0; i < n; i++) {
		printf("P%d\t %d\t %d\t %d\t %d\t %d \t %d\t %d\t%d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].priority,p[i].start_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time,p[i].response_time);
    }
    printf("\nAverage Turnaround Time = %.2f",avg_turnaround_time);
    printf("\nAverage Waiting Time =%.2f ",avg_waiting_time);
    printf("\nAverage Response Time =%.2f ",avg_response_time);
}
void Priority_Non_pre() {
	int n,i,idx,mn,min_arrival_time,max_completion_time;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;
    int burst_remaining[100];
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));

    
    int current_time = 0;
    int completed = 0;
    int prev = 0;
    
    printf("Enter the number of processes: ");
  scanf("%d",&n);
  for(i = 0; i < n; i++) {
        printf("Enter arrival time of process %d:",i+1);
        scanf("%d",&p[i].arrival_time);
        printf("Enter burst time of process %d: ",i+1 );
        scanf("%d",&p[i].burst_time);
        printf("Enter priority of the process %d: ",i+1);
        scanf("%d" ,&p[i].priority);
        p[i].pid = i+1;
        burst_remaining[i] = p[i].burst_time;

        printf("\n");
    }
   while(completed != n) {
        int idx = -1;
        int mx = -1;
        for(i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(p[i].priority > mx) {
                    mx = p[i].priority;
                    idx = i;
                }
                if(p[i].priority == mx) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mx = p[i].priority;
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            if(burst_remaining[idx] == p[idx].burst_time) {
                p[idx].start_time = current_time;
                total_idle_time += p[idx].start_time - prev;
            }
            burst_remaining[idx] -= 1;
            current_time++;
            prev = current_time;
            
            if(burst_remaining[idx] == 0) {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                total_response_time += p[idx].response_time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else {
             current_time++;
        }  
    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    avg_response_time = (float) total_response_time / n;
	printf("P#\t AT\t BT\tPRI\tST\t CT\t TAT\t WT\tRT\t\n\n");

    for(i = 0; i < n; i++) {
		printf("P%d\t %d\t %d\t %d\t %d\t %d \t %d\t %d\t%d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].priority,p[i].start_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time,p[i].response_time);
    }
    printf("\nAverage Turnaround Time = %.2f",avg_turnaround_time);
    printf("\nAverage Waiting Time =%.2f ",avg_waiting_time);
    printf("\nAverage Response Time =%.2f ",avg_response_time);
}

