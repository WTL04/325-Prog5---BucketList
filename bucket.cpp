#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//global var
int globalSwapCount = 0;

#include <vector>
#include <cstdlib> // for rand

class Bucket {
private:
    std::vector<int> v;

public:
    // Constructor
    Bucket() {}

    // Generate 'size' random numbers between 'min' and 'max'
    void generate(int size, int min, int max) {
        for (int i = 0; i < size; i++) {
            int randInt = min + rand() % (max - min + 1); // Get num in range (min to max)
            v.push_back(randInt); // Push the random number into the vector
        }
    }

    // Sort the vector using bubble sort
    void sort() {
        for (int i = 0; i < v.size(); i++) {
            for (int j = i + 1; j < v.size(); j++) {
                if (v[j] < v[i]) {
                    int temp = v[i];
                    v[i] = v[j];
                    v[j] = temp;

                    globalSwapCount++;
                }
            }
        }
    }

    // Return the size of the vector
    int size() {
        return v.size();
    }

    // Return the element at index 'a'
    int atIndex(int index) {
        return v[index];
    }

    // Merge another Bucket 'b' into this Bucket
    void merge(Bucket & b) 
    {
        vector<int> mergedVector;

        int i = 0, j = 0;

        while (i < v.size() && j < b.size()) {
            if (v[i] <= b.atIndex(j)) {
                mergedVector.push_back(v[i++]);
            } else {
                mergedVector.push_back(b.atIndex(j++));
            }
        }

        while (i < v.size()) {
            mergedVector.push_back(v[i++]);
        }

        while (j < b.size()) {
            mergedVector.push_back(b.atIndex(j++));
        }

        v = mergedVector;
    }
};



int main(int argc, char *argv[])
{
    srand(time(0));

    int bucketCount = stoi(argv[1]);
    int bucketSize = stoi(argv[2]);
    int bucketMin = stoi(argv[3]);
    int bucketMax = stoi(argv[4]);

    cout << "Bucket Count:"<<bucketCount<<endl;
    cout << "Bucket Size:"<<bucketSize<<endl;
    cout << "Bucket Min Value:"<<bucketMin<<endl;
    cout << "Bucket Max value:"<<bucketMax<<endl;

    vector<Bucket> list; // create empty Bucket vector
    Bucket *bptr;

    for(int i=0; i<bucketCount; i++) // creating bucketCount Buckets
    {
        bptr = new Bucket; // allocating new Bucket
        bptr-> generate(bucketSize, bucketMin, bucketMax); //Bucket::generate(int,int,int,int)
        list.push_back(*bptr); // pushing Bucket onto list
    }

    for (auto it = list.begin(); it != list.end(); it++)
    {
        it-> sort(); // Bucket::sort
    }

    Bucket endGame; // create empty Bucket to merge ALL buckets

    while (list.size() > 0) // vector<Bucket>::size()
    {
        endGame.merge(list[0]); // merge first bucket in list into endGame
        list.erase(list.begin()); // erase the first bucket in the list
    }

    // write all the numbers in endGame bucket to a file
    fstream out("bucketList.out", ios::out);

    for(int i=0; i<endGame.size(); i++) // Bucket::size()
    {
        out << endGame.atIndex(i) << endl; // Bucket::atIndex(int)  
    }

    cout << "Global Swap Count:"<<globalSwapCount<<endl;
    cout << "\nbucketList.out has "<<bucketCount * bucketSize<< " sorted numbers\n";
    
    return 0;
}