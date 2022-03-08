#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
int titForTwoTat(int previous[]);
int titForTat(int previous[]);
int susTitForTat(int previous[]);
int freeRider(void);
int alwaysCoop(void);
int geneticAlgo(void);
int main(void){
    int history1[6] = {0,0,0,0,0,0};
    int history2[6] = {0,0,0,0,0,0};
    int count1 = 0;//count of hours for history1
    int count2 = 0;//count of hours for history2
    for(int j = 0;j<5;j++){//change number here to change how many times the program runs six times
        for(int p = 0;p<6;p++){//resetting the history array
            history2[p] = 0;
            history1[p] = 0;
        }
        for(int x = 0;x<6;x++){//filling the history array 
            history2[x] = titForTat(history1);//insert program 1
            history1[x] = geneticAlgo();//insert program 2
            if(history1[x]==1&&history2[x]==2){//giving the fitness values to each of the chromosones
                count1+=20;
                count2+=0;
            }
            else if(history1[x]==2&&history2[x]==1){
                count1+=0;
                count2+=20;
            }
            else if(history1[x]==2&&history2[x]==2){
                count1+=10;
                count2+=10;
            }
            else if(history1[x]==1&&history2[x]==1){
                count1+=1;
                count2+=1;
            }
            printf("value of 1: %d,value of 2:%d,count1:%d,count2:%d\n",history1[x],history2[x],count1,count2);
            sleep(1);//sleep for random numbers of some algorithms to print correctly
        }
    }
    printf("\nThe number of hours accumulated by algorithm 1: %d \nThe number of hours accumulated in algorithm 2: %d",count1,count2);
}

int titForTat(int previous[]){
    if(previous[0]==0){//0 means in this case the start of the experiment
        return 1;//1 means to cooperate
    }
    else{
    int size = 0;
    for(int c = 0 ; c<6;c++){
        if(previous[c]!=0){
            size++;
        }
    }
    return previous[size-1];//return opponents previous move
    }
}
int titForTwoTat(int previous[]){
    int size = 0;
    for(int c = 0 ; c<6;c++){
        if(previous[c]!=0){
            size++;
        }
    }
    if(previous[0]==0){//0 means in this case the start of the experiment
    return 1;//1 means to cooperate
    }
    
    else if(previous[size-2]==2&&previous[size-1]==2&&size>1){
        return 2;//2 means to defect
    }
    else{
        return 1;
    }
}
int susTitForTat(int previous[]){
    if(previous[0]==0){//0 means in this case the start of the experiment
        return 2;//2 means to defect
    }
    else{
        int size = 0;
        for(int c = 0 ; c<6;c++){
            if(previous[c]!=0){
                size++;
            }
        }
        return previous[size-1];//return opponents previous move
    }
}
int freeRider(void){
    return 2;//always return defect
}
int alwaysCoop(void){
    return 1;//always return cooperate
}

int geneticAlgo(void){
    srand(time(NULL));//setting the rand so that we can get truely random numbers
    int pop[10][7];//10 population samples with 6 genes each in sequence with seventh for counting fitness value
    for(int c = 0; c<10;c++){
        for(int d = 0 ; d<6;d++){
            pop[c][d] = (rand()%2+1);//filling in the array with either 1 or 2
        }
    }
    int count = 0;
    for(int i = 0;i<100;i++){//do the entire process 100 times running the population and crossing it
        for(int w = 0; w<2;w++){//do it twice to get a full new population
            for(int j = 0;j<10;j++){
                pop[j][6]=0;//resetting the fitness value of each array
            }
            for(int c = 0;c<10;c+=2){//looping and finding the fitness value of each chromosone
                
                for(int d = 0; d<6;d++){//running to find the most sucessful of the two chromosones
                    if(pop[c][d]==1&&pop[c+1][d]==2){//giving the fitness values to each of the chromosones
                        pop[c][6]+=20;
                        pop[c+1][6]+=0;
                    }
                    else if(pop[c][d]==2&&pop[c+1][d]==1){
                        pop[c][6]+=0;
                        pop[c+1][6]+=20;
                    }
                    else if(pop[c][d]==2&&pop[c+1][d]==2){
                        pop[c][6]+=10;
                        pop[c+1][6]+=10;
                    }
                    else if(pop[c][d]==1&&pop[c+1][d]==1){
                        pop[c][6]+=1;
                        pop[c+1][6]+=1;
                    }
                }
                if(pop[c][6]>pop[c+1][6]){//getting the best of the two into the population to replace previous
                    for(int w = 0; w<6;w++){
                        pop[count][w]=pop[c+1][w];
                    }
                }
                if(pop[c][6]<pop[c+1][6]){
                    for(int w = 0; w<6;w++){
                        pop[count][w]=pop[c][w];
                    }
                }
                count++;
            }
        }
        count = 0;
        int temp;
        for(int w=0;w<10;w+=2){//setting up the mating step
            int cross = rand()%5+1;//selecting where to cross the two chromosomes
            for(int c = 0;c<=cross;c++){//switching the two genes
                temp = pop[w][c];
                pop[w][c]=pop[w+1][c];
                pop[w+1][c] = temp;
            }
        }
        for(int w= 0; w<10;w++){//mutation step
            for(int c = 0; c<6;c++){
                temp = rand()%6;
                if(temp==5){
                    pop[w][c] = (rand()%2)+1;
                }
            }
        }
    } 
    return pop[1][5];   
}
