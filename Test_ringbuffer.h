
//
// Created by User on 05.04.2023.
//

#ifndef WORK_ON_LESSON_TEST_RINGBUFFER_H
#define WORK_ON_LESSON_TEST_RINGBUFFER_H
#include <iostream>
template<typename T>
void assert_filo(T expr, T expr_true,const std::string exprString,
                                const std::string exprTrueStr, int numTest){

}
#define ASSERT_EQUAL(expr,expr_true) assert_equal(expr,expr_true,#expr,#expr_true,0)
#define ASSERT_EQUAL_numTest(expr,expr_true,numTest) assert_equal(expr,expr_true,#expr,#expr_true,numTest)
#define RESET_NUMTEST assert_equal(0,0,"","",-1)


#endif //WORK_ON_LESSON_TEST_RINGBUFFER_H
