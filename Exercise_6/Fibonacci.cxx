// g++ Fibonacci.cxx -o Fibonacci -std=c++17 -O2 -g -ltbb

#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#include <tbb/global_control.h>
#include <tbb/parallel_scan.h>

// You don't need to change any code in these two helpers.
// They benchmark an algorithm and print a few items of the output sequence:
template<typename Container, typename Callable>
void benchmark(std::string jobName, Container const & input, Container & output, Callable callable) {
  using namespace std::chrono_literals;
  std::cout << "---------------------------------\n";
  const auto start = std::chrono::steady_clock::now();

  for (unsigned int run = 0; run < 50; ++run) {
    callable(input, output);
  }

  const auto stop = std::chrono::steady_clock::now();
  std::cout << jobName << ": " << (stop-start) / 1ms << " ms.\n";
}

template<typename Container>
void print(Container & output) {
  for (unsigned int i = 0; i < std::min(5ul,output.size()); ++i) {
    std::cout << output[i] << "\n";
  }
  std::cout << "...\n";

  for (unsigned int i = output.size()-3; i >= 5 && i < output.size(); ++i) {
    std::cout << output[i] << "\n";
  }
}


/**
 *  This class can be used to compute Fibonacci numbers using a scan algorithm.
 *  A parallel scan needs to know the previous element of the sequence, but for Fibonacci
 *  numbers we need the two previous elements.
 *
 *  The power of the below class is to move *two* Fibonacci numbers from the previous to the
 *  next step, so a single instance of this class suffices to compute the next element of the Fibonacci
 *  sequence. This is done by applying a 2x2 matrix to two consecutive Fibonacci numbers:
 *  [F_n+1] = [ ? ? ] * [F_n  ]
 *  [F_n  ]   [ ? ? ]   [F_n-1]
 *
 *  The subsequent element can be reached by applying the matrix twice:
 *  [F_n+2] = [ ? ? ]*[ ? ? ] * [F_n  ]
 *  [F_n+1]   [ ? ? ] [ ? ? ]   [F_n-1]
 *
 *  In a parallel scan, we can therefore use matrix multiplications, which are associative but not
 *  commutative, so all prerequisites are fulfilled.
 */
class FiboMatrix {
    using Int_t = uint64_t;
    // Task 3: Fill in the matrix that computes the two next Fibonacci numbers:
    Int_t matrix[2][2] = {{1,1},
                          {1,0}};

  public:
    FiboMatrix() = default;
    FiboMatrix(Int_t a, Int_t b, Int_t c, Int_t d) : matrix{{a, b}, {c, d}} {  }
    FiboMatrix(Int_t m[2][2]) : matrix{{m[0][0], m[0][1]}, {m[1][0], m[1][1]}} {  }

    friend std::ostream & operator<<(std::ostream & stream, FiboMatrix const & m) {
        stream << "[[" << m.matrix[0][0] << " " << m.matrix[0][1] << "]\n"
               << " [" << m.matrix[1][0] << " " << m.matrix[1][1] << "]]\n";
        return stream;
    }

    /// A matrix multiplication function for two instances of FiboMatrix
    friend FiboMatrix operator*(FiboMatrix const & lhs, FiboMatrix const & rhs) {
        const auto & a = lhs.matrix;
        const auto & b = rhs.matrix;

        Int_t result[2][2];
        result[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0];
        result[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1];
        result[1][0] = a[1][0]*b[0][0] + a[1][1]*b[1][0];
        result[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1];

        return FiboMatrix{result};
    }
};



int main(int argc, char* argv[]) {
    // Read number of elements to compute and number of threads for TBB if provided:
    std::size_t N = argc > 1 ? std::atol(argv[1]) : 100000;
    unsigned int nThread = argc > 2 ? std::atoi(argv[2]) : 8;
    tbb::global_control gc(tbb::global_control::max_allowed_parallelism, nThread);


    std::vector<unsigned long long> fibo;
    fibo.reserve(N);


    // Task 4: Implement the iterative Fibonacci computation below and compare to the matrix
    // algorithm.
    benchmark("Iterative algorithm", fibo, fibo, [N](const auto & input, auto & output){
      output.clear();
      // We need to seed the sequence:
      output.push_back(0);
      output.push_back(1);

      // Task 4.(a): Implement the iterative algorithm.
      // Notice how you need to access the *two* previous elements, so
      // this algorithm cannot work with a parallel scan.
      while (output.size() < N) {
        const auto size = output.size();
        output.push_back(output[size-1] + output[size-2]);
      }
    });
    // print(fibo);

    // Task 4.(b): Test the matrix algorithm.
    // Let's repeatedly apply the matrix, and print a few steps.
    // If you solved the previous tasks correctly, each corner of the matrices should
    // show a Fibonacci sequence, but they start at different numbers:
    //
    // [[2 1]
    //  [1 1]]
    //
    // [[3 2]
    //  [2 1]]
    //
    // [[5 3]
    //  [3 2]]
    //  ...
    // FiboMatrix fm;
    // std::cout << "-------------------------------------\nThe Fibonacci matrices:\n";
    // std::cout << fm;
    // std::cout << fm * fm;
    // ...


    std::vector<FiboMatrix> fiboInputs(N);
    std::vector<FiboMatrix> fiboResults(N);

    // Task 5: Look up how to use C++ "inclusive_scan" or "exclusive_scan" to raise the Fibonacci matrices
    // to the correct power.
    // We are reading the matrices from "fiboInputs", and write the results to "fiboResults".
    // https://en.cppreference.com/w/cpp/algorithm/inclusive_scan
    // https://en.cppreference.com/w/cpp/algorithm/exclusive_scan
    //
    // Hints:
    // - By default, C++ will use 'operator+' to compute the successor, but you can pass "std::multiplies<>{}"
    //   for "BinaryOp" to make it use 'operator*'.
    // - If you decide to use the exclusive_scan, you need to pass an identity element. This can be
    // FiboMatrix{1,0,0,1}.
    //
    // - What is the difference between inclusive and exclusive scan?
    // - Why is this algorithm slower than the trivial sequence from task 1?

    benchmark("Sequential matrix algorithm inclusive", fiboInputs, fiboResults, [](auto const & input, auto & output){
        // Inclusive scan is slower than the non-matrix implementation, since we do more opertaions.
        std::inclusive_scan(input.begin(), input.end(), output.begin(), std::multiplies<FiboMatrix>{});
    });
    // print(fiboResults);

    benchmark("Sequential matrix algorithm exclusive", fiboInputs, fiboResults, [](auto const & input, auto & output){
        // The difference with the exclusive scan is the inclusion of the input or not.
        std::exclusive_scan(input.begin(), input.end(), output.begin(), FiboMatrix{1,0,0,1}, std::multiplies<FiboMatrix>{});
    });
    // print(fiboResults);

    // Task 6: C++ can parallelise many standard algorithms when an additional execution parameter is passed.
    // Try invoking the scan algorithm from above, but pass "std::execution::par_unseq" as first argument.
    // How large is the speedup compared to the sequential algorithm?

    benchmark("Parallel matrix algorithm (C++) inclusive", fiboInputs, fiboResults, [&](auto const & input, auto & output){
        std::inclusive_scan(std::execution::par_unseq, input.begin(), input.end(), output.begin(),  std::multiplies<FiboMatrix>{});
    });

    benchmark("Parallel matrix algorithm (C++) exclusive", fiboInputs, fiboResults, [&](auto const & input, auto & output){
        std::exclusive_scan(std::execution::par_unseq, input.begin(), input.end(), output.begin(), FiboMatrix{1,0,0,1},  std::multiplies<FiboMatrix>{});
    });
    // print(fiboResults);

    // Task 7: Let's repeat the parallelisation of scan using TBB. With TBB, you get full control over partitioning,
    // input, output, and the number of threads. In fact, the parallel C++ execution above might be implemented
    // using TBB (this is the choice of the compiler vendors).
    //
    // To run the problem "manually" using TBB, we need to pass:
    // - A partitioning strategy (blocked range)
    // - An identity element
    // - A lambda to compute partial sequences over a chunk of the data space,
    // - A reduction function to combine the partial results
    // In the last two cases, this boils down to using operator* in the right place.
    //
    // The number of threads that TBB uses can be configured at startup, see "nThread" at the beginning of the main()
    // function. You can pass the number of Fibonacci numbers to compute and the number of threads to use as arguments
    // to the program:
    //   ./Fibonacci <nFibonacci> <nThread>
    //
    // Run the parallel Fibonacci computation with 1 or 10 million elements and {1, 2, 4, 8, ...} threads, and see
    // how the speedup scales with the number of threads.
    // What scaling behaviour would you expect for a scan-like problem? What is the theoretical speedup with
    // an unlimited number of cores?
/*
    benchmark("Parallel matrix algorithm (TBB, " + std::to_string(nThread) + " threads)", fiboInputs, fiboResults, [&](auto const & input, auto & output){
        tbb::parallel_scan(tbb::blocked_range<unsigned int>(0, N),
                           FiboMatrix{1, 0, 0, 1},
                           [&](const tbb::blocked_range<unsigned int>& r, FiboMatrix const & partialResult, bool is_final_scan) -> FiboMatrix {
                             auto temp = partialResult;
                             // Run through a block of input data, computing a partial sequence.
                             // TBB manages the partitioning for us:
                             for (auto i=r.begin(); i<r.end(); ++i) {
                               temp = temp * input[i];
                               // In the last iteration, we write the results into the output vector:
                               if( is_final_scan ) output[i] = temp;
                             }
                             return temp;
                           },
                           [](auto const & left, auto const & right) { return left * right; });
    });
    print(fiboResults);
*/
    return 0;
}

