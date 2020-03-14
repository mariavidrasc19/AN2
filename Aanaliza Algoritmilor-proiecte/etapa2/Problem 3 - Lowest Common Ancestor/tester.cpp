#include <cstdio>
#include <errno.h>

#include "algo.h"

const int NUM_TESTS = 10;
const int MAX_TEST_NAME_SIZE = 32;

int parse_input(const char* input_file, std::vector<std::vector<int>>& input, std::vector< std::pair<int, int>>& interogari) {

	int N, rc, M;
	
	fprintf(stderr, "%s\n", input_file);
	FILE* fp = fopen(input_file, "r");
	if (fp == NULL) {
		fprintf(stderr, "Invalid input file(-1)\n");
		return -1;
	}

	rc = fscanf(fp, "%d", &N);
	if (rc != 1) {
		fclose(fp);
		fprintf(stderr, "Invalid input file(-2.1)\n");
		return -2;
	}
	rc = fscanf(fp, "%d", &M);
	if (rc != 1) {
		fclose(fp);
		fprintf(stderr, "Invalid input file(-2.2)\n");
		return -2;
	}

	input.resize(N - 1);

	for (int i = 0; i < N - 1; ++i) {
		input[i].resize(2);
		rc = fscanf(fp, "%d", &input[i][0]);
		if (rc != 1) {
			fclose(fp);
			fprintf(stderr, "Invalid input file(-3.1)\n");
			return -3;
		}
		rc = fscanf(fp, "%d", &input[i][1]);
		if (rc != 1) {
			fclose(fp);
			fprintf(stderr, "Invalid input file(-3.2)\n");
			return -3;
		}
	}

	interogari.resize(M);
	for (int i = 0; i < M; ++i) {
		int a, b;
		rc = fscanf(fp, "%d", &a);
		if (rc != 1) {
			fclose(fp);
			fprintf(stderr, "Invalid input file(-4.1)\n");
			return -4;
		}
		rc = fscanf(fp, "%d", &b);
		if (rc != 1) {
			fclose(fp);
			fprintf(stderr, "Invalid input file(-4.2)\n");
			return -4;
		}
		interogari[i] = std::pair<int, int> (a, b);
	}

	fclose(fp);
	return 0;
}

int parse_output(const char* reference_file, std::vector<int>& expected) {

	FILE* fp = fopen(reference_file, "r");
	if (fp == NULL) {
		goto bad_exit;
	}

	int rc;
	for (int i = 0, sz = expected.size(), elem; i < sz; ++i) {
		rc = fscanf(fp, "%d\n", &elem);
		if (rc != 1) {
			goto cleanup;
		}

		expected[i] = elem;
	}

	fclose(fp);
	return 0;

cleanup:
	fclose(fp);
bad_exit:
	fprintf(stderr, "Invalid reference file\n");
	return -1;
}

int run_test(const char* input_file, const char* reference_file) {

	int rc; /* return code */
	std::vector<int> expected;
	std::vector<std::vector<int>> input;
	std::vector< std::pair<int, int>> interogari;
	std::vector<int> myOutput;

	/* Parse test data */
	rc = parse_input(input_file, input, interogari);
	if (rc) {
		goto bad_exit;
	}

	/* Call algorithm */
	myOutput = lca(input, interogari);

	expected.resize(interogari.size());

	/* Parse reference data */
	rc = parse_output(reference_file, expected);
	if (rc) {
		goto bad_exit;
	}

	/* Check answer */
	if (myOutput == expected) {
		printf("Test PASSED!\n");
	} else {
		printf("Test FAILED!\n");
	}

	return 0;

bad_exit:
	return -1;
}


int main () {
	
	char input_test[MAX_TEST_NAME_SIZE], 
		 reference_file[MAX_TEST_NAME_SIZE];

	for (int i = 0; i < NUM_TESTS; ++i) {

		sprintf(input_test, "./in/test%d.in", i);
		sprintf(reference_file, "./out/test%d.out", i);

		printf("Running test %d\n", i);

		if (run_test(input_test, reference_file)) {
			fprintf(stderr, "Failed to run test %d\n", i);
			return -1;
		}
	}

	return 0;
}
