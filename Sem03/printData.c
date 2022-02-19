#include <stdio.h>
int main(){

    char name[20];
    int age;
    printf("Enter a name: ");
    scanf("%s", name);
    printf("Enter a age: ");
    scanf("%d", &age);

    printf("Your data: \n");
    printf("Name: %s, Age: %d\n", name, age);
    return 0;
}
