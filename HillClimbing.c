int simphill(void){
    int goal = 100;//variable goal set to how efficient you want to find the 
    int initialState[2][7] = {0};//setting arrays to zero and initalizing them
    int currentState[2][7] = {0};
    for(int c = 0; c<2;c++){//finding an initial state
        for(int d = 0 ; d<6;d++){
            initialState[c][d] = (rand()%2+1);//filling in the array with either 1 or 2
        }
    }
    int c = 0;
    for(int d = 0; d<6;d++){//finding hours to see if state found is goal state
        if(initialState[c][d]==1&&initialState[c+1][d]==2){
            initialState[c][6]+=20;
            initialState[c+1][6]+=0;
        }
        else if(initialState[c][d]==2&&initialState[c+1][d]==1){
            initialState[c][6]+=0;
            initialState[c+1][6]+=20;
        }
        else if(initialState[c][d]==2&&initialState[c+1][d]==2){
            initialState[c][6]+=10;
            initialState[c+1][6]+=10;
        }
        else if(initialState[c][d]==1&&initialState[c+1][d]==1){
            initialState[c][6]+=1;
            initialState[c+1][6]+=1;
        }
    }
    int hoursIn = initialState[1][6] + initialState[0][6];
    if(hoursIn<=goal){//checking to see if it is goal state
        return initialState[1][5];//returning if it is
    }
    for(int c = 0; c<2;c++){//copying the inital array into the currentarray
        for(int d = 0 ; d<7;d++){
            currentState[c][d] = initialState[c][d];
        }
    }
    int hoursCur = hoursIn;//setting current hours to match copied array
    
    for(int c = 0 ; c<2;c++){//going though each number in the array flipping it to see if it is better than the previous array
        for(int d = 0 ; d<6; d++){

            initialState[1][6] = 0;
            initialState[0][6] = 0;
            
            if(initialState[c][d] == 1){//flip one of the numbers
                initialState[c][d] = 2;
            }
            else{
                initialState[c][d] = 1;
            }
            for(int m = 0; m<6;m++){//finding hours of new change to array
                if(initialState[0][m]==1&&initialState[1][m]==2){
                    initialState[0][6]+=20;
                    initialState[1][6]+=0;
                }
                else if(initialState[0][m]==2&&initialState[1][m]==1){
                    initialState[0][6]+=0;
                    initialState[1][6]+=20;
                }
                else if(initialState[0][m]==2&&initialState[0+1][m]==2){
                    initialState[0][6]+=10;
                    initialState[1][6]+=10;
                }
                else if(initialState[0][m]==1&&initialState[1][m]==1){
                    initialState[0][6]+=1;
                    initialState[1][6]+=1;
                }
            }
            int hoursIn = initialState[1][6] + initialState[0][6];//calculating total hours
            if(hoursIn<hoursCur){
                for(int f = 0 ; f<7;f++){//updating current to better state
                    currentState[0][f] = initialState[0][f];
                    currentState[1][f] = initialState[1][f];
                }
                hoursCur = hoursIn;//updating current state
                d = 0;
                c= 0;
                if(hoursCur<=goal){//checking if goal state reached
                    return currentState[0][5];//if it is returning the answer
                }
            }
            else{
                for(int f = 0 ; f<7;f++){//returning state to previous 
                    initialState[0][f] = currentState[0][f];
                    initialState[1][f] = currentState[1][f];
                }//continuing to find the optimal answer

            }

        }

    }
    simphill();//wouldve found solution by now so reset with different random numbers

            
}