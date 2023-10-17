/*In the C programming language, create a Laptop structure to describe the specifications of a given
notebook computer. The structure should contain: (5 points)
•	Company that produces it (string of 100 characters)
•	Monitor size in inches (actual number)
•	Is it with touch or not (boolean variable)
•	Price (integer)
Create a structure ITStore , containing: (5 points)
•	Store name (string of 100 characters)
•	Location (string of 100 characters)
•	An array of available laptops (an array of a maximum of 100 elements of the Laptop structure)
•	Number of elements in the array (integer)
Create a print function to print the information about all laptops in one store in the format: (10 points)
[Store name] [Location]
[Brand1] [monitor_dim] [Price1]
[Brand2] [monitor_dim2] [Price2]
[Brand3] [monitor_dim3] [Price3]
…
Create a function cheapest_offer that receives an array of variables of type ITStore and prints
the name and location of the store that offers the cheapest laptop and its PRICE.
The cheapest laptop is the one that has the lowest PRICE plus a touch option. If there are more such stores,
the first one found is printed.* (15 points)*
Add them to the main function (10 points).
The number of stores is entered from the keyboard,
then for each store the name and location are entered, then the number of computers,
then for each of the computers the company that produces it, the size of the monitor,
whether it has a touch screen and the PRC. Then all entered stores and the cheapest offer are printed.
*/

#include <stdio.h>
//Laptop Struct
typedef struct Laptop{
    char brand[100];
    float monitor_dim;
    int has_touch;
    int price;
}laptop;
//Reading function for laptop
laptop readLaptop(){
    laptop l;
    scanf("%s %f %d %d",l.brand,&l.monitor_dim,&l.has_touch,&l.price);
    return l;
}
//Printing function for laptop
void printLaptop(laptop l){
    float dim=l.monitor_dim*10;
    if((int)dim%10==0){
        printf("%s %d %d\n",l.brand,(int)l.monitor_dim,l.price);
    } else{
        printf("%s %.1f %d\n",l.brand,l.monitor_dim,l.price);
    }
}
//ITStore struct
typedef struct ITStore{
    char name[100];
    char location[100];
    laptop laptops[100];
    int number_laptops;
}ITStore;
//Reading function for ITStore
ITStore readITStore(){
    ITStore ITS;
    scanf("%s %s %d", ITS.name, ITS.location, &ITS.number_laptops);
    for(int i=0 ; i < ITS.number_laptops ; i++){
        ITS.laptops[i]=readLaptop();
    }
    return ITS;
}
//Printing function for ITStore
void printITStore(ITStore ITS){
    printf("%s %s\n",ITS.name,ITS.location);
    for(int i=0 ; i < ITS.number_laptops ; i++){
        printLaptop(ITS.laptops[i]);
    }
}

//Finding the laptop with the lowest PRC that has a touch screen from one IT STORE
laptop lowestPriceHasTouch(ITStore its){
    int k=0;
    laptop hasTouch[100];
    for(int i=0 ; i<its.number_laptops ; i++){
        if(its.laptops[i].has_touch==1){//if laptop has touch
            hasTouch[k++]=its.laptops[i];//we store it to the hasTouch array
        }
    }
    laptop cheapestHasTouch=hasTouch[0];
    for(int i=1 ; i<k ; i++){
        if(hasTouch[i].price<cheapestHasTouch.price){
            cheapestHasTouch=hasTouch[i];
        }
    }
    return cheapestHasTouch;
}
//Comparing two IT Stores by the laptop that has the cheapest PRC and has touch
int cmpITS(ITStore its1, ITStore its2){
    laptop l1= lowestPriceHasTouch(its1);
    laptop l2= lowestPriceHasTouch(its2);
    return l1.price<l2.price;
}

void cheapest_offer(ITStore *ITS, int n){
    ITStore cheapest=ITS[0];
    for(int i=0 ; i<n ; i++){
        if(cmpITS(ITS[i],cheapest)==1){
            cheapest=ITS[i];
        }
    }
    laptop l= lowestPriceHasTouch(cheapest);
    printf("Najeftina ponuda ima prodavnicata:\n%s %s\n",cheapest.name,cheapest.location);
    printf("Najniskata cena iznesuva: %d",l.price);
}

int main(){
    int n;
    scanf("%d",&n);
    ITStore stores[100];
    for(int i=0 ; i<n ; i++){
        stores[i]=readITStore();
    }
    for(int i=0 ; i<n ; i++){
        printITStore(stores[i]);
    }
    cheapest_offer(stores,n);
    return 0;
}