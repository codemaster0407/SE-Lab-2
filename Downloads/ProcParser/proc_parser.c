#include<stdio.h>
#include<string.h>
#include<unistd.h>
#define _GNU_SOURCE


int context_times[1000], processes_times[1000], read_time[1000], write_time[1000];

int pointer_ctxt = 0, pointer_process = 0,pointer_r = 0, pointer_w = 0;
int curr_time = 0;

int delete_first_ele(char arr[]){
    for(int i=0; arr[i]!='\0';i++){
        arr[i] = arr[i+1];
    }

}

int modulus(int a, int b){
    if(a-b<0){
        return b-a;
    }
    else{
        return a-b;
    }
}

float sum_arr(int arr[]){
    float sum = 0;

    for(int i=0; i<10; i++){
        sum += arr[i];
    }
    return sum;
}

long int arr_sum(long int arr[], int m){
    long int sum =0;

    for(int i=0; i<m; i++){
        sum+= arr[i];
    }
    return sum;
}




int main(int argc, char *argv[]){
    //Checking if there are any arguments given
    //If given, then it executes the second part of the code
    if(argc!=1){
        int read_rate=atoi(argv[1]),print_rate=atoi(argv[2]);
        while(1){
            printf("\n");

            //Declaring all the variables for storing the values

            float user_time,sum_times,system_time,idle_time; 
            float mem_avail,mem_tot;

            //Condition for reading 
            if(curr_time%print_rate != 0){
                sleep(read_rate);
            }
            //printing the output if the above condition is not satisfied
            else{
                
                FILE *fp = fopen("/proc/stat","rb");  //Opening /proc/stat file for context switches, processes created and CPU statistics.

                char ch;

                char CPU_Stats[10000];
                char ctxt[100];
                char procs[100];
                int j=0;
                int k = 0;
                int m = 0;
                int count_c = 0,count_p = 0;
                int count_n = 0;
                
                //Using file pointers to remove the excess data and storing the useful data for our calculations.
                do{
                    ch = fgetc(fp);

                    if(ch=='\n'){
                        count_n++;
                    }
                    if(ch =='c'){
                        count_c++;
                    }

                    if(count_n<2){
                        CPU_Stats[m] = ch;
                        if(count_n==2){
                            m++;
                            CPU_Stats[m] = '\0';

                        }
                        m++;
                    }

                    if(count_c > 2){
                        ctxt[j] = ch;
                        if(ch == '\n'){
                            count_c = -1000;
                            j++;
                            ctxt[j] = '\0';
                            j = 0;
                        }
                        j++;
                    }

                    if(ch=='p'){
                        count_p++;
                        
                    }
                    if(count_p>3){
                        procs[k] = ch;
                        k++;
                        if(ch == '\n'){
                            
                            k++;
                            procs[k] = '\0';
                            
                        }
                    }

                    
                    
                }while(ch!=EOF);


                

                //Converting the characters into integers

                char temp_ctxt[1000];
                j = 0;
                for(int i=0; ctxt[i]!='\0'; i++){
                    if(ctxt[i]>=48 && ctxt[i]<=57){
                        
                        temp_ctxt[j] = ctxt[i];
                        j++;
                    }
                }
                temp_ctxt[j] = '\0';
                printf("\n");

                

            

                char temp_procs[100];
                j = 0;
                for(int i=0; procs[i]!='\0'; i++){
                    if(procs[i]>=48 && procs[i]<=57){
                        
                        temp_procs[j] = procs[i];
                        j++;
                    }
                }
                temp_procs[j] = '\0';
                int processes = atoi(temp_procs);
                int context_switches = atoi(temp_ctxt);

                //Adding the values of the current instance to the arrays so that we can find the rates at given instances.
                
                context_times[pointer_ctxt] = context_switches;
                processes_times[pointer_process] = processes;

                pointer_ctxt++;
                pointer_process++;

                //Storing the different CPU's idle,user and kernel mode times.

                int arr[10];
                j = 0;
                int s= 5;

                for(int i=0; i<10; i++){
                    char temp_arr[100];
                    
                    for(s ; CPU_Stats[s] != ' '; s++){
                        temp_arr[j] = CPU_Stats[s];
                        j++;

                        if(CPU_Stats[s+1] == ' ' || CPU_Stats[s+1] == '\n'){
                            temp_arr[j] = '\0';
                            s= s+2;
                            break;
                        }
                        
                    }
                    
                    j = 0;
                    
                    arr[i] = 2 * atoi(temp_arr);
                    memset(temp_arr, 0, sizeof temp_arr);
                }
                
                
                

                sum_times = sum_arr(arr);

                
                count_n = 0;

                int space_count = 0;

                char user_mode[10], system[10], idle[10];
                
                j = 0;
                k =0, m = 0;
                for(int i=0; CPU_Stats[i]!='\0'; i++){
                    if(CPU_Stats[i] == ' '){
                        space_count++;
                        
                    }
                    
                    if(space_count==2){
                        
                        user_mode[j] = CPU_Stats[i];
                        j++;
                        if(CPU_Stats[i+1] == ' '){
                            
                            user_mode[j] = '\0';
                        }
                    }

                    if(space_count==4){
                        
                        system[k] = CPU_Stats[i];
                        k++;
                        if(CPU_Stats[i+1] == ' '){
                            
                            system[k] = '\0';
                        }
                    }

                    if(space_count==5){
                        
                        idle[m] = CPU_Stats[i];
                        m++;
                        if(CPU_Stats[i+1] == ' '){
                            
                            idle[m] = '\0';
                        }
                    }
                }
                delete_first_ele(user_mode);
                delete_first_ele(system);
                delete_first_ele(idle);
                printf("\n");
                printf("\n");

                
                //Converting the character datas into integer data

                user_time = atoi(user_mode);
                system_time = atoi(system);
                idle_time = atoi(idle);

                
                
                
                
                

                FILE *memory = fopen("/proc/meminfo","rb");  //proc/meminfo used for finding the memory details

                char memory_info[1000];
                int count_nl = 0;
                j = 0;
                do{
                    ch = fgetc(memory);
                    if(ch == '\n'){
                        count_nl++;
                    }
                    if(count_nl<2){
                        memory_info[j] = ch;
                        j++;
                    }
                    if(count_nl>=2){
                        memory_info[j] = '\0';
                        break;
                    }
                    
                }while(ch!=EOF);

                //Storing the total memory and available memory in two arrays so that we can convert them into integer data later 

                char total_memory[100], memory_available[100];
                
                count_nl = 0;
                j = 0, m = 0;

                for(int i=0; memory_info[i] !='\0'; i++){
                    if(memory_info[i] == '\n'){
                            count_nl++;
                        }
                    if(memory_info[i]>=48 && memory_info[i]<=57){
                        
                        if(count_nl == 0){
                            total_memory[j] = memory_info[i];
                            j++;

                            if(memory_info[i+1] == '\n'){
                                total_memory[j] = '\0';
                            }
                        }
                        if(count_nl == 1){
                            memory_available[m] = memory_info[i];
                            m++;
                        }
                    }
                }
                //Converting them to integer values 
                mem_tot = atoi(total_memory);
                mem_avail = atoi(memory_available);









                int count = 0;
                
                char reads[10000],writes[10000];
                j=0;
                m=0;
                char rw[100000];
                FILE *disk = fopen("/proc/diskstats","rb");  //Opening /proc/diskstats for reads and writes in the system.
                do{
                    ch = fgetc(disk);
                    
                    rw[j] = ch;
                    j++;
                    
                }while(ch!=EOF);
                

                //Storing reads and writes in different arrays so that we can convert them into integer valueslater 


                j = 0;
                for(int i=0; rw[i]!='\0'; i++){
                    if(rw[i] == '\n'){
                        count++;
                    }

                    if(count == 3){
                        reads[j] = rw[i];
                        j++;
                        if(rw[i+1] == '\n'){
                            reads[j] = '\0';
                        }

                    }

                    if(count == 7){
                        writes[m] = rw[i];
                        m++;
                        if(rw[i+1] == '\n'){
                            writes[j] = '\0';
                        }
                    }

                }

                long int r[10000],w[10000];
            
                count = 0;
                j = 0;
                m = 0;
                
                for(int i=20; reads[i]!='\0'; i++){
                    char temp_arr[100];
                    if(reads[i]!=' '){
                        temp_arr[j] = reads[i];
                        j++;
                    }

                    else if(reads[i] == ' '){
                        temp_arr[j] = '\0';
                        r[m] = atoi(temp_arr);
                
                        m++;
                        j = 0;
                    }
                    
                    
                    
                }

            

                long int sum_reads = arr_sum(r,m);
                
                count = 0;
                j = 0;
                m = 0;


                for(int i=20; writes[i]!='\0'; i++){
                    char temp_arr[100];
                    if(writes[i]!=' '){
                        temp_arr[j] = writes[i];
                        j++;
                    }

                    else if(writes[i] == ' '){
                        temp_arr[j] = '\0';
                        w[m] = atoi(temp_arr);
                        
                        m++;
                        j = 0;
                    }
                    
                    
                    
                }
                
                //Adding all the reads and writes and adding them to the read_time arrray and write_time array so that we can find the 
                //rates of disks and writes at different instances using the pointer_r and pointer_w
                long int sum_writes = arr_sum(w,m);
                
                read_time[pointer_r] = sum_reads;
                pointer_r++;

                write_time[pointer_w] = sum_writes;
                pointer_w++;

                
                //Printing all the outputs 

                printf("\n");
                printf("The percentage of the time of processor spent in user Mode : %.3f%%\n",(2*user_time / sum_times) * 100);
                printf("The percentage of the time of processor spent in System Mode : %.3f%%\n",(2*system_time / sum_times) * 100) ;
                printf("The percentage of the time of processor is idle : %.3f%%\n",(2*idle_time / sum_times)*100 );


                printf("The rate of context switches are %d\n", modulus(context_times[pointer_ctxt],context_times[pointer_ctxt-1]));
                printf("The rate of processes created in a second are %d\n", modulus(processes_times[pointer_process], processes_times[pointer_process-1]));

                printf("\nThe percentage of free memory available is %.3f%%\n", (mem_avail/mem_tot)* 100);
                printf("\nThe amount of memory available is %.0f Kb\n\n", mem_avail);

                
                printf("\nThe rate of reads per second is %ld",modulus(read_time[pointer_r],read_time[pointer_r-1]));
                printf("\nThe number of writes per second is %ld",modulus(write_time[pointer_w],write_time[pointer_w-1]));

                printf("\n_______________________________________________________________________");

            
            }
            
            //Adding the current time with the read_rate so that we can check for printing condition .
            curr_time = curr_time+read_rate;
        }
    }



    //1st part of the code when there is no input given 

    else{
        FILE *memory_info = fopen("/proc/meminfo","rb");  //For memory details

        char ch;
        int count_of_B = 0;
        do{
            ch = fgetc(memory_info);
            printf("%c",ch);
            if(ch == 'B'){
                count_of_B++;
            }
            if(count_of_B == 2){
                break;
            }
        
        }while(ch!=EOF);
        fclose(memory_info);

        printf("\n\n");

        printf("The version of the kernel is ");
        FILE *kernel_version = fopen("/proc/version","rb");  //For finding the version of the kernel 
        char kernel[1000000];
        int j=0;
        while(fscanf(kernel_version,"%c",&kernel[j]) != EOF){
            j++;
        }   

        for(int i=0; kernel[i]!='(';i++){
        
            printf("%c",kernel[i]);
        }
        fclose(kernel_version);

        printf("\n\n");

        FILE *cpu_info = fopen("/proc/cpuinfo","rb");  //For finding the CPU info 
        // char ch;
        int count_I= 0;
        printf("The processor type is ");
        do{
            ch = fgetc(cpu_info);
            if(ch == 'I'){
                count_I++;
            }

            if(count_I == 2){
                if(ch == 's'){
                    break;
                }
                printf("%c",ch);
            
            }
        }while(ch!=EOF);
        fclose(cpu_info);
        printf("\n");
        j = 0;
    
        FILE *system_reboot = fopen("/proc/uptime","rb");  //To find the last reboot time of the system.
        char time[10000];
        printf("Last time the system was rebooted is "); 
        do{
            ch = fgetc(system_reboot);
            if(ch == ' '){
            break;
            }
            printf("%c",ch);

        }while(ch!=EOF);

        printf(" seconds ago\n");
        fclose(system_reboot);
    }
}