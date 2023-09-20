// Purpose
// A program to demonstrate the application of a simple digital filter
// 
// Overview
// A sequence of data items and digital filter values need to be entered by the
// user. The application of the filter to the data involves a simple convolution 
// operation. The filtered data are stored separately. 
//
// Example
//  before filtering: 
//   data_in = [0 1 3 6 3 1 0]
//   filter = [-0.5 1 -0.5]
//  after filtering:
//   data_out = [-0.5 -0.5 3 -0.5 -0.5]
//  where
//   data_out[0]=data_in[0]*filter[0]+data_in[1]*filter[1]+data_in[2]*filter[2]
//   data_out[1]=data_in[1]*filter[0]+data_in[2]*filter[1]+data_in[3]*filter[2]
//   data_out[2]=data_in[2]*filter[0]+data_in[3]*filter[1]+data_in[4]*filter[2]
//   data_out[3]=data_in[3]*filter[0]+data_in[4]*filter[1]+data_in[5]*filter[2]
//   data_out[4]=data_in[4]*filter[0]+data_in[5]*filter[1]+data_in[6]*filter[2]
//
// The program checks the following
// 1. The data and filter values must have been entered before the filter is 
//    applied
// 2. The filter is not applied if the number of filter values is greater than
//    the number of input data values
// 3. The data and filter values must have been entered and the filter applied 
//    before the filtered data can be displayed
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// the data values and the filter
struct TheFilter {
  double* Values;   // the filter values
  uint64_t Length;  // number of filter values
  bool Valid;   // true if the filter values have been obtained
};

struct TheData {
  double* Values;  // holds the data to be filtered
  uint64_t Length;  // number of data values
  bool Valid;   // true if the data values have been obtained
};

// function return values
enum {OK,FILTER_TOO_LONG};

// function prototypes
void EnterData(struct TheData*);
void EnterFilter(struct TheFilter*);
uint8_t ApplyFilter(struct TheFilter, struct TheData, struct TheData*);
void DisplayData(struct TheFilter, struct TheData, struct TheData);
 
// Control the principal operations of the program
// Arguments: None
// Returns: 0 on completion
int main()
{
  // define the filter and its initial values
  struct TheFilter Filter = {0,0,false};

  // define the original data and its initial values
  struct TheData OriginalData = {0,0,false};

  // define the filtered data and its initial values
  struct TheData FilteredData = {0,0,false};

  char UserInput;

  // loop until the user wishes to exit
  while (1) {
    
    // show the menu of options
    printf("\n");
    printf("Filter Menu\n");
    printf("-----------\n");
    printf("\n");
    printf("1. Enter data for filtering\n");
    printf("2. Enter filter values\n");
    printf("3. Apply filter\n");
    printf("4. Display filtered data\n");
    printf("5. Exit from the programi\n\n");
    
    // get the user's choice
    printf("Enter your option: ");
    scanf(" %c", &UserInput);
    printf("\n");
    
    // act on the user's input
    switch(UserInput) {
      case '1':
        EnterData(&OriginalData);
        FilteredData.Valid = false;
        break;

      case '2':
        EnterFilter(&Filter);
        FilteredData.Valid = false;
        break;      
 
      case '3':
        if (Filter.Valid == true && OriginalData.Valid == true &&
            FilteredData.Valid == false) {
          if (ApplyFilter(Filter,OriginalData,&FilteredData) == FILTER_TOO_LONG) {
             printf("The filter must not be longer than the data\n");
          }
          else {
            FilteredData.Valid = true;
            printf("Filter applied\n");
          }
        }
        break;

      case '4':
        if (Filter.Valid == true && OriginalData.Valid == true &&
            FilteredData.Valid == true) {
          DisplayData(Filter,OriginalData,FilteredData);
        }
	   else {
	     printf("Data have not yet been filtered\n");
	   }
        break;

      case '5':
        free(Filter.Values);
        free(OriginalData.Values);
        free(FilteredData.Values);
        return 0;
        break;

      default:
        printf("Invalid entry\n\n");
        break;
    }
  }
}

// Allow the user to enter the data to be filtered
// Arguments:
//   (1) the structure containing the input data
// Returns: nothing
// 
void EnterData(struct TheData* GetData)
{  
  // initialize the data structure that holds the data to be filtered, including 
  // getting the number of data values from the user
  free(GetData->Values);
  printf("How many data values do you wish to enter: ");
  scanf("%llu",&GetData->Length);
  GetData->Valid = true;

  // allocate memory to the data
  GetData->Values = malloc(sizeof(double)*GetData->Length);
  if (GetData->Values == 0) {
    printf("Unable to allocate sufficient memory\n");
    exit(1);
  }

  // obtain all of the data values
  printf("\n");
  printf("Enter the data values\n");
  printf("---------------------\n");
  for (uint64_t CountData = 0; CountData < GetData->Length; CountData++) {
    printf("Enter value %llu : ", CountData+1);
    scanf("%lf", &GetData->Values[CountData]);
  }
}

// Allow the user to enter the filter values
// Arguments:
//   (1) the structure of the filter to be defined
// Returns: nothing
// 
void EnterFilter(struct TheFilter* GetFilter)
{  
  // initialize the data structure that holds the filter, including getting 
  // the number of filter values from the user
  free(GetFilter->Values);
  printf("How many filter values do you wish to enter: ");
  scanf("%llu",&GetFilter->Length);
  GetFilter->Valid = true;

  // allocate memory to the filter values
  GetFilter->Values = malloc(sizeof(double)*GetFilter->Length);
  if (GetFilter->Values == 0) {
    printf("Unable to allocate sufficient memory\n");
    exit(1);
  }

  // obtain all of the filter values
  printf("\n");
  printf("Enter the filter values\n");
  printf("-----------------------\n");
  for (uint64_t CountFilter = 0; CountFilter < GetFilter->Length; CountFilter++) {
    printf("Enter value %llu : ", CountFilter+1);
    scanf("%lf", &GetFilter->Values[CountFilter]);
  }
}

// Apply the filter to the input data and store in the filtered data structure
// Arguments:
//   (1) the structure of the filter to be applied
//   (2) the structure containing the data to be filtered
//   (3) the structure to hold the filtered data
// Returns: OK - if the filter is applied
//          FILTER_TOO_LONG - the filter is longer than the data 
//  
uint8_t ApplyFilter(struct TheFilter Filter, struct TheData DataIn, struct TheData* DataOut)
{  
  // return an error if the filter is longer than the data
  if (Filter.Length > DataIn.Length) return FILTER_TOO_LONG;

  // initialize the data structure that holds the filtered data
  free(DataOut->Values);
  DataOut->Length = DataIn.Length - Filter.Length + 1;

  // get memory for the filtered data
  DataOut->Values = malloc(sizeof(double)*DataOut->Length);
  if (DataOut->Values == 0) {
    printf("Unable to allocate sufficient memory");
    exit(1);
  }

  // apply the filter to the data
  for (uint64_t CountData = 0; CountData < DataOut->Length; CountData++) {
    DataOut->Values[CountData] = 0.0; 
    for (uint64_t CountFilter = 0; CountFilter<Filter.Length; CountFilter++) {
      DataOut->Values[CountData] += DataIn.Values[CountData+CountFilter] *
                                    Filter.Values[CountFilter]; 
    }
  }

  return OK;
}


// Display input data, filter values and output data
// Arguments:
//   (1) the structure of the filter to be applied
//   (2) the structure containing the data to be filtered
//   (3) the structure that holds the filtered data
// Returns: nothing
// 
void DisplayData(struct TheFilter Filter, struct TheData DataIn, struct TheData DataOut)
{  
  // display all of the input data values
  printf("\n");
  printf("The input data values\n");
  printf("---------------------\n");
  printf("[ ");
  for (uint64_t CountData = 0; CountData < DataIn.Length; CountData++) {
    printf("%lf ", DataIn.Values[CountData]);
  }
  printf("]");
    
  // display all of the filter values
  printf("\n");
  printf("The filter data values\n");
  printf("----------------------\n");
  printf("[ ");
  for (uint64_t CountData = 0; CountData < Filter.Length; CountData++) {
    printf("%lf ", Filter.Values[CountData]);
  }
  printf("]");
    
  // display all of the data output values
  printf("\n");
  printf("The data output values\n");
  printf("----------------------\n");
  printf("[ ");
  for (uint64_t CountData = 0; CountData < DataOut.Length; CountData++) {
    printf("%lf ", DataOut.Values[CountData]);
  }
  printf("]");
}