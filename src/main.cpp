#include <hpx/hpx_init.hpp>
#include <hpx/hpx_main.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/util/lightweight_test.hpp>
#include <hpx/include/parallel_for_loop.hpp>
#include <hpx/include/parallel_executor_parameters.hpp>
#include <numeric>

//void print_array(std::vector<double> M)
//{
//	for (std::size_t i=0;i<M.size();i++) {
//            std::cout << M[i] << "   ";
//	}
//}


int main(int argc, char* argv[])
{
    using hpx::parallel::for_loop;
    using hpx::parallel::execution::par;

    std::size_t n = 10000000UL;
    std::vector<double> x(n,1);
    std::vector<double> y(n,1);
    double a=3.0;

    size_t size=16UL;
    size_t chunk_size=8UL;
    hpx::parallel::execution::dynamic_chunk_size ds(chunk_size);

    std::uint64_t t = hpx::util::high_resolution_clock::now();
    for_loop( par.with(ds), size_t(0), n, [&](int i)
             {
                 y[i] += a * x[i];
             });
    std::uint64_t elapsed = hpx::util::high_resolution_clock::now() - t;
    std::cout<<"size:   "<<n<<"   time(ns): "<<elapsed*1e-9<<std::endl;

    double sum_of_elems = std::accumulate(y.begin(), y.end(), 0);
    HPX_TEST_EQ(sum_of_elems, 4*n);

return 0;
}