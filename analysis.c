// C program to calculate the First and 
// Follow sets of a given grammar 
#include "lex.h"
#include<stdio.h> 
#include<ctype.h> 
#include<string.h> 
#include <unistd.h>
#include <stdlib.h>

// Functions to calculate Follow 
void followfirst(char * , int, int); 
void follow(char * c); 
  
// Function to calculate First 
void findfirst(char * , int, int); 
  
int count, n = 0; 
  
// Stores the final result  
// of the First Sets 
char calc_first[10][100][100]; 
  
// Stores the final result 
// of the Follow Sets 
char calc_follow[10][100][100]; 
int m = 0; 
  
// Stores the GrTokens->tokens rules 
struct Token * GrTokens;
char f[10][100][100];
int posF=0;

char first[10][100][100]; 
int posFirst=0;

int k; 
char ck[100]; 
int e; 



char doneT[100][100];
int ptrT=-1;

void calculFF() 
{ 
    int jm = 0; 
    int km = 0; 
    int i, choice; 
    char * c;
    char ch; 
    count = *getTokenLen(); 
    int kay; 
    char done[count][100]; 
    int ptr = -1; 
    GrTokens = getTokens();

    

    int point1 = 0, point2, xxx;
    
      
    for(k = 0; k < count; k++) 
    { 
        c = GrTokens->tokens[k][0]; //get all the first[posFirst] NT of rule
        point2 = 0; 
        xxx = 0; 
          
        // Checking if First of c has 
        // already been calculated 
        for(kay = 0; kay <= ptr; kay++) 
            if(strcmp(c,done[kay])==0) 
                xxx = 1; 
                  
        //if already calculated , pass
        if (xxx == 1) 
            continue; 
          
        // Function call  
        //doneT=malloc(100*sizeof(char*)); 
        ptrT =-1;

        findfirst(c, 0, 0);
        //free(ptrT);
        ptr += 1; 
          
        // Adding c to the calculated list 
        strcpy(done[ptr] , c); 
        printf("\nFirst(%s) = { ", c); 
        strcpy(first[posFirst][0],c);
        strcpy(calc_first[point1][point2++], c); 
        n++;
        // Printing the First Sets of the grammar 
        for(i = 1; i <n; i++) { 
            printf("%s, ", first[posFirst][i]); 
            strcpy(calc_first[point1][point2++],first[posFirst][i]); 
        } 
        printf("}\n"); 
        n=0; 
        posFirst++;
        point1++; 
    } 
    printf("\n"); 
    printf("-----------------------------------------------\n\n"); 

    char donee[count][100]; 
    ptr = -1; 
      
    // Initializing the calc_follow array 
    for(k = 0; k < count; k++) { 
        for(kay = 0; kay < 100; kay++) { 
            calc_follow[k][kay][0]='\0'; 
        } 
    } 
    point1 = 0; 
    int count = 0; 
    for(e = 0; e < count; e++) 
    { 
        strcpy(ck,GrTokens->tokens[e][0]); 
        point2 = 0; 
        xxx = 0; 
          
        // Checking if Follow of ck 
        // has alredy been calculated 
        for(kay = 0; kay <= ptr; kay++) 
            if(strcmp(ck,donee[kay])==0) 
                xxx = 1; 
                  
        if (xxx == 1) 
            continue; 
        count += 1; 
        ptrT=-1;
        m=1;
        // Function call 
        follow(ck); 
        ptr += 1; 
          
        // Adding ck to the calculated list 
        strcpy(donee[ptr],ck); 
        printf("Follow(%s) = { ", ck); 
        strcpy(calc_follow[point1][point2++],ck); 
          
        // Printing the Follow Sets of the grammar 
        
        for(i = 1; i < m; i++) { 
            printf("%s, ", f[posF][i]); 
            strcpy(calc_follow[point1][point2++] ,f[posF][i]); 
        } 
        printf(" }\n\n"); 
        
        point1++;  
        posF++;
    } 
    printf("-----------------------------------------------\n\n"); 
    
} 
  
void follow(char * c) 
{ 
    int i, j; 
      
    // Adding "$" to the follow 
    // set of the start symbol 
    if(strcmp(GrTokens->tokens[0][0] ,c)==0) { 

        int kay = 0, duplicate=0;
        for(kay = 0; kay <= ptrT; kay++) {
            if(strcmp("$",doneT[kay])==0){
                duplicate = 1; 
            }
        }
        if(!duplicate){
            strcpy(f[posF][m++], "$"); 
            ptrT++;
            strcpy(doneT[ptrT] , "$");
        }
    } 
    for(i = 0; i < 10; i++) 
    { 
        for(j = 2;j < 10; j++) 
        { 
            if(strcmp(GrTokens->tokens[i][j], c)==0) 
            { 
                if(strcmp(GrTokens->tokens[i][j+1], "\0")!=0) 
                { 
                    // Calculate the first[posFirst] of the next 
                    // Non-Terminal in the GrTokens->tokens 
                    followfirst(GrTokens->tokens[i][j+1], i, (j+2)); 
                } 
                  
                if(strcmp(GrTokens->tokens[i][j+1], "\0")==0 && strcmp(c,GrTokens->tokens[i][0])!=0) 
                { 
                    // Calculate the follow of the Non-Terminal 
                    // in the L.H.S. of the GrTokens->tokens 
                    follow(GrTokens->tokens[i][0]); 
                } 
            }  
        } 
    } 
} 
  
void findfirst(char * c, int q1, int q2) //findfirst(c,0,0) in main
{ 
    int j; 
      
    // The case where we  
    // encounter a Terminal 
    if(!(isupper(c[0]))) { 
        strcpy(first[posFirst][n++], c); 
    } 
    
    for(j = 0; j < count; j++){ 
        if(strcmp(GrTokens->tokens[j][0],c)==0) { //if the rule has NT in  left
            if(strcmp(GrTokens->tokens[j][2],"#")==0) { // if the right has only epsilon
                if(GrTokens->tokens[q1][q2][0] == '\0') {// if its end of rule
                    n++;
                    strcpy(first[posFirst][n],"#"); 
                }
               else {//not end of rule
                    if(GrTokens->tokens[q1][q2][0]  != '\0' 
                            && (q1 != 0 || q2 != 0)){ 
                        // Recursion to calculate First of New 
                        // Non-Terminal we encounter after epsilon 
                       findfirst(GrTokens->tokens[q1][q2], q1, (q2+1)); 
                    } 
                    else{
                        n++;
                        strcpy(first[posFirst][n],"#"); 
                    }
               }
            }else{// if the right dont have epsilon  

                if(!isupper(GrTokens->tokens[j][2][0])){ 
                
                    int kay = 0, duplicate=0;
                    for(kay = 0; kay <= ptrT; kay++) {
                        if(strcmp(GrTokens->tokens[j][2],doneT[kay])==0){
                            duplicate = 1; 
                        }
                    }
                    if(duplicate){
                        continue;
                    }
                    n++;
                    strcpy(first[posFirst][n],GrTokens->tokens[j][2]); //if not NT, so we put in first[posFirst]
                    ptrT++;
                    strcpy(doneT[ptrT] , GrTokens->tokens[j][2]);
                        
                    
                    
                }else{
                    // Recursion to calculate First of 
                    // New Non-Terminal we encounter  
                    // at the beginning 
                    findfirst(GrTokens->tokens[j][2], j, 3); 
                } 
            }
        } 
    }  
} 
  
void followfirst(char * c, int c1, int c2) 
{ 
    int k; 
      
    // The case where we encounter 
    // a Terminal 
    if(!(isupper(c[0]))) {
        int kay = 0, duplicate=0;
        for(kay = 0; kay <= ptrT; kay++) {
            if(strcmp(c,doneT[kay])==0){
                duplicate = 1; 
            }
        }
        if(!duplicate){
            strcpy(f[posF][m++], c); 
            ptrT++;
            strcpy(doneT[ptrT] , c);
        }
        
    }else
    { 
        int i = 0, j = 1; 
        for(i = 0; i < count; i++) 
        { 
            if(strcmp(calc_first[i][0],c)==0) 
                break; 
        } 
          
        //Including the First set of the 
        // Non-Terminal in the Follow of 
        // the original query 
        while(calc_first[i][j][0]!='\0') 
        { 
            if(strcmp(calc_first[i][j],"#")!=0)  
            { 
                int kay = 0, duplicate=0;
                for(kay = 0; kay <= ptrT; kay++) {
                    if(strcmp(calc_first[i][j],doneT[kay])==0){
                        duplicate = 1; 
                    }
                }
                if(!duplicate){
                    strcpy(f[posF][m++], calc_first[i][j]); 
                    ptrT++;
                    strcpy(doneT[ptrT] , calc_first[i][j]);
                }
            } 
            else
            { 
                if(strcmp(GrTokens->tokens[c1][c2],"\0")==0)
                { 
                    // Case where we reach the 
                    // end of a GrTokens->tokens 
                    follow(GrTokens->tokens[c1][0]); 
                } 
                else
                { 
                    // Recursion to the next symbol 
                    // in case we encounter a "#" 
                   followfirst(GrTokens->tokens[c1][c2], c1, c2+1); 
                } 
            } 
            j++; 
        } 
    } 
} 

void table(){
	int sid,i,ptr,kay,xxx,k;
	sid=getposLT();
	
	strcmp(GrTokens->list_T[sid], "$");

	sid++;
	printf("LL(1) Parsing Table for the above grammer\n");
	printf("\t|\t");
	for(i = 0;i < sid; i++){
		printf("%s\t",GrTokens->list_T[i]);
	}
	printf("\n============================================================\n");
	char first_token[count][sid][100];
	for(i=0;i<count;i++){
		int destiny = 0;
		k = 2;
		int ct = 0;
		char * tem[100];
		while(strcmp(GrTokens->tokens[i][k],"\0")!=0){
			if(!isupper(GrTokens->tokens[i][k][0])){
				strcpy(tem[ct++],GrTokens->tokens[i][k]);
				strcpy(tem[ct++],"_");
				strcpy(tem[ct++], "\0");
				k++;
				break;
			}
			else{
				int j=0,m = 0;
				for(j=0;j<count;j++){
					if(strcmp(calc_first[j][0], GrTokens->tokens[i][k])==0){
						for(m=1;m<100;m++){
							if(strcmp(calc_first[j][m] ,"!")!=0){
								tem[ct++] = calc_first[j][m];
							}
							else
								break;
						}
					break;
					}
				}
				strcpy(tem[ct++] ,"_");
			}
			k++;
		}
		int j = 0,m;		
		for(m = 0;m<ct;m++){
			if(strcmp(tem[m],"#")==0){
				j = 1;
			}
			else if(strcmp(tem[m],"_")==0){
				if(j == 1){
					j = 0;
				}
				else
					break;
			}
			else{
				strcpy(first_token[i][destiny++], tem[m]);
			}
		}
	}
	char  table[count][sid+1][100];
	ptr = -1;
	for(i = 0; i < count ; i++){
		for(kay = 0; kay < (sid + 1) ; kay++){
			table[i][kay][0]= '\0';
		}
	}
	for(i = 0; i < count ; i++){
		strcmp(ck,GrTokens->tokens[i][0]);
		xxx = 0;
		for(kay = 0; kay <= ptr; kay++)
			if(strcmp(ck,table[kay][0])==0)
				xxx = 1;
		if (xxx == 1)
			continue;
		else{
			ptr = ptr + 1;
			strcpy(table[ptr][0],ck);
		}
	}
	for(i = 0; i < count ; i++){
		int m = 0;
		while(strcmp(first_token[i][m],"\0")!=0){
			int to,ni=0;
			for(to=0;to<sid;to++){
				if(strcmp(first_token[i][m],GrTokens->list_T[to])==0){
					ni = 1;
				}
			}
			if(ni == 1){
				char  xz[100]; 
				strcpy(xz,GrTokens->tokens[i][0]);
				int cz=0;
				while(strcmp(table[cz][0],xz)!=0){
					cz = cz + 1;
				}
				int vz=0;
				while(strcmp(GrTokens->list_T[vz] ,first_token[i][m])!=0){
					vz = vz + 1;
				}
				table[cz][vz+1][0]= (char )(i + 65);
			}
			m++;
		}
	}
	for(k=0;k<sid;k++){
		for(kay=0;kay<100;kay++){
			if(strcmp(calc_first[k][kay], "!")==0){
				break;
			}
			else if(strcmp(calc_first[k][kay] , "#")==0){
				int fz = 1;
				while(strcmp(calc_follow[k][fz], "!")!=0){
					char  xz[100]; 
					strcpy(xz,GrTokens->tokens[k][0]);
					int cz=0;
					while(strcmp(table[cz][0] ,xz)!=0){
						cz = cz + 1;
					}
					int vz=0;
					while(strcmp(GrTokens->list_T[vz],calc_follow[k][fz])!=0){
						vz = vz + 1;
					}
					strcpy(table[k][vz+1],"#");
					fz++;	
				}
				break;
			}
		}
	}
	for(i = 0; i < count ; i++){
		printf("\t\t\t   %s\t|\t",table[i][0]);
		for(kay = 1; kay < (sid + 1) ; kay++){
			if(strcmp(table[i][kay] ,"!")==0)
				printf("\t\t");
			else if(strcmp(table[i][kay], "#")==0)
				printf("%s=#\t\t",table[i][0]);
			else{
				int mum = (int)(table[i][kay][0]);
				mum -= 65;
				char tmp[100];
				//strcpy(tmp,GrTokens->tokens[mum]);
				printf("%s\t\t",tmp);
			}
		}
		printf("\n");
		printf("\t\t\t---------------------------------------------------------------------------------------------------------------------");
		printf("\n");
	}
	int j;
	/*printf("\n\nPlease enter the desired INPUT STRING = ");
	char input[100];
	scanf("%s",input);
	printf("\n\t\t\t\t\t===========================================================================\n");
	printf("\t\t\t\t\t\tStack\t\t\tInput\t\t\tAction");
	printf("\n\t\t\t\t\t===========================================================================\n");
	int i_ptr = 0,s_ptr = 1;
	char stack[100];
	stack[0] = '$';
	stack[1] = table[0][0];
	while(s_ptr != -1){
		printf("\t\t\t\t\t\t");
		int vamp = 0;
		for(vamp=0;vamp<=s_ptr;vamp++){
			printf("%c",stack[vamp]);
		}
		printf("\t\t\t");
		vamp = i_ptr;
		while(input[vamp] != '\0'){
			printf("%c",input[vamp]);
			vamp++;
		}
		printf("\t\t\t");
		char her = input[i_ptr];
		char him = stack[s_ptr];
		s_ptr--;
		if(!isupper(him)){
			if(her == him){
				i_ptr++;
				printf("POP ACTION\n");
			}
			else{
				printf("\nString Not Accepted by LL(1) Parser !!\n");
				exit(0);
			}
		}
		else{
			for(i=0;i<sid;i++){
				if(GrTokens->list_T[i] == her)
					break;
			}
			char produ[100];
			for(j=0;j<count;j++){
				if(him == table[j][0]){
					if (table[j][i+1] == '#'){
						printf("%c=#\n",table[j][0]);
						produ[0] = '#';
						produ[1] = '\0';
					}
					else if(table[j][i+1] != '!'){
						int mum = (int)(table[j][i+1]);
						mum -= 65;
						strcpy(produ,GrTokens->tokens[mum]);
						printf("%s\n",produ);
					}
					else{
						printf("\nString Not Accepted by LL(1) Parser !!\n");
						exit(0);
					}
				}
			}
			int le = strlen(produ);
			le = le - 1;
			if(le == 0){
				continue;
			}
			for(j=le;j>=2;j--){
				s_ptr++;
				stack[s_ptr] = produ[j];
			}
		}
	}
	if (input[i_ptr] == '\0'){
		printf("OK : verification success\n");
	}
	else
		printf("KO : verification failed\n");
	*/
	free(GrTokens);
}