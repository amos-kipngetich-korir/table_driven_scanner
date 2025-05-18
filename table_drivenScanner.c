    #define S0 0
    #define S1 1
    #define S2 2
    #define S3 3
    #define S4 4
    #define S5 5
    #define S6 6
    #define S7 7
    #define S8 8
    #define S9 9
    #define S10 10
    #define S11 11
    #define S12 12
    #define Se 13
    #define bad -1
    #define Character 10
    #define Digit 20
    #define Other 30
    #define NUMOPERATOR 40
    #define RELOPERATOR 50
    #define End_line 60
    #define ARRAYOPERATOR 70
    #include <string.h>
    #include <stdio.h>
    #include <ctype.h>
    int MAX_SIZE=100;
    int MAX_STRING_LEN  = 100;
    int NUM_STRINGS=1000;
    int stack[20];
    int top = -1;//clearing the stack
    // Rollback(char lexeme[])
    // {
    // lexeme=lexeme[i]
    // }
    // void NextWord()
    // {
    //     push(bad);
    //     lexeme='';
    //     state=s0;
    // }
    // /* Check if the stack is empty */
    struct dictionary{
        char* lexeme[1000];
        char* category[1000];
        //char* tag[100];
    };
    struct dictionary dict;
    int isempty(){
    if(top == -1)
         return 1;
     else
        return 0;
    }

    // /* Check if the stack is full */
    int isfull(){
     if(top == MAX_SIZE)
       return 1;
     else
        return 0;
    }

    // /* Function to return the topmost element in the stack */
    int peek(){
     return stack[top];
     }

    // /* Function to delete from the stack */
    int pop(){
    int data;
    if(!isempty()) {
        data = stack[top];
       top = top - 1;
        return data;
    } else {
        printf("Could not retrieve data, Stack is empty.\n");
    }
    }

    // /* Function to insert into the stack */
    int push(int data){
    if(!isfull()) {
        top = top + 1;
        stack[top] = data;
        //printf("\npush state: %d",stack[top]);
    } else {
        printf("Could not insert data, Stack is full.\n");
     }
     }
    enum SA {
    s1=S2,s2=S4,s3=S5
    
 };
 enum relexpr{EQ,LE,GE,NE};
 const char* rel_op[]={"==","<=","=>","!="};
int isInputInEnum(enum SA input) {
    switch (input) {
        case S2:
            return 1;
            break; // Input matches an enum value
        case S4:
            return 1;
            break;
        case S5:
            return 1;
            break;
        default:
            return 0; // Input does not match any enum value

    }
}
    // /*Character Category*/
    int CharCat(char ch)
     {
     if ( ((ch>='a' && ch<='z' ) )|| ((ch>='A' && ch<='Z' ))) {
         return Character;
     }
    else if ((ch>='0') && (ch <='9')){
        return Digit;
    }
     else if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='(' || ch==')' || ch=='}' || ch=='{' ) {
     return NUMOPERATOR;
    }
    else if(ch=='>'|| ch=='<' || ch=='=' || ch=='!'){
        return RELOPERATOR;
    }
     else if ( ch==';'){
        return End_line;
    }
    else if(ch=='[' || ch==']' || ch==','){
        return ARRAYOPERATOR;
    }
    else{
        return Other;
    }
    }
    int State_Transition(int state, int value) {
    switch (state) {
        case 0:
            if (value == 10) {
                return S1;//first letter of the identifier
            } else if (value == 20 || value == 30) {
                return Se;//identifier should not start with a number
            }
            else if (value == 40){
                return S4;//for the operator
            }
            else if (value == 60){
                return S5;// for the end_line
            }
            else if(value==50){
                return S6;
            }
            else if(value=70){
                return S7;
            }
            break;
        case 1:
            if (value == 10) {
                return S2;//describing two characters following each other and making an identifier
            } 
            else if (value == 20) {
                return S2;//the second character can be a number
            }
            else if(value=70){
                return S7;
            }
            break;
        case 2:
            if (value == 10 || value == 30) {
                return S2;//still allowed
            } else if (value == 20) {
                return S2;//still allowed
            }
            break;
        case 6:
        if(value==50){
            return S6;
        }
        case 7:
        if(value==20){
            return S8;
        }
        else if(value==70){
           return  S12;
        }
        break;
        case 8:
        if(value==70){
            return S9;
        }
        break;
        case 9:
        if(value==20){
            return S8;
        }
        else if(value==70){
            return S10;
        }
        break;
        default:
        return -1; // Handle invalid state or value
    }
}
  char * keyword[]={"main","int","enum","char"};
  char * type_tags[]={"int","char","bool"};
//   int isInputInEnum(enum SA input) {
//     switch (input) {
//         case S2:
//             return 1;
//             break; // Input matches an enum value
//         case S4:
//             return 1;
//             break;
//         case S5:
//             return 1;
//             break;
//         default:
//             return 0; // Input does not match any enum value

//     }
// }

     char* validate(int state,char *lexeme)
     {
        printf("\nSTATE: %d LEXEMES: %s",state,lexeme);
        if (state == 2) {
            
            // Trim whitespace
            lexeme[strcspn(lexeme, " \n\r")] = '\0';   
        
            // Check for Keywords (highest priority)
            if (strcmp(lexeme,"main")==0 || strcmp(lexeme,"typedef") == 0 || strcmp(lexeme,"stringarray") == 0 ) {
                printf(": Keyword");
                return "Keyword";
            }
            // Check for Tags (second priority)
            else if (strcmp(lexeme,"int") == 0 || strcmp(lexeme,"char") == 0 || strcmp(lexeme,"bool") == 0) {
                printf(": tag");
                return "tag";  
            }
            // Default: Identifier
            else {
                printf(": Identifier");
                return "Identifier";
            }
        }
    else if(state==S4){  
        return "Num_Operator";//identifier type.
     }
     else if ( state==S5){
        return "Endline";
     }
     else if(state==S6){
        return "Rel_Operator";
     }
     else if(state==S10 || state==S12 || state==S9){
        return "Array";
     }
    else{
        return "Invalid";
     }
     }
     void truncateLexeme(char* lexeme, int desiredLength) {
    //if (strlen(lexeme) > desiredLength) {
        lexeme[desiredLength] = '\0'; // Null-terminate at desired length
    //}
}
    // /* Main function */
int scanner(){
// 100 strings, each up to 99 characters plus null terminator
    int k=0;
    char input[100];
    char colon=':';
    char **lexeme = (char **)malloc(NUM_STRINGS * sizeof(char *));
    for (int i = 0; i < NUM_STRINGS; i++) {
        lexeme[i] = (char *)malloc(MAX_STRING_LEN * sizeof(char));
        
        if (lexeme[i] == NULL) {
            printf("Memory allocation failed for string %d!\n", i);
        }
    }
    printf("Enter the lexeme: ");
    // Read a string from the user into the first element of lexemes
    scanf("%[^\n]", input); // %99s to prevent buffer overflow
for(int i=0;i<30;i++){
    for(int j=0;j<30;j++){
    lexeme[i][j]=input[k];
    if (isspace(input[k])) {
        lexeme[i][j]='\0';
            j=30;
        }
        //  printf("%c",input[k]);
         k++;
    }
//    printf("\n");
 if (input[k]==colon) {
            i=30;
        }
}
 
 
    // printf("enter the lexeme: ");
    // char lexeme [100];
    int j=0;
    k=5;
    char input2;
   
    // scanf("%s",lexeme);

    // // printf("Lexeme:%s ",lexeme);
    // //  printf("char: %c",input);
    // // printf("\nCategory:%d",CharCat(input));
   int state=S0;
   //printf("\nstate transition:");
   for(int i=0;i<=30;i++){
// printf("state transition for lexeme %d",i);
do{
   input2=lexeme[i][j];
   printf("%c",input2);
   state=State_Transition(state,CharCat(input2));
   push (state);
   j++;
   }while(lexeme[i][j]!='\0');
//    state=0;
//    j=0;
 
 
//    printf("\n%s",validate(state));
//  do
//  {
//  if(isInputInEnum((enum SA) state)){
//   top=-1;

//  }
 
//  cat=CharCat(lexeme[i+1]);
 //state=State_Transition(state,CharCat(cat));
//  }
//  while(state!=se);
k=strlen(lexeme[i]);
     do
{
 state=pop();
 //printf("popped state: %d",state);
 //printf("\n%d  lexeme[%d]: %c",i,i,lexeme[i]);s
truncateLexeme(lexeme[i],k );
//printf("\n%d  lexeme[%d]: %c",i,i,lexeme[i]);
 k--;

}
 while((k>0) && ((!isInputInEnum((enum SA)state))));

   if (isInputInEnum((enum SA)state)) {
     dict.lexeme[i]=lexeme[i];
    // printf("\n%d %s",state,lexeme[i]);

      dict.category[i]=validate(state,lexeme[i]);
      
// printf("\n{ %s %s }",dict.lexeme[i],dict.category[i]);
    } 
    else {
        //printf("\n{ %s Invalid }",lexeme[i]);
    } 
   state=S0;
   j=0;
   top=-1;
//    if(lexeme[i]!='\0'){
//      printf("\n");
//    }
}
for(int i=0;i<=50;i++){
    printf("\n %s %s",dict.lexeme[i],dict.category[i]);
    // if(!strcmp(dict.category[i],"identifier")){
    //   if(!strcmp(dict.category[i-1],"tag") && i>0) {
    //     printf("variable correctly declared");
    //   }
    //   else{
    //     printf("variable not declared first");
    //   }
    // }
    if(!strcmp(dict.lexeme[i],";")){
        i=50; 
    }
}
// for ( int j=0;j<15;j++){
//     if(!strcmp(dict.category[j],"tag")){
//         strcpy(dict.tag[j],dict.category[j]);
//         strcpy(dict.category[j],dict.category[j+1]);  
//         printf("\n %s %s %s",dict.lexeme[j],dict.category[j],dict.tag[j]);
//     }
// }
// push(bad);
//    // print stack data
//    while(!isempty()) {
//       int data = pop();
//       printf("%d\n",data);
//    }
return 0;
}