#include <stdio.h>

int main() {
    int calories;
    printf("Enter the number of calories consumed today: ");
    scanf("%d", &calories);
    
    if (calories < 2000) {
        printf("You have consumed less than the recommended daily intake of 2000 calories.\n");
    } else if (calories == 2000) {
        printf("You have met the recommended daily intake of 2000 calories.\n");
    } else {
        printf("You have exceeded the recommended daily intake of 2000 calories.\n");
    }
    
    return 0;
}