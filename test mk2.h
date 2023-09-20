// test data and structure definitions

// allow portable types
#include <stdint.h>

// function to obtain data for input
void InputTest(void);

// format of input and filter data
extern int32_t* input_data;
extern uint32_t num_input_data;
extern int32_t* filter_data;
extern uint32_t num_filter_data;

// format required for test data
struct the_test_data {
  uint32_t num_input_data;
  int32_t* input_data;
  uint32_t num_filter_data;
  int32_t* filter_data;
};

