/*
 dot kernel
*/

namespace mtl {
    
double dotproduct(size_t N, size_t iterations = 1){
    
    mtl::dense_vector<value_type> a(N), b(N);
    value_type c = 0;
    
    vinit(N, a);
    vinit(N, b);
    
    std::vector<double> times;
    for(size_t i = 0; i < iterations; ++i){
        
        auto start = std::chrono::steady_clock::now();
        c = dot(a, b);
        auto end = std::chrono::steady_clock::now();
        
        auto diff = end - start;
        times.push_back(std::chrono::duration<double, std::milli> (diff).count()); //save time in ms for each iteration
    }
    
    double tmin = *(std::min_element(times.begin(), times.end()));
    double tavg = average_time(times);
    
    // check to see if nothing happened during run to invalidate the times
    if(variance(tavg, times) > max_variance){
        std::cerr << "mtl kernel 'dotproduct': Time deviation too large! \n";
    }
    
    return tavg;
    
}

}