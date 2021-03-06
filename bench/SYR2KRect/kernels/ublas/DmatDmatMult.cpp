/*
 dense matrix and dense matrix multiplication kernel
*/

namespace boost {
    
double dmatdmatmult(size_t N, size_t iterations = 1) {
    
    boost::numeric::ublas::matrix<value_type> a(N, N), b(N, N), c(N, N);
    
    minit(a.size1(), a);
    minit(b.size1(), b);
    
    std::vector<double> times;
    for(size_t i = 0; i < iterations; ++i){
        
        auto start = std::chrono::steady_clock::now();
        noalias(c) = prod(a, b);
        auto end = std::chrono::steady_clock::now();
        
        auto diff = end - start;
        times.push_back(std::chrono::duration<double, std::milli> (diff).count()); //save time in ms for each iteration
    }
    
    double tmin = *(std::min_element(times.begin(), times.end()));
    double tavg = average_time(times);
 
    // check to see if nothing happened during run to invalidate the times
    if(variance(tavg, times) > max_variance){
        std::cerr << "boost kernel 'dmatdmatmult': Time deviation too large! \n";
    }
    
    return tavg;
    
}

}