#include <iostream>
#include <vector>
using namespace std;


class  Suffix {
public:
    int index;   // Starting index of the suffix in the original string
    int rank1;   // Primary rank based on current prefix length
    int rank2;   // Secondary rank used to break ties in rank1
    Suffix(int Index , int Rank1,int Rank2){
        index = Index;
        rank1 = Rank1;
        rank2 = Rank2;
    }
    Suffix(){}
};

bool compare(const Suffix& s1, const Suffix& s2) {
    if (s1.rank1 == s2.rank1) {
        return s1.rank2 < s2.rank2;
    }
    return s1.rank1 < s2.rank1;
}

// Merge function for merging two halves of the suffix array
void merge(vector<Suffix>& suffixArray, int left, int mid, int right) {
    int len1 = mid - left + 1;
    int len2 = right - mid;

    Suffix* leftPart = new Suffix[len1];
    Suffix* rightPart = new Suffix[len2];

    for (int i = 0; i < len1; i++) leftPart[i] = suffixArray[left + i];
    for (int i = 0; i < len2; i++) rightPart[i] = suffixArray[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < len1 && j < len2) {
        if (compare(leftPart[i], rightPart[j])) {
            suffixArray[k++] = leftPart[i++];
        } else {
            suffixArray[k++] = rightPart[j++];
        }
    }

    while (i < len1)
    {
        suffixArray[k++] = leftPart[i++];
    }
    while (j < len2)
    {
        suffixArray[k++] = rightPart[j++];
    }

    delete[] leftPart;
    delete[] rightPart;
}

void mergeSort(vector<Suffix>&suffixArray, int left, int right) {
    if (left >= right) return;
    int mid = (left +right) / 2;
    mergeSort(suffixArray, left, mid);
    mergeSort(suffixArray, mid + 1, right);
    merge(suffixArray, left, mid, right);
}

// Class representing the suffix array construction
class SuffixArray {
    string inputString;   // Input string
    int length;          // Length of the input string
    vector<int> suffixIndices;  // Array to store suffix indices

public:
    SuffixArray(string input) {
        inputString = input;
        length  = input.size();
        suffixIndices.resize(length);
    }

    // Constructs the suffix array using prefix-doubling method
    void constructSuffixArray() {
        // Initialize suffixes with their starting indices and ranks
        vector<Suffix> suffixes(length);
        for (int i = 0; i < length; i++) {
            suffixes[i].index = i;
            suffixes[i].rank1 = inputString[i] - 'a';
            suffixes[i].rank2 = (i + 1 < length) ? inputString[i + 1] - 'a' : -1;
        }

        // Sort suffixes based on initial ranks
        mergeSort(suffixes, 0, length - 1);

        vector<int> indexArray(length);  // Temporary array for updating ranks
        for (long long  k = 4; k < 2 * length; k <<= 1) {
            int rank = 0;
            int previousRank = suffixes[0].rank1;
            suffixes[0].rank1 = rank;
            indexArray[suffixes[0].index] = 0;

            // Assign new ranks based on previous sorted order
            for (int i = 1; i < length; i++) {
                if (suffixes[i].rank1 == previousRank && suffixes[i].rank2 == suffixes[i - 1].rank2) {
                    suffixes[i].rank1 = rank;
                } else {
                    previousRank = suffixes[i].rank1;
                    suffixes[i].rank1 = ++rank;
                }
                indexArray[suffixes[i].index] = i;
            }

            // Update rank2 values based on the next part of the suffix
            for (int i = 0; i < length; i++) {
                int nextIndex = suffixes[i].index + k / 2;
                suffixes[i].rank2 = (nextIndex < length) ? suffixes[indexArray[nextIndex]].rank1 : -1;
            }

            // Re-sort suffixes with updated ranks
            mergeSort(suffixes, 0, length - 1);
        }

        // Store the result in the suffixIndices array
        for (int i = 0; i < length; i++) {
            suffixIndices[i] = suffixes[i].index;
        }
    }

    void printSuffixArray() {
        for (int i = 0; i < length; i++) {
            cout << suffixIndices[i] << " ";
        }
        cout << "\n";
    }
};

int main() {
    SuffixArray suffixArray("ACGACTACGATAAC$");
    suffixArray.constructSuffixArray();
    suffixArray.printSuffixArray();
    return 0;
}
