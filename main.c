#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NAME_LENGTH 20
#define PRICE_LENGTH 20
#define LIST_LENGTH 1000

struct laptop {
    char brand[NAME_LENGTH];
    float price;
};

void filterFunction(int argCount, char* inputFileName, int productNum);
int validateFile(FILE* file_ptr);
void sortLaptopByPrice(FILE* inputFile_ptr, int productNum);
int readFileAndCreateLaptopList(FILE* inputFile_ptr, struct laptop* laptopList);
void printByProductNum(struct laptop* laptopList, int laptopCount, int productNum);
void quickSortByAscendingOrder(struct laptop* laptopList, int L, int R);
void swap(struct laptop* laptopList, int left, int right);

int main(int argc, char* argv[]) {
    int argCount = argc;
    char* inputFileName = argv[1];
    int productNum = atoi(argv[2]);
    filterFunction(argCount, inputFileName, productNum);
    return 0;
}

void filterFunction(int argCount, char* inputFileName, int productNum) {
    if (argCount == 3) {
        FILE* inputFile_ptr = fopen(inputFileName, "r");
        if (!validateFile(inputFile_ptr)) {
            printf("Could not open files!\n");
        } else {
            sortLaptopByPrice(inputFile_ptr, productNum);
        }
        fclose(inputFile_ptr);
    } else {
        printf("Invalid CommandLine Input!\n");
    }
}

int validateFile(FILE* file_ptr) {
    if (file_ptr == NULL) {
        return 0;
    } else {
        return 1;
    }
}

void sortLaptopByPrice(FILE* inputFile_ptr, int productNum) {
    struct laptop* laptopList = (struct laptop*) malloc(sizeof(*laptopList) * LIST_LENGTH);
    if (laptopList == NULL) {
        printf("No memory is allocated!\n");
        exit(0);
    }
    int laptopCount = readFileAndCreateLaptopList(inputFile_ptr, laptopList);
    printByProductNum(laptopList, laptopCount, productNum);
}

int readFileAndCreateLaptopList(FILE* inputFile_ptr, struct laptop* laptopList) {
    char brand[NAME_LENGTH];
    char price[PRICE_LENGTH];
    int count = 0;
    while (!feof(inputFile_ptr)) {
        fscanf(inputFile_ptr, "%s %s", brand, price);
        strcpy(laptopList[count].brand, brand);
        laptopList[count].price = atof(price);
        count++;
    }
    return count;
}

void printByProductNum(struct laptop* laptopList, int laptopCount, int productNum) {
    quickSortByAscendingOrder(laptopList, 0, laptopCount - 1);
    laptopList = realloc(laptopList, sizeof(struct laptop) * productNum);
    int count;
    if (laptopCount > productNum) {
        count = productNum;
    } else {
        count = laptopCount;
    }
    for (int index = 0; index < count; index++) {
        printf("%-20s %.0f\n", laptopList[index].brand, laptopList[index].price);
    }
    free(laptopList);
}

void quickSortByAscendingOrder(struct laptop* laptopList, int L, int R) {
    int left = L;
    int right = R;
    float pivot = laptopList[(L + R) / 2].price;
    do {
        while (laptopList[left].price < pivot)
            left++;
        while (laptopList[right].price > pivot)
            right--;
        if (left <= right) {
            swap(laptopList, left, right);
            left++;
            right--;
        }
    } while (left <= right);
    if (L < right)
        quickSortByAscendingOrder(laptopList, L, right);
    if (left < R)
        quickSortByAscendingOrder(laptopList, left, R);
}

void swap(struct laptop* laptopList, int left, int right) {
    struct laptop temp;
    temp = laptopList[left];
    laptopList[left] = laptopList[right];
    laptopList[right] = temp;
}