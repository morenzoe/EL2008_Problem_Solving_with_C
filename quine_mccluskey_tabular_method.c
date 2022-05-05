#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data[257];      // minterm in decimal
    int bin[26];        // minterm in binary
    int noofones;       // sum of bin
    int isimplicant;    // 1 or 0
    int minarr[1000];
    
    char term[26];
    
    struct node* right;
};

struct node *root;      // head of minterm linked list
struct node *head;      // 
struct node *improot;
struct node *save;
struct node *fin;

int var;                // number of variables
int min;                // number of minterms
int number=1;
int columns=2;
int check=1;
int limit;              // biggest num of ones
int imptable[100][100]; //
int counter=0;
int essential[1000];
int t=0;
int no=0;
int minterms[1000];     // array of minterms

char a[26];
char b[26];       //variable names are stored as alphabets, can be modified to work for more variables

void group1();                          //the minterms are grouped according to the number of ones
void arrange();                         //the minterms are arranged according t their magnitude
void swap(struct node*,struct node*);   //data of two nodes is swapped
void disp();                            //various column with pairings are displayed
void further_groupings();               //the minterms are paired
void end_loop(struct node*);            //the extra node in a list is deleted
void display_implicants();              //the implicants are displayed
void implicants(struct node*);          //initializes each term as an implicant
void collect();                         //converts the term from binary notation to variables
void variables();                       //the variables for the function are stored
void convert();                         //reduces the prime implicants which occur more than once to one
void implicants_table();                //the prime implicants table is formed and essential implicants are found
void func();                            //the minimized function is displayed
void other_implicants();                //the prime implicants other than the essential ones are collected
void final_terms();                     //the final terms in the minimized function are noted
void store_minterms();                  //minterms are stored in an array

int main()
{
    int i;  // storing minterm loop variable
    int j;  // minterm in dec, will be converted to bin
    int k;  // bin indexing
    int x;  // dec to bin loop variable
    
    struct node* temp;
    
    printf("\nEnter the number of variables : ");       //no. of variables and minterms are recorded
    scanf("%d",&var);
    printf("\nEnter the number of minterms : ");
    scanf("%d",&min);
    
    i=min-1; // for looping
    
    root=(struct node*)malloc(sizeof(struct node));
    temp=(struct node*)malloc(sizeof(struct node));
    
    printf("\nEnter the minterms one by one\n\n");
    scanf("%d",&temp->data[0]);                     //first minterm is stored
    
    j=temp->data[0];    // minterm in dec, will be converted to bin
    temp->noofones=0;   // init
    x=var;              // bin digits = num of var, see truth table
    k=0;                // init
    
    // converts minterm to binary notation
    while(x--)      
    {
        // dec to bin, division method
        if(j%2==1)
        {
            temp->bin[k]=1;  
            temp->noofones++;
        }
        else
        {
            temp->bin[k]=0;
        }
        j=j/2;
        k++;
    }
    
    // rest of the minterms are stored
    while(i--)      
    {
        // jadi ribet karena ga pake fungsi linked list (push, dkk)
        temp=temp->right=(struct node*)malloc(sizeof(struct node));
        
        // same procedure as first minterm
        scanf("%d",&temp->data[0]);
        j=temp->data[0];
        temp->noofones=0;
        x=var;
        k=0;
        while(x--)
        {
            if(j%2==1)          //converts the minterms to binary notation
            {
                temp->bin[k]=1;
                temp->noofones++;       //the number of ones in binary notation
            }
            else
            {
                temp->bin[k]=0;
            }
            j=j/2;
            k++;
        }
    }
    
    // end of linked list
    temp->right=NULL;
    
    //various functions are called according to their needs
    
    // sort linked list by minterm valu
    arrange();      
    
    // traverse linked list, store minterm in array
    store_minterms();
    
    // sort linked list by num of ones
    group1();
    
    
    disp();
    end_loop(root);
    head=(struct node*)malloc(sizeof(struct node));
    while(check>0)
    {
        further_groupings();
    }
    save->right=NULL;           //storing null value in link field of list storing prime implicants
    printf("No pairs formed hence no further calculation required\n\n");
    end_loop(improot);
    collect();
    display_implicants();
    variables();
    implicants_table();
    other_implicants();
    final_terms();
    end_loop(fin);
    convert();
    func();
    return 0;
}

//arranging the minterms in increasing order of magnitude
void arrange()          
{
    struct node *temp1,*temp2;
    temp1=temp2=root;
    while(temp1!=NULL)
    {
        temp2=root;
        while(temp2!=NULL)
        {
            //if not in order their values are exchanged with swap function
            if(temp1->data[0]<temp2->data[0])       
            {
                swap(temp1,temp2);
            }
            temp2=temp2->right;
        }
        if(temp1->right==NULL)
        {
            //the magnitude of the last minterm is recorded later for prime implicants table
            limit=temp1->data[0];           
        }
        temp1=temp1->right;
    }
}

//array to store all the minterms
void store_minterms()       
{
    int i=0;
    struct node* temp;
    temp=root;
    while(temp!=NULL)
    {
        minterms[i]=temp->data[0];
        i++;
        temp=temp->right;
    }
}

//swapping all the data of two nodes
void swap(struct node* temp1,struct node* temp2)        
{
    int x,y,i=0;
    i=var;
    for(i=0;i<var;i++)      //binary notation is exchanged
    {
        y=temp1->bin[i];
        temp1->bin[i]=temp2->bin[i];
        temp2->bin[i]=y;
    }
    y=temp1->noofones;          //no. of ones is exchanged
    temp1->noofones=temp2->noofones;
    temp2->noofones=y;
    x=temp1->data[0];           //data(minterm) is exchanged
    temp1->data[0]=temp2->data[0];
    temp2->data[0]=x;
}

//where the minterms are arranged according to the number of ones
void group1()       
{
    int i,j,k=0;
    struct node *temp,*next;
    temp=save=root;
    root=next=(struct node*)malloc(sizeof(struct node));
    for(i=0;i<=var;i++)
    {
        temp=save;
        while(temp!=NULL)
        {
            //minterms are arranged according to no. of ones , first 0 ones then 1 ones... and so on
            if(temp->noofones==i)       
            {
                // fill node next with node temp values
                next->data[0]=temp->data[0];
                k++;
                for(j=0;j<var;j++)
                {
                    next->bin[j]=temp->bin[j];
                }
                next->noofones=temp->noofones;
                next=next->right=(struct node*)malloc(sizeof(struct node));
            }
            temp=temp->right;
        }
    }
    minterms[k]=-1;
    next->right=NULL;
}

void disp()     //for displaying the various column with pairings
{
    int i,j=min;
    struct node* temp;
    temp=root;
    printf("\n\nColumn #%d\n\n\n",number);          //number tells us which column is being printed
    while(temp->right!=NULL)
    {
        printf("%d\t",temp->data[0]);
        for(i=var-1;i>=0;i--)
        {
            printf("%d",temp->bin[i]);
        }
        temp=temp->right;
        printf("\n");
    }
    temp->right=NULL;
    number++;
}

void end_loop(struct node* ptr)         //reducing the number of nodes in a list with one extra node
{
    struct node* temp;
    temp=ptr;
    while(temp->right->right!=NULL)
    {
        temp=temp->right;
    }
    temp->right=NULL;
}

void further_groupings()    //grouping based on difference in binary notation
{
    int i,count,k,j,x;
    struct node *temp,*next,*p,*imp;
    check=0;
    if(columns==2)      //for second column
    {
        imp=improot=(struct node*)malloc(sizeof(struct node));
        p=head;
    }
    else        //for other columns
    {
        imp=save;
        root=head;
        p=head=(struct node*)malloc(sizeof(struct node));
    }
    temp=root;
    implicants(root);
    printf("\n\nColumn #%d\n\n\n",number);
    while(temp!=NULL)
    {
        next=temp->right;
        while(next!=NULL)
        {
            count=0;
            if(next->noofones-temp->noofones==1)        //if two terms differ in their no. of ones by one
            {
                for(i=0;i<var;i++)
                {
                    if(temp->bin[i]!=next->bin[i])
                    {
                        k=i;            //the place in which they differ is noted
                        count++;
                    }
                }
            }
            if(count==1)        //checks if the two terms differ by one place in binary notation
            {
                temp->isimplicant=0;        //if they do then they are not a prime implicant
                next->isimplicant=0;
                check++;
                for(i=0;i<var;i++)
                {
                    p->bin[i]=temp->bin[i];         //binary notation is stored
                }
                p->bin[k]=-1;
                x=0;
                for(j=0;j<columns/2;j++)            //data from first term is stored
                {
                    p->data[x]=temp->data[j];
                    x++;
                }
                for(j=0;j<columns/2;j++)            //data from second term is stored
                {
                    p->data[x]=next->data[j];
                    x++;
                }
                p->noofones=temp->noofones;
                for(j=0;j<columns;j++)      //the pair formed is displayed
                {
                    printf("%d,",p->data[j]);
                }
                printf("\b ");
                printf("\t");
                for(i=var-1;i>=0;i--)
                {
                    if(p->bin[i]==-1)
                        printf("-");
                    else
                        printf("%d",p->bin[i]);
                }
                printf("\n");
                p=p->right=(struct node*)malloc(sizeof(struct node));           // one extra node that is to be deleted
            }
            next=next->right;
        }
        temp=temp->right;
    }
    p->right=NULL;
    if(check!=0)
    {
        end_loop(head);     //extra node is deleted
    }
    temp=root;
    while(temp!=NULL)           //for selecting the prime implicants
    {
        if(temp->isimplicant==1)        // if term is a prime implicant it is stored separately in list with head pointer improot
        {
            i=0;
            for(i=0;i<columns/2;i++)
            {
                imp->data[i]=temp->data[i];
            }
            imp->data[i]=-1;
            for(i=0;i<var;i++)
            {
                imp->bin[i]=temp->bin[i];
            }
            imp=imp->right=(struct node*)malloc(sizeof(struct node));
        }
        temp=temp->right;
    }
    save=imp;
    columns=columns*2;
    number++;
}

void display_implicants()       //displays the implicants
{
    int i=0;
    struct node* temp;
    temp=improot;
    printf("\n\nThe prime implicants are:- \n\n");
    while(temp!=NULL)
    {
        i=0;
        i=var-1;
        while(i>=0)     //displays the binary notation
        {
            if(temp->bin[i]==-1)
            {
                printf("-");
            }
            else
            {
                printf("%d",temp->bin[i]);
            }
            i--;
        }
        printf("\t\t");
        i=0;
        while(temp->data[i]!=-1)        //displays the minterm pairs
        {
            printf("%d,",temp->data[i]);
            i++;
        }
        printf("\b ");
        temp=temp->right;
        printf("\n\n");
        counter++;
    }
}

void implicants(struct node* ptr)       //initializing each term as a prime implicant
{
    struct node* temp;
    temp=ptr;
    while(temp!=NULL)
    {
        temp->isimplicant=1;
        temp=temp->right;
    }
}

void collect()          //reduces the terms that occur more than once to a single
{
    int common=0,i;
    struct node *temp1,*temp2,*temp3;
    temp1=temp2=improot;
    while(temp1!=NULL)
    {
        temp2=temp1->right;
        while(temp2!=NULL)
        {
            common=0;
            for(i=0;i<var;i++)          //if their binary notation is same one will be deleted
            {
                if(temp2->bin[i]==temp1->bin[i])
                {
                    common++;
                }
            }
            if(common==var)
            {
                temp3=improot;
                while(temp3->right!=temp2)      //the repeated term is deleted
                {
                    temp3=temp3->right;
                }
                temp3->right=temp2->right;
                temp2=temp3;
            }
            temp2=temp2->right;
        }
        temp1=temp1->right;
    }
}

void variables()            //stores variables(alphabets)
{
    int i;
    for(i=0;i<26;i++)
    {
        a[i]=65+i;      //variables
        b[i]=97+i;      //their compliments
    }
}

void convert()          //it converts the binary notation of each term to variables
{
    int i,j;
    struct node* temp;
    temp=fin;
    while(temp!=NULL)
    {
        j=0;
        for(i=0;i<var;i++)
        {
            if(temp->bin[i]==0)
            {
                temp->term[j]=b[i];
                j++;
            }
            if(temp->bin[i]==1)
            {
                temp->term[j]=a[i];
                j++;
            }
        }
        temp=temp->right;
    }
}

void func()         //displays the minimized function in SOP form
{
    struct node* temp;
    temp=fin;
    printf("\n\nThe minimized function is :- ");
    while(temp!=NULL)
    {
        printf("%s",temp->term);
        if(temp->right!=NULL)
        {
            printf(" + ");
        }
        temp=temp->right;
    }
    printf("\n\n");
}

void implicants_table()         //function for creating prime implicants table as well as selecting essential prime implicants
{
    struct node* temp;
    int i,j,k,m,n,x,y,count=0,count2=0,a=0;
    for(i=0;i<counter;i++)
    {
        for(j=0;j<=limit;j++)
        {
            imptable[i][j]=0;           //0 or - is placed in all places of a table
        }
    }
    i=0;
    j=0;
    k=0;
    temp=improot;
    while(temp!=NULL)
    {
        k=0;
        while(temp->data[k]!=-1)
        {
            imptable[i][temp->data[k]]=1;  // 1 or X is placed for the column with same index as that of the number in the pair
            k++;
        }
        i++;
        temp=temp->right;
    }
    printf("\n\n\t\t\tPrime Implicants Table\n\n\n");
    temp=improot;
    i=0;
    printf(" ");
    while(minterms[i]!=-1)
    {
        printf("%d\t",minterms[i]);         //the minterms are displayed in row
        i++;
    }
    printf("\n\n");
    for(i=0;i<counter;i++)          //X and - are placed for the terms with corresponding minterm values
    {
        printf(" ");
        a=0;
        for(j=0;j<=limit;j++)
        {
            if(j==minterms[a])
            {
                if(imptable[i][j]==0)
                {
                    printf("-");
                }
                if(imptable[i][j]==1)
                {
                    printf("X");
                }
                printf("\t");
                a++;
            }
        }
        y=0;
        while(temp->data[y]!=-1)        //prints the minterm pair
        {
            printf("%d,",temp->data[y]);
            y++;
        }
        printf("\b ");
        temp=temp->right;
        printf("\n\n");
    }
    printf("\n\n");
    for(i=0;i<counter;i++)      //for finding essential prime implicants
    {
        for(j=0;j<=limit;j++)
        {
            count=0;
            if(imptable[i][j]==1)
            {
                y=j;
                x=i;
                for(k=0;k<counter;k++)
                {
                    if(imptable[k][j]==1)       //checks if there is only one X in a column
                    {
                        count++;
                    }
                }
                if(count==1)  //places - in place of X in every column of the table whose one row contains only one X in a column
                {
                    essential[t]=x;
                    t++;
                    for(n=0;n<=limit;n++)
                    {
                        if(imptable[i][n]==1)
                        {
                            for(m=0;m<counter;m++)
                            {
                                imptable[m][n]=0;
                            }
                        }
                    }
                }
            }
        }
    }
    essential[t]=-1;
    i=0;
}

void other_implicants()     //after finding the essential prime implicants other terms necessary are marked
{
    no=0;           //to check if any term is found in each iteration
    int count1=0,count2=0;
    int i,j;
    for(i=0;i<counter;i++)
    {
        count1=0;
        for(j=0;j<=limit;j++)
        {
            if(imptable[i][j]==1)       //no. of X's or 1's are calculated
            {
                no++;
                count1++;
            }
        }
        if(count1>count2)       //to find the term with maximum X's in a row
        {
            essential[t]=i;
            count2=count1;
        }
    }
    for(j=0;j<=limit;j++)           //removing the X's in the row as well a those X's which are in same column
    {
        if(imptable[essential[t]][j]==1)
        {
            for(i=0;i<counter;i++)
            {
                imptable[i][j]=0;
            }
        }
    }
    t++;
    essential[t]=-1;
    if(no>0)            //if one or more terms is found the function is called again otherwise not
    {
        other_implicants();
    }
}

void final_terms()          //in this function all the terms in the minimized expression are stored in a linked list
{
    int i=0,j,c=0,x;
    struct node *temp,*ptr;
    fin=temp=(struct node*)malloc(sizeof(struct node));
    while(essential[i]!=-1)
    {
        ptr=improot;
        x=essential[i];
        for(j=0;j<x;j++)        //so that pointer points to the node whose index was stored in array named essential
        {
            ptr=ptr->right;
        }
        j=0;
        while(ptr->data[j]!=-1)         // the data of the node is stored
        {
            temp->data[j]=ptr->data[j];
            j++;
        }
        temp->data[j]=-1;
        for(j=0;j<var;j++)          //the binary code is stored
        {
            temp->bin[j]=ptr->bin[j];
        }
        temp=temp->right=(struct node*)malloc(sizeof(struct node));
        i++;
        c++;
    }
    temp->right=NULL;
}