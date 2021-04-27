#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <iomanip>

using namespace std;

int is_prime(int N) {
    if (N == 0 or N == 1)
        return 0;
    for (int i=2; i*i <= N; i++) {
        if (N % i == 0)
        return 0;
    }
    return 1;
}

void resheto_dlya_prostyh(int * mas, int size) {
    mas[0]=0;
    mas[1]=0;
    for (int i=2; i<size; i++)
        mas[i]=1;
    for (int i=2; i<size; i++) {
        if (mas[i] == 1) {
            for (int j=2*i; j<size; j+=i) {
                mas[j]=0;
            }
        }
    }
}
void resheto_dlya_deliteley(int * mas, int size) {
    for (int i=0; i<size; i++)
        mas[i]=0;
    for (int i=1; i<size; i++) {
        for (int j = i; j<size; j+=i) {
            mas[j]++;
        }
    }
}
int div_count_sqrt(int N) {
    int ans = 0;
    for (int i=2; i*i <= N; i++) {
        if (i*i == N)
            ans++;
        else {
            if (N % i == 0) {
                ans+=2;
            }
        }
    }
    return ans;
}
/*
double time_measurement(void (func)(int), int N) {
    clock_t time1 = clock();
    func(N);
    return difftime(clock(), time1)/CLOCKS_PER_SEC;
}
void find_all_primes_from_one_to(int N) {
    vector <int> primes;
    for (int i=0; i<N; i++) {
        if (is_prime(i)) {
            primes.push_back(i);
        }
    }
}*/

int main() {
    cout << fixed << setprecision(7);
    clock_t time1, time2;
    double seconds;
    int a, b, min_d;
    /////////////////////////////////////////////////////////////
    time1 = clock();
    vector <int> primes;
    for (int i = 0; i<15000000; i++) {
        if (is_prime(i)) {
            primes.push_back(i);
        }
    }
    a=0, b=0;
    min_d = 15000000;
    for (int i=1; i<primes.size(); i++) {
        if (primes[i-1] > 500000 && primes[i] < 15000000) {
            if (primes[i] - primes[i-1] < min_d) {
                a = primes[i-1];
                b = primes[i];
                min_d = b-a;
            }
        }
    }
    time2 = clock();
    seconds = difftime(time2, time1)/CLOCKS_PER_SEC;
    cout << "Vector" <<endl;
    cout << "Time: " << seconds << endl;
    primes.clear();
    //////////////////////////////////////////////////////////
    time1 = clock();
    int* arr = new int[15000000];
    resheto_dlya_prostyh(arr, 15000000);
    min_d = 15000000;
    int last_prime = 0;
    for (int i=500000; i<15000000; i++) {
        if (arr[i] == 1) {
            if (last_prime == 0) {
                last_prime = i;
            }
            else {
                if (i-last_prime < min_d) {
                    a = last_prime;
                    b = i;
                    min_d = b-a;
                }
                last_prime = i;
            }
        }
    }
    time2 = clock();
    seconds = difftime(time2, time1)/CLOCKS_PER_SEC;
    cout << "Resheto" << endl;
    cout << "Time: " << seconds <<endl;
    delete[] arr;
    /////////////////////////////////////////////////////////////
    time1 = clock();
    vector <int> p;
    int* arr2 = new int[15000000];
    resheto_dlya_prostyh(arr2, 15000000);
    for (int i=0; i<15000000; i++) {
        if (arr2[i]==1)
            p.push_back(i);
    }
    //delete[] arr2;
    min_d = 15000000;
    for (int i=1; i<primes.size(); i++) {
        if (p[i-1] > 500000 && p[i] < 15000000) {
            if (p[i] - p[i-1] < min_d) {
                a = p[i-1];
                b = p[i];
                min_d = b-a;
            }
        }
    }
    time2 = clock();
    seconds = difftime(time2, time1)/CLOCKS_PER_SEC;
    cout << "Combined"<<endl;
    cout << "Time: " << seconds <<endl;
    p.clear();
    int lol;
    cin >> lol;
    /*
    Результат - решето Эратосфена требует много памяти, но заполняется очень быстро. Если почему-то
    ЖИЗНЕННО необходимо сократить затраты на память, можно перегнать данные из массива в вектор с простыми,
    иначе это, скорее всего, неоправдано. Заполнять вектор с самого начала с помощью функции, которая
    определяет, является ли число простым, стоит только в том случае, если память важнее времени, т.к.
    выполняться это будет ОЧЕНЬ долго. Сложнось будет O(n^(3/2)). В случае с решетом сложность - O(n*log(n)).
    */
    return 0;
}
