/*
 dense matric and vector multiplication kernel
*/

namespace boost {

double dmatvecmult(size_t N, size_t iterations = 1) {
    
    boost::numeric::ublas::matrix<value_type> a(N, N);
    boost::numeric::ublas::vector<value_type> b(N), c(N);
    
    minit(a.size1(), a);
    vinit(b.size(), b);
    
    std::vector<double> times;
    for(size_t i = 0; i < iterations; ++i){
        
        auto start = std::chrono::steady_clock::now();
        //boost::numeric::ublas::axpy_prod(a, b, c, false);
        noalias(c) = prod(a, b);
        auto end = std::chrono::steady_clock::now();
        
        auto diff = end - start;
        times.push_back(std::chrono::duration<double, std::milli> (diff).count()); //save time in ms for each iteration
    }
    
    double tmin = *(std::min_element(times.begin(), times.end()));
    double tavg = average_time(times);
    
    // check to see if nothing happened during run to invalidate the times
    if(variance(tavg, times) > max_variance){
        std::cerr << "boost kernel 'dmatvecmult': Time deviation too large! \n";
    }
    
    return tavg;
    
}

}