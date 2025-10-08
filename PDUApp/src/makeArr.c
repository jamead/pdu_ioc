   #include <stdio.h>
   #include <stdlib.h>

   float* createArray(int size) {
     //  float* arr = (float*)malloc(size * sizeof(int));
       float arr[size];
       if (arr == NULL) {
           return NULL; // Memory allocation failed
       }
       for (int i = 0; i < size; i++) {
           arr[i] = i * 2;
       }
       return &arr[0];
   }

   int main() {
       int size = 5;
       float* myArray = createArray(size);
       if (myArray != NULL) {
           for (int i = 0; i < size; i++) {
               printf("%f ", myArray[i]);
           }
           printf("\n");
           free(myArray); // Free the allocated memory
       }
       return 0;
   }
