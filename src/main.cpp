#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

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

vector<int> InsertionSort(vector<int> input_vector)
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

int main()
{
    string input;
    vector<int> numbers;

    cout << "Zadejte cisla ktere chcete seradit: (oddelujte mezerou)";
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
    cout << "(insertion_sort, bogo_sort)";
    getline(cin, sort_input);

    // apply sort
    vector<int> numbers_sorted;
    if (sort_input == "insertion_sort")
    {
        numbers_sorted = InsertionSort(numbers);
    }
    else if (sort_input == "bogo_sort")
    {
        BogoSort bogo_sort;
        numbers_sorted = bogo_sort.bogo_main(numbers);
    }
    else{
        cout << "Nechcete sortovat? ok" << endl;
        return 0;
    }

    //output the res array
    string out_string;
    for (int i = 0; i < input.length(); i++)
    {
        out_string.insert(i, to_string(numbers_sorted[i]));
    }
    //get rid of extra characters
    cout << out_string.substr(0, numbers_sorted.size()) << endl;

    return 0;
}