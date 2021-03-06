/*
 Dense vector and dense vector multiplication kernel
*/

namespace blaze {
    
double vecvecmult(size_t N, size_t iterations = 1){
    
    blaze::DynamicVector<value_type> a(N), b(N);
    double c = 0;
    
    vinit(a.size(), a);
    vinit(b.size(), b);
    
    std::vector<double> times;
    for(size_t i = 0; i < iterations; ++i){
        
        auto start = std::chrono::steady_clock::now();
        c = (a, b);
        auto end = std::chrono::steady_clock::now();
        
        auto diff = end - start;
        times.push_back(std::chrono::duration<double, std::milli> (diff).count()); //save time in ms for each iteration
    }
    
    double tmin = *(std::min_element(times.begin(), times.end()));
    double tavg = average_time(times);
    
    // check to see if anything happened during run to invalidate the times
    if(variance(tavg, times) > max_variance){
        std::cerr << "blaze kernel 'vecvecmult': Time deviation too large! \n";
    }
    
    return tavg;
    
}

}