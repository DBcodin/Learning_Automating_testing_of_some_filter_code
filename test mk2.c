// Provide sets of test input data

// allow portable types
#include <stdint.h>

// access data for testing
#include "test.h"

// data to be passed on for testing 
	
// define some data example
int32_t input_data0[] = {2,3,4,5,4,3,2,7,8,9};
int32_t filter_data0[] = {-1,2,-1};
int32_t input_data1[] = {1, 2};
int32_t filter_data1[] = {1};
int32_t input_data2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int32_t filter_data2[] = {1,2};

// put data sets in structures
struct the_test_data test_data[] = {
	{
	sizeof(input_data1)/sizeof(int32_t),
	input_data0,
	sizeof(filter_data1)/sizeof(int32_t),
	filter_data0,
  },
	{
	sizeof(input_data1)/sizeof(int32_t),
	input_data1,
	sizeof(filter_data1)/sizeof(int32_t),
	filter_data1,
  },
	{
	sizeof(input_data2)/sizeof(int32_t),
	input_data2,
	sizeof(filter_data2)/sizeof(int32_t),
	filter_data2,
  }
};
  	 
void InputTest() {
  static uint32_t count_test_data = 0;
	num_input_data = test_data[count_test_data].num_input_data;
	input_data = test_data[count_test_data].input_data;
	num_filter_data = test_data[count_test_data].num_filter_data;
	filter_data = test_data[count_test_data].filter_data;
}
