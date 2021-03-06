#include "frequency.h"

const double ENGLISH_FREQ[] = {
		0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,  // A-G
		0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,  // H-N
		0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,  // O-U
		0.00978, 0.02360, 0.00150, 0.01974, 0.00074                     // V-Z
};


double chi2(char* data, int data_len) {
	int ignored_chars = 0;
	int letter_counts[26] = { 0 };

	for (int i = 0; i < data_len; i++) {
		char c = data[i];
		if (c >= 65 && c <= 90) letter_counts[c - 65]++;
		else if (c >= 97 && c <= 122) letter_counts[c - 97]++;
		else if (c >= 32 && c <= 126) ignored_chars++;
		else if (c == 9 || c == 10 || c == 13) ignored_chars++;
		else return 100000;
		//else ignored_chars++;
	}

	double chi2 = 0;
	int len = data_len - ignored_chars;
	if (len < 1)
		return 100000;
	for (int i = 0; i < 26; i++) {
		double observed = letter_counts[i];
		double expected = len * ENGLISH_FREQ[i];
		double diff = observed - expected;
		chi2 += (diff * diff) / expected;
	}

	return chi2;
}