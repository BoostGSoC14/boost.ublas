/*
  symm2
*/

namespace boost {
    
double symm2(size_t N, size_t iterations = 1){
    
    boost::numeric::ublas::matrix<value_type, boost::numeric::ublas::row_major> A(N, N), B(N, N), C(N, N);
    value_type c = 3;
    
    minit(A.size1(), A);
    minit(B.size1(), B);
    minit(C.size1(), C);
    
    std::vector<double> times;
    for(size_t i = 0; i < iterations; ++i){
        
        auto start = std::chrono::steady_clock::now();
        C = c * prod(trans(A), B) + c * C;
        auto end = std::chrono::steady_clock::now();
        
        auto diff = end - start;
        times.push_back(std::chrono::duration<double, std::milli> (diff).count()); //save time in ms for each iteration
    }

    double tmin = *(std::min_element(times.begin(), times.end()));
    double tavg = average_time(times);
    
    // check to see if nothing happened during run to invalidate the times
    if(variance(tavg, times) > max_variance){
        std::cerr << "boost kernel 'symm2': Time deviation too large! \n";
    }
    
    return tavg;
}

}