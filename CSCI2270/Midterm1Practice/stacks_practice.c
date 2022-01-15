int ShiftArray(Product arr[], int size, int target){
    for (int i=0; i < size; i++){
        if (arr[i].price == target){
            for (int j=i; j < (size-1); j++){
                arr[j] = arr[j+1];
            }
            i--;
            size--;
        }
    }
    return size;
}


string commonRepeatingElement(Product arr[],int length){
    int count;
    int max=0;
    string max_pname = "";
    for(int i=0;i<length;i++){
        count = 0;
        for(int j=0;j<length;j++){
            if(arr[i].pname == arr[j].pname){
                count = count + 1;
                if(count > max){
                    max=count;
                    max_pname = arr[i].pname;
                }
            }
        }
    }
    return max_pname;
}

int *CopyArray(int array[], int length, int value)
{
    int *b = new int[length];
    int index = 0;
    
    for(int i=0;i<length;i++)
    {
        if(array[i] != value)
        {
            b[index] = array[i];
            index++;
        }
    }
    return b;
}

//Question 4

int secondLargest(int arr[],int size)
{
    int temp =0;
    for(int i=0;i<size;i++)
    {
        for(int j=0;j <size-1;j++)
        {
            if(arr[j] > arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    return arr[size-2];
}

int * makeNewArray(int inputArray[], int arraySize, int compareNum){
    int * newArray = new int[arraySize];
    int index = 0
    for (int i = 0; i < arraySize; i++){
        if (inputArray[i] > compareNum){
            newArray[index] = inputArray[i];
            index++;
        }
    }
    return newArray;
}

