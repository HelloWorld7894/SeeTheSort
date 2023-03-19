#include <iostream>
#include <vector>

using namespace std;

void PrintSortProcess(vector<int> input_vector)
{
       
}

vector<int> InsertionSort(vector<int> input_vector)
{   
    //we are going to sort in ascending order
    for (int i = 0; i < input_vector.size(); i++)
    {
        if (i != input_vector.size() - 1){
            int elem1 = input_vector[i];
            int elem2 = input_vector[i + 1];

            if (elem1 > elem2 )
            {
                input_vector[i] = elem2;
                input_vector[i + 1] = elem1;
            }
        }

    }

    return input_vector;
}

vector<int> BogoSort(vector<int> input_vector)
{
    return input_vector;
}

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
        numbers_sorted = BogoSort(numbers);
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