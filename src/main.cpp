#include <hpx/hpx_init.hpp>
#include <hpx/hpx_main.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/util/lightweight_test.hpp>
#include <hpx/include/parallel_for_loop.hpp>
#include <hpx/include/parallel_executor_parameters.hpp>

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

    int n =500;
    std::vector<double> x(n,1);
    std::vector<double> y(n,1);
    double a=3.0;

    for_loop(par, 0, n,
             [&](int i)
             {
                 y[i] += a * x[i];
             });

return 0;
}