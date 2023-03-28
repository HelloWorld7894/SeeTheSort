#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <tuple>

using namespace std;
using namespace std::chrono;

int GetMaxElement(vector<int> input_vector)
{
    int current_max = 0;
    for (int i = 0; i < input_vector.size(); i++)
    {
        if (input_vector[i] > current_max)
        {
            current_max = input_vector[i];
        }
    }

    return current_max;
}

void PrintSortProcess(vector<int> input_vector, int iter)
{
    cout << "Phase " + to_string(iter) << endl;
    cout << " " << endl;

    int max_element = GetMaxElement(input_vector);
    string space[max_element][input_vector.size()];

    // input into space array
    for (int i = 0; i < input_vector.size(); i++)
    {
        int value = input_vector[i];
        int yi = 0;
        while (yi <= value)
        {
            space[yi][i] = "::";
            yi += 1;
        }
    }

    // cout whole space array
    for (int yi = 0; yi < max_element; yi++) //iter on y
    {
        string out_x;
        for (int xi = 0; xi < input_vector.size(); xi++) //iter on x
        {
            out_x.append(space[yi][xi]);
            out_x.append("   "); //just adding some space between hist values
        }
        cout << out_x << endl;
    }
}


//
// SORTS
//

class InsertionSort {
    public:
        vector<int> insertion_main(vector<int> input_vector)
        {

            //we are going to sort in ascending order
            for (int i = 0; i < input_vector.size(); i++)
            {
                //PrintSortProcess(input_vector, i); //TODO: dodělat někdy!

                if (i != input_vector.size() - 1){
                    int elem1 = input_vector[i];
                    int elem2 = input_vector[i + 1];

                    if (elem1 > elem2 )
                    {
                        input_vector[i] = elem2;
                        input_vector[i + 1] = elem1;
                    }
                }

                if (i >= 1)
                {
                    int i_backwards = 0;
                    while (input_vector[i - i_backwards] < input_vector[i - i_backwards - 1])
                    {
                        int elem1 = input_vector[i - i_backwards];
                        int elem2 = input_vector[i - i_backwards - 1];

                        input_vector[i - i_backwards] = elem2;
                        input_vector[i - i_backwards - 1] = elem1;
                        i_backwards += 1;
                    }
                }

            }
            return input_vector;
        }
};

class BogoSort {
    public:
        bool isSorted(vector<int> input_vector)
        {
            bool sorted = true;
            for (int i = 0; i < input_vector.size(); i++)
            {
                if (i != input_vector.size() - 1 && input_vector[i] > input_vector[i + 1])
                {
                    sorted = false;
                    break;
                }
            }
            return sorted;
        }

        vector<int> Shuffle(vector<int> input_vector)
        {
            random_device rd;
            auto rng = default_random_engine { rd() };
            shuffle(begin(input_vector), end(input_vector), rng);

            return input_vector;
        }

        vector<int> bogo_main(vector<int> input_vector)
        {
            vector<int> vector_shuffle = input_vector;
            // check if sorted
            while (!BogoSort::isSorted(vector_shuffle))
            {
                vector_shuffle = Shuffle(input_vector);
            }
            return vector_shuffle;
        }
};

class SelectionSort
{
    public:
        auto scan_array(vector<int> input_vector)
        {
            struct result 
            {
                int min_value;
                int min_val_index;
            };
            result res;
            
            res.min_value = input_vector[0];
            res.min_val_index = 0;
            for(int i = 1; i < input_vector.size(); i++)
            {
                if (input_vector[i] < res.min_value)
                {
                    res.min_value = input_vector[i];
                    res.min_val_index = i;
                }
            }
    
            return res;
        }

        vector<int> selection_main(vector<int> input_vector)
        {

            for (int i = 0; i < input_vector.size(); i++)
            {  
                int current_elem = input_vector[i];
                auto result = scan_array(input_vector);
                if (result.min_value < input_vector[i])
                {
                    //change indexes
                    input_vector[result.min_val_index] = current_elem;
                    current_elem = result.min_value;
                }
            }
            

            return input_vector;
        }
};

class MergeSort
{
    public:
        // Merge two subarrays L and M into arr
        vector<int> merge(vector<int> input_vector, int p, int q, int r) {
        
            // Create L ← A[p..q] and M ← A[q+1..r]
            int n1 = q - p + 1;
            int n2 = r - q;

            int L[n1], M[n2];

            for (int i = 0; i < n1; i++)
                L[i] = input_vector[p + i];
            for (int j = 0; j < n2; j++)
                M[j] = input_vector[q + 1 + j];

            // Maintain current index of sub-arrays and main array
            int i, j, k;
            i = 0;
            j = 0;
            k = p;

            // Until we reach either end of either L or M, pick larger among
            // elements L and M and place them in the correct position at A[p..r]
            while (i < n1 && j < n2) {
                if (L[i] <= M[j]) {
                input_vector[k] = L[i];
                i++;
                } else {
                input_vector[k] = M[j];
                j++;
                }
                k++;
            }

            // When we run out of elements in either L or M,
            // pick up the remaining elements and put in A[p..r]
            while (i < n1) {
                input_vector[k] = L[i];
                i++;
                k++;
            }

            while (j < n2) {
                input_vector[k] = M[j];
                j++;
                k++;
            }
            
            return input_vector;
        }

        // Divide the array into two subarrays, sort them and merge them
        vector<int> mergesort_main(vector<int> input_vector, int l, int r) {
            if (l < r) {
                // m is the point where the array is divided into two subarrays
                int m = l + (r - l) / 2;

                input_vector = mergesort_main(input_vector, l, m);
                input_vector = mergesort_main(input_vector, m + 1, r);

                // Merge the sorted subarrays
                input_vector = merge(input_vector, l, m, r);
            }

            return input_vector;
        }

};

int main()
{
    string input;
    vector<int> numbers;

    cout << "Zadejte cisla ktere chcete seradit (oddelujte mezerou): ";
    getline(cin, input);
    
    // input to vector
    for (int i = 0; i < input.length(); i++)
    {
        if (!isspace(input[i]))
        {
            numbers.push_back(int(input[i]) - '0');
        }
    }

    // sort input?
    string sort_input;
    cout << "Jaky sort chcete pouzit?" << endl;
    cout << "(insertion_sort, bogo_sort, selection_sort): ";
    getline(cin, sort_input);

    // apply sort
    vector<int> numbers_sorted;

    //timestamp checking
    auto start = high_resolution_clock::now();

    if (sort_input == "insertion_sort")
    {
        InsertionSort insertion_sort;
        numbers_sorted = insertion_sort.insertion_main(numbers);
    }
    else if (sort_input == "bogo_sort")
    {
        BogoSort bogo_sort;
        numbers_sorted = bogo_sort.bogo_main(numbers);
    }
    else if (sort_input == "selection_sort")
    {
        SelectionSort selection_sort;
        numbers_sorted = selection_sort.selection_main(numbers);
    }
    else if (sort_input == "merge_sort")
    {
        MergeSort merge_sort;
        numbers_sorted = merge_sort.mergesort_main(numbers, 0, numbers.size());
    }
    else{
        cout << "Nechcete sortovat? ok" << endl;
        return 0;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    //output the res array
    string out_string;
    for (int i = 0; i < input.length(); i++)
    {
        out_string.insert(i, to_string(numbers_sorted[i]));
    }
    //get rid of extra characters
    cout << "OUT: " << endl;
    cout << out_string.substr(0, numbers_sorted.size()) << endl;
    cout << "Elapsed Time: " << duration.count() << " microseconds" << endl;

    return 0;
}