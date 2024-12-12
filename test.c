// #include <CUnit/CUnit.h>
// #include <CUnit/Basic.h>

// void test() {
//     CU_ASSERT(1 == 1);
//     CU_ASSERT(2 == 2);
//     CU_ASSERT(3 == 3);
// }

// int main() {
//     // Initialize the CUnit test registry
//     if (CUE_SUCCESS != CU_initialize_registry())
//         return CU_get_error();

//     // Add a suite to the registry
//     CU_pSuite suite = CU_add_suite("test", NULL, NULL);
//     if (NULL == suite) {
//         CU_cleanup_registry();
//         return CU_get_error();
//     }

//     // Add the test to the suite
//     if (NULL == CU_add_test(suite, "test", test)) {
//         CU_cleanup_registry();
//         return CU_get_error();
//     }

//     // Run all tests using the basic interface
//     CU_basic_set_mode(CU_BRM_VERBOSE);
//     CU_basic_run_tests();
//     CU_cleanup_registry();
//     return CU_get_error();
// }

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "customer_UI_funcs.c"
#include "delivery.h"
// #include "customer_order.c"
// Declare the sign_up function
int sign_up(const char* filename);

int username_pass(char* pre_msg, char* filename);

int add_money(char* filename, char*current_cust1, char*username, char*password, char*name, char*address, char*phone, double money_in_acc);


// typedef struct current_customer1{
// 	char nm[21]; char ph[11]; char ad[201];
// 	char us[11]; char ps[11];
// 	double mny; // money
// } cc_new;


//float main_order(cc_new cust,char* restfilename, char* cust_order_file, char* num_of_delivs_file);

// Path to the temporary file used for testing
const char* temp_cust_det = "temp_cust_det.txt";

void test_successful_registration(void) {
    // Prepare the input for the sign_up function
    const char* input_data = "TestName\nTestAddress\n1234567890\nTestUser\nTestPass\n";
    FILE* input_file = fopen("test_input.txt", "w");
    fputs(input_data, input_file);
    fclose(input_file);

    // Redirect stdin to read from the input file
    freopen("test_input.txt", "r", stdin);

    // Ensure the temporary cust_det file is empty
    FILE* temp_file = fopen(temp_cust_det, "w");
    fclose(temp_file);

    // Call the sign_up function with the temporary file
    int result = sign_up(temp_cust_det);

    // Reset stdin
    freopen("/dev/tty", "r", stdin);

    // Check that sign_up returned success
    CU_ASSERT_EQUAL(result, 1);

    // Verify that the user data was added to temp_cust_det
    temp_file = fopen(temp_cust_det, "r");
    CU_ASSERT_PTR_NOT_NULL_FATAL(temp_file);

    char line[512];
    int found = 0;
    while (fgets(line, sizeof(line), temp_file)) {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';

        // Expected format: username password name address phone money_in_wallet
        const char* expected_line = "TestUser TestPass TestName TestAddress 1234567890 0.0 ";
        if(strcmp(line, expected_line) == 0){
            found = 1;
            break;
        }
    }
    fclose(temp_file);

    // Cleanup
    remove("test_input.txt");
    remove(temp_cust_det);

    // Assert that the expected line was found
    CU_ASSERT_EQUAL(found, 1);
}

void test_username_pass(void) {
    const char* temp_cust_det = "temp_cust_det.txt";
    const char* login_input_success = "TestUser\nTestPass\n";
    const char* login_input_fail = "TestUser\nWrongPass\n";

    // Prepare the customer data file with known credentials
    FILE* cust_file = fopen(temp_cust_det, "w");
    if (cust_file == NULL) {
        CU_FAIL("Failed to create temporary customer data file");
        return;
    }
    const char* user_data = "TestUser TestPass TestName TestAddress 1234567890 0.0\n";
    fputs(user_data, cust_file);
    fclose(cust_file);

    // **Test Successful Login**

    // Write the successful login input to a file
    FILE* input_file = fopen("login_input.txt", "w");
    if (input_file == NULL) {
        CU_FAIL("Failed to create login input file");
        remove(temp_cust_det);
        return;
    }
    fputs(login_input_success, input_file);
    fclose(input_file);

    // Redirect stdin to read from the input file
    FILE* original_stdin = stdin;
    stdin = fopen("login_input.txt", "r");
    if (stdin == NULL) {
        CU_FAIL("Failed to redirect stdin");
        remove(temp_cust_det);
        remove("login_input.txt");
        return;
    }

    // Call the function (assuming it returns an int indicating success or failure)
    int result = username_pass("Test Pre-message", temp_cust_det);

    // Close the redirected stdin and restore original stdin
    fclose(stdin);
    stdin = original_stdin;

    // Check if login was successful
    printf("Result ubhndfgrs: %d\n", result);
    CU_ASSERT_EQUAL(result, 0);

    // **Test Failed Login**

    // Write the failed login input to a file
    input_file = fopen("login_input.txt", "w");
    if (input_file == NULL) {
        CU_FAIL("Failed to create login input file");
        remove(temp_cust_det);
        return;
    }
    fputs(login_input_fail, input_file);
    fclose(input_file);

    // Redirect stdin to read from the input file again
    stdin = fopen("login_input.txt", "r");
    if (stdin == NULL) {
        CU_FAIL("Failed to redirect stdin");
        remove(temp_cust_det);
        remove("login_input.txt");
        return;
    }

    // Call the function again
    result = username_pass("Test Pre-message", temp_cust_det);

    // Close the redirected stdin and restore original stdin
    fclose(stdin);
    stdin = original_stdin;

    // Check if login failed as expected
    printf("Result htbginruya: %d\n", result);
    CU_ASSERT_EQUAL(result, 1);

    // Cleanup
    remove(temp_cust_det);
    remove("login_input.txt");
}

void test_add_money(void) {
    // Prepare the input for the add_money function
    const char* input_data = "100\n";
    FILE* input_file = fopen("test_input.txt", "w");
    fputs(input_data, input_file);
    fclose(input_file);

    // Redirect stdin to read from the input file
    freopen("test_input.txt", "r", stdin);

    // Ensure the temporary cust_det file is empty
    FILE* temp_file = fopen(temp_cust_det, "w");
    fclose(temp_file);

    
    //Prepare the customer data file with known credentials
    FILE* cust_file = fopen(temp_cust_det, "w");
    if (cust_file == NULL) {
        CU_FAIL("Failed to create temporary customer data file");
        return;
    }
    // malloc the user_data by allocating memory of 261 bytes
    const char* user_data = (char*)malloc(261);
    strcpy(user_data, "TestUser TestPass TestName TestAddress 1234567890 0.0\n");
    fputs(user_data, cust_file);
    fclose(cust_file);

    // Call the add_money function with the temporary file
    int result = add_money(temp_cust_det, user_data, "TestUser", "TestPass", "TestName", "TestAddress", "1234567890", 0.0);

    // Reset stdin
    freopen("/dev/tty", "r", stdin);

    // Check that add_money returned success
    CU_ASSERT_EQUAL(result, 1);

    // Verify that the user data was updated in temp_cust_det
    temp_file = fopen(temp_cust_det, "r");
    CU_ASSERT_PTR_NOT_NULL_FATAL(temp_file);

    char line[512];
    int found = 0;
    while (fgets(line, sizeof(line), temp_file)) {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';

        // Expected format: username password name address phone money_in_wallet
        const char* expected_line = "TestUser TestPass TestName TestAddress 1234567890 100.00 ";
        if(strcmp(line, expected_line) == 0){
            found = 1;
            break;
        }
    }
    fclose(temp_file);

    // Cleanup
    remove("test_input.txt");
    remove(temp_cust_det);

    // Assert that the expected line was found
    CU_ASSERT_EQUAL(found, 1);
}

void test_main_order(void){
    // Prepare the input for the main_order function
    printf("Testinggggggggg\n");
    const char* temp_cust_det = "temp_cust_det.txt";
    const char* input_data = "1\n4\n7\n1\n1\n8\n6\n1\n0";
    FILE* input_file = fopen("test_input.txt", "w");
    fputs(input_data, input_file);
    fclose(input_file);

    // Redirect stdin to read from the input file
    freopen("test_input.txt", "r", stdin);


    // Ensure the temporary num_of_delivs file is empty
    FILE* temp_file1 = fopen("test_num_of_delivs.txt", "w");
    fclose(temp_file1);

    // Prepare the num_of_delivs file with known data
    FILE* num_of_delivs_file = fopen("test_num_of_delivs.txt", "w");
    if (num_of_delivs_file == NULL) {
        CU_FAIL("Failed to create temporary test_num_of_delivs file");
        return;
    }
    fputs("0", num_of_delivs_file);
    fclose(num_of_delivs_file);

    //Prepare the customer data file with known credentials
    FILE* cust_file = fopen(temp_cust_det, "w");
    if (cust_file == NULL) {
        CU_FAIL("Failed to create temporary customer data file");
        return;
    }
    // malloc the user_data by allocating memory of 261 bytes
    const char* user_data = (char*)malloc(261);
    strcpy(user_data, "TestUser TestPass TestName TestAddress 1234567890 0.0\n");
    fputs(user_data, cust_file);
    fclose(cust_file);

    // Prepare a restaurant data file with known data
    FILE* rest_file = fopen("temp_rest.txt", "w");
    if (rest_file == NULL) {
        CU_FAIL("Failed to create temporary restaurant data file");
        return;
    }

    const char* rest_data = "TestRestaurant\nTestAddress\n1.0\n1234567890\n2\nDish1 Veg Category1 100\nDish2 Non-Veg Category2 200\n";
    fputs(rest_data, rest_file);
    fclose(rest_file);


    // Ensure the temporary cust_order file is empty
    FILE* temp_file2 = fopen("test_cust_order.txt", "w");
    fclose(temp_file2);

    // Prepare the cust_order file with known data
    FILE* cust_order_file = fopen("test_cust_order.txt", "w");
    if (cust_order_file == NULL) {
        CU_FAIL("Failed to create temporary test_cust_order file");
        return;
    }

    // create a struct of type cc_new
    cc_new cust;
    strcpy(cust.nm, "TestName");
    strcpy(cust.ad, "TestAddress");
    strcpy(cust.ph, "1234567890");
    strcpy(cust.us, "TestUser");
    strcpy(cust.ps, "TestPass");
    cust.mny = 10000000.0;

    // Call the main_order function
    float result = main_order(cust, "temp_rest.txt", "test_cust_order.txt", "test_num_of_delivs.txt");

    // Reset stdin
    freopen("/dev/tty", "r", stdin);

    // Check that main_order returned success
    CU_ASSERT_EQUAL(result, 154.0);

    // Verify that the cust_order file was updated
    cust_order_file = fopen("test_cust_order.txt", "r");
    CU_ASSERT_PTR_NOT_NULL_FATAL(cust_order_file);

    char line[512];
    int found = 0;
    while (fgets(line, sizeof(line), cust_order_file)) {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';
        // Expected format: status name phone address deliv_id price deliv_cost
        const char* expected_line = "not_assigned TestName 1234567890 TestAddress TestAddress 0 0001 100.00 54.00";
        if(strcmp(line, expected_line) == 0){
            found = 1;
            break;
        }
    }
    fclose(cust_order_file);

    // Cleanup
    remove("test_input.txt");
    remove("test_num_of_delivs.txt");
    remove("test_cust_order.txt");
    remove("temp_rest.txt");
    remove(temp_cust_det);

    // Assert that the expected line was found
    CU_ASSERT_EQUAL(found, 1);


}

void test_cust_workflow(void){
    // Prepare the input for the main_order function
    // printf("Testinggggggggg\n");
    const char* temp_cust_det = "temp_cust_det.txt";
    const char* input_data = "1\n4\n7\n1\n1\n8\n6\n1\n0\nYes\n1\nYes\n1111\nexit\n";
    FILE* input_file = fopen("test_input.txt", "w");
    fputs(input_data, input_file);
    fclose(input_file);

    // Redirect stdin to read from the input file
    freopen("test_input.txt", "r", stdin);


    // Ensure the temporary num_of_delivs file is empty
    FILE* temp_file1 = fopen("test_num_of_delivs.txt", "w");
    fclose(temp_file1);

    // Prepare the num_of_delivs file with known data
    FILE* num_of_delivs_file = fopen("test_num_of_delivs.txt", "w");
    if (num_of_delivs_file == NULL) {
        CU_FAIL("Failed to create temporary test_num_of_delivs file");
        return;
    }
    fputs("0", num_of_delivs_file);
    fclose(num_of_delivs_file);

    //Prepare the customer data file with known credentials
    FILE* cust_file = fopen(temp_cust_det, "w");
    if (cust_file == NULL) {
        CU_FAIL("Failed to create temporary customer data file");
        return;
    }
    // malloc the user_data by allocating memory of 261 bytes
    const char* user_data = (char*)malloc(261);
    strcpy(user_data, "TestUser TestPass TestName TestAddress 1234567890 0.0\n");
    fputs(user_data, cust_file);
    fclose(cust_file);

    // Prepare a restaurant data file with known data
    FILE* rest_file = fopen("temp_rest.txt", "w");
    if (rest_file == NULL) {
        CU_FAIL("Failed to create temporary restaurant data file");
        return;
    }

    const char* rest_data = "TestRestaurant\nTestAddress\n1.0\n1234567890\n2\nDish1 Veg Category1 100\nDish2 Non-Veg Category2 200\n";
    fputs(rest_data, rest_file);
    fclose(rest_file);


    // Ensure the temporary cust_order file is empty
    FILE* temp_file2 = fopen("test_cust_order.txt", "w");
    fclose(temp_file2);

    // Prepare the cust_order file with known data
    FILE* cust_order_file = fopen("test_cust_order.txt", "w");
    if (cust_order_file == NULL) {
        CU_FAIL("Failed to create temporary test_cust_order file");
        return;
    }

    // create a struct of type cc_new
    cc_new cust;
    strcpy(cust.nm, "TestName");
    strcpy(cust.ad, "TestAddress");
    strcpy(cust.ph, "1234567890");
    strcpy(cust.us, "TestUser");
    strcpy(cust.ps, "TestPass");
    cust.mny = 10000000.0;

    // Call the main_order function
    float result = main_order(cust, "temp_rest.txt", "test_cust_order.txt", "test_num_of_delivs.txt");

    

    // Check that main_order returned success
    CU_ASSERT_EQUAL(result, 154.0);

    // Verify that the cust_order file was updated
    cust_order_file = fopen("test_cust_order.txt", "r");
    CU_ASSERT_PTR_NOT_NULL_FATAL(cust_order_file);

    char line[512];
    int found = 0;
    while (fgets(line, sizeof(line), cust_order_file)) {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';
        // Expected format: status name phone address deliv_id price deliv_cost
        const char* expected_line = "not_assigned TestName 1234567890 TestAddress TestAddress 0 0001 100.00 54.00";
        if(strcmp(line, expected_line) == 0){
            found = 1;
            break;
        }
    }
    fclose(cust_order_file);

    // Cleanup
    // remove("test_input.txt");
    // remove("test_num_of_delivs.txt");
    // remove("test_cust_order.txt");
    // remove("temp_rest.txt");
    // remove(temp_cust_det);

    // Assert that the expected line was found
    CU_ASSERT_EQUAL(found, 1);

    // Create a dummy user for delivery guy
    FILE* del_file = fopen("temp_deliv.txt", "w");
    if (del_file == NULL) {
        CU_FAIL("Failed to create temporary delivery data file");
        return;
    }

    const char* del_data = "TestDeliv\n1234567890\npass\n32777";
    fputs(del_data, del_file);
    fclose(del_file);

    // printf("\nwe started way below now we here\n\n");
    // Prepare the accepted_file with known data and delivered file with known data
    char* accepted_file = "test_accepted.txt";
    char* delivereded_file = "test_delivered.txt";
    char* cust_order1 = "test_cust_order.txt";

    // printf("\nwe started way below now we here2\n\n");
    FILE* temp1 = fopen(accepted_file, "w");
    FILE* temp2 = fopen(delivereded_file, "w");
    // printf("\nwe started way below now we here3\n\n");
    fclose(temp1);
    // printf("\nwe started way below now we here4\n\n");
    fclose(temp2);

    // printf("\nwe started way below now we here1\n\n");
    delivery_main("TestDeliv",cust_order1,accepted_file,delivereded_file,1);

    // Reset stdin
    freopen("/dev/tty", "r", stdin);

    // found=0;
    // delivereded_file = fopen("test_delivered.txt", "r");

    // strcpy(line,"");

    // // while (fgets(line, sizeof(line), delivereded_file)) {
    // //     // Remove newline character
    // //     line[strcspn(line, "\n")] = '\0';
    // //     // Expected format: status name phone address deliv_id price deliv_cost
    // //     const char* expected_line = "TestName 1234567890 TestAddress TestAddress 0 0001 100.00 54.00";
    // //     if(strcmp(line, expected_line) == 0){
    // //         found = 1;
    // //         break;
    // //     }
    // // }

    // fclose(delivereded_file);

    // TestDeliv TestName 1234567890 TestAddress TestAddress 1111 0001 100.00 54.00

    int found1 = 0;
    FILE* delivereded1_file = fopen("test_delivered.txt", "r");
    char line1[512];

    while (fgets(line1, sizeof(line1), delivereded1_file)) {
        // Remove newline character
        line1[strcspn(line1, "\n")] = '\0';
        // Expected format: status name phone address deliv_id price deliv_cost
        const char* expected_line = "TestDeliv TestName 1234567890 TestAddress TestAddress 1111 0001 100.00 54.00";
        if(strcmp(line1, expected_line) == 0){
            found1 = 1;
            break;
        }
    }

    fclose(delivereded1_file);

    // Assert that the expected line was found
    CU_ASSERT_EQUAL(found1, 1);


    // Cleanup

    remove("test_input.txt");
    remove("test_num_of_delivs.txt");
    remove("test_cust_order.txt");
    remove("temp_rest.txt");
    remove(temp_cust_det);
    remove("temp_deliv.txt");
    remove("test_accepted.txt");
    remove("test_delivered.txt");

}

int main() {
    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Add a suite to the registry
    CU_pSuite suite = CU_add_suite("RegistrationTestSuite", NULL, NULL);
    if (NULL == suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the test to the suite
    if (NULL == CU_add_test(suite, "test_successful_registration", test_successful_registration)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_username_pass", test_username_pass)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_add_money", test_add_money)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_main_order", test_main_order)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(suite, "test_cust_workflow", test_cust_workflow)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}